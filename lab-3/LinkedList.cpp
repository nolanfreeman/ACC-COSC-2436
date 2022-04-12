#include "LinkedList.h"

#include <iostream>
#include <string>
#include <vector>

LinkedList::LinkedList()
    : headPtr(nullptr), numItems(0)
{ }

LinkedList::~LinkedList()
{
    while (headPtr != nullptr)
    {
        Node* del {headPtr};
        headPtr = headPtr->getNext();

        del->setNext(nullptr);
        delete del;
    }

    numItems = 0;
    headPtr = nullptr;
}

bool LinkedList::addNode(const std::string& valueToInsert)
{
    bool isDuplicate {false};

    if (numItems == 0)
    {
        headPtr = new Node(valueToInsert);
        numItems++;
    }
    else
    {
        Node* curr {headPtr};
        Node* prev {nullptr};

        while (curr != nullptr && curr->getValue() <= valueToInsert)
        {
            prev = curr;
            curr = curr->getNext();
        }

        if (prev != nullptr)
            isDuplicate = (prev->getValue() == valueToInsert);

        if (!isDuplicate)
        {
    //std::cout << "-------------------------------\n";
    //std::cout << valueToInsert << '\n';
            Node* newNode {new Node(valueToInsert)};

            if (prev == nullptr)
            {
                newNode->setNext(headPtr);
                headPtr = newNode;
            }
            else
            {
                prev->setNext(newNode);
                newNode->setNext(curr);
            }
            numItems++;
        }
    }

    // std::cout << "-------------------------------\n";
    // std::vector<std::string> vList = toVector();
//
    // // loop through each value in the vector
    // // assigning its data to the variable "node"
    // int counter{0};
    // for (auto node : vList)
    // {
        // // print the value of the next element
        // std::cout << ++counter << ": " << node << '\n';
    // }
    // std::cout << "-------------------------------\n\n";

    return !isDuplicate;
}

auto LinkedList::toVector() const -> std::vector<std::string>
{
    std::vector<std::string> oVect;

    Node* curr {headPtr};

    while (curr != nullptr)
    {
        oVect.push_back(curr->getValue());
        curr = curr->getNext();
    }

    return oVect;
}

int LinkedList::getNumItems() const
{
    return numItems;
}
