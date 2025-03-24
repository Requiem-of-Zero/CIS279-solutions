#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include "Node.h"
#include "SortedNumberList.h"
using namespace std;

void PrintList(SortedNumberList& list);
vector<string> SpaceSplit(string source);

int main(int argc, char *argv[]) {
    // Read the line of input numbers
    string inputLine;
    getline(cin, inputLine);

    // Split on space character
    vector<string> terms = SpaceSplit(inputLine);

    // Insert each value and show the sorted list's contents after each insertion
    SortedNumberList list;
    for (auto term : terms) {
        try {
            double number = stod(term);
            cout << "List after inserting " << number << ": " << endl;
            list.Insert(number);
            PrintList(list);
        } catch (const invalid_argument& e) {
            cerr << "Invalid input: '" << term << "' is not a valid number." << endl;
        }
    }

    getline(cin, inputLine);
    terms = SpaceSplit(inputLine);

   // Remove each value
   for (auto term : terms) {
      double number = stod(term);
      cout << "List after removing " << number << ": " << endl;
      list.Remove(number);
      PrintList(list);
   }


    return 0;
}

void PrintList(SortedNumberList& list) {
    Node* node = list.head;
    while (node) {
        cout << node->GetData() << " ";
        node = node->GetNext();
    }
    cout << endl;
}

vector<string> SpaceSplit(string source) {
    vector<string> result;
    size_t start = 0;
    for (size_t i = 0; i < source.length(); i++) {
        if (' ' == source[i]) {
            if (start != i) {  // Avoid empty strings from extra spaces
                result.push_back(source.substr(start, i - start));
            }
            start = i + 1;
        }
    }
    if (start < source.length()) {
        result.push_back(source.substr(start));
    }
    return result;
}


// Read the input line with numbers to remove
