// ACC-COSC-2436 Lab 3 - Linked Lists
// Author: Nolan Freeman Abbbott

// PROGRAM DESCRIPTION:
// --- x
// --- x

#include <fstream>
#include <iostream>
#include <string>

#include <LinkedList>

int main() {

    LinkedList<std::string> list;
    ifstream file;
    std::string filename {};

    bool validFile {false};
    while (!validFile)
    {
        std::cin >> filename;

        file.open(filename)

        if (!file)
            std::cout << "File: \"" << filename << "\" could not be found." << '\n';
        else
            validFile = true;
    }

    std::string line {};
    int lineCount {0};
    while (file != EOF)
    {
        std::getline(line);

        list.addNode(line);
        lineCount++;
    }

    std::cout << "Parsed file: \"" << filename << "\" containing " << lineCount << " lines." << '\n';

    // display

    std::vector vList = list.toVector();
    int nodeCount {0};
    for (auto node : vList)
    {
        std::cout << node << '\n';
        nodeCount++;
    }

    std::cout << nodeCount << " unique nodes printed from " << lineCount << " lines of input.";

    file.close();

    return 0;
}
