#include <iostream>
#include <fstream>
#include <string>
#include "PriorityQueue.h"

void pushToQueue(PriorityQueue &queue, HuffNode value)
{
    if (queue.size == 0)
    {
        auto *node = new QueueNode;
        node->value = new HuffNode;
        *(node->value) = value;
        queue.head = node;
        queue.size++;
        return;
    }

    QueueNode *temp_node = queue.head;

    while ((temp_node->next != nullptr)
           && (*(temp_node->next->value) < value))
        temp_node = temp_node->next;

    auto *node = new QueueNode;
    node->value = new HuffNode;
    *(node->value) = value;

    if (value < *(queue.head->value))
    {
        node->next = queue.head;
        queue.head = node;
    }
    else
    {
        node->next = temp_node->next;
        temp_node->next = node;
    }
    queue.size++;
}
HuffNode *getTopFromQueue(PriorityQueue &queue) { return queue.head->value; }
void popFromQueue(PriorityQueue &queue)
{
    queue.head = queue.head->next;
    queue.size--;
}
PriorityQueue getAllSymbols(std::string &input)
{
    HuffNode symbols[255];
    for (int i = 0; i < 255; ++i)
        symbols[i].sym = (char)i;

    for (char s : input)
        symbols[s].frequency += 1;

    PriorityQueue current_symbols;

    for (HuffNode &symbol : symbols)
        if (symbol.frequency != 0)
            pushToQueue(current_symbols, symbol);

    return current_symbols;
}
void printQueue(QueueNode *queue_h,std::string out_file)
{
    std::ofstream output(out_file);
    while (queue_h != nullptr)
    {
        HuffNode *sym = queue_h->value;
        if (out_file.empty())
            std::cout << sym->sym << " : " << sym->frequency << std::endl;
        else
            output << sym->sym << " : " << sym->frequency << "\\" << std::endl;
        queue_h = queue_h->next;
    }
    std::cout << std::endl;
}