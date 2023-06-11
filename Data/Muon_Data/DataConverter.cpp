// DataCleaner.cpp

// This C++ program allows to convert the number of ticks to nanoseconds.

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

int main(int argc, char* argv[]) {
    // std::string path_in = "R3_data_4.csv";
    std::string path_in = argv[1];
    
    std::ifstream is;
    is.open(path_in);
    
    std::stringstream stream_pathin(path_in);
    std::string filename;
    std::getline(stream_pathin, filename, '.');


    std::ofstream os;
    std::string path_out = filename+"_ns.csv";
    os.open(path_out);
    
    std::string line, word;
    
    std::getline(is, line); // Skip INITIAL line (header)

    std::vector<std::string> row;

    double m = 4;
    double q;

    std::stringstream header(line);
    while(std::getline(header, word, ',')) {
            row.push_back(word);
    }
    
    // Define the CALIBRATION parameter q according to the
    // HEADER: P1, P2 or P3 (m is always 4)
    if(row[2]=="tP1"){
        q = 40.97;  
        os << "tP1" << '\n';  
        std::cout << "tP1\n";
    }
    else if(row[2]=="tP2"){
        q = 41.72;  
        os << "tP2" << '\n'; 
        std::cout << "tP2\n";      
    }
    else if(row[2]=="tP3"){
        q = 42.43;
        os << "tP3" << '\n'; 
        std::cout << "tP3\n";   
    }

    
    while(std::getline(is, line)){
        row.clear();
        std::stringstream str(line);
        
        while(std::getline(str, word, ',')) {
            row.push_back(word);
        }

        // std::stod converts STRING to DOUBLE
        double tPn = std::stod(row[2]);

        tPn=(tPn*m)+q;

        os << tPn << '\n';
        
    }
    
    
    is.close();
    os.close();
}
