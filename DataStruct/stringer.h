#ifndef STRINGER_H
#define STRINGER_H

#include <iostream>

namespace skt {

class string {
private:
    char* m_str;
    int m_size;
    int m_cap;

    struct Iterator {
    private:
        char* m_ptr;

    public:
        using iterator_category = std::random_access_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = char;
        using pointer = char*;
        using reference = char&;

        Iterator(pointer ptr);

        reference operator*() const;
        pointer operator->() const;

        /* not done yet*/
        Iterator& operator++();
        const Iterator operator++(const int);
    };

public:
    string();
    string(const char*);
    string(const string&);
    string(int);
    string(int, char);
    string(string&&);
    ~string();

public:
    string& operator=(const string&);
    string& operator=(const char*);
    string& operator=(string&&);
    string& operator+=(const string&);
    string& operator+=(const char*);
    char& operator[](int);
    friend string operator+(const string&, const string&);
    friend string operator+(const char*, const string&);
    friend string operator+(const string&, const char*);
    friend bool operator==(const string&, const string&);
    friend bool operator!=(const string&, const string&);
    friend bool operator<(const string&, const string&);
    friend bool operator>(const string&, const string&);
    friend bool operator<=(const string&, const string&);
    friend bool operator>=(const string&, const string&);
    friend std::ostream& operator<<(std::ostream&, const string&);

public:
    char& at(int);
    const char* c_str() const;
    /* must be implamented !!!!!!!!

    element access ( at, front, back, data, c_str )
    capacity ( empty, size/length, max_size, reverse, capacity, shrink_to_fit )
    search ( find, rfind, find_firts_of, find_last_of )
    modifiers ( clear, insert, emplace, erase, push_back, append, compare, replace, substr, copy, pop_back, resize, swap )
    numeric conversions ( stoi, stol, stoul, stod, to_string )

    */

};
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
string::Iterator::Iterator(pointer ptr) : m_ptr{ptr} {}

string::Iterator::reference string::Iterator::operator*() const {return *m_ptr;}

string::Iterator::pointer string::Iterator::operator->() const {return m_ptr;}


string::Iterator& string::Iterator::operator++() {
    ++m_ptr;
    return *this;
}

const string::Iterator string::Iterator::operator++(const int) {
    Iterator temp = *this;
    ++(*this);
    return temp;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
string::string() : m_str{}, m_size{}, m_cap{} {}

string::string(const char* str) {
    int i = 0;
    while (*(str + i) != '\0') {
        ++i;
    }
    m_size = i;
    m_cap = i;

    m_str = new char[m_size];
    for (int j = 0; j < m_size; ++j) {
        m_str[j] = str[j];
    }
    *(m_str + m_size) = '\0'; 
}

string::string(const string& other) : m_size{other.m_size}, m_cap{other.m_cap} {
    m_str = new char[m_size];
    for (int i = 0; i < m_size; ++i) {
        m_str[i] = other.m_str[i];
    }
    *(m_str + m_size) = '\0';
}

string::string(int size) : m_str{new char[size]}, m_size{size}, m_cap{size} {}

string::string(int size, char c) : m_size{size}, m_cap{size} {
    m_str = new char[m_size];
    for (int i = 0; i < m_cap; ++i) {
        m_str[i] = c;
    }
}

string::string(string&& other) : m_str{other.m_str}, m_size{other.m_size}, m_cap{other.m_cap} {
    other.m_cap = 0;
    other.m_size = 0;
    other.m_str = nullptr;
}

string::~string() {
    delete [] m_str;
    m_str = nullptr;
    m_size = 0;
    m_cap = 0;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
string& string::operator=(const string& other) {
    if (m_str == other.m_str) {
        return*this;
    }
    if (m_str) {
        delete [] m_str;
    }

    m_size = other.m_size;
    m_cap = other.m_cap;
    m_str = new char[m_size];
    for (int i = 0; i < m_size; ++i) {
        m_str[i] = other.m_str[i];
    }
    *(m_str + m_size) = '\0';
    return *this;
}

string& string::operator=(const char* str) {
    if (m_str) {
        delete [] m_str;
    }

    int i = 0;
    while (*(str + i) != '\0') {
        ++i;
    }
    m_size = i;
    m_cap = i;

    m_str = new char[m_size];
    for (int j = 0; j < m_size; ++j) {
        m_str[j] = str[j];
    }
    *(m_str + m_size) = '\0';
    return *this;
}

string& string::operator=(string&& other) {
    if (m_str == other.m_str) {
        return *this;
    }
    if (m_str) {
        delete [] m_str;
    }

    m_size = other.m_size;
    m_cap = other.m_cap;
    m_str = other.m_str;

    other.m_size = 0;
    other.m_cap = 0;
    other.m_str = nullptr;
    return *this;
}

string& string::operator+=(const string& str) {
    *this = *this + str;
    return *this;
}

string& string::operator+=(const char* str) {
    *this = *this + string(str);
    return *this;
}

string operator+(const string& str1, const string& str2) {
    string temp(str1.m_size + str2.m_size);
    for (int i = 0; i < str1.m_size; ++i) {
        temp.m_str[i] = str1.m_str[i];
    }

    for (int i = str1.m_size, j = 0; i < str1.m_size + str2.m_size; ++i, j++) {
        temp.m_str[i] = str2.m_str[j];
    }
    return temp;
}

string operator+(const char* str1, const string& str2) {
    return string(str1) + str2;
}

string operator+(const string& str1, const char* str2) {
    return str1 + string(str2);
}

char& string::operator[](int pos) {
    return *(m_str + pos);
}

std::ostream& operator<<(std::ostream& os, const string& str) {
    os << str.m_str;
    return os;
}

bool operator==(const string& str1, const string& str2) {
    if (str1.m_size != str2.m_size) {
        return false;
    }
    
    for (int i = 0; i < str1.m_size; ++i) {
        if (str1.m_str[i] != str2.m_str[i]) {
            return false;
        }
    }
    return true;
}

bool operator!=(const string& str1, const string& str2) {
    return !(str1 == str2);
}

bool operator<(const string& str1, const string& str2) {
    if (str1.m_size < str2.m_size) {
        return true;
    }
    
    for (int i = 0; i < str1.m_size; ++i) {
        if (str1.m_str[i] > str2.m_str[i]) {
            return false;
        }
    }
    return true;
}

bool operator>(const string& str1, const string& str2) {
    if (str1.m_size < str2.m_size) {
        return false;
    }
    
    for (int i = 0; i < str1.m_size; ++i) {
        if (str1.m_str[i] < str2.m_str[i]) {
            return false;
        }
    }
    return true;
}

bool operator<=(const string& str1, const string& str2) {
    if (str1 < str2 || str1 == str2) {
        return true;
    }
    return false;
}

bool operator>=(const string& str1, const string& str2) {
    if (str1 > str2 || str1 == str2) {
        return true;
    }
    return false;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
char& string::at(int pos) {
    if (pos < 0 || pos >= m_size) {
        throw std::out_of_range("\nOut of range !\n");
    }
    return *(m_str + pos);
}

const char* string::c_str() const {
    return m_str;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

} // skt

#endif // STRINGER_H