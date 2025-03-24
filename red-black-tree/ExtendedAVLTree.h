#ifndef EXTENDEDAVLTREE_H
#define EXTENDEDAVLTREE_H
using namespace std;
#include "ExtendedAVLNode.h"
#include "AVLTree.h"

class ExtendedAVLTree : public AVLTree {
protected:
   virtual BSTNode* MakeNewNode(int key) override {
      return new ExtendedAVLNode(key);
   }

   virtual void InsertNode(BSTNode* node) override {
      AVLTree::InsertNode(node);

      ExtendedAVLNode* current = (ExtendedAVLNode*) node;
      while (current) {
         current->UpdateSubtreeKeyCount();
         current = (ExtendedAVLNode*) current->GetParent();
      }
   }

   virtual bool RemoveNode(BSTNode* nodeToRemove) override {
      if (!nodeToRemove) return false;

      BSTNode* parent = nodeToRemove->GetParent();
      bool removed = AVLTree::RemoveNode(nodeToRemove);

      ExtendedAVLNode* current = (ExtendedAVLNode*) parent;
      while (current) {
         current->UpdateSubtreeKeyCount();
         current = (ExtendedAVLNode*) current->GetParent();
      }

      return removed;
   }

public:
   ExtendedAVLTree() : AVLTree() {}

   virtual int GetNthKey(int n) override {
      ExtendedAVLNode* current = (ExtendedAVLNode*) root;

      while (current) {
         int leftCount = current->GetLeft() ? ((ExtendedAVLNode*) current->GetLeft())->GetSubtreeKeyCount() : 0;
         if (n < leftCount) {
            current = (ExtendedAVLNode*) current->GetLeft();
         } else if (n == leftCount) {
            return current->GetKey();
         } else {
            n -= (leftCount + 1);
            current = (ExtendedAVLNode*) current->GetRight();
         }
      }

      throw out_of_range("n is out of range in GetNthKey()");
   }
};

#endif
