#include <iostream>
#include <string>
#include "PriorityQueue.h"
#include "H_tree.h"
#include "Compress_Decompress.h"
#include "Words.h"


// commands for check:
// du -sh CLionProjects/PeppeHuffman/tests/input1.txt
// du -sh CLionProjects/PeppeHuffman/tests/output1.txt
// du -sh CLionProjects/PeppeHuffman/tests/output2.txt


// ex path:
// /Users/nikolai/CLionProjects/PeppeHuffman/tests/input1.txt
// /Users/nikolai/CLionProjects/PeppeHuffman/tests/output1.txt


enum Operation
{
    Compress,
    Decompress
};

Operation get_operation(const std::string& input)
{
    if (input == "compress")
        return Compress;
    else if (input == "decompress")
        return Decompress;
    else
    {
        std::cerr << "Incorrect operation, check the input!" << std::endl;
        exit(-1);
    }
}

std::string get_file_path()
{
    std::string path;
    std::cout << "Write full path to file: ";
    std::cin >> path;
    return path;
}

void start_operation(Operation oper, std::string path)
{
    HuffNode *tree_h;
    PriorityQueue queue_h;
    std::string input;
    std::string compress_input;
    switch(oper)
    {
        case Compress:
            std::cout << "\nCompressing...";

            input = get_input_from_file(path);
            queue_h = getAllSymbols(input);

            printQueue(queue_h.head, "/Users/nikolai/CLionProjects/PeppeHuffman/tests/queue_output.txt");
            std::cout << "queue_output.txt was created!";

            tree_h = create_h_tree(queue_h);
            get_codes(tree_h, "");
            print_codes("/Users/nikolai/CLionProjects/PeppeHuffman/tests/Codes.txt");
            std::cout << "Codes.txt was created!\n";

            compress_file("/Users/nikolai/CLionProjects/PeppeHuffman/tests/output1.txt", input);
            std::cout << "Compressed successfully, check the folder!" << std::endl;
            break;
        case Decompress:
            std::cout << "Decompressing..." << std::endl;

            compress_input = read_compressed_file(path);

            get_codes_from_file("/Users/nikolai/CLionProjects/PeppeHuffman/tests/Codes.txt");
            //print_new_codes("");
            decompress_file("/Users/nikolai/CLionProjects/PeppeHuffman/tests/output2.txt", compress_input);
            std::cout << "Decompressed successfully, check the folder!" << std::endl;
            break;
        default:
            break;
    }
}


int main()
{
    std::string input;
    std::cout << "Choose an operation: 'compress' or 'decompress': ";
    std::cin >> input;
    start_operation(get_operation(input), get_file_path());
    return 0;
}