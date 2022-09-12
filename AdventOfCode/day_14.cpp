#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <map>

void polym_insertion(const std::string& path) {
    std::ifstream fin;
    fin.open(path);

    std::unordered_map<std::string, std::string> pairs;
    std::string polym;
    std::string pair;
    std::string token;
    fin >> polym;

    while (!fin.eof()) {
        fin >> pair;
        fin >> token;
        fin >> token;
        pairs[pair] = token;
    }
    pair = "";

    // std::cout << polym << "\n\n";
    // for (auto it = pairs.begin(); it != pairs.end(); ++it) {
    //     std::cout << it->first << " -> " << it->second << "\n";
    // }

    int count = 10;
    while (count) {
        std::string polym_temp = "";
        for (int i = 1; i < polym.length(); ++i) {
            pair += polym[i - 1];
            pair += polym[i];
            // std::cout << "\np[1]: " << polym[i]
            // std::cout << "\npair: " << pair;
            polym_temp += polym[i - 1];
            polym_temp += pairs[pair];
            // std::cout << "\npolym_temp: " << polym_temp;
            pair = "";
        }
        polym_temp += polym[polym.length() - 1];
        polym = polym_temp;
        --count;
    }

    std::map<char, int> letter_counts;

    for (int i = 0; i < polym.length(); ++i) {
        ++letter_counts[polym[i]];
    }

    // std::cout << polym << "\n\n";
    // for (auto it = letter_counts.begin(); it != letter_counts.end(); ++it) {
    //     std::cout << it->first << " -> " << it->second << "\n";
    // }

    int max = 0;
    int min = INT_MAX;

    for (auto it = letter_counts.begin(); it != letter_counts.end(); ++it) {
        if (max < it->second) {
            max = it->second;
        }
        if (min > it->second) {
            min = it->second;
        }
    }

    // std::cout << "\nanswer: " << max - min << "\n";
    std::cout << "\nsize:" << polym.length() << "\n";
    std::cout << "\nmax: " << max << "  min: " << min << "\n\n";
}

void polym_insertion_big(const std::string& path) {
    std::ifstream fin;
    fin.open(path);

    std::unordered_map<std::string, std::string> pairs;
    std::string polym;
    std::string pair;
    std::string token;
    fin >> polym;

    while (!fin.eof()) {
        fin >> pair;
        fin >> token;
        fin >> token;
        pairs[pair] = token;
    }
    pair = "";

    // std::cout << polym << "\n\n";
    // for (auto it = pairs.begin(); it != pairs.end(); ++it) {
    //     std::cout << it->first << " -> " << it->second << "\n";
    // }

    int count = 20;
    while (count) {
        std::string polym_temp = "";
        for (int i = 1; i < polym.length(); ++i) {
            pair += polym[i - 1];
            pair += polym[i];
            // std::cout << "\np[1]: " << polym[i]
            // std::cout << "\npair: " << pair;
            polym_temp += polym[i - 1];
            polym_temp += pairs[pair];
            // std::cout << "\npolym_temp: " << polym_temp;
            pair = "";
        }
        polym_temp += polym[polym.length() - 1];
        polym = polym_temp;
        --count;

        unsigned max = 0;
        unsigned min = INT_MAX;

        std::map<char, int> letter_counts;

        for (int i = 0; i < polym.length(); ++i) {
            ++letter_counts[polym[i]];
        }

        char high;
        char low;
        for (auto it = letter_counts.begin(); it != letter_counts.end(); ++it) {
            if (max < it->second) {
                max = it->second;
                high = it->first;
            }
            if (min > it->second) {
                min = it->second;
                low = it->first;
            }
        }

        // std::cout << "\nanswer: " << max - min << "\n";
        std::cout << "\nsize:" << polym.length() << "\n";
        std::cout << "\nmax: " << high << "_" << max << "   min: " << low << "_" << min << "\n\n";
    }

    // std::cout << polym << "\n\n";
    // for (auto it = letter_counts.begin(); it != letter_counts.end(); ++it) {
    //     std::cout << it->first << " -> " << it->second << "\n";
    // }

}