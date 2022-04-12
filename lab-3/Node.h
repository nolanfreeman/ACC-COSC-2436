#ifndef NODE_
#define NODE_

#include <string>

class Node
{
    private:
        std::string line;
        Node* next;

    public:
        Node() = delete;
        Node(std::string line, Node* next);

        Node* getNext() const;
        std::string getValue() const;
        void setNext(Node* nextNode);

};

#include "Node.cpp"

#endif // NODE_
