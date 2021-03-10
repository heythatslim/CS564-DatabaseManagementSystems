//
// File: wl.h
// 
//  Description: header file for word locator wl.cpp 
//  Student Name: Sung Joon Lim
//  UW Campus ID: 9075324815
//  enamil: lim62@wisc.edu
//

#include <iterator>
#include <sstream>
#include <list>
#include <locale>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cctype>

struct child {
        std::string             word;
        std::vector<int>        indexList;
        child                   *left;
        child                   *right;
};

class bitree{
        public:
                bitree(){
                        root = NULL;
                        is_empty = true;
                };

                void add(std::string str, int index);
                child *find(std::string str, int index);
                void rm_tree();
                bool is_empty;

        private:
                void rm_tree(child *node);
                void add(std::string str, child *node, int index);
                child *find(std::string str, child *node, int index);
                child *root;
};


