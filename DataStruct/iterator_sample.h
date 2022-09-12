#ifndef ITERATOR_SAMPLE_H
#define ITERATOR_SAMPLE_H

#include <iostream>

namespace skt {

template <typename T>
class Arr {
private:
    T* m_arr;
    int m_size;

public:
    Arr() : m_arr{nullptr}, m_size{} {}
    Arr(int s) : m_arr{new T[s]}, m_size{s} {}
    ~Arr() {
        delete [] m_arr;
        m_arr = nullptr;
        m_size = 0;
    }

    void insert_i() {
        for (int i = 0; i < m_size; ++i) {
            m_arr[i] = i;
        }
    }

    void insert_ti() {
        for (int i = 0; i < m_size; ++i) {
            m_arr[i] = 3 * i;
        }
    }

    void show() {
        std::cout << "\n";
        for (int i = 0; i < m_size; ++i) {
            std::cout << m_arr[i] << " ";
        }
        std::cout << "\n";
    }
    
    struct Iterator {
        using iterator_category = std::random_access_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = T;
        using pointer = T*;
        using reference = T&;

        Iterator(pointer ptr) : m_ptr{ptr} {}

        reference operator*() const {return *m_ptr;}
        pointer operator->() const {return m_ptr;}

        Iterator& operator++() {
            ++m_ptr;
            return *this;
        }

        Iterator operator++(const T) {
            Iterator tmp = *this;
            ++(*this);
            return tmp;
        }

        Iterator& operator--() {
            --m_ptr;
            return *this;
        }

        Iterator operator--(const T) {
            Iterator tmp = *this;
            --(*this);
            return tmp;
        }

        Iterator& operator+(int a) {
            m_ptr += a;
            return *this;
        }

        Iterator& operator-(int a) {
            m_ptr -= a;
            return *this;
        }

        friend difference_type operator-(const Iterator a,const Iterator b) {
            return a.m_ptr - b.m_ptr;
        }
        
        friend bool operator==(Iterator a, Iterator b) {
            return a.m_ptr == b.m_ptr;
        }

        friend bool operator!=(Iterator a, Iterator b) {
            return a.m_ptr != b.m_ptr;
        }
    private:
        T* m_ptr;
    };

    Iterator begin() {return Iterator(m_arr);}
    Iterator end() {return Iterator(m_arr + m_size);}
};

} // skt

#endif