#ifndef HEAP_TREE_H
#define HEAP_TREE_H

#include <iostream>
#include <initializer_list>
#include <vector>
#include <utility>

namespace skt {

template <typename T>
class heap_tree {
    
private:
    std::vector<T> m_tree;

private:
    int left(int);
    int right(int);
    int parent(int);
    void max_heapify(int);
    void min_heapify(int);

public:
    heap_tree() = default;
    heap_tree(int);
    heap_tree(const heap_tree<T> &);
    heap_tree(heap_tree<T> &&);
    heap_tree(std::initializer_list<T>);
    ~heap_tree() {m_tree.clear();}

public:
    heap_tree<T>& operator=(const heap_tree<T> &);
    heap_tree<T>& operator=(heap_tree<T> &&);
    heap_tree<T>& operator+=(const heap_tree<T>&);
    
    template <typename E>
    friend std::ostream& operator<<(std::ostream&, const heap_tree<E>&);
    template <typename E>
    friend bool operator==(const heap_tree<E>&, const heap_tree<E>&);
    template <typename E>
    friend bool operator!=(const heap_tree<E>&, const heap_tree<E>&);
    template <typename E>
    friend heap_tree<E> operator+(const heap_tree<E>&, const heap_tree<E>&);

public:
    void build_max_heap();
    void build_min_heap();
    void delete_element(const T&);
    T extract_max_element();
    T extract_min_element();
    int linear_search(const T&);
    int height();
    void insert(const T&);
}; 

template <typename T>
heap_tree<T>::heap_tree(int size) {
    m_tree.resize(size);
}

template <typename T>
heap_tree<T>::heap_tree(const heap_tree<T>& other) {
    m_tree = other.m_tree;
}

template <typename T>
heap_tree<T>::heap_tree(heap_tree<T>&& other) {
    m_tree = std::move(other.m_tree);
}

template <typename T>
heap_tree<T>::heap_tree(std::initializer_list<T> list) {
    if (list.size()) {
        m_tree.resize(list.size());
        int i = 0;
        for (auto it = list.begin(); it != list.end(); ++it) {
            m_tree[i] = *it;
            ++i;
        }
    }
    this->build_max_heap();
}

template <typename T>
heap_tree<T>& heap_tree<T>::operator=(const heap_tree<T>& other) {
    m_tree = other.m_tree;
    return *this;
} 

template <typename T>
heap_tree<T>&  heap_tree<T>::operator=(heap_tree<T>&& other) {
    m_tree = std::move(other.m_tree);
    return *this;
}

template <typename T>
heap_tree<T>& heap_tree<T>::operator+=(const heap_tree<T>& other) {
    int size = other.m_tree.size();
    if (size > m_tree.size()) {
        size = m_tree.size();
    }
    for (int i = 0; i < size; ++i) {
        m_tree[i] += other.m_tree[i];
    }
    return *this;
}

template <typename E>
std::ostream& operator<<(std::ostream& os, const heap_tree<E>& tree) {
    for (int i = 0; i < tree.m_tree.size(); ++i) {
        os << tree.m_tree[i] << " ";
    }
    os << std::endl;

    return os;
}

template <typename E>
bool operator==(const heap_tree<E>& left, const heap_tree<E>& right) {
    if (left.m_tree.size() != right.m_tree.size()) {
        return false;
    }
    else {
        for (int i = 0; i < left.m_tree.size(); ++i) {
            if (left.m_tree[i] != right.m_tree[i]) {
                return false;
            }
        }
    }
    return true;
}

template <typename E>
bool operator!=(const heap_tree<E>& left, const heap_tree<E>& right) {
    return !(left == right);
}

template <typename E>
heap_tree<E> operator+(const heap_tree<E>& left, const heap_tree<E>& right) {
    int size = left.m_tree.size();
    if (size > right.m_tree.size()) {
        size = right.m_tree.size();
    }
    heap_tree<E> new_tree(size);
    for (int i = 0; i < size; ++i) {
        new_tree.m_tree[i] = left.m_tree[i] + right.m_tree[i];
    }
    return new_tree;
}

template <typename T>
int heap_tree<T>::left(int index) {
        return index * 2 + 1;
}

template <typename T>
int heap_tree<T>::right(int index) {
        return index * 2 + 2;
}

template <typename T>
int heap_tree<T>::parent(int index) {
        return (index - 1) /2 ;
}

template <typename T>
void heap_tree<T>::max_heapify(int index) {
    int max = index;
    int left = this->left(index);
    int right = this->right(index);

    if (left < m_tree.size() && m_tree[left] > m_tree[max]) {
        max = left;
    }    
    if (right < m_tree.size() && m_tree[right] > m_tree[max]) {
        max = right;
    }

    if (max != index) {
        std::swap(m_tree[max], m_tree[index]);
        max_heapify(max);
    }
}

template <typename T>
void heap_tree<T>::build_max_heap() {
    for (int i = m_tree.size()/2; i >= 0; --i) {
        this->max_heapify(i);
    }
}

template <typename T>
void heap_tree<T>::min_heapify(int index) {
    int max = index;
    int left = this->left(index);
    int right = this->right(index);

    if (left < m_tree.size() && m_tree[left] < m_tree[max]) {
        max = left;
    }
    
    if (right < m_tree.size() && m_tree[right] < m_tree[max]) {
        max = right;
    }

    if (max != index) {
        std::swap(m_tree[max], m_tree[index]);
        min_heapify(max);
    }
}

template <typename T>
void heap_tree<T>::build_min_heap() {
    for (int i = m_tree.size()/2; i >= 0; --i) {
        this->min_heapify(i);
    }
}

template <typename T>
void heap_tree<T>::delete_element(const T& elem) {
    int i = 0;
    for (; i < m_tree.size(); ++i) {
        if (m_tree[i] == elem) {
            break;
        }
    }

    std::swap(m_tree[i], m_tree[m_tree.size() - 1]);
    m_tree.resize(m_tree.size() - 1);
    this->build_max_heap();
}

template <typename T>
T heap_tree<T>::extract_max_element() {
    if (m_tree.empty()) {
        return -1111111111;
    }

    int max = m_tree[0];
    std::swap(m_tree[0], m_tree[m_tree.size() - 1]);
    m_tree.resize(m_tree.size() - 1);
    this->build_max_heap();
    return max;
}

template <typename T>
T heap_tree<T>::extract_min_element() {
    if (m_tree.empty()) {
        return -1111111111;
    }

    int min = m_tree[0];
    std::swap(m_tree[0], m_tree[m_tree.size() - 1]);
    m_tree.resize(m_tree.size() - 1);
    this->build_min_heap();
    return min;
}

template <typename T>
int heap_tree<T>::linear_search(const T& elem) {
    int i = 0;
    bool found = false;;
    for (;i < m_tree.size(); ++i) {
        if (m_tree[i] == elem) {
            found = true;
            break;
        }
    }

    if (found) {
        return i;
    }
    return -1;
}

template <typename T>
int heap_tree<T>::height() {
    if (m_tree.size()) {
        int h = 0;
        int i = 0;
        while (i < m_tree.size()) {
            i = (i * 2) + 1;
            ++h;
        }
        return h;
    }
    return -1;
}

template <typename T>
void heap_tree<T>::insert(const T& elem) {
    m_tree.push_back(elem);
    this->build_max_heap();
}

} // skt

#endif // HEAP_TREE_H