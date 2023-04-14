#pragma once

#include <fstream>
#include <iostream>
#include <string>

using namespace std;

class FileHandler {
    private:
        string path;
        fstream file;
        string buffer;
        int inputpos;
        
    public:
        FileHandler() : inputpos(0) {
            cout << "Specify the path of the file to compile: ";
            cin >> path;
            file.open(path, ifstream::in);
            if (!file.is_open()) {
                cout << "Error: Cannot open file at: " + path << endl;
                buffer = "";
            } 
            else 
                buffer = { (std::istreambuf_iterator<char>(file)), (std::istreambuf_iterator<char>()) };
        }

        FileHandler(string p) : path(p) , inputpos(0) {
            file.open(path, ifstream::in);

            if (!file.is_open()) {
                cout << "Error: Cannot open file at: " + path << endl;
                buffer = "";
            }
            else 
                buffer = { (std::istreambuf_iterator<char>(file)), (std::istreambuf_iterator<char>()) };
        }

        char NextChar() {
            char c = buffer.at(inputpos);
            if (c != EOF) 
                ++inputpos;
            return c;
        }

        int RollBack() {
            if (inputpos == 0)
                return -1;
            --inputpos; return 0;
        }

        int getSizeOfProgram() {
            return this->buffer.length();
        }

        int getCurrPos() {
            return this->inputpos;
        }
};