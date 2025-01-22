#include <iostream>
#include <vector>

struct symbolData
{
    // Fix these data types later
   std::string symbol;
   std::vector<int> range;
};

std::vector<symbolData> symbolDataVec;

//Populate the 2d array to then print out in main
void decode(int width, int height, int* headPos, int* dataPos, int* char_vector, int* range_vector){
    
}

int main(){
    // Read in size parameters
    int length;
    int width;
    
    std::cin >> length;
    std::cin >> width;
    
    
    std::cout << length << " " << width << std::endl;
    
    std::string symbolString;
    std::cin.ignore();
    std::getline(std::cin, symbolString);
    std::cout << "symbolString" << symbolString << std::endl;
    int symbolStringLen = symbolString.length();
    
    // Test symbol data input collection
    for(int i=0; i < symbolStringLen ; i++){
       
       std::string x;
       std::cin >> x;
       
       if(i == 0){
           symbolData instance;
           symbolDataVec.push_back(instance);
           instance.symbol = x;
       }        
       else if(x == ","){
           symbolData instance;
           symbolDataVec.push_back(instance);
           std:: cin >> x;
           instance.symbol = x;
           
           std:: cin >> x;
        
       }
       
       else{
            int  y = std::stoi(x);
            symbolDataVec.back().range.push_back(y);
       }
    }
    
 std::cout << "Symbol: " << symbolDataVec.back().symbol << ", Range: " << symbolDataVec.back().range.back() << std::endl;    
 

    // Read in headPos data
    std::string headPos;
    std::getline(std::cin, headPos);
    
    std::cout << "HeadPos data " << headPos << std::endl;


    // Read in dataPos data
    std::string dataPos;
    std::getline(std::cin, dataPos);
    
    std::cout  << "dataPos data " << dataPos << std::endl;


