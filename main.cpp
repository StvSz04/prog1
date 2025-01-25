#include <iostream>
#include <vector>

struct symbolData
{
    // Fix these data types later
   std::string symbol;
   std::vector<int> range;
};

// A vector of type symbolData(Struct)
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
    
    
    
    std::string symbolString;
    std::cin.ignore();
    std::getline(std::cin, symbolString);
    int symbolStringLen = symbolString.length();
    
    
    // Test symbol data input collection
    char x;
    for(int i=0; i < symbolStringLen; i++){
       
       x = symbolString[i];
       
       if(x == ' '){
          // Return to for loop
       }
       
       else if(i == 0){
           symbolData instance;
           instance.symbol = x;
           symbolDataVec.push_back(instance);
       }        
       
       else if(x == ','){
           symbolData instance;
           x = symbolString[i + 1];
           instance.symbol = x;
           symbolDataVec.push_back(instance);
           i++;

           
        
       }
       else{
           std::string stringToInt = "";
           while(true){
               if( x == ' '){
                    break;
                }
                else if(x == ','){
                    i--;
                    break;
                }
                stringToInt += x;
                x = symbolString[i + 1];
                i++;
           }
           
           if(stringToInt != ""){
               int  y = std::stoi(stringToInt);
               symbolDataVec.back().range.push_back(y);
           }
       }
       
       
    }

    // Read in headPos data
    std::string headPos;
    std::cin.ignore();
    std::getline(std::cin, headPos);

    // Read in dataPos data
    std::string dataPos;
    std::getline(std::cin, dataPos);
}