#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>
#include <map>
#include "H_Node.h"
#include "Words.h"


std::map <char, std::string> codes; //just a container for codes while compressing
std::map <std::string, char> new_codes; //just a container for codes while decompressing
int deleted_nulls;

std::string get_elem_code(char elem) { return codes[elem]; }

char get_new_elem_code(std::string elem) { return new_codes[elem]; }

bool elem_exists_with_new_code(std::string elem) { return new_codes.find(elem) != new_codes.end(); }

void get_codes(HuffNode *tree, std::string code)
{
    if (tree->left == tree->right)
    {
        codes[tree->sym] = code;
        return;
    }
    std::string left_code  = code + "0";
    std::string right_code = code + "1";

    if (tree->left)
        get_codes(tree->left, left_code);
    if (tree->right)
        get_codes(tree->right, right_code);
}

void print_codes(std::string path)
{
    std::ofstream output(path);
    for (auto &t: codes)
    {
        if (path.empty())
            std::cout << t.first << "__" << t.second << std::endl;
        else
            output << t.first << "__" << t.second << "\\" << std::endl;
    }
    std::cout << std::endl;
}

void get_codes_from_file(std::string path)
{
    std::ifstream inf(path);
    std::stringstream s_buf;
    if (!inf)
    {
        std::cerr << "File wasn't not found!" << std::endl;
        inf.close();
        exit(-2);
    }
    s_buf << inf.rdbuf();
    char *normal_string = (char*)calloc(s_buf.str().length(), sizeof(char));
    strcpy(normal_string, s_buf.str().c_str());
    char *token = strtok(normal_string, "\\");

    while (token != nullptr)
    {
        if (!strchr(token, '_'))
        {
            deleted_nulls = strlen(token);
            return;
        }

        char a;
        char *b = (char*)calloc(50, sizeof(char));
        sscanf(token, "%c __ %s", &a, b);
        new_codes[(std::string) b] = a;
        token = strtok(nullptr, "\\\n");
    }
}

void print_new_codes(std::string path)
{
    std::ofstream output(path);
    for (auto &t : new_codes)
        std::cout << t.first << " - " << t.second << std::endl;
    std::cout << std::endl;
}
