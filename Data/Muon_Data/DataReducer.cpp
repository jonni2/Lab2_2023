// File used to delete all the data in the 1st bin: [0, 200] ns

#include <iostream>
#include <fstream>
#include <string>
#include <cassert>

int main(int argc, char* argv[]) {
    
    if(argc != 3) {
        std::cout << "USAGE: ./a.out path_in path_out\n";
        assert(0);
    }
    
    std::string path_in = argv[1];
    std::string path_out = argv[2];
    
    std::ifstream is(path_in);
    std::ofstream os;
    os.open(path_out);
    
    std::string line; // Placeholder for the i_th line
    
    std::getline(is, line); // Read the header
    
    os << line << '\n';
    
    while(std::getline(is, line)) {
        
        double tP = std::stod(line);
        if(tP > 200) os << tP << '\n';
        
    }
    
    
    is.close();
    os.close();
}
