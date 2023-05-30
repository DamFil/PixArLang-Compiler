// we can use a stack for the symbol table
// we can also use a linked list
#pragma once
#include <iostream>
#include <map>
#include <vector>
#include <string>

using namespace std;

typedef enum representationType
{
    var,
    fun,
    none
} repr;

class Entity
{
public:
    string scope;
    string type;
    repr r; // whether it is a function identifer, or just a variable

    Entity(string scope, string type, repr r) : scope(scope), type(type), r(r) {}
    ~Entity() {}
};

class SymbolTable
{
private:
    int current, tempCurrent;
    vector<map<string, Entity *>> nmspaces{};

public:
    SymbolTable() : current(0), tempCurrent(0) {}
    ~SymbolTable() {}

    void push(map<string, Entity *> binding)
    {
        nmspaces.push_back(binding);
        ++current;
    }

    void pop()
    {
        nmspaces.pop_back();
        --current;
    }

    Entity *lookup(string key)
    {
        if (current == -1)
        {
            current = nmspaces.size() - 1; // resetting it back to the oriignal scope
            cout << "Error: \"" << key << "\" is not declared anywhere." << endl;
            return new Entity("END", "END", none);
        }
        try
        {
            Entity *found = nmspaces.at(current).at(key);
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

    void insert(pair<string, Entity *> newkey)
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