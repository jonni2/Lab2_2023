// DataCleaner.cpp

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

int main() {
    std::string path_in = "R3_data_4_clean.csv";
    
    std::ifstream is;
    is.open(path_in);
    
    std::ofstream os;
    std::string path_out = "R3_data_4_clean2.csv";
    os.open(path_out);
    
    std::string line, word;
    
    std::getline(is, line); // Skip INITIAL line (header)
    os << line << '\n';
    
    std::vector<std::string> row;
    
    while(std::getline(is, line)){
        row.clear();
        std::stringstream str(line);
        
        while(std::getline(str, word, ',')) {
            row.push_back(word);
        }
        
        // Remove all the lines with ONLY 4095
        // bool condition0 = (row[2] == "4095" && row[3] == "4095" && row[4] == "4095");
        // Remove all the lines WITHOUT 4095
        // bool condition1 = (row[2] != "4095" && row[3] != "4095" && row[4] != "4095");
        bool condition2 = (row[2] != "4095") && (row[3] != "4095") && (row[4] == "4095");
        bool condition3 = (row[2] != "4095") && (row[3] == "4095") && (row[4] != "4095");
        // Accept only lines which DON'T have condition0 and condition1
        if(!(condition2 || condition3)) {
            os << line << '\n';
        }
    }
    
    
    is.close();
    os.close();
}
