#pragma once

#include <fstream>
#include <iostream>
#include <string>

using namespace std;

class FileHandler
{
private:
    string path;
    fstream file;
    string buffer;
    int inputpos;

public:
    FileHandler() = delete;

    FileHandler(string p) : path(p), inputpos(-1) //-1 because calling nextChar sets it to 0
    {
        file.open(path, ifstream::in);

        if (!file.is_open())
        {
            cout << "Error: Cannot open file at: " + path << endl;
            buffer = "";
        }
        else
            buffer = {(std::istreambuf_iterator<char>(file)), (std::istreambuf_iterator<char>())};
    }

    int nextChar()
    {
        ++inputpos;
        try
        {
            return buffer.at(inputpos);
        }
        catch (std::out_of_range)
        {
            return 'EOF';
        }
    }

    int peekChar()
    {
        try
        {
            return buffer.at(inputpos + 1);
        }
        catch (std::out_of_range)
        {
            return 'EOF';
        }
    }

    int rollBack()
    {
        if (inputpos == 0 || inputpos == this->buffer.size())
            return -1;
        --inputpos;
        return 0;
    }

    int getSizeOfProgram()
    {
        return this->buffer.length();
    }

    int getCurrPos()
    {
        return this->inputpos;
    }
};