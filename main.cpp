#include <iostream>
#include <vector>
#include <queue>
#include <pthread.h>

struct symbolData{
   char symbol;
   std::vector<int> range;
};

struct imageData{
    int *length;
    int *width; 
    std::vector<symbolData>* symbolDataVector; 
    std::vector<int>* headPosVector;
    std::vector<int>* dataPosVector;
    std::vector<std::vector<char>>* outputVector;
    
};

struct threadData {
    imageData* imageDataInstance;
    int row;  
};


//Decode the input data and populate 2D outputVector;
void* decode(void* arg){
    threadData* ptrThreadDataInst = static_cast<threadData*>(arg);  
    imageData* ptrImageDataInstance = ptrThreadDataInst->imageDataInstance; 
    std::vector<int>* ptrHeadPosVector = ptrImageDataInstance->headPosVector;
    std::vector<int>* ptrDataPosVec = ptrImageDataInstance->dataPosVector;
    std::vector<symbolData>* ptrSymbolDataVector = ptrImageDataInstance->symbolDataVector;
    std::vector<std::vector<char>>* ptrOutputVec = ptrImageDataInstance->outputVector;
    int row = ptrThreadDataInst->row;
    int lastDataPos;
        
        if(row == (*ptrImageDataInstance->length) - 1){
            lastDataPos = (*ptrDataPosVec).size();
        }
        else{
            lastDataPos = (*ptrHeadPosVector)[row + 1];
        }
        // Loop for each dataPos element in a given row
        for(int dPosIdx = (*ptrHeadPosVector)[row]; dPosIdx < lastDataPos; dPosIdx++){
            // Loop to check each symbol
            for(int symIndex = 0; symIndex <  (*ptrSymbolDataVector).size(); symIndex++){
                // Loop to check each range, divide the condition by 2 because only need to loop half of the range indexes
                for(int rangeIdx = 0; rangeIdx <= (*ptrSymbolDataVector)[symIndex].range.size()/2; rangeIdx++){
                    if( (*ptrDataPosVec)[dPosIdx] >=  (*ptrSymbolDataVector)[symIndex].range[rangeIdx] && (*ptrDataPosVec)[dPosIdx] <= (*ptrSymbolDataVector)[symIndex].range[rangeIdx + 1]){
                        (*ptrOutputVec)[row][(*ptrDataPosVec)[dPosIdx]] =  (*ptrSymbolDataVector)[symIndex].symbol;
                        break;
                    }
                }
            }
            
        }
    pthread_exit(nullptr);
}   

int getSizeParameter(){
    int sizeParameter;
    std::cin >> sizeParameter;
    return sizeParameter;
}

void  getSymbolData(std::vector<symbolData>& symbolDataVector){
    std::string inputString; 
    std::cin.ignore();       // Clear the input stream of \n
    std::getline(std::cin, inputString);
    int inputStringLen = inputString.length();
    char x;
    
    // A for loop to extract all characters and intergers from symbolString
    for(int i=0; i < inputStringLen; i++){
        x = inputString[i];
       
       if(x == ' '){
          continue;
       }
       
       // First index will always be character
       else if(i == 0){
           symbolData instance;
           instance.symbol = x;
           symbolDataVector.push_back(instance);
       }        
      
       else if(x == ','){
           symbolData instance; 
           x = inputString[i + 1]; // Assign x to the next character in the string(symbolString) which will be a letter/symbol
           instance.symbol = x; 
           symbolDataVector.push_back(instance);
           i++; // increment index(i) to account for reading in the next character within symbolString

           
        
       }
       // This branch handles reading and storing ints 
       else{
           std::string tempNumStr = ""; // Define and instantiate a string to temporarily hold the ints read in from symbolString
          // Loop to extract integers
           while(true){
               // Break the loop if a space or  commma is encountered
               if( x == ' ' || x == ','){
                    i--; 
                    break;
                }
                tempNumStr += x;
                x = inputString[i + 1]; // Assign x to the next char in stringToInt
                i++; // Increment i to account due to the previous step to maintain the for loop logic
           }
           
           if(tempNumStr != ""){
               int number = std::stoi(tempNumStr);
               symbolDataVector.back().range.push_back(number); // push number to last vectors' range vector
           }                                                
       }
    }
}

//Retreive headPos or DataPos data
void getPosData(std::vector<int>& tempPosVector){
    std::string posDataStr;
    char x;
    std::getline(std::cin, posDataStr);
    int posDataLen = posDataStr.length();
    std::string tempNumStr;
    
    for(int i = 0; i < posDataLen; i++){
        tempNumStr = "";
        x = posDataStr[i];
        while(true){
            if( x == ' ' || i == posDataLen){
                break;
            }
            tempNumStr += x;
            x = posDataStr[i + 1];
            i++;
        }
        if(tempNumStr != ""){
            int num = std::stoi(tempNumStr);
            tempPosVector.push_back(num);
        }
    }
    
}

int main(){
    std::vector<symbolData> symbolDataVector;
    std::vector<int> headPosVector;
    std::vector<int> dataPosVector;
    int length;
    int width;

    // Get all data from input
    width = getSizeParameter();
    length = getSizeParameter();
    getSymbolData(symbolDataVector);
    getPosData(headPosVector);
    getPosData(dataPosVector);
    std::vector<std::vector<char>> outputVector = std::vector<std::vector<char>>(length, std::vector<char>(width, ' '));
    
    // Initialize struct of type imageData
    imageData imageDataInstance;
    imageDataInstance.width = &width;
    imageDataInstance.length = &length;
    imageDataInstance.symbolDataVector = &symbolDataVector;
    imageDataInstance.headPosVector = &headPosVector;
    imageDataInstance.dataPosVector = &dataPosVector;
    imageDataInstance.outputVector = &outputVector;
    
    // Call the decode function and utilize threads
    std::vector<pthread_t> threads(length);
    for(int i=0; i< *(imageDataInstance.length); i++){
        threadData* threadDataInst = new threadData();
        threadDataInst->imageDataInstance = &imageDataInstance;
        threadDataInst->row = i; 
        pthread_create(&threads[i],nullptr, decode, (void *)threadDataInst);
    }
    //Join threads
    for(int i = 0; i < length; i++) {
        pthread_join(threads[i], nullptr);
    }
    //Print 2d vector
    for (int i = 0; i < length; i++) { 
        for (int j = 0; j < width; j++) {
            std::cout << outputVector[i][j];
        }
        std::cout << std::endl;  // Print a newline after each row
    }
    return 0;
}
