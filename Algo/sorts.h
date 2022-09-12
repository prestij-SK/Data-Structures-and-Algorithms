#ifndef SORTS_H
#define SORTS_H

#include <vector>

template <typename T>
void swap (T& a, T& b) {
    int temp = a;
    a = b;
    b = temp;
}

template <typename T>
void bubble_sort(std::vector<T>& arr) {
    for (int i = 0; i < arr.size(); ++i) {
        for (int j = 0; j < arr.size(); ++j) {
            if (arr[i] < arr[j]) {
                swap(arr[i], arr[j]);
            }
        }
    }
}

template <typename T>
void selection_sort(std::vector<T>& arr) {
    for (int i = 0; i < arr.size(); ++i) {
        for (int j = i + 1; j < arr.size(); ++j) {
            if (arr[i] > arr[j]) {
                swap(arr[i], arr[j]);
            }
        }
    }
}

template <typename T>
void insertion_sort(std::vector<T>& arr) {
    for (int i = 1; i < arr.size(); ++i) {
        int j = i - 1;
        int current = arr[i];
        while (current < arr[j] && j >= 0) {
            arr[j + 1] = arr[j];
            --j;
        }
        arr[j + 1] = current;
    }
}

template <typename T>
T binary_search(std::vector<T>& arr, T val) {
    int left = 0;
    int right = arr.size() - 1;
    for (int i = 0; i < arr.size(); ++i) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == val) {
            return val;
        }
        if (arr[mid] < val) {
            right = mid - 1;
        }
        else {
            left = mid + 1;
        }
    }
    return -1;
}

template <typename T>
void counting_sort(std::vector<T>& arr) {
    int max = arr[0];
    for (int i = 1; i < arr.size(); ++i) {
        if (max < arr[i]) {
            max = arr[i];
        }
    }
    if (!max) {
        max = 1;
    }
    std::vector<T> arr_count(max);

    for (int i = 0; i < arr.size(); ++i) {
        ++arr_count[arr[i]];
    }

    int i = 0;
    int j = 0;
    while (i < arr.size()) {
        while (arr_count[j] > 0) {
            arr[i] = j;
            --arr_count[j];
            ++i;
        }
        ++j;
    }
}

template <typename T>
int partition(std::vector<T>& arr, int low, int high) {
    T pivot = arr[high];
    int i = low;

    for (int j = low; j < high; ++j) {
        if (arr[j] < pivot) {
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);

    return i + 1;
}

template <typename T>
void quick_sort(std::vector<T>& arr, int low, int high) {
    if (low < high) {
        int index = partition(arr, low, high);
        quick_sort(arr, low, index - 1);
        quick_sort(arr, index + 1, high);\
    }
}

template <typename T>
void merge(std::vector<T>& arr, int first, int mid, int last) {
    int first1 = first;
    int last1 = mid;
    int first2 = mid + 1;
    int last2 = last;
    int i = first;
    std::vector<T> temp(arr.size());

    while (first1 <= last1 && first2 <= last2) {
        if (arr[first1] < arr[first2]) {
            temp[i] = arr[first1];
            ++first1;
        }
        else {
            temp[i] = arr[first2];
            ++first2;
        }
        ++i;
    }

    while (first1 <= last1) {
        temp[i] = arr[first1];
        ++first1;
        ++i;
    }
    while (first2 <= last2) {
        temp[i] = arr[first2];
        ++first2;
        ++i;
    }

    for (int j = first; j <= last; ++j) {
        arr[j] = temp[j];
    }
}

template <typename T>
void merge_sort(std::vector<T>& arr, int first, int last) {
    if (first < last) {
        int mid = first + (last - first) / 2;
        merge_sort(arr, first, mid);
        merge_sort(arr, mid + 1, last);
        merge(arr, first, mid, last);
    }
}

template <typename T>
void max_heapify(std::vector<T>& arr, int index) {
    int max = index;
    int left = index*2 + 1;
    int right = index*2 + 2;

    if (left < arr.size() && arr[left] > arr[max]) {
        max = left;
    }
    
    if (right < arr.size() && arr[right] > arr[max]) {
        max = right;
    }

    if (max != index) {
        std::swap(arr[max], arr[index]);
        max_heapify(arr, max);
    }
}

template <typename T>
void heap_sort(std::vector<T>& arr) {
    for (int i = arr.size()/2; i >= 0; --i) {
        max_heapify(arr, i);
    }
    
    std::vector<T> temp = arr;
    for (int i = 0; i < arr.size(); ++i) {
        arr[i] = temp[0];
        std::swap(temp[0], temp[temp.size() - 1]);
        temp.resize(temp.size() - 1);

        for (int j = temp.size()/2; j >= 0; --j) {
            max_heapify(temp, j);
        }
    }
}

#endif // SORTS_H