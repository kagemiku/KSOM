#ifndef KG_NODE_H
#define KG_NODE_H


#include <string>
#include <cstring>


namespace kg {


template <typename T>
class Node {
private:
    T* elems_;
    size_t size_;

private:
    auto copyMember(const Node<T>& rhs) -> void;

public:
    Node(size_t size=1);
    Node(const Node<T>& rhs);
    ~Node();
    auto operator+() const -> Node<T>;
    auto operator-() const -> Node<T>;
    auto operator+(const Node<T>& rhs) const -> Node<T>;
    auto operator+(T val) const -> Node<T>;
    auto operator-(const Node<T>& rhs) const -> Node<T>;
    auto operator-(T val) const -> Node<T>;
    auto operator*(const Node<T>& rhs) const -> Node<T>;
    auto operator*(T val) const -> Node<T>;
    auto operator/(const Node<T>& rhs) const -> Node<T>;
    auto operator/(T val) const -> Node<T>;
    auto operator=(const Node<T>& rhs) -> Node<T>&;
    auto operator+=(const Node<T>& rhs) -> Node<T>&;
    auto operator+=(T val) -> Node<T>&;
    auto operator-=(const Node<T>& rhs) -> Node<T>&;
    auto operator-=(T val) -> Node<T>&;
    auto operator*=(const Node<T>& rhs) -> Node<T>&;
    auto operator*=(T val) -> Node<T>&;
    auto operator/=(const Node<T>& rhs) -> Node<T>&;
    auto operator/=(T val) -> Node<T>&;
    auto operator[](size_t idx) const -> T&;
    auto setElem(T elem, size_t idx) -> void;
    auto elem(size_t idx) const -> T;
    auto size() const -> int;
};


template <typename T>
auto Node<T>::copyMember(const Node<T>& rhs) -> void
{
    #ifdef _OPENMP
    #pragma omp parallel for schedule(static)
    #endif
    for ( auto i = 0; i < size_; i++ ) {
        this->elems_[i] = rhs.elems_[i];
    }
}


template <typename T>
Node<T>::Node(size_t size)
    :size_(size)
{
    elems_ = new T[size_];
    std::memset(elems_, 0, sizeof(T)*size_);
}


template <typename T>
Node<T>::Node(const Node<T>& rhs)
    :size_(rhs.size_)
{
    elems_ = new T[size_];
    copyMember(rhs);
}


template <typename T>
Node<T>::~Node()
{
    delete[] elems_;
}


template <typename T>
auto Node<T>::operator+() const -> Node<T>
{
    Node<T> node(*this);

    return node;
}


template <typename T>
auto Node<T>::operator-() const -> Node<T>
{
    Node<T> node(size_);
    #ifdef _OPENMP
    #pragma omp parallel for schedule(static)
    #endif
    for ( auto i = 0; i < size_; i++ ) {
        node.elems_[i] = -this->elems_[i];
    }

    return node;
}


template <typename T>
auto Node<T>::operator+(const Node& rhs) const -> Node<T>
{
    if ( size_ != rhs.size_ ) {
        throw std::string("different size");
    }

    Node<T> node(size_);
    #ifdef _OPENMP
    #pragma omp parallel for schedule(static)
    #endif
    for ( auto i = 0; i < size_; i++ ) {
        node.elems_[i] = this->elems_[i] + rhs.elems_[i];
    }

    return node;
}


template <typename T>
auto Node<T>::operator+(T val) const -> Node<T>
{
    Node<T> node(size_);
    #ifdef _OPENMP
    #pragma omp parallel for schedule(static)
    #endif
    for ( auto i = 0; i < size_; i++ ) {
        node.elems_[i] = this->elems_[i] + val;
    }

    return node;
}


template <typename T>
auto Node<T>::operator-(const Node& rhs) const -> Node<T>
{
    if ( size_ != rhs.size_ ) {
        throw std::string("different size");
    }

    Node<T> node(size_);
    #ifdef _OPENMP
    #pragma omp parallel for schedule(static)
    #endif
    for ( auto i = 0; i < size_; i++ ) {
        node.elems_[i] = this->elems_[i] - rhs.elems_[i];
    }

    return node;
}


template <typename T>
auto Node<T>::operator-(T val) const -> Node<T>
{
    Node<T> node(size_);
    #ifdef _OPENMP
    #pragma omp parallel for schedule(static)
    #endif
    for ( auto i = 0; i < size_; i++ ) {
        node.elems_[i] = this->elems_[i] - val;
    }

    return node;
}


template <typename T>
auto Node<T>::operator*(const Node& rhs) const -> Node<T>
{
    if ( size_ != rhs.size_ ) {
        throw std::string("different size");
    }

    Node<T> node(size_);
    #ifdef _OPENMP
    #pragma omp parallel for schedule(static)
    #endif
    for ( auto i = 0; i < size_; i++ ) {
        node.elems_[i] = this->elems_[i] * rhs.elems_[i];
    }

    return node;
}


template <typename T>
auto Node<T>::operator*(T val) const -> Node<T>
{
    Node<T> node(size_);
    #ifdef _OPENMP
    #pragma omp parallel for schedule(static)
    #endif
    for ( auto i = 0; i < size_; i++ ) {
        node.elems_[i] = this->elems_[i] * val;
    }

    return node;
}


template <typename T>
auto Node<T>::operator/(const Node& rhs) const -> Node<T>
{
    if ( size_ != rhs.size_ ) {
        throw std::string("different size");
    }

    Node<T> node(size_);
    #ifdef _OPENMP
    #pragma omp parallel for schedule(static)
    #endif
    for ( auto i = 0; i < size_; i++ ) {
        if ( rhs.elems_[i] == static_cast<T>(0) ) {
            throw std::string("divided by zero");
        }
        node.elems_[i] = this->elems_[i] / rhs.elems_[i];
    }

    return node;
}


template <typename T>
auto Node<T>::operator/(T val) const -> Node<T>
{
    if ( val == static_cast<T>(0) ) {
        throw std::string("divided by zero");
    }

    Node<T> node(size_);
    #ifdef _OPENMP
    #pragma omp parallel for schedule(static)
    #endif
    for ( auto i = 0; i < size_; i++ ) {
        node.elems_[i] = this->elems_[i] / val;
    }

    return node;
}

template <typename T>
auto Node<T>::operator=(const Node& rhs) -> Node<T>&
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
auto Node<T>::operator+=(const Node& rhs)  -> Node<T>&
{
    if ( size_ != rhs.size_ ) {
        throw std::string("different size");
    }

    #ifdef _OPENMP
    #pragma omp parallel for schedule(static)
    #endif
    for ( auto i = 0; i < size_; i++ ) {
        elems_[i] += rhs.elems_[i];
    }

    return *this;
}


template <typename T>
auto Node<T>::operator+=(T val) -> Node<T>&
{
    #ifdef _OPENMP
    #pragma omp parallel for schedule(static)
    #endif
    for ( auto i = 0; i < size_; i++ ) {
        elems_[i] += val;
    }

    return *this;
}


template <typename T>
auto Node<T>::operator-=(const Node& rhs) -> Node<T>&
{
    if ( size_ != rhs.size_ ) {
        throw std::string("different size");
    }

    #ifdef _OPENMP
    #pragma omp parallel for schedule(static)
    #endif
    for ( auto i = 0; i < size_; i++ ) {
        elems_[i] -= rhs.elems_[i];
    }

    return *this;
}


template <typename T>
auto Node<T>::operator-=(T val) -> Node<T>&
{
    #ifdef _OPENMP
    #pragma omp parallel for schedule(static)
    #endif
    for ( auto i = 0; i < size_; i++ ) {
        elems_[i] -= val;
    }

    return *this;
}


template <typename T>
auto Node<T>::operator*=(const Node& rhs) -> Node<T>&
{
    if ( size_ != rhs.size_ ) {
        throw std::string("different size");
    }

    #ifdef _OPENMP
    #pragma omp parallel for schedule(static)
    #endif
    for ( auto i = 0; i < size_; i++ ) {
        elems_[i] *= rhs.elems_[i];
    }

    return *this;
}


template <typename T>
auto Node<T>::operator*=(T val) -> Node<T>&
{
    #ifdef _OPENMP
    #pragma omp parallel for schedule(static)
    #endif
    for ( auto i = 0; i < size_; i++ ) {
        elems_[i] *= val;
    }

    return *this;
}


template <typename T>
auto Node<T>::operator/=(const Node& rhs) -> Node<T>&
{
    if ( size_ != rhs.size_ ) {
        throw std::string("different size");
    }

    #ifdef _OPENMP
    #pragma omp parallel for schedule(static)
    #endif
    for ( auto i = 0; i < size_; i++ ) {
        if ( rhs.elems_[i] == static_cast<T>(0) ) {
            throw std::string("divided by zero");
        }
        elems_[i] /= rhs.elems_[i];
    }

    return *this;
}


template <typename T>
auto Node<T>::operator/=(T val) -> Node<T>&
{
    if ( val == static_cast<T>(0) ) {
        throw std::string("divided by zero");
    }

    #ifdef _OPENMP
    #pragma omp parallel for schedule(static)
    #endif
    for ( auto i = 0; i < size_; i++ ) {
        elems_[i] /= val;
    }

    return *this;
}


template <typename T>
auto Node<T>::operator[](size_t idx) const -> T&
{
    if ( idx >= size_ ) {
        throw std::string("out of range.");
    }

    return elems_[idx];
}


template <typename T>
auto Node<T>::setElem(T elem, size_t idx) -> void
{
    if ( idx >= size_ ) {
        throw std::string("out of range.");
    }

    elems_[idx] = elem;
}


template <typename T>
auto Node<T>::elem(size_t idx) const -> T
{
    if ( idx >= size_ ) {
        throw std::string("out of range.");
    }

    return elems_[idx];
}


template <typename T>
auto Node<T>::size() const -> int
{
    return size_;
}


}


#endif

