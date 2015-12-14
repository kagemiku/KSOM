#pragma once

#include <string>
#include <vector>
#include "Node.h."


namespace kg {



template <typename T>
class Evaluater {
private:
    std::vector<std::vector<Node<T>>> map_;

private: 
    auto calcDistance(const Node<T>& node1, const Node<T>& node2) const -> double;
    auto calcDistanceRightNode(unsigned int r, unsigned int c) const throw (std::string) -> double;
    auto calcDistanceBelowNode(unsigned int r, unsigned int c) const throw (std::string) -> double;

public:
    Evaluater(const std::vector<std::vector<Node<T>>>& map);
    Evaluater(const Evaluater<T>& rhs) = delete;
    ~Evaluater();
    auto operator=(const Evaluater<T>& rhs) -> Evaluater<T> = delete;

    auto evaluateMap() const -> double;
};


template <typename T>
Evaluater<T>::Evaluater(const std::vector<std::vector<Node<T>>>& map)
    :map_(map)
{
}


template <typename T>
Evaluater<T>::~Evaluater()
{
}


template <typename T>
auto Evaluater<T>::calcDistance(const Node<T>& node1, const Node<T>& node2) const -> double
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
auto Evaluater<T>::calcDistanceRightNode(unsigned int r, unsigned int c) const throw (std::string) -> double
{
    if ( r >= map_.size() || c >= map_[0].size() - 1 ) {
        throw std::string("out of range.");
    }

    auto& refNode1 = map_[r][c];
    auto& refNode2 = map_[r][c + 1];
    
    return calcDistance(refNode1, refNode2);
}


template <typename T>
auto Evaluater<T>::calcDistanceBelowNode(unsigned int r, unsigned int c) const throw (std::string) -> double
{ 
    if ( r >= map_.size() - 1 || c >= map_[0].size() ) {
        throw std::string("out of range.");
    }

    auto& refNode1 = map_[r][c];
    auto& refNode2 = map_[r + 1][c];
    
    return calcDistance(refNode1, refNode2);
}


template <typename T>
auto Evaluater<T>::evaluateMap() const -> double
{
    const auto rows = map_.size();
    const auto cols = map_[0].size();
    const auto dimension = map_[0][0].size();

    auto evaluateValue = 0.0;
    for ( auto r = 0; r < rows; r++ ) {
        for ( auto c = 0; c < cols - 1; c++ ) {
            evaluateValue += calcDistanceRightNode(r, c);

            if ( r != rows - 1 ) {
                evaluateValue += calcDistanceBelowNode(r, c);
            }
        }
    }

    return evaluateValue;
}


}
