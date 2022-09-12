#include <fstream>
#include <iostream>
#include <vector>

void gamma_epsi(const std::string& path) {
    std::ifstream fin;
    std::vector<int> code(12);
    
    fin.open(path);
    if (fin.is_open()) {
        std::string token = "";
        while (!fin.eof()) {
            fin >> token;
            for (int i = 0; i < 12; ++i) {
                if (token[i] == '1') {
                    ++code[i]; 
                }
                else if (token[i] == '0') {
                    --code[i];
                }
            }
        }
    }
    else {
        std::cout << "\nFILE ERROR !\n";
    }
    fin.close();

    for (int i = 0; i < 12; ++i) {
        if (code[i] < 0) {
            std::cout << "0";
        }
        else {
            std::cout << "1";
        }
    }
    std::cout << "\n\n";
}

void oxygen_co(const std::string& path) {
    std::ifstream fin;
    std::string token = "";
    std::string final_ox = "";
    std::string final_co = "";
    bool co_change = false;
    int size = 0;
    int count_ox = 0;
    int count_co = 0;

    fin.open(path);
    while (!fin.eof()) {
        fin >> token;
        if (token[size] == '1') {
            ++count_ox;
        }
        else if (token[size] == '0') {
            --count_ox;
        }
    }
    if (count_ox < 0) {
        final_ox += '0';
        final_co += '1';
    }
    else {
        final_ox += '1';
        final_co += '0';
    }
    count_ox = 0;
    ++size;
    fin.close();

    while (size < 12) {
        fin.open(path);
        while (!fin.eof()) {
            fin >> token;
            if (final_ox.compare(token.substr(0, size)) == 0) {
                if (token[size] == '1') {
                    ++count_ox;
                }
                else if (token[size] == '0') {
                    --count_ox;
                }
                co_change = true;
            }

            if (final_co.compare(token.substr(0, size)) == 0){
                if (token[size] == '1') {
                    ++count_co;
                }
                else if (token[size] == '0') {
                    --count_co;
                }
            }
        }     
        if (count_ox == 1) {
            final_ox += '1';
        }
        else if (count_ox == -1) {
            final_ox += '0';
        }
        else if (count_ox < 0) {
            final_ox += '0';
        }
        else {
            final_ox += '1';
        }
        count_ox = 0;

        if (count_co == 1) {
            final_co += '1';
        }
        else if (count_co == -1) {
            final_co += '0';
        }
        else if (count_co < 0) {
            final_co += '1';
        }
        else {
            final_co += '0';
        }
        count_co = 0;

        fin.close();
        ++size;
    }

    std::cout << "ox:  " << final_ox << "\n";
    std::cout << "co:  " << final_co;
    std::cout << "\n\n";
}