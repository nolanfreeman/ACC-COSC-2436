#include "Node.h"

#include <string>

Node::Node(std::string line, Node* next=nullptr)
    : line(line), next(next)
{ }

Node* Node::getNext() const
{
    return next;
}

std::string Node::getValue() const
{
    return line;
}

void Node::setNext(Node* nextNode)
{
    next = nextNode;
}
