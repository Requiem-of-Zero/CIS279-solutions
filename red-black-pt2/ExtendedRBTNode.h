#ifndef EXTENDEDRBTNODE_H
#define EXTENDEDRBTNODE_H

#include "RBTNode.h"

class ExtendedRBTNode : public RBTNode {
private:
   int subtreeKeyCount;

public:
   ExtendedRBTNode(int nodeKey) : RBTNode(nodeKey) {
      subtreeKeyCount = 1;
   }
   
   virtual int GetSubtreeKeyCount() override {
      return subtreeKeyCount;
   }

   void UpdateSubtreeKeyCount() {
      int leftCount = GetLeft() ? GetLeft()->GetSubtreeKeyCount() : 0;
      int rightCount = GetRight() ? GetRight()->GetSubtreeKeyCount() : 0;
      subtreeKeyCount = 1 + leftCount + rightCount;
   }

   virtual void SetLeft(BSTNode* newLeftChild) override {
      RBTNode::SetLeft(newLeftChild);
      UpdateSubtreeKeyCount();
   }
   // Your code here
   virtual void SetRight(BSTNode* newRightChild) override {
      RBTNode::SetRight(newRightChild);
      UpdateSubtreeKeyCount();
   }
};

#endif