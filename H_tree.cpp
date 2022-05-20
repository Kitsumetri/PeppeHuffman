#include "H_Node.h"
#include "PriorityQueue.h"
#include "H_tree.h"

HuffNode* create_h_tree(PriorityQueue &queue_h)
{
    while (queue_h.size != 1)
    {
        HuffNode *node1 = getTopFromQueue(queue_h);
        popFromQueue(queue_h);
        HuffNode *node2 = getTopFromQueue(queue_h);
        popFromQueue(queue_h);
        pushToQueue(queue_h, getNodes(node1, node2));
    }
    HuffNode *result = getTopFromQueue(queue_h);
    popFromQueue(queue_h);
    return result;
}