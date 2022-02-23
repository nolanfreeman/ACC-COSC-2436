#include "ArrayBag.h"
#include <iostream>
#include <cstddef>

template<class ItemType>
void ArrayBag<ItemType>::bubbleSort()
{
    int min{0};
    for (int low{0}; low < itemCount-1; ++low)
    {
        min = low;
        for (int cur{low+1}; cur < itemCount; ++cur)
            if (items[cur] < items[min])
                min = cur;

        int temp{items[low]};
        items[low] = items[min];
        items[min] = temp;
    } // end for
    isBagSorted = true;
} // end bubbleSort

template<class ItemType>
int ArrayBag<ItemType>::binarySearchIterative(const ItemType& value) const
{
    bool valueFound{false};

    int leftBound{0},
        rightBound{itemCount-1},
        midpoint{};

    do { // while: !found, and there are still values to search through
        midpoint = leftBound + (rightBound - leftBound) / 2;

        if (value == items[midpoint])
            valueFound = true;
        else if (value > items[midpoint])
            leftBound = midpoint+1;
        else if (value < items[midpoint])
            rightBound = midpoint-1;

    } while (!valueFound && (leftBound <= rightBound));

    return valueFound ? midpoint : -1;
} // end binarySearchIterative

template<class ItemType>
int ArrayBag<ItemType>::binarySearchRecursive(const ItemType& value) const
{
    int leftBound{0},
        rightBound{itemCount-1},
        midpoint{};

    return binarySearchRecursiveHelper(value, leftBound, rightBound, midpoint);
} // end binarySearchRecursive

template<class ItemType>
int ArrayBag<ItemType>::binarySearchRecursiveHelper(const ItemType& value, int& leftBound, int& rightBound, int& midpoint) const
{
    midpoint = leftBound + (rightBound - leftBound) / 2;
    bool valueFound{false};

    if (leftBound > rightBound)
    {
        midpoint = -1;
        valueFound = true;
    }
    else
    {
        if (value == items[midpoint])
            valueFound = true;
        else if (value > items[midpoint])
            leftBound = midpoint+1;
        else if (value < items[midpoint])
            rightBound = midpoint-1;
    } // end if

    return valueFound ? midpoint
                      : binarySearchRecursiveHelper(value, leftBound, rightBound, midpoint);
} // end binarySearchRecursiveHelper

template<class ItemType>
bool ArrayBag<ItemType>::isSorted() const
{
    return this->isBagSorted;
} // end isSorted

template<class ItemType>
ArrayBag<ItemType>::ArrayBag(): itemCount(0), maxItems(DEFAULT_CAPACITY), isBagSorted(false)
{
}  // end default constructor

template<class ItemType>
int ArrayBag<ItemType>::getCurrentSize() const
{
	return itemCount;
}  // end getCurrentSize

template<class ItemType>
bool ArrayBag<ItemType>::isEmpty() const
{
	return itemCount == 0;
}  // end isEmpty

template<class ItemType>
bool ArrayBag<ItemType>::add(const ItemType& newEntry)
{
	bool hasRoomToAdd = (itemCount < maxItems);
	if (hasRoomToAdd)
	{
		items[itemCount] = newEntry;
		itemCount++;
        // added to simply client interface
        isBagSorted = false;
	}  // end if
    
	return hasRoomToAdd;
}  // end add

template<class ItemType>
bool ArrayBag<ItemType>::remove(const ItemType& anEntry)
{
   int locatedIndex = getIndexOf(anEntry);
	bool canRemoveItem = !isEmpty() && (locatedIndex > -1);
	if (canRemoveItem)
	{
		itemCount--;
		items[locatedIndex] = items[itemCount];
	}  // end if
    
	return canRemoveItem;
}  // end remove

template<class ItemType>
void ArrayBag<ItemType>::clear()
{
	itemCount = 0;
}  // end clear

template<class ItemType>
int ArrayBag<ItemType>::getFrequencyOf(const ItemType& anEntry) const
{
   int frequency = 0;
   int curIndex = 0;       // Current array index
   while (curIndex < itemCount)
   {
      if (items[curIndex] == anEntry)
      {
         frequency++;
      }  // end if
      
      curIndex++;          // Increment to next entry
   }  // end while
   
   return frequency;
}  // end getFrequencyOf

template<class ItemType>
bool ArrayBag<ItemType>::contains(const ItemType& anEntry) const
{
	return getIndexOf(anEntry) > -1;
}  // end contains

template<class ItemType>
std::vector<ItemType> ArrayBag<ItemType>::toVector() const
{
   std::vector<ItemType> bagContents;
	for (int i = 0; i < itemCount; i++)
		bagContents.push_back(items[i]);
      
   return bagContents;
}  // end toVector

// private
template<class ItemType>
int ArrayBag<ItemType>::getIndexOf(const ItemType& target) const
{
	bool found = false;
   int result = -1;
   int searchIndex = 0;
   
   // If the bag is empty, itemCount is zero, so loop is skipped
   while (!found && (searchIndex < itemCount))
   {
      if (items[searchIndex] == target)
      {
         found = true;
         result = searchIndex;
      } 
      else
      {
         searchIndex++;
      }  // end if
   }  // end while
   
   return result;
}  // end getIndexOf

