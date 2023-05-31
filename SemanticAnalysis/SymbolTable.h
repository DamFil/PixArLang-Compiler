// we can use a stack for the symbol table
// we can also use a linked list
#pragma once
#include <iostream>
#include <map>
#include <vector>
#include <string>

using namespace std;

typedef enum typeOfIdentifer
{
    integer,
    floater,
    colour,
    boolean,
    pad_height,
    pad_width,
    NotAType,
    ERROR
} type;

typedef enum representationType
{
    var,
    fun,
    param,
    none
} repr;

typedef enum result
{
    sameScope,
    diffScope
} res;

class TypeObject
{
public:
    vector<type> types;
    repr r;

    TypeObject(vector<type> types, repr r) : types(types), r(r) {}
    ~TypeObject() {}
};

class SymbolTable
{
private:
    int current, tempCurrent;
    vector<map<string, TypeObject *>> nmspaces{};

public:
    SymbolTable() : current(0), tempCurrent(0) {}
    ~SymbolTable() {}

    void push()
    {
        map<string, TypeObject *> binding{};
        nmspaces.push_back(binding);
        ++current;
    }

    void pop()
    {
        nmspaces.pop_back();
        --current;
    }

    TypeObject *lookup(string key)
    {
        for (int i = current; i <= 0; i--)
        {
            auto found = nmspaces.at(i).find(key);
            if (found != nmspaces.at(i).end())
            {
                tempCurrent = i;
                return (*found).second;
            }
        }

        return nullptr;
    }

    res insert(pair<string, TypeObject *> newkey)
    {
        lookup(newkey.first);
        if (tempCurrent == current)
        {
            // you are trying to insert 2 same identifiers in the same scope
            cout << "Cannot have 2 same Identifiers in the same scope" << endl;
            return sameScope;
        }

        nmspaces.at(current).insert(newkey);
        return diffScope;
    }

    int getCurrent()
    {
        return this->current;
    }
};