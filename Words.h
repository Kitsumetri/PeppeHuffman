#pragma once
#include "H_tree.h"
#include "H_Node.h"

void get_codes(HuffNode *tree, std::string code);
void get_codes_from_file(std::string path);
void print_codes(std::string path);
std::string get_elem_code(char elem);

void print_new_codes(std::string path);
char get_new_elem_code(std::string elem);
bool elem_exists_with_new_code(std::string elem);