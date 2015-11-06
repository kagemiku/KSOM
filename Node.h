#pragma once

#include <string>
#include <cstring>


template <typename T>
class Node {
private:
	T* elems_;
	int size_;
 
private:
	void copyMember(const Node<T>& rhs);

public:
	Node(int size=1);
	Node(const Node<T>& rhs);
	~Node(void);
	Node<T> operator+() const;
	Node<T> operator-() const;
	Node<T> operator+(const Node<T>& rhs) const;
	Node<T> operator+(T val) const;
	Node<T> operator-(const Node<T>& rhs) const;
	Node<T> operator-(T val) const;
	Node<T> operator*(const Node<T>& rhs) const;
	Node<T> operator*(T val) const;
	Node<T>& operator=(const Node<T>& rhs);
	Node<T>& operator+=(const Node<T>& rhs);
	Node<T>& operator+=(T val);
	Node<T>& operator-=(const Node<T>& rhs);
	Node<T>& operator-=(T val);
	T& operator[](int idx) const;
	void setElem(T elem, int idx);
	T elem(int idx) const;
	int size(void) const;
}; 


template <typename T>
void Node<T>::copyMember(const Node<T>& rhs)
{
	for ( int i = 0; i < size_; i++ ) {
		this->elems_[i] = rhs.elems_[i];
	}
}


template <typename T>
Node<T>::Node(int size)
	:size_(size) 
{ 
	elems_ = new T[size_];
    std::memset(elems_, 0, sizeof(elems_));
} 


template <typename T>
Node<T>::Node(const Node<T>& rhs) 
	:size_(rhs.size_)
{
	elems_ = new T[size_];
	copyMember(rhs);
}


template <typename T>
Node<T>::~Node(void) 
{ 
	delete[] elems_;
}


template <typename T>
Node<T> Node<T>::operator+() const
{
	Node<T> node(*this);

	return node;
}


template <typename T>
Node<T> Node<T>::operator-() const 
{
	Node<T> node(size_);
	for ( int i = 0; i < size_; i++ ) {
		node.elems_[i] = -this->elems_[i];
	}

	return node;
}


template <typename T>
Node<T> Node<T>::operator+(const Node& rhs) const
{
	if ( size_ != rhs.size_ ) {
		throw std::string("different size");
	}

	Node<T> node(size_);
	for ( int i = 0; i < size_; i++ ) {
		node.elems_[i] = this->elems_[i] + rhs.elems_[i];
	}

	return node;
}


template <typename T>
Node<T> Node<T>::operator+(T val) const
{
	Node<T> node(size_);
	for ( int i = 0; i < size_; i++ ) {
		node.elems_[i] = this->elems_[i] + val;
	}

	return node;
}


template <typename T>
Node<T> Node<T>::operator-(const Node& rhs) const
{
	if ( size_ != rhs.size_ ) {
		throw std::string("different size");
	}

	Node<T> node(size_);
	for ( int i = 0; i < size_; i++ ) {
		node.elems_[i] = this->elems_[i] - rhs.elems_[i];
	}

	return node;
}


template <typename T>
Node<T> Node<T>::operator-(T val) const
{
	Node<T> node(size_);
	for ( int i = 0; i < size_; i++ ) {
		node.elems_[i] = this->elems_[i] - val;
	}

	return node;
}


template <typename T>
Node<T> Node<T>::operator*(const Node& rhs) const
{
	if ( size_ != rhs.size_ ) {
		throw std::string("different size");
	}

	Node<T> node(size_);
	for ( int i = 0; i < size_; i++ ) {
		node.elems_[i] = this->elems_[i] * rhs.elems_[i];
	}

	return node;
}


template <typename T>
Node<T> Node<T>::operator*(T val) const
{
	Node<T> node(size_);
	for ( int i = 0; i < size_; i++ ) {
		node.elems_[i] = this->elems_[i] * val;
	}

	return node;
}


template <typename T>
Node<T>& Node<T>::operator=(const Node& rhs)
{
	if ( this == &rhs ) {
		return *this;
	}

	size_ = rhs.size_;

	T* tmp = elems_;
	elems_ = new T[size_];
	delete[] tmp;
	copyMember(rhs);

	return *this;
}


template <typename T>
Node<T>& Node<T>::operator+=(const Node& rhs) 
{
	if ( size_ != rhs.size_ ) {
		throw std::string("different size");
	}

	for ( int i = 0; i < size_; i++ ) {
		elems_[i] += rhs.elems_[i];
	}

	return *this;
}


template <typename T>
Node<T>& Node<T>::operator+=(T val)
{
	for ( int i = 0; i < size_; i++ ) {
		elems_[i] += val;
	}

	return *this;
}


template <typename T>
Node<T>& Node<T>::operator-=(const Node& rhs)
{
	if ( size_ != rhs.size_ ) {
		throw std::string("different size");
	}

	for ( int i = 0; i < size_; i++ ) {
		elems_[i] -= rhs.elems_[i];
	}

	return *this;
}


template <typename T>
Node<T>& Node<T>::operator-=(T val)
{
	for ( int i = 0; i < size_; i++ ) {
		elems_[i] -= val;
	}

	return *this;
}


template <typename T>
T& Node<T>::operator[](int idx) const
{
	if ( idx < 0 || idx >= size_ ) {
		throw std::string("out of range.");
	}

	return elems_[idx];
}


template <typename T>
void Node<T>::setElem(T elem, int idx)
{
	if ( idx >= size_ ) {
		throw std::string("out of range.");
	}

	elems_[idx] = elem;
}


template <typename T>
T Node<T>::elem(int idx) const
{
	if ( idx >= size_ ) {
		throw std::string("out of range.");
	}

	return elems_[idx];
}


template <typename T>
int Node<T>::size(void) const
{
	return size_;	
}
