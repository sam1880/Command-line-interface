#include<iostream>
#include<string>
#include<sstream>
#include<vector>
#include<windows.h>
#include <unordered_map>
#include <functional>

void createFile(const std::string& fileName){ 
    HANDLE file = CreateFileA(fileName.c_str(), GENERIC_WRITE, 0, NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL);

    if(file == INVALID_HANDLE_VALUE){
        std::cout<<"failed to create the file"<<std::endl;
    }
    else{
        
        std::cout<<fileName<<" created"<<std::endl;
        CloseHandle(file);
    }
}

std::unordered_map<std::string, std::function<void(const std::string&)>> commandMap = {
    {"new", createFile}
};

int decideCommand(std::vector<std::string>& words){
    std::string command = words[0];
    if(commandMap.find(command) != commandMap.end()){
        
        commandMap[command](words[1]); 
    }
    else{
        std::cout<<"command not found"<<std::endl;
    }
    return 0;
}

int main(){
    std::string input;

    while(true){
        std::cout<<"cli>";

        std::getline(std::cin, input);
        if(input == "exit"){
            std::cout<<"exiting.."<<std::endl;
            break;
        }

        std::stringstream ss(input);
        std::vector<std::string> words;
        std::string word;
        
        while(ss >> word){
            words.push_back(word);
        }

        if(!words.empty()){
            decideCommand(words); 
        }
    }

    return 0;
}
