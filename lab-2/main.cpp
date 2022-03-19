// PROGRAM DESCRIPTION
//
//
//

/** @file main.cpp */

#include <fstream>
#include <iostream>
#include <string>

#include "LinkedStack.h"

int main() {
    LinkedStack<int> stack;

    std::string filename;
    std::ifstream file;

    // prompt for a file name until a valid one is found and able to be opened.
    bool validFile{false};
    while (!validFile)
    {
        std::cout << "Enter the name of an auction file: ";
        std::getline(std::cin, filename);

        file.open(filename);

        // verify if the file can be opened.
        // continue if no, break loop if yes
        if (!file)
            std::cout << "Filename: \"" << filename << "\" doesn't exist, or is ill-formatted.\n";
        else
            validFile = true;
    } // end while

    std::cout << "\nOpening file: \"" << filename << '"' << "\n\n";

    std::string auctionTitle{""};
    std::getline(file, auctionTitle);

    int bid{0};
    while(file >> bid)
    {
        if (stack.isEmpty() || bid > stack.peek())
            stack.push(bid);
    } // end while

    // print the value of the last added entry, which will always be the largest.
    std::cout << auctionTitle << " sold for $" << stack.peek() << '\n';

    // clean up files and dynamic memory
    file.close();

    return 0;
} // end main
