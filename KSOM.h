#pragma once

#include <iostream>
#include <limits>
#include <cmath>
#include "Node.h"


namespace {
	const double MAX_DISTANCE = std::numeric_limits<double>::max();
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
	inline double calcAlpha(int time);
	inline double calcSigma(int time);
	inline double calcH(double distance, int time);
	inline double calcDistance(int x1, int y1, int x2, int y2);
	inline double calcDistance(const Node<T>& node1, const Node<T>& node2); 
 
public:
	KSOM(Node<T>* const src, int length, Node<T>** map, int rows, int cols, int maxIterate, double alpha0, double sigma0);
	~KSOM();

	bool computeOnes();
	void compute();
	int time() const; 
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
double KSOM<T>::calcAlpha(int time)
{
	return alpha0_ * exp(-static_cast<double>(time)/static_cast<double>(maxIterate_));
}


template <typename T>
double KSOM<T>::calcSigma(int time)
{
	return sigma0_ * exp(-static_cast<double>(time)/static_cast<double>(maxIterate_));
}


template <typename T>
double KSOM<T>::calcH(double distance, int time)
{
	return exp(-pow(distance, 2.0)/(2*pow(calcSigma(time), 2.0)));
}


template <typename T>
double KSOM<T>::calcDistance(int x1, int y1, int x2, int y2)
{
	return sqrt(pow(x1 - x2, 2.0) + pow(y1 - y2, 2.0));
}


template <typename T>
double KSOM<T>::calcDistance(const Node<T>& node1, const Node<T>& node2)
{
	double dis = 0.0;
	for ( int i = 0; i < dimension_; i++ ) {
		dis += pow(node1[i] - node2[i], 2.0);
	}

	return sqrt(dis);
}


template <typename T>
bool KSOM<T>::computeOnes()
{
	if ( time_ >= maxIterate_ ) {
		return false;
	}

    const int idx = time_;
	const Node<T>& refNode = src_[idx];
	double minDis = MAX_DISTANCE;
	int minDisRow = 0, minDisCol = 0;
	for ( int r = 0; r < rows_; r++ ) {
		for ( int c = 0; c < cols_; c++ ) {
			double dis = calcDistance(refNode, map_[r][c]);
			if ( dis < minDis ) {
				minDis = dis;
				minDisRow = r;
				minDisCol = c;
			}
		}
	}
 
	const double alpha = calcAlpha(time_);
	for ( int r = 0; r < rows_; r++ ) {
		for ( int c = 0; c < cols_; c++ ) {
			const double dis = calcDistance(r, c, minDisRow, minDisCol);
			const double h = calcH(dis, time_);

			for ( int i = 0; i < dimension_; i++ ) {
				map_[r][c][i] += static_cast<T>(h*alpha*(refNode[i] - map_[r][c][i]));
			}
		}
	} 

	++time_;
    
	return true;
}


template <typename T>
void KSOM<T>::compute()
{
	while ( computeOnes() ) {
		;
	}
}

template <typename T>
int KSOM<T>::time() const
{
	return time_;
}
