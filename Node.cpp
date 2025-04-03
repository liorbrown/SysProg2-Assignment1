#include "Node.hpp"

void Node::destroy(Node* node){
    if (node){
        destroy(node->next);
        delete node;
    }
}