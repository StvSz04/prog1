#include <iostream>
#include <vector>
#include <queue>
#include <pthread.h>

// Define a struct that holds corresponding symbols and ranges
struct symbolData{
   char symbol;
   std::vector<int> range;
};

struct imageData{
    int length;
    int width; 
    std::vector<symbolData> symbolDataVector; 
    std::vector<int> headPosVector;
    std::vector<int> dataPosVector;
    std::vector<std::vector<char>> outputVector;
    
};

struct threadData {
    imageData* imageDataInstance;  // Pointer to imageData
    int row;  // Row index for the current thread
};


//Decode the input data and return the 2d vector containing the ascii values
void* decode(void* arg){
    threadData* data = static_cast<threadData*>(arg);  // Cast to threadData
    imageData* imageDataInstance = data->imageDataInstance;  // Get imageData pointer
    int row = data->row;
    
    std::vector<std::vector<char>> outputVector(imageDataInstance->length, std::vector<char>(imageDataInstance->width, ' ')); // Create a 2d vector to hold positions of decoded ascii chars
    //Loop each row
        int range;
        
        if(row == imageDataInstance->length - 1){
            range = imageDataInstance->dataPosVector.size();
        }
        else{
            range = imageDataInstance->headPosVector[row  + 1];
        }
        // Loop each necessary index in dataPosVector
        for(int j= imageDataInstance->headPosVector[row ]; j < range; j++){
            //Loop for each symbol
            for(int y=0; y < imageDataInstance->symbolDataVector.size(); y++){
                //check all ranges for each symbol
                for(int z=0; z <= imageDataInstance->symbolDataVector[y].range.size()/2; z++){
                    if(imageDataInstance->dataPosVector[j] >= imageDataInstance->symbolDataVector[y].range[z] && imageDataInstance->dataPosVector[j] <= imageDataInstance->symbolDataVector[y].range[z + 1]){
                        imageDataInstance->outputVector[row ][imageDataInstance->dataPosVector[j]] = imageDataInstance->symbolDataVector[y].symbol;
                        z++;
                    }
                }
            }
            
        }
    pthread_exit(NULL);
}   

int getSizeParameter(){
    int sizeParameter;
    std::cin >> sizeParameter;
    return sizeParameter;
}

void  getSymbolData(std::vector<symbolData>& symbolDataVector){
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
    
}

//Retreive headPos or DataPos data
void getPosData(std::vector<int>& tempPosVector){
    std::string posData; // Define a string to hold HeadPos data
    char x;
    std::getline(std::cin, posData);
    int posDataLen = posData.length();
    std::string temp; //String to temp hold numbers
    
    for(int i = 0; i < posDataLen; i++){
        temp = "";
        x = posData[i];
        while(true){
            if( x == ' '){
                break;
                }
            else if(i == posDataLen){
                 break;
             }
        
            temp += x;
            x = posData[i + 1];
            i++;
                
        }
        if(temp != ""){
            int num = std::stoi(temp);
            tempPosVector.push_back(num);
        }
    }
    
}

int main(){
    // A vector of type symbolData to store instances of symbolData
    std::vector<symbolData> symbolDataVector;
    // A vector to store headPos data
    std::vector<int> headPosVector;
    // A vector to store dataPos data
    std::vector<int> dataPosVector;
    
    int length;// Define an int to hold length (# of rows)
    int width; // Define an int to hold width ( # of cols)
    
    // Get all data from input
    width = getSizeParameter();
    length = getSizeParameter();
    getSymbolData(symbolDataVector);
    getPosData(headPosVector);
    getPosData(dataPosVector);
    
    // Initialize struct of type inputData
    imageData imageDataInstance;
    imageDataInstance.width = width;
    imageDataInstance.length = length;
    imageDataInstance.symbolDataVector = symbolDataVector;
    imageDataInstance.headPosVector = headPosVector;
    imageDataInstance.dataPosVector = dataPosVector;
    imageDataInstance.outputVector = std::vector<std::vector<char>>(length, std::vector<char>(width, ' '));
    
    // Call the decode function
    std::vector<pthread_t> threads(length);
    for(int i=0; i<imageDataInstance.length; i++){
        threadData* data = new threadData();
        data->imageDataInstance = &imageDataInstance;
        data->row = i;
        pthread_create(&threads[i],NULL, decode, data);
    }
    
    for(int i = 0; i < length; i++) {
        pthread_join(threads[i], NULL);
    }

    //Print 2d vector
    for (int i = 0; i < length; i++) {  // Iterate over rows
        for (int j = 0; j < width; j++) {  // Iterate over columns
            std::cout << imageDataInstance.outputVector[i][j];  // Print the value at (i, j)
        }
        std::cout << std::endl;  // Print a newline after each row
    }
    return 0;
}