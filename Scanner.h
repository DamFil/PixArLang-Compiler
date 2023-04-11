#pragma once

#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<vector<int>> transition_table =
{//                            0    1   2   3   4   5   6   7   8   9   10  11  12  13  14  15  16  17  18  19  20  21  22  23  24  25  26
        /* a-f */           {  1,   1, -1, -1,  5,  6,  7,  8,  9, 10,  -1, -1, -1, -1, -1, -1, -1, 17, -1, 19, -1, 19, -1, -1, -1, -1, -1},
        /* g-z */           {  1,   1, -1, -1, -1, -1, -1, -1, -1, -1,  -1, -1, -1, -1, -1, -1, -1, 17, -1, 19, -1, 19, -1, -1, -1, -1, -1},
        /* 0-9 */           {  2,   1,  2,  2,  5,  6,  7,  8,  9, 10,  -1, -1, -1, -1, -1, -1, -1, 17, -1, 19, -1, 19, -1, -1, -1, -1, -1},
        /* + */             { 11,  -1, -1, -1, -1, -1, -1, -1, -1, -1,  -1, -1, -1, -1, -1, -1, -1, 17, -1, 19, -1, 19, -1, -1, -1, -1, -1},
        /* - */             { 24,  -1, -1, -1, -1, -1, -1, -1, -1, -1,  -1, -1, -1, -1, -1, -1, -1, 17, -1, 19, -1, 19, -1, -1, -1, -1, -1},
        /* < */             { 12,  -1, -1, -1, -1, -1, -1, -1, -1, -1,  -1, -1, -1, -1, -1, -1, -1, 17, -1, 19, -1, 19, -1, -1, -1, -1, -1},
        /* > */             { 12,  -1, -1, -1, -1, -1, -1, -1, -1, -1,  -1, -1, -1, -1, -1, -1, -1, 17, -1, 19, -1, 19, -1, -1, 25, -1, -1},
        /* # */             {  4,  -1, -1, -1, -1, -1, -1, -1, -1, -1,  -1, -1, -1, -1, -1, -1, -1, 17, -1, 19, -1, 19, -1, -1, -1, -1, -1}, 
        /* / */             { 16,  -1, -1, -1, -1, -1, -1, -1, -1, -1,  -1, -1, -1, -1, -1, -1, 17, 17, -1, 19, -1, 22, -1, -1, -1, -1, -1},
        /* ! */             { 14,  -1, -1, -1, -1, -1, -1, -1, -1, -1,  -1, -1, -1, -1, -1, -1, -1, 17, -1, 19, -1, 19, -1, -1, -1, -1, -1},
        /* = */             { 12,  -1, -1, -1, -1, -1, -1, -1, -1, -1,  -1, -1, 13, -1, 15, -1, -1, 17, -1, 19, -1, 19, -1, -1, -1, -1, -1},
        /* * */             { 11,  -1, -1, -1, -1, -1, -1, -1, -1, -1,  -1, -1, -1, -1, -1, -1, 19, 17, -1, 19, 21, 19, -1, -1, -1, -1, -1},
        /* _ */             { -1,   1, -1, -1, -1, -1, -1, -1, -1, -1,  -1, -1, -1, -1, -1, -1, -1, 17, -1, 19, -1, 19, -1, -1, -1, -1, -1},
        /* . */             { -1,  -1,  3, -1, -1, -1, -1, -1, -1, -1,  -1, -1, -1, -1, -1, -1, -1, 17, -1, 19, -1, 19, -1, -1, -1, -1, -1},
        /* \n */            { 26,  -1, -1, -1, -1, -1, -1, -1, -1, -1,  -1, -1, -1, -1, -1, -1, -1, 18, -1, 20, -1, 19, -1, -1, -1, -1, -1},
        /* (,),{,},;,:,, */ { 23,  -1, -1, -1, -1, -1, -1, -1, -1, -1,  -1, -1, -1, -1, -1, -1, -1, 17, -1, 19, -1, 19, -1, -1, -1, -1, -1}
};