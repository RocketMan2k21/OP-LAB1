
#include "fileStream.h"
#include "filePointer.h"
#include <iostream>
#include <string.h>


using namespace std;

int main(int argc, char const *argv[])
{
    string filename = "newfile.txt";
    
    if(argc !=2){
        cout << "Two arguments required!";
        exit(0);
    } 
    
    if(strcmp(argv[1], "-FileStream") == 0){
        inputFile(filename);
        checkFile(filename);
        findsimilarities(filename);
        finduppercase(filename);
        findthebiggest(filename);
        outputFile(filename);
    }
    else if(strcmp(argv[1], "-FilePointer") == 0){
        p_inputFile(filename);
        p_checkFile(filename);
        p_findsimilarities(filename);
        p_finduppercase(filename);
        p_findthebiggest(filename);
        p_outputFile(filename);
    }
    else{
        cout << "Wrong  arguments";
        exit(0);
    }
}
