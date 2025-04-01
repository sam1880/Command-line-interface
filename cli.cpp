#include<iostream>
#include<unordered_map>
#include<sstream>
#include<functional>
#include<windows.h>
#include<vector>

void createFile(const std::string& fileName){
    HANDLE file = CreateFileA(fileName.c_str(), GENERIC_WRITE, 0, NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL  );
    if(file != INVALID_HANDLE_VALUE){
        std::cout<<fileName<<" created successfully"<<std::endl;
        CloseHandle(file);
    }
    else{
        std::cout<<"err file not created"<<std::endl;
    }
}

void deleteFile(const std::string& fileName){
    BOOL file = DeleteFileA(fileName.c_str());
    if(file){
        std::cout<<"file deleted"<<std::endl;
    }
    else{
        std::cout<<"file cant be deleted"<<std::endl;
    }
}


void changeDirectory(const std::string& path){
    if(SetCurrentDirectoryA(path.c_str())){
        std::cout<<"current directory set to"<<path<<std::endl;
    }
    else{
        std::cout<<"error  retrieving the directory";
    }
}

void retrieveDirectory(const std::string&){
    char buffer[MAX_PATH];
    if(GetCurrentDirectoryA(MAX_PATH, buffer)){
        std::string currentPath(buffer);
        std::cout<<"current diirectory "<<currentPath<<std::endl;
    }
}

std::unordered_map<std::string, std::function<void(const std::string&)>> cm = {
    {"new", createFile},
    {"bin", deleteFile},
    {"to", changeDirectory},
    {"in", retrieveDirectory}
};

int handleCommand(std::vector<std::string>& words) {
    std::string command = words[0];
    
    if (cm.find(command) != cm.end()) {
        if (words.size() > 1) { // Fix: Check if second argument exists
            cm[command](words[1]);
        } else {
            std::cout << "Error: Missing filename argument." << std::endl;
        }
    } else {
        std::cout << "Error: Command not found." << std::endl;
    }

    return 0;
}

std::vector<std::string> handleInput(std::string input){
    std:: vector<std::string> words;
    std:: string word;
    std:: stringstream ss(input);
    while(ss >> word){
        words.push_back(word);
    }
    return (words);
}

int runCli(){
    std:: string input;

    while(true){
        char buffer[MAX_PATH];;
        if(GetCurrentDirectoryA(MAX_PATH, buffer)){
            std::string currentPath(buffer);
            std::cout<<currentPath<<"cli>";
        }

        std::getline(std::cin, input);
        std::vector<std::string>words = handleInput(input);

        if(input == "exit"){
            std::cout<<"exiting"<<std::endl;
            break;
        }

        if(!words.empty()){
            handleCommand(words);
        }
    }

    return 0;
}

int main(){
    runCli();
    return 0;
}