#ifndef KG_EVALUATOR_H
#define KG_EVALUATOR_H


#include <string>
#include <vector>
#include <cmath>
#include <limits>
#include "node.hpp"


namespace kg {


template <typename T>
using Matrix = std::vector<std::vector<T>>;


template <typename T>
class Evaluator {
private:
    static auto isValidArgs(const std::vector<kg::Node<T>>& source,
                            const Matrix<kg::Node<T>>& map) -> bool;
    static auto calcDistance(const Node<T>& node1,
                                const Node<T>& node2) -> double;
    static auto findNearestNode(const kg::Node<T>& node,
                                const Matrix<kg::Node<T>>& map) -> kg::Node<T>;

public:
    Evaluator() = delete;
    Evaluator(const Evaluator<T>& rhs) = delete;
    ~Evaluator();
    auto operator=(const Evaluator<T>& rhs) -> Evaluator<T> = delete;

    static auto evaluateMap(const std::vector<kg::Node<T>>& source,
                            const Matrix<kg::Node<T>>& map)
                            throw (std::string) -> double;
};


template <typename T>
Evaluator<T>::~Evaluator()
{
}


template <typename T>
auto Evaluator<T>::isValidArgs(const std::vector<kg::Node<T>>& source,
                                const Matrix<kg::Node<T>>& map) -> bool
{
    if ( source[0].size() != map[0][0].size() ) {
        return false;
    }

    for ( auto node : source ) {
        if ( node.size() != source[0].size() ) {
            return false;
        }
    }

    for ( const auto& row : map ) {
        if ( row.size() != map[0].size() ) {
            return false;
        }
        for ( const auto& node : row ) {
            if ( node.size() != map[0][0].size() ) {
                return false;
            }
        }
    }

    return true;
}


template <typename T>
auto Evaluator<T>::calcDistance(const Node<T>& node1,
                                const Node<T>& node2) -> double
{
    const auto dimension = node1.size();
    auto dis = 0.0;
    #ifdef _OPENMP
    #pragma omp parallel for schedule(static) reduction(+:dis)
    #endif
    for ( int i = 0; i < dimension; i++ ) {
        dis += pow(node1[i] - node2[i], 2.0);
    }

    return sqrt(dis);
}

template <typename T>
auto Evaluator<T>::findNearestNode(const kg::Node<T>& node,
                                    const Matrix<kg::Node<T>>& map) -> kg::Node<T>
{
    const auto rows = map.size();
    const auto cols = map[0].size();
    auto minDis = std::numeric_limits<double>::max();
    auto minDisRow = 0, minDisCol = 0;
    #ifdef _OPENMP
    #pragma omp parallel for schedule(static)
    #endif
    for ( auto r = 0; r < rows; r++ ) {
        #ifdef _OPENMP
        #pragma omp parallel for schedule(static)
        #endif
        for ( auto c = 0; c < cols; c++ ) {
            auto dis = calcDistance(node, map[r][c]);
            #ifdef _OPENMP
            #pragma omp critical (updateDistance)
            #endif
            {
                if ( dis < minDis ) {
                    minDis      = dis;
                    minDisRow   = r;
                    minDisCol   = c;
                }
            }
        }
    }

    return map[minDisRow][minDisCol];
}


template <typename T>
auto Evaluator<T>::evaluateMap(const std::vector<kg::Node<T>>& source,
                                const Matrix<kg::Node<T>>& map)
                                throw (std::string) -> double
{
    if ( !isValidArgs(source, map) ) {
        throw std::string("invalid arguments");
    }

    auto evaluationValue = 0.0;
    for ( const auto& node : source ) {
        const auto nearestNode  = findNearestNode(node, map);
        const auto dis          = calcDistance(node, nearestNode);

        evaluationValue += dis;
    }

    return evaluationValue;
}


}


#endif

