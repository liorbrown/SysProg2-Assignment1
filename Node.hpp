#pragma once

class Node{
    private:
        const unsigned int val;
        Node* next;
        Node* prev;
    public:
        Node(const unsigned int val): val(val), next(nullptr), prev(nullptr){}

        unsigned int getVal() const {return this->val;}
        Node* getNext() const{return this->next;}
        Node*& getNext() {return this->next;}
        Node* getPrev() const{return this->prev;}
        Node*& getPrev() {return this->prev;}
        static void destroy(Node*);
};