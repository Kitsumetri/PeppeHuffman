#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <bitset>
#include "Compress_Decompress.h"
#include "Words.h"


std::string get_input_from_file(std::string path)
{
    std::ifstream inf(path);
    std::stringstream buffer;
    if (!inf)
    {
        std::cerr << "File wasn't not found!" << std::endl;
        inf.close();
        exit(-2);
    }
    buffer << inf.rdbuf();
    return buffer.str();
}

void compress_file(std::string path, std::string &input)
{
    std::ofstream output(path, std::ios::binary);
    if (!output)
    {
        std::cerr << "Error!" << std::endl;
        output.close();
        exit(-3);
    }

    std::string total;
    std::vector <unsigned char> bin; //just a container for binary words
    char elem;

    for (int i = 0; i < input.length(); ++i)
    {
        elem = input[i];
        total += get_elem_code(elem);
        if (total.length() >= 8)
        {
            bin.push_back(std::bitset<8>(total.substr(0, 8)).to_ulong());
            total = total.substr(8, total.length() - 8);
        }
    }
    std::ofstream append_output("/Users/nikolai/CLionProjects/PeppeHuffman/tests/Codes.txt", std::ios::app);
    while (total.length() && total.length() < 8)
    {
        total += "0";
        append_output << "0";
    }
    append_output << std::endl;
    append_output.close();

    bin.push_back(std::bitset<8>(total.substr(0, total.length())).to_ulong());

    for (unsigned char b : bin)
        output.write((char*)&b, sizeof(char));
}

std::string read_compressed_file(std::string path)
{
    std::ifstream inf(path, std::ios::binary);
    if (!inf)
    {
        std::cerr << "File not found!" << std::endl;
        inf.close();
        exit(-2);
    }
    std::string temp;
    std::vector <char> buffer(std::istreambuf_iterator <char> (inf), {});

    for (char b: buffer)
        temp += std::bitset<8>(b).to_string();

    return temp;
}

void decompress_file(std::string path, std::string &data)
{
    std::ofstream ouf(path);
    if (!ouf)
    {
        std::cerr << "Error!" << std::endl;
        ouf.close();
        exit(-3);
    }

    std::string substr;
    extern int deleted_nulls;

    for (int i = 0; i < data.length(); ++i)
        for (int j = i+1; j < data.length(); ++j)
        {
            if (i == data.length() - deleted_nulls)
            {
                ouf.close();
                return;
            }
            substr = data.substr(i, j-i);
            if (elem_exists_with_new_code(substr))
            {
                i = j;
                ouf << get_new_elem_code(substr);
            }
        }
    ouf.close();
}