#ifndef SORTEDNUMBERLIST_H
#define SORTEDNUMBERLIST_H
#include "Node.h"

class SortedNumberList {
private:
   // Optional: Add any desired private functions here

public:
   Node* head;
   Node* tail;

   SortedNumberList() {
      head = nullptr;
      tail = nullptr;
   }

   // Inserts the number into the list in the correct position such that the
   // list remains sorted in ascending order.
   void Insert(double number) {
      // Your code here
      Node* newNode = new Node(number);
    
    if (!head) { // Empty list
        head = newNode;
        tail = newNode;
        return;
    }
    
    Node* current = head;
    
    // Find insertion point
    while (current && current->GetData() < number) {
        current = current->GetNext();
    }
    
    if (!current) { // Insert at the end
        tail->SetNext(newNode);
        newNode->SetPrevious(tail);
        tail = newNode;
    } else if (current == head) { // Insert at the beginning
        newNode->SetNext(head);
        head->SetPrevious(newNode);
        head = newNode;
    } else { // Insert in the middle
        Node* prev = current->GetPrevious();
        prev->SetNext(newNode);
        newNode->SetPrevious(prev);
        newNode->SetNext(current);
        current->SetPrevious(newNode);
    }
   }

   // Removes the node with the specified number value from the list. Returns
   // true if the node is found and removed, false otherwise.
   bool Remove(double number) {
      // Your code here (remove placeholder line below)
      Node* current = head;
    
    // Find node to remove
    while (current && current->GetData() != number) {
        current = current->GetNext();
    }
    
    if (!current) { // Number not found
        return false;
    }
    
    if (current == head) { // Remove head
        head = current->GetNext();
        if (head) {
            head->SetPrevious(nullptr);
        } else { // List is now empty
            tail = nullptr;
        }
    } else if (current == tail) { // Remove tail
        tail = current->GetPrevious();
        tail->SetNext(nullptr);
    } else { // Remove middle node
        Node* prev = current->GetPrevious();
        Node* next = current->GetNext();
        prev->SetNext(next);
        next->SetPrevious(prev);
    }
    
    delete current;
    return true;
   }
};

#endif
