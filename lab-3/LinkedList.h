#ifndef LINKED_LIST_
#define LINKED_LIST_

#include <string>
#include <vector>

#include "ListInterface.h"
#include "Node.h"

class LinkedList : ListInterface
{
    private:
        Node* headPtr;
        int numItems;

    public:
        LinkedList();
        virtual ~LinkedList();

        bool addNode(const std::string& value);
        auto toVector() const -> std::vector<std::string>;
        int getNumItems() const;
};

#include "LinkedList.cpp"

#endif // LINKED_LIST_
