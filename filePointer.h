#include <iostream>
#include <string>

using namespace std;

bool p_isUpperCase(char c) { // перевірка чи знак в верхньому регістрі
    return c >= 'A' && c <= 'Z';
}

bool p_firstAndLastLetterMatch(string word) { //Перевірка чи збігає перша буква з останньою в слові
    return word[0] == word[word.length() - 1];
}

void p_inputFile(string filename, int mode){
    cout << "Enter your text (Type CTRL+Z on a new line to end input)" << endl;
    
    string line;
    string input;

    while (getline(cin, line)) {//Зчитування рядка
        input += line + '\n';//формування всього тексту 
    }

    if(mode == 0){
        FILE* myFile = fopen(filename.c_str(), "w");
        fputs(input.c_str(), myFile);//Запис у файл
        cout << "File created successfully" << endl;
        fclose(myFile);
    }else{
        FILE* myFile = fopen(filename.c_str(), "a");
        fputs(input.c_str(), myFile);//Запис у файл
        cout << "Data appended successfully" << endl;
        fclose(myFile);
    }

    
}

void p_outputFile(string filename){
    FILE* myFile = fopen(filename.c_str(), "r");
    
    char line[100];
    cout << "Your output file:" << endl;

    while(fgets(line, sizeof(line), myFile)){//Зчитування рядків
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
    myFile = fopen(filename.c_str(), "r"); 
    chFile = fopen("output.txt", "w"); 
    
    
    
    string mystr;
    char c;
    int line = 0; 
    char buffer[100]; 
    
    while(fgets(buffer, sizeof(buffer), myFile)) { //Зчитування рядка
        mystr = buffer;
        line ++;
        if(line % 2 == 0){ //Якщо рядок парний
            string word = "";
            for(int i = 0; i < mystr.length(); i++){
                c = mystr[i];
                if(c == ' '){ // Якщо слово закінчилось
                   if(p_firstAndLastLetterMatch(word)){ // дублювання слова
                    fputs((word + " " + word + " ").c_str(), chFile);
                   }else fputs((word + " ").c_str(), chFile);
                   
                   word = "";
                   
                }
                else word += c;                     
                
            }
            if(p_firstAndLastLetterMatch(word)){ //дублювання слова, яке в кінці рядка
                fputs((word + " " + word + " ").c_str(), chFile);
            }else fputs(word.c_str(), chFile);

        }else fputs(mystr.c_str(), chFile); //Якщо не парний то просто зберігаємо рядок
        
       
    }

    fclose(myFile);
    fclose(chFile);
}

void p_finduppercase(string filename) {
    FILE *inputFile, *chFile;
    inputFile = fopen("output.txt", "r"); 
    chFile = fopen(filename.c_str(), "w"); 
    string line;
    int lineNumber = 1;

    char buffer[100]; 

    while (fgets(buffer, sizeof(buffer), inputFile)) { //Читаємо рядок
        line = buffer;

        if (lineNumber % 2 == 1) {  //якщо непарний
            string word = "";
            string newLine = "";

            for (int i = 0; i <= line.length(); i++) {
                char c = line[i];
                if (c == ' ' || c == '\0') { //пошук слова
                    if (!p_isUpperCase(word[0])) { // якщо перша буква не головно
                        newLine += " " + word; //зберігаємо слова
                    }
                    word = ""; //в інакшому випадку видаляємо слово
                } else {
                    word += c; 
                }
            }

            fputs(newLine.c_str(), chFile);//Запис рядка
            
        } else {
            fputs(line.c_str(), chFile);//Запис незміненого рядка
            
        }

        lineNumber++;
    }

    fclose(inputFile); 
    fclose(chFile);
    remove("output.txt");
}

void p_findthebiggest(string filename){ //Пошук найбільшого рядка
    FILE* myFile = fopen(filename.c_str(), "r");
    char line[100];
    string prevLine = "";
    string currentLine = "";
    int length;
    int lineNumber = 1;
    int maxLineNumber;
    
    while(fgets(line, sizeof(line), myFile)){
        currentLine = line;
        if(currentLine.length() > prevLine.length()){ //якщо зчитуваний рядок більше за попередній то він стає найбільшим
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

