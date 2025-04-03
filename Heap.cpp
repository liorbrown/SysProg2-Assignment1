#include "Heap.hpp"
#include <stdexcept>

using namespace std;

void Heap::insert(const unsigned int val){
    Node* node = new Node(val);

    node->getNext() = this->head;
    this->head = node;
}

unsigned int Heap::extractMin(){
    if (this->isEmpty())
        throw runtime_error{"Heap is empty 🫤"};

    Node* minNode = this->head;

    for (Node* n = minNode->getNext(); n ; n = n->getNext())
        if (n->getVal() < minNode->getVal())
            minNode = n;
    
    unsigned int min = minNode->getVal();

    Node* prev = minNode->getPrev();
    Node* next = minNode->getNext();

    delete minNode;

    if (prev)
        prev->getNext() = next;

    if (next)
        next->getPrev() = prev;
    
    return min;
}
