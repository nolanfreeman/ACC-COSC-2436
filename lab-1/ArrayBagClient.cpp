//

#include <climits> // INT_MAX
#include <iostream> // std::cout, std::cin
#include <string> // std::string

#include "ArrayBag.h" // ArrayBag<type>

void addOption(ArrayBag<int>& bag);
void findOption(ArrayBag<int>& bag, const bool& recursively=false);
int makeSelection(const int& low, const int& high);
void printList(const int* list, const int& size);
int promptOperation(const std::string& operation);
void sortOption(ArrayBag<int>& bag);

int main()
{
	ArrayBag<int> bag;
	// int items[] = {1, 33, 6, 9, 2, 65, 4, 29, 5, 8, 39, 88, 7, 25, 51, 3, 99, 14, 11, 10};
	int items[] {1, 33, 6, 9, 2, 65, 4, 29, 5, 8, 39};
	// int initialValueCount{20};
	int initialValueCount{11};
		
	std::cout << "\nAdding positive integers to the bag:\n";
	for (int i{0}; i < 11; ++i)
		bag.add(items[i]);

	printList(items, initialValueCount);

	// hold the menu option the user will select
	int selection{0};
	// true when the user decides to quit
	bool isDone{false};
	//
	bool autoDisplayContents{true};

	do // while (!done)
	{
		std::cout << '\n'
				  << "Main Menu:\n"
				  << "(1) Print bag contents\n"
				  << "(2) Add a value to bag\n"
				  << "(3) Remove value from bag\n"
				  << "(4) Find value in bag (iteratively)\n"
				  << "(5) Find value in bag (recursively)\n"
				  << "(6) Sort bag\n"
				  << "(7) Quit\n"
				  << "Please make a selection: ";

		selection = makeSelection(1, 7);

		switch (selection)
		{
			case 1:
				// print bag contents
				std::cout << "\nPrinting bag contents:\n";
				// does nothing; contents are autodisplayed after
				// each valid selection (unless the user quits)
				break;
			case 2:
				// Add value to bag
				addOption(bag);
				break;
			case 3:
				// Remove value from bag
				if (bag.remove(promptOperation("REMOVE")))
					std::cout << "Value removed.\n";
				else
					std::cout << "Value not in bag.\n";

				break;
			case 4:
				// Find value in bag iteratively
				findOption(bag, false); // false == !recursive
				break;
			case 5:
				// Find value in bag recursively
				findOption(bag, true); // true == recursive
				break;
			case 6:
				// Sort bag
				sortOption(bag);
				break;
			case 7:
				// quit
				std::cout << "\nQuitting...\nGoodbye.\n";
				isDone = true;
				autoDisplayContents = false;
				break;
			case -1:
				// Selection was predicably invalid
				// [[fallthrough]]; // explicit fallthrough (C++17)
			default:
				// Selection was invalid
				std::cout << "\nInvalid selection.\n";
				autoDisplayContents = false;
				break;
		}

		if (autoDisplayContents)
		{
			// convert the bag to a vector, which can be
			// used like a normal list since values are stored
			// contiguously in memory
			printList(&bag.toVector()[0], bag.getCurrentSize());
		}

		// reset the value to true,
		// in the event of an invalid selection
		autoDisplayContents = true;

	} while (!isDone);

   return 0;
   
}  // end main

//
void addOption(ArrayBag<int>& bag)
{
	int value{promptOperation("ADD")};

	std::cout << '\n';

	if (bag.contains(value))
	{
		std::cout << "Value already exists in bag.\n";
	}
	else
	{
		if (bag.add(value))
			std::cout << "Value Added.\n";
		else
			std::cout << "Value not added. Bag is full.\n";
	}
}

//
void sortOption(ArrayBag<int>& bag)
{
	// determine whether the bag was already sorted
	bool wasSorted{bag.isSorted()};

	if (!wasSorted)
	{
		std::cout << "\nSorting bag...\n";
		// sets bag::isBagSorted to true
	    bag.bubbleSort();
		std::cout << "Done. ";
	}

	// let the user know if it was already sorted, or not
	std::cout << "Bag is" << (wasSorted ? " already " : " ") << "sorted.\n";
}

//
void findOption(ArrayBag<int>& bag, const bool& recursively)
{
	int valueToFind{};

	if (!bag.isSorted())
	{
		std::cout << "\nYou must sort the bag before searching it.\nDo this now?\n"
		          << "(1) Yes\n"
				  << "(2) No\n"
				  << "Selection: ";

		// 1 == yes; 2 == no
		if (makeSelection(1, 2) == 1)
			sortOption(bag);
		else
			std::cout << "\nNot sorting. Returning to main menu...\n";
	}

	if (bag.isSorted())
	{
		valueToFind = promptOperation("FIND");

		bool found{};

		// search methods return -1 is value not found
		if (recursively)
			found = (bag.binarySearchRecursive(valueToFind) != -1);
		else
			found = (bag.binarySearchIterative(valueToFind) != -1);

		std::cout << "The value " << valueToFind
				  << (found ? " is " : " is not ")
				  << "in the bag.\n";
	}
}

//
int makeSelection(const int& low, const int& high)
{
	int selection{-1};

	// while input is not an integer
	// ie. cannot be pushed into the variable
	while (!(std::cin >> selection))
	{
		// clear fail bit && ignore extra characters
		// and newline left in input stream
		std::cin.clear();
		std::cin.ignore(1000, '\n');
		std::cout << "Please enter a positive Integer: ";
	}

	std::cin.ignore(1000, '\n');

	// verify the selection is within desired range
	if (!(selection >= low && selection <= high))
		selection = -1;

	return selection;
}

//
int promptOperation(const std::string& operation)
{
	std::cout << "\nWhat value would you like to " << operation << "? ";

	// INT_MAX allows user to input any number
	// that a signed integer can hold
	// (determined by computers architecture)
	return makeSelection(1, INT_MAX);
}

//
void printList(const int* list, const int& size)
{
	std::cout << "{ ";

	for (int i{0}; i < size; ++i)
	{
		// print each value of the list conditionally
		// adding ", " if value is not the last value
		std::cout << list[i] << ( i < size-1 ? ", " : "");
	}

	std::cout << " }\n";
}
