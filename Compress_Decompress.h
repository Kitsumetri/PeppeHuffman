#pragma once

std::string get_input_from_file(std::string path);
void compress_file(std::string path, std::string &input);
std::string read_compressed_file(std::string path);
void decompress_file(std::string path, std::string &data);