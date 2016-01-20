#ifndef KG_KSOM_H
#define KG_KSOM_H


#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <tuple>
#include <limits>
#include <cmath>
#include "node.hpp"


namespace kg {


namespace {
    constexpr auto MAX_DISTANCE = std::numeric_limits<double>::max();
};


template <typename T>
class KSOM {
private:
    using Position = std::tuple<int, int>;

    const std::vector<Node<T>> src_;
    const int length_;
    const int dimension_;

    std::vector<std::vector<Node<T>>> map_;
    const int rows_;
    const int cols_;

    const double alpha0_;
    const double sigma0_;
    const int maxIterate_;
    int time_;

    const bool randomIndex_;
    std::mt19937 mt_;
    std::uniform_int_distribution<> randIdx_;

private:
    inline auto calcAlpha(int time) const -> double;
    inline auto calcSigma(int time) const -> double;
    inline auto calcH(double distance, int time) const -> double;
    inline auto calcDistance(const Position& pt1, const Position& pt2) const -> double;
    inline auto calcDistance(const Node<T>& node1,
            const Node<T>& node2) const -> double;
    inline auto nextIndex() -> unsigned int;
    inline auto findNearestNode(int idx) const -> Position;
    inline auto learnNode(int idx, const Position& nearestPoint) -> void;

public:
    KSOM(const std::vector<Node<T>>& src, const std::vector<std::vector<Node<T>>>& map,
            int maxIterate, double alpha0, double sigma0,
            bool randomly=true) throw (std::string);
    ~KSOM();

    auto computeOnes() -> bool;
    auto compute() -> void;
    auto time() const -> int;
    auto map() const -> std::vector<std::vector<Node<T>>>;
};


template <typename T>
KSOM<T>::KSOM(const std::vector<Node<T>>& src,
        const std::vector<std::vector<Node<T>>>& map,
        int maxIterate, double alpha0, double sigma0, bool randomly) throw (std::string)
    :randomIndex_(randomly)
    ,src_(src)
    ,length_(src_.size())
    ,dimension_(src[0].size())
    ,map_(map)
    ,rows_(map_.size())
    ,cols_(map_[0].size())
    ,alpha0_(alpha0)
    ,sigma0_(sigma0)
    ,maxIterate_(maxIterate)
    ,time_(0)
{
    for ( auto node : src_ ) {
        if ( node.size() != dimension_ ) {
            throw std::string("dimension of source node is different.");
        }
    }
    for ( auto row : map_ ) {
        if ( row.size() != cols_ ) {
            throw std::string("number of columns in map is different.");
        }
        for ( auto node : row ) {
            if ( node.size() != dimension_ ) {
                throw std::string("dimension of map node is different.");
            }
        }
    }

    std::random_device rnd;
    mt_         = std::mt19937(rnd());
    randIdx_    = std::uniform_int_distribution<>(0, length_ - 1);
}


template <typename T>
KSOM<T>::~KSOM()
{
}


template <typename T>
auto KSOM<T>::calcAlpha(int time) const -> double
{
    return alpha0_*exp(-static_cast<double>(time)/static_cast<double>(maxIterate_));
}


template <typename T>
auto KSOM<T>::calcSigma(int time) const -> double
{
    return sigma0_*exp(-static_cast<double>(time)/static_cast<double>(maxIterate_));
}


template <typename T>
auto KSOM<T>::calcH(double distance, int time) const -> double
{
    return exp(-pow(distance, 2.0)/(2*pow(calcSigma(time), 2.0)));
}


template <typename T>
auto KSOM<T>::calcDistance(const Position& pt1, const Position& pt2) const -> double
{
    const auto x1 = std::get<0>(pt1), y1 = std::get<1>(pt1);
    const auto x2 = std::get<0>(pt2), y2 = std::get<1>(pt2);

    return sqrt(pow(x1 - x2, 2.0) + pow(y1 - y2, 2.0));
}


template <typename T>
auto KSOM<T>::nextIndex() -> unsigned int
{
    auto index = 0U;
    if ( randomIndex_ ) {
        index = randIdx_(mt_);
    } else {
        index = time_ % src_.size();
    }

    return index;
}


template <typename T>
auto KSOM<T>::calcDistance(const Node<T>& node1, const Node<T>& node2) const -> double
{
    auto dis = 0.0;
    #ifdef _OPENMP
    #pragma omp parallel for schedule(static) reduction(+:dis)
    #endif
    for ( int i = 0; i < dimension_; i++ ) {
        dis += pow(node1[i] - node2[i], 2.0);
    }

    return sqrt(dis);
}


template <typename T>
auto KSOM<T>::findNearestNode(int idx) const -> Position
{
    const auto& refNode = src_[idx];
    auto minDis = MAX_DISTANCE;
    auto minDisRow = 0, minDisCol = 0;
    #ifdef _OPENMP
    #pragma omp parallel for schedule(static)
    #endif
    for ( auto r = 0; r < rows_; r++ ) {
        #ifdef _OPENMP
        #pragma omp parallel for schedule(static)
        #endif
        for ( auto c = 0; c < cols_; c++ ) {
            auto dis = calcDistance(refNode, map_[r][c]);
            #ifdef _OPENMP
            #pragma omp critical (updateDistance)
            #endif
            {
                if ( dis < minDis ) {
                    minDis = dis;
                    minDisRow = r;
                    minDisCol = c;
                }
            }
        }
    }

    return std::make_tuple(minDisRow, minDisCol);
}


template <typename T>
auto KSOM<T>::learnNode(int idx, const Position& nearestPoint) -> void
{
    const auto& refNode = src_[idx];
    const auto alpha = calcAlpha(time_);
    #ifdef _OPENMP
    #pragma omp parallel for schedule(static)
    #endif
    for ( auto r = 0; r < rows_; r++ ) {
        #ifdef _OPENMP
        #pragma omp parallel for schedule(static)
        #endif
        for ( auto c = 0; c < cols_; c++ ) {
            auto currentPoint   = std::make_tuple(r, c);
            const auto dis      = calcDistance(currentPoint, nearestPoint);
            const auto h        = calcH(dis, time_);

            #ifdef _OPENMP
            #pragma omp parallel for schedule(static)
            #endif
            for ( auto i = 0; i < dimension_; i++ ) {
                map_[r][c][i] += static_cast<T>(h*alpha*(refNode[i] - map_[r][c][i]));
            }
        }
    }
}

template <typename T>
auto KSOM<T>::computeOnes() -> bool
{
    if ( time_ >= maxIterate_ ) {
        return false;
    }

    const auto idx          = nextIndex();
    const auto nearestPoint = findNearestNode(idx);
    learnNode(idx, nearestPoint);
    ++time_;

    return true;
}


template <typename T>
auto KSOM<T>::compute() -> void
{
    while ( computeOnes() ) {
        ;
    }
}

template <typename T>
auto KSOM<T>::time() const -> int
{
    return time_;
}


template <typename T>
auto KSOM<T>::map() const -> std::vector<std::vector<Node<T>>>
{
    return map_;
}


}


#endif

