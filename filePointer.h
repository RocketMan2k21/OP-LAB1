#include <iostream>
#include <string>

using namespace std;

bool p_isUpperCase(char c) {
    return c >= 'A' && c <= 'Z';
}

bool p_firstAndLastLetterMatch(string word) {
    return word[0] == word[word.length() - 1];
}

void p_inputFile(string filename){
    cout << "Enter your text (Type CTRL+Z on a new line to end input)" << endl;

    string line;
    string input;

    while (getline(cin, line)) {
        input += line + '\n'; 
    }

    FILE* myFile = fopen(filename.c_str(), "w");
    fputs(input.c_str(), myFile);
    cout << "File created successfully" << endl;
    fclose(myFile);
}

void p_outputFile(string filename){
    FILE* myFile = fopen(filename.c_str(), "r");
    
    char line[100];
    cout << "Your output file:" << endl;

    while(fgets(line, sizeof(line), myFile)){
        cout << line;
    }

    
    

}

void p_checkFile(string filename){
    FILE* myFile = fopen(filename.c_str(), "r");
    if(myFile == NULL){
        cout << "File cannot be opened!" << endl;
        exit(0);
    };
}

void p_findsimilarities(string filename) {
    FILE *myFile, *chFile;
    myFile = fopen(filename.c_str(), "r"); // opening input file in read mode
    chFile = fopen("output.txt", "w"); // opening output file in write mode
    
    
    
    string mystr;
    char c;
    int line = 0; 
    char buffer[100]; // buffer to read each line
    
    while(fgets(buffer, sizeof(buffer), myFile)) {
        mystr = buffer;
        line ++;
        if(line % 2 == 0){
            string word = "";
            for(int i = 0; i < mystr.length(); i++){
                c = mystr[i];
                if(c == ' '){
                   if(p_firstAndLastLetterMatch(word)){
                    fputs((word + " " + word + " ").c_str(), chFile);
                   }else fputs((word + " ").c_str(), chFile);
                   
                   word = "";
                   
                }
                else word += c;                     
                
            }
            if(p_firstAndLastLetterMatch(word)){
                fputs((word + " " + word + " ").c_str(), chFile);
            }else fputs(word.c_str(), chFile);

        }else fputs(mystr.c_str(), chFile);
        
        //fputs("\n", chFile);
    }

    fclose(myFile);
    fclose(chFile);
}

void p_finduppercase(string filename) {
    FILE *inputFile, *chFile;
    inputFile = fopen("output.txt", "r"); // opening file in read mode
    chFile = fopen(filename.c_str(), "w"); // opening file in write mode
    string line;
    int lineNumber = 1;

    char buffer[100]; // buffer to read each line

    while (fgets(buffer, sizeof(buffer), inputFile)) { // reading file line by line
        line = buffer;

        if (lineNumber % 2 == 1) { // checking if line number is odd
            string word = "";
            string newLine = "";

            for (int i = 0; i <= line.length(); i++) {
                char c = line[i];
                if (c == ' ' || c == '\0') { // finding words in the line
                    if (!p_isUpperCase(word[0])) { // checking if word starts with uppercase letter
                        newLine += " " + word;
                    }
                    word = "";
                } else {
                    word += c;
                }
            }

            fputs(newLine.c_str(), chFile);
            //fputs("\n", chFile);
        } else {
            fputs(line.c_str(), chFile);
            //fputs("\n", chFile);
        }

        lineNumber++;
    }

    fclose(inputFile); // closing files
    fclose(chFile);
    remove("output.txt");
}

void p_findthebiggest(string filename){
    FILE* myFile = fopen(filename.c_str(), "r");
    char line[100];
    string prevLine = "";
    string currentLine = "";
    int length;
    int lineNumber = 1;
    int maxLineNumber;
    
    while(fgets(line, sizeof(line), myFile)){
        currentLine = line;
        if(currentLine.length() > prevLine.length()){
            length = currentLine.length();
            maxLineNumber = lineNumber;
            prevLine = currentLine;
        }else{ 
            length = prevLine.length();
        }
        lineNumber++;
    }

    fclose(myFile);

    FILE* myFile1 = fopen(filename.c_str(), "a");
    fputs("\nLenght - ", myFile1);
    fprintf(myFile1, "%d\n", length);
    fputs("Number - ", myFile1);
    fprintf(myFile1, "%d\n", maxLineNumber);
    fclose(myFile1);

    
}

