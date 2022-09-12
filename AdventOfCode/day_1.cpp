#include <iostream>
#include <fstream>
#include <string>
#include <utility>

void depth_messurement_increase(const std::string& path) {
    std::ifstream fin;

    fin.open(path);
    if (fin.is_open()) {
        std::string token;
        int num;
        int prev;
        int count = 0;
        fin >> token;
        prev = std::stoi(token);
    
        while (!fin.eof()) {
            fin >> token;
            num = std::stoi(token);
            if (num > prev) {
                ++count;
            }
            prev = num;
        }
        std::cout << "\nincrease count:  " << count;
        fin.close();
    }
    else {
        std::cout << "\nFILE ERROR !\n";
    }
}

void depth_window_messurement_increase(const std::string& path) {
    std::ifstream fin;

    fin.open(path);
    if (fin.is_open()) {
        std::string token;
        int num1;
        int num2;
        int num3;
        int sum;
        int count = 0;
        fin >> token;
        num1 = std::stoi(token);
        fin >> token;
        num2 = std::stoi(token);
        fin >> token;
        num3 = std::stoi(token);
        sum = num1 + num2 + num3;
        
        while (!fin.eof()) {
            num1 = num2;
            num2 = num3;
            fin >> token;
            num3 = std::stoi(token);
            if (sum < (num1 + num2 + num3)) {
                ++count;
            }
            sum = num1 + num2 + num3;
            std::cout << num1 << "  " << num2 << "  " << num3 << "\n";
        }
        std::cout << "\nincrease count:  " << count;
        fin.close();
    }
    else {
        std::cout << "\nFILE ERROR !\n";
    }
}