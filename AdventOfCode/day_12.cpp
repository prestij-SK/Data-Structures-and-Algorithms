#include <iostream>
#include <string>
#include <fstream>
#include <unordered_map>
#include <vector>

bool upper_case(const std::string& str) {
    if (str[0] >= 'A' && str[0] <= 'Z') {
        return true;
    }
    return false;
}

void path_counter(const std::string& file) {
    std::ifstream fin;
    std::unordered_map<std::string, std::vector<std::string>> paths;
    std::string token;
    std::string path1 = "";
    std::string path2 = "";
    fin.open(file);

    while (!fin.eof()) {
        fin >> token;

        for (int i = 0; i < token.length(); ++i) {
            if (token[i] == '-') {
                path2 = token.substr(i + 1, token.length() - i);
                break;
            }
            path1 += token[i];
        }

        paths[path1].push_back(path2);
        if (path1.compare("start") == 0) { // in my case, start always left side
            path1 = "";
            path2 = "";
            continue;
        }
        paths[path2].push_back(path1);
        path1 = "";
        path2 = "";
    }
    fin.close();

    // for (auto it = paths.begin(); it != paths.end(); ++it) {
    //     std::cout << it->first << " -> ";
    //     for (auto jt : it->second) {
    //         std::cout << jt << "  ";
    //     }
    //     std::cout << "\n";
    // }

    // std::cout << "\n\n";

    // for (int i = 0; i < paths["start"].size(); ++i) {
    //     std::cout << paths["start"][i] << " -> ";
    //     for (auto it : paths[paths["start"][i]]) {
    //         std::cout << it << " ";
    //     }
    //     std::cout << "\n";
    // }

    std::cout << "\n\n";

    for (int i = 0; i < paths["start"].size(); ++i) {
        std::cout << paths["start"][i] << " -> ";
        for (auto it : paths[paths["start"][i]]) {
            std::cout << it << " ";
        }
        std::cout << "\n";
    }
}