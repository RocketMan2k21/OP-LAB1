#include <iostream>
#include <fstream>
#include <string>


using namespace std;

bool firstAndLastLetterMatch(string word) {
    return word[0] == word[word.length() - 1];
}

bool isUpperCase(char c) {
    return c >= 'A' && c <= 'Z';
}

void inputFile(string filename){
   cout << "Enter your text (Type CTRL+Z on a new line to end input)" << endl;

    string line;
    string input;

    while (getline(std::cin, line)) {
        input += line + '\n'; 
    }

    ofstream myFile(filename);
    myFile << input;
    cout << "File created successfully" << endl;
    myFile.close();
 
}

void outputFile(string filename){
    ifstream myFile(filename);
    string line;
    cout << "Your output file:" << endl;
    while(getline(myFile, line)){
        cout << line << endl;
    }
}

void checkFile(string filename){
    ifstream myFile(filename);
    if(!myFile.is_open()){
        cout << "File cannot be opened" << endl;
        exit(0);
    }
}

void findsimilarities(string filename)
{ 
    ifstream myFile(filename);
    ofstream chFile("output.txt");
    
    string mystr;
    char c;
    int line = 0;    
    
    while(getline(myFile, mystr)){
        line ++;
        if(line % 2 == 0){
            string word = "";
            for(int i = 0; i < mystr.length(); i++){
                c = mystr[i];
                if(c == ' '){
                   if(firstAndLastLetterMatch(word)){
                    chFile << word << " " << word << " ";
                   }else chFile << word << " ";
                   
                   word = "";
                   
                }
                else word += c;                     
                
            }
            if(firstAndLastLetterMatch(word)){
                chFile << word << " " << word << " ";
            }else chFile << word;

        }else chFile << mystr;
        
        chFile << endl;
    }

    myFile.close();
    chFile.close();
}

void finduppercase(string filename){
    ifstream inputFile("output.txt"); // відкриття файлу для зчитування
    ofstream chFile(filename);

    string line;
    int lineNumber = 1;

    while (getline(inputFile, line)) { // зчитування файлу по рядках
        if (lineNumber % 2 == 1) { // перевірка на парність рядка
            string word = "";
            string newLine = "";

            for (int i = 0; i <= line.length(); i++) {
                char c = line[i];
                if (c == ' ' || c == '\0') { // знаходження окремих слів у рядку
                    if (!isUpperCase(word[0])) { // перевірка чи починається слово з великої літери
                        newLine += " " + word;
                    }
                    word = "";
                } else {
                    word += c;
                }
            }

            chFile << newLine << endl;
        } else {
            chFile << line << endl;
        }

        lineNumber++;
    }

    inputFile.close(); // закриття файлу
    remove("output.txt");
}

void findthebiggest(string filename){
    
    ifstream myFile(filename);

    string prevLine = "";
    string line = "";
    int lenght;
    int lineNumber = 1;
    int maxLineNumber;
    

    while(getline(myFile, line)){
        if(line.length() > prevLine.length()){
            lenght = line.length();
            maxLineNumber = lineNumber;
            prevLine = line;
        }else{ 
            lenght = prevLine.length();
        }
        lineNumber++;
    }

    myFile.close();

    ofstream myFile1(filename, ios::app);
    myFile1 << "Lenght - " << lenght << endl;
    myFile1 << "Number - " << maxLineNumber << endl;
    myFile1.close();
}
