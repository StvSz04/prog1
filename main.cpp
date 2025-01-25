#include <iostream>
#include <vector>

// Define a struct that holds corresponding symbols and ranges
struct symbolData
{
   std::string symbol;
   std::vector<int> range;
};


//Populate the 2d array to then print out in main
void decode(int width, int length, const std::vector<symbolData>& symbolDataVec, const std::vector<int>& headPosVector, const  std::vector<int>& dataPosVector ){
    
}

int main(){
    // A vector of type symbolData to store instances of symbolData
    std::vector<symbolData> symbolDataVector;
    // A vector to store headPos data
    std::vector<int> headPosVector;
    // A vector to store dataPos data
    std::vector<int> dataPosVector;
   
    int length;// Define an int to hold length
    int width; // Define an int to hold width
    std::cin >> length; // Read in Length
    std::cin >> width; // Read in width
    
    std::string symbolString; // Define a string to hold the input data corresponding to all symbols and ranges
    std::cin.ignore();       // Clear the input stream of \n
    std::getline(std::cin, symbolString); // Read in the entire lin containing data corresponding to all symbols and ranges
    int symbolStringLen = symbolString.length(); // Retrieve the length of symbolString to use for a for loop
    
    char x; // Define a char to hold each char within symbolString when extracting inside the for loop
    
    // A for loop to extract all characters and intergers from symbolString
    for(int i=0; i < symbolStringLen; i++){
       
       x = symbolString[i]; // Assign x to the current index in symbolString
       
       // If x is a space char then return to begining of loop
       if(x == ' '){
          // Return to for loop
       }
       
       // At the begining of the loop execute these lines
       else if(i == 0){
           symbolData instance; // Create a new instance of symbolData
           instance.symbol = x; // Assign the symbol memeber of the instance to x
           symbolDataVector.push_back(instance); // push the new instance of symbolData to the vector symbolDataVec
       }        
       
       // If the current char(x) is a comma then execute these lines
       else if(x == ','){
           symbolData instance; // Create a new instance of symbolData
           x = symbolString[i + 1]; // Assign x to the next character in the string(symbolString) which will be a letter/symbol
           instance.symbol = x;  // Assign the symbol memeber of the instance to x
           symbolDataVector.push_back(instance); // push the new instance of symbolData to the vector symbolDataVec
           i++; // increment index(i) to account for reading in the next character within symbolString

           
        
       }
       // This branch handles reading and storing ints 
       else{
           std::string stringToInt = ""; // Define and instantiate a string to temporarily hold the ints read in from symbolString
          // Loop to extract all parts of an int for example if the int is 10 it will read in 1 and then 0 using the loop
           while(true){
               // Break the loop if a space is encountered
               if( x == ' '){
                    break;
                }
                // Break the loop if a comma is encountered and decrement index(i) to account for previous in while loop incrementation
                else if(x == ','){
                    i--;
                    break;
                }
                stringToInt += x; // Append the char that contains a int to stringToInt
                x = symbolString[i + 1]; // Assign x to the next char in stringToInt
                i++; // Increment i to account due to the previous step to maintain the for loop logic
           }
           
           // Once all parts of the int have been extracted then convert the string(stringToInt) to a int 
           // and assign the last instance of symbolData's range to this value
           if(stringToInt != ""){
               int  temp = std::stoi(stringToInt); // Convert stringToInt, using stoi, to and int. Store in a temp var (temp)
               symbolDataVector.back().range.push_back(temp); // Assign the int value(temp) to the last instance of a symbolData struct's range member in symbolDataVec 
           }                                                // Last value because a "read" number will always correspond to the last instance of a symbolData struct instance
       }
       
       
    }

    // Read in headPos data
    std::string headPosData; // Define a string to hold HeadPos data
    std::getline(std::cin, headPosData);
    int headPosDataLen = headPosData.length();
    for(int i = 0; i < headPosDataLen; i++){
        char x = headPosData[i];
        int num = x - 0;
        headPosVector.push_back(num);
    }

    // Read in dataPos data
    std::string dataPosData;
    std::getline(std::cin, dataPosData);
    int dataPosDataLen = dataPosData.length();
    for(int i = 0; i < dataPosDataLen; i++){
        char x = dataPosData[i];
        int num = x - 0;
        dataPosVector.push_back(num);
    }
    
    
    // Call the decode function
    decode(width, length, symbolDataVector, headPosVector, dataPosVector);
}