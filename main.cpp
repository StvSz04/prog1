#include <iostream>
#include <vector>

struct symbol_data
{
   char symbol;
   std::vector<int> range;
};


//Populate the 2d array to then print out in main
void decode(int width, int height, int* headPos, int* dataPos, int* char_vector, int* range_vector){
    
}

int main(){
    // Read in size parameters
    int length;
    int width;
    
    std::cin >> length;
    std::cin >> width;
    
    
    std::cout << length << width;
    
    // Read in char and their ranges
    // Using getline(), .length(), .find(), substr() to cut up the dynamic sized input
    std::string char_parameters;
    char delim = ',';
    std::getline(std::cin, char_parameters, delim);

    // Read in headPos data
    std::string headPos;
    std::getline(std::cin, headPos);
    
    std::cout << headPos;


    // Read in dataPos data
    std::string dataPos;
    std::getline(std::cin, dataPos);
    
    std::cout << dataPos;





 
    
}