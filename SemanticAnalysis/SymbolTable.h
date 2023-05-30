// we can use a stack for the symbol table
// we can also use a linked list
#pragma once
#include <iostream>
#include <map>
#include <vector>
#include <string>

using namespace std;

class SymbolTable
{
private:
    int current, tempCurrent;
    vector<map<string, string>> nmspaces{};

public:
    SymbolTable() : current(0), tempCurrent(0) {}
    ~SymbolTable() {}

    void push(map<string, string> binding)
    {
        nmspaces.push_back(binding);
        ++current;
    }

    void pop()
    {
        nmspaces.pop_back();
        --current;
    }

    string lookup(string key)
    {
        if (current == -1)
        {
            current = nmspaces.size() - 1;
            cout << "Error: \"" << key << "\" is not declared anywhere." << endl;
            return "END";
        }
        try
        {
            string found = nmspaces.at(current).at(key);
            tempCurrent = current;
            current = nmspaces.size() - 1;
            return found;
        }
        catch (std::out_of_range)
        {
            --current;
            lookup(key);
        }
    }

    void insert(pair<string, string> newkey)
    {
        lookup(newkey.first);
        if (tempCurrent == current)
        {
            // you are trying to redeclare an identifer in the same scope
            cout << "Error: You already declared an identifier with that name in the same scope" << endl;
            exit(EXIT_FAILURE);
        }

        nmspaces.at(current).insert(newkey);
    }
};