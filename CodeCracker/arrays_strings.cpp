#include <string>
#include <unordered_map>

// 1.1
bool has_unique_chars(const std::string& str) {
    std::unordered_map<char, bool> unique;

    for (auto s : str) {
        if (unique[s]) {
            return false;
        }
        else {
            unique[s] = true;
        }
    }
    return true;
}

// 1.2
bool check_permutation_of_strings(const std::string& str1, const std::string& str2) {
    if (str1.length() > str2.length()) {
        return false;
    }

    for (int i = 0; i < str2.length() - str1.length() + 1; ++i) {
        std::string temp = str2.substr(i, str1.length());
        int num = 0;
        for (int j = 0; j < str1.length(); ++j) {
            num ^= temp[j] ^ str1[j];
        }
        if (!num) {
            return true;
        }
    }
    return false;
}

// 1.3
std::string insert_in_spaces(const std::string& str, const std::string& change) {
    int i = str.length() - 1;
    for (;i >= 0; --i) {
        if (str[i] != ' ') {
            break;
        }
    }
    
    std::string new_string = "";
    for (; i >= 0; --i) {
        if (str[i] == ' ') {
            new_string = change + new_string;
            continue;
        }
        new_string = str[i] + new_string;
    }
    return new_string;
}

// 1.4
bool palindrom_permutation(const std::string& str) {
    std::unordered_map<char, int> symbols;
    
    for (int i = 0; i < str.length(); ++i) {
        ++symbols[str[i]];
    }

    bool odd = false;
    for (auto it : symbols) {
        if (it.second % 2) {
            if (odd) {
                return false;
            }
            odd = true;
        }
    }
    return true;
}

// 1.5
bool can_be_same_one_oper(const std::string& str1, const std::string& str2) {
    if (str1.length() == str2.length() + 1) {
        if (str1.substr(0, str1.length() - 1) == str2) {
            return true;
        }
    }
    else if (str1.length() == str2.length() - 1) {
        if (str1 == str2.substr(0, str2.length() - 1)) {
            return true;
        }
    }
    else if (str1.length() == str2.length()) {
        bool oper_done = false;
        for (int i = 0; i < str1.length(); ++i) {
            if (str1[i] != str2[i]) {
                if (oper_done) {
                    return false;
                }
                oper_done = true;
            }
        }
        return true;
    }
    return false;
}

// 1.6
std::string compressor(const std::string& str) {
    std::string compr = "";
    char curr;
    for (int i = 0; i < str.length(); ++i) {
        curr = str[i];
        int counter = 1;
        for (int j = i + 1; j < str.length(); ++j) {
            if (str[j] != curr) {
                i = j - 1;
                break;
            }
            ++counter;
        }
        compr += std::to_string(counter);
        compr += curr;
    }
    
    if (str.length() <= compr.length()) {
        return str;
    }
    return compr;
}

// 1.7
int** rotated_matrix(int** mat, int size) {
    int** mat_90 = new int*[size];
    for (int i = 0; i < size; ++i) {
        mat_90[i] = new int[size];
    }

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            mat_90[i][j] = mat[size - j - 1][i];
        }
    }
    return mat_90;
}

// 1.8
void set_to_zero_rows_and_columns(int** mat, int m, int n) {
    bool info[m][n];
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            info[i][j] = false;
            if (mat[i][j] == 0) {
                info[i][j] = true;
            }
        }
    }

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (info[i][j]) {
                for (int k = 0; k < m; ++k) {
                    mat[k][j] = 0;
                }
                for (int k = 0; k < n; ++k) {
                    mat[i][k] = 0;
                }
            }
        }
    }
}

// 1.9
bool is_string_rotation(const std::string& str1, const std::string& str2) {
    if (str1.length() != str2.length()) {
        return false;
    }

    std::string temp = str1 + str1;
    for (int i = 0; i < str2.length(); ++i) {
        if (temp.substr(i, str1.length()) == str2) {
            return true;
        }
    }
    return false;
}