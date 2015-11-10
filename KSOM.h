#pragma once

#include <iostream>
#include <limits>
#include <cmath>
#include "Node.h"


namespace {
	const auto MAX_DISTANCE = std::numeric_limits<double>::max();
};


template <typename T>
class KSOM {
private:
	const Node<T>* src_;
	const int length_;
	const int dimension_;

	Node<T>** map_;
	const int rows_;
	const int cols_;

	const double alpha0_;
	const double sigma0_; 
	const int maxIterate_;
	int time_;
	
private:
	inline auto calcAlpha(int time) -> double;
	inline auto calcSigma(int time) -> double;
	inline auto calcH(double distance, int time) -> double;
	inline auto calcDistance(int x1, int y1, int x2, int y2) -> double;
	inline auto calcDistance(const Node<T>& node1, const Node<T>& node2) -> double; 
	inline auto findNearestNode(int idx, int& nearestRow, int& nearestCol) -> void;
	inline auto learnNode(int idx, int nearestRow, int nearestCol) -> void;
 
public:
	KSOM(Node<T>* const src, int length, Node<T>** map, int rows, int cols, int maxIterate, double alpha0, double sigma0);
	~KSOM();

	auto computeOnes() -> bool;
	auto compute() -> void;
	auto time() const -> int; 
};


template <typename T>
KSOM<T>::KSOM(Node<T>* const src, int length, Node<T>** map, int rows, int cols, int maxIterate, double alpha0, double sigma0)
	:src_(src)
	,length_(length)
	,dimension_(src[0].size())
	,map_(map)
	,rows_(rows)
	,cols_(cols)
	,alpha0_(alpha0)
	,sigma0_(sigma0)
	,maxIterate_(maxIterate)
	,time_(0)
{
}


template <typename T>
KSOM<T>::~KSOM()
{
}

 
template <typename T>
auto KSOM<T>::calcAlpha(int time) -> double
{
	return alpha0_ * exp(-static_cast<double>(time)/static_cast<double>(maxIterate_));
}


template <typename T>
auto KSOM<T>::calcSigma(int time) -> double
{
	return sigma0_ * exp(-static_cast<double>(time)/static_cast<double>(maxIterate_));
}


template <typename T>
auto KSOM<T>::calcH(double distance, int time) -> double
{
	return exp(-pow(distance, 2.0)/(2*pow(calcSigma(time), 2.0)));
}


template <typename T>
auto KSOM<T>::calcDistance(int x1, int y1, int x2, int y2) -> double
{
	return sqrt(pow(x1 - x2, 2.0) + pow(y1 - y2, 2.0));
}


template <typename T>
auto KSOM<T>::calcDistance(const Node<T>& node1, const Node<T>& node2) -> double
{
	auto dis = 0.0;
	for ( int i = 0; i < dimension_; i++ ) {
		dis += pow(node1[i] - node2[i], 2.0);
	}

	return sqrt(dis);
}


template <typename T>
auto KSOM<T>::findNearestNode(int idx, int& nearestRow, int& nearestCol) -> void
{
	const Node<T>& refNode = src_[idx];
	auto minDis = MAX_DISTANCE;
	auto minDisRow = 0, minDisCol = 0;
	for ( auto r = 0; r < rows_; r++ ) {
		for ( auto c = 0; c < cols_; c++ ) {
			auto dis = calcDistance(refNode, map_[r][c]);
			if ( dis < minDis ) {
				minDis = dis;
				minDisRow = r;
				minDisCol = c;
			}
		}
	}

	nearestRow = minDisRow;
	nearestCol = minDisCol;
}


template <typename T>
auto KSOM<T>::learnNode(int idx, int nearestRow, int nearestCol) -> void
{
	const Node<T>& refNode = src_[idx];
	const auto alpha = calcAlpha(time_);
	for ( auto r = 0; r < rows_; r++ ) {
		for ( auto c = 0; c < cols_; c++ ) {
			const auto dis = calcDistance(r, c, nearestRow, nearestCol);
			const auto h = calcH(dis, time_);

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
 
	auto nearestRow = 0, nearestCol = 0;
	findNearestNode(time_, nearestRow, nearestCol); 
	learnNode(time_, nearestRow, nearestCol);
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
