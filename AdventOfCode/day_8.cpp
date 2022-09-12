#include <iostream>
#include <fstream>

void abcdefg_num_count(const std::string& path) {
    std::ifstream fin;

    fin.open(path);
    std::string token;
    int count = 0;
    while (!fin.eof()) {
        fin >> token;
        if (token.compare("|") == 0) {
            for (int i = 0; i < 4; ++i) {
                fin >> token;
                if (token.length() == 2 || token.length() == 3 || token.length() == 4 || token.length() == 7) {
                    ++count;
                }
            }
        }
    }
    std::cout << "\n\nanswer:  " << count << "\n\n";
}