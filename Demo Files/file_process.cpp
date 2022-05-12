#include<dirent.h>
#include<sys/stat.h>
#include<iostream>
#include<string>
#include<fstream>
#include<vector> 
#include <stdlib.h>
#include <stdio.h>
#include <time.h>       // import time

using namespace std;

// global variables
vector<string> pathList;
clock_t start;

void explore(char *dir_name){
    DIR *dir;  // pointer to an open director
    struct dirent *entry; // stuff in the directory
    struct stat info; // information about each entry
    string path;

    // open directory
    dir = opendir(dir_name);
    if(!dir){
        cout << "no directory found" << endl;
        return;
    }

    // read directories
    while((entry = readdir(dir)) != NULL){
        // continue getting the path of the files until there's no directories or files left
        if(entry->d_name[0] != '.'){

            // create the path
            path = string(dir_name) + "/" + string(entry->d_name);

            // store path
            pathList.push_back(path);
            
            // check path info
            stat(path.c_str(),&info);
            if(S_ISDIR(info.st_mode)){
            
                explore((char*)path.c_str());
            }
        }
    }
    
    // close directories
    closedir(dir);
}

void readbyID(int idInput){
    // Create a text string, which is used to output the text file
    string key;
    int id;

    // Read from the text file
    
    for(int i = 0; i < pathList.size(); i++){
        if(pathList[i].find(".txt") != string::npos){
            ifstream file(pathList[i]);

            // skip the first line
            getline(file,key);

            // Use a while loop together with the getline() function to read the file line by line
            while (getline (file, key)) {
                id = stoi(key.substr(0,2));    
                if(id == idInput){ 
                    cout << "ID\tName\tAge\tScore"<<endl;
                    cout << key << "\n\n";
                    return;
                }
            }
            // Close the file
            file.close();
        }
    }
    
}

void sequential(string nameInput){
    // Create a text string, which is used to output the text file
    string key;

    // Read from the text file
    
    for(int i = 0; i < pathList.size(); i++){
        if(pathList[i].find(".txt") != string::npos){
            ifstream file(pathList[i]);

            // skip the first line
            getline(file,key);

            // Use a while loop together with the getline() function to read the file line by line
            while (getline (file, key)) {
                
                if(key.find(nameInput) != string::npos){
                    cout << "ID\tName\tAge\tScore"<<endl;
                    cout << key << "\n\n";
                    return;
                }
            }
            // Close the file
            file.close();
        }
    }
}

bool textFileEmpty(){
    // return true if the file is empty with .txt file, false otherwise
    for(int i = 0; i < pathList.size(); i++){
        if(pathList[i].find(".txt") != string::npos){
            // if .txt found
            return false;
        }
    }
    return true;
}

void random(string nameInput,int idInput){
    // Create a text string, which is used to output the text file
    string key;
    int id;
    int size =  pathList.size();
    int randomNo;

    // Read from the text file
    
    while(!textFileEmpty()){
        
        randomNo = 0 + (rand() % size-1);
        if(pathList[randomNo].find(".txt") != string::npos){
            
            ifstream file(pathList[randomNo]);

            // skip the first line
            getline(file,key);


            // Use a while loop together with the getline() function to read the file line by line
            while (getline (file, key)) {
                
                if(key.find(nameInput) != string::npos){
                    cout << "ID\tName\tAge\tScore"<<endl;
                    cout << key << "\n\n";
                    return;
                }
            }
            
            // Close the file
            file.close();
        }

        pathList.erase(pathList.begin()+randomNo);
        size--;
       
    }
}

int lowIndex(string low){
    for(int i = 0; i < pathList.size(); i++){
    
        if(pathList[i].find(low) != string::npos)
            return i;
    }
    return -1;
}

int highIndex(string high){
    for(int i = 0; i < pathList.size(); i++){
    
        if(pathList[i].find(high) != string::npos )
            return i;
    }
    return -1;
}



void limit(string low, string high, int idInput){
    // Create a text string, which is used to output the text file
    string key;
    int id;

    // Read from the text file
    int lowFile = lowIndex(low);
    int highFile = highIndex(high);
    if(lowFile > highFile){
        int temp = lowFile;
        lowFile = highFile;
        highFile = temp;
    }

    if(lowFile == highFile){
        
        ifstream file(pathList[lowFile]);

            // skip the first line
        getline(file,key);


            // Use a while loop together with the getline() function to read the file line by line
        while (getline (file, key)) {
            id = stoi(key.substr(0,2));   
                
            if(id == idInput){ 
                cout << "ID\tName\tAge\tScore"<<endl;
                cout << key << "\n\n";
                
            } 
            
        }
        // Close the file
        file.close();
   
    }

        
    for(int i = lowFile; i < highFile; i++){
    
        if(pathList[i].find(".txt") != string::npos){
            
            ifstream file(pathList[i]);

            // skip the first line
            getline(file,key);


            // Use a while loop together with the getline() function to read the file line by line
            while (getline (file, key)) {
                
                id = stoi(key.substr(0,2));   
                
                if(id == idInput){ 
                    cout << "ID\tName\tAge\tScore"<<endl;
                    cout << key << "\n\n";
                    
                }
            }
            // Close the file
            file.close();
        }
      
    }
}



void relativeProcessing(){
    // gets the data for the specified relative record number
    int idInput;
    cout << "What relative record number are you looking for ?[ID]";
    cin >> idInput;
    readbyID(idInput);
    
}

void sequentialProcessing(){
    // gets the key sequentially
    string nameInput;
    cout << "What key(name) are you looking for?";
    cin >> nameInput;
    sequential(nameInput);
}

void randomProcessing(){
    // gets the data randomly until a file is found
    string nameInput;
    int idInput;
    cout << "What name are you looking for? ";
    cin >> nameInput;
    cout << "What is the id you are looking for? ";
    cin >> idInput;
  
    random(nameInput,idInput);
}

void sequentialLimitProcessing(){
    // process it sequentially through a given boundary

    string low,high;
    int idInput;
    cout << "What lower file boundary you are looking for? ";
    cin >> low;
    cout << "What is the higher file boundary you are looking for? ";
    cin >> high;
    cout << "What is the id you are looking for? ";
    cin >> idInput;

  
    limit(low,high,idInput);
}

int main(){
    string option;
    explore((char*)".");

    cout << "All the path are as follow:" << endl;
        for(int i = 0; i < pathList.size(); i++){
            cout << pathList[i] << endl;
        }
    cout << endl;

    cout << "Welcome to the file processor\n" << endl;
    while(option!="q"){
    
        // welcome message and user input
        cout << "Which file processing algorithms do you wish to use?[enter q to quit]" << endl;
        cout << "1) Relative-record-number processing \n" <<
        "2) Sequential-by-key processing.\n" <<
        "3) Random-by-key processing.\n" <<
        "4) Sequential-within-limits processing" << endl;

        cin >> option;
        if(option == "1"){
            start = clock (); // time start
            relativeProcessing();
            cout << "Time Taken for Relative-record-number processing: " << 
            (((float)( clock() - start )) / CLOCKS_PER_SEC)*1000000000 << " nano seconds.\n" << endl;
        }

        else if(option == "2"){
            start = clock ();
            sequentialProcessing();
            cout << "Time Taken for Sequential-by-key processing: " << 
            (((float)( clock() - start )) / CLOCKS_PER_SEC)*1000000000 << " nano seconds.\n" << endl;
        }

        else if(option == "3"){
            start = clock ();
            randomProcessing();
            cout << "Time Taken for Random-by-key processing: " << 
            (((float)( clock() - start )) / CLOCKS_PER_SEC)*1000000000 << " nano seconds.\n" << endl;
        }

        else if(option == "4"){
            start = clock ();
            sequentialLimitProcessing();
            cout << "Time Taken for Sequential-within-limits processing: " << 
            (((float)( clock() - start )) / CLOCKS_PER_SEC)*1000000000 << " nano seconds.\n" << endl;
        }

        else 
            ;

        explore((char*)".");
    }
        
    return 0;
}