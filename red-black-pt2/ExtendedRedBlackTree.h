#ifndef EXTENDEDREDBLACKTREE_H
#define EXTENDEDREDBLACKTREE_H
using namespace std;
#include "RedBlackTree.h"
#include "ExtendedRBTNode.h"

class ExtendedRedBlackTree : public RedBlackTree {
protected:
   virtual BSTNode* MakeNewNode(int key) override {
      return new ExtendedRBTNode(key);
   }

   

public:
   virtual void InsertNode(BSTNode* node) override {
      BinarySearchTree::InsertNode(node);
      ExtendedRBTNode* current = (ExtendedRBTNode*)node;
      while (current) {
         current->UpdateSubtreeKeyCount();
         current = (ExtendedRBTNode*)current->GetParent();
      }
      ((RBTNode*)node)->color = RBTNode::REDCOLOR;
      InsertionBalance((RBTNode*)node);
   }

   virtual bool RemoveNode(BSTNode* nodeToRemove) override {
      bool result = RedBlackTree::RemoveNode(nodeToRemove);
      ExtendedRBTNode* current = (ExtendedRBTNode*)GetRoot();
      UpdateAllCounts(current);
      return result;
   }

   void UpdateAllCounts(ExtendedRBTNode* node) {
      if (!node) return;
      if (node->GetLeft()) UpdateAllCounts((ExtendedRBTNode*)node->GetLeft());
      if (node->GetRight()) UpdateAllCounts((ExtendedRBTNode*)node->GetRight());
      node->UpdateSubtreeKeyCount();
   }

   virtual int GetNthKey(int n) override {
      ExtendedRBTNode* current = (ExtendedRBTNode*)root;
      while (current) {
         int leftCount = current->GetLeft() ? current->GetLeft()->GetSubtreeKeyCount() : 0;
         if (n < leftCount) {
            current = (ExtendedRBTNode*)current->GetLeft();
         }
         else if (n > leftCount) {
            n -= leftCount + 1;
            current = (ExtendedRBTNode*)current->GetRight();
         }
         else {
            return current->GetKey();
         }
      }
      throw runtime_error("Invalid n in GetNthKey");
   }
};

#endif