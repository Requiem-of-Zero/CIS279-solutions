#ifndef EXTENDEDAVLNODE_H
#define EXTENDEDAVLNODE_H
#include "AVLNode.h"

class ExtendedAVLNode : public AVLNode {
private:
   int subtreeKeyCount;

public:
   ExtendedAVLNode(int nodeKey) : AVLNode(nodeKey) {
      subtreeKeyCount = 1;
   }
   
   virtual int GetSubtreeKeyCount() override {
      return subtreeKeyCount;
   }
   
   // Your code here
   void UpdateSubtreeKeyCount(){
      int leftCount = 0;
      int rightCount = 0;

      ExtendedAVLNode* left = (ExtendedAVLNode*) GetLeft();
      if(left){
         leftCount = left -> GetSubtreeKeyCount();
      }

      ExtendedAVLNode* right = (ExtendedAVLNode*) GetRight();
      if(right){
         rightCount = right -> GetSubtreeKeyCount();
      }
      subtreeKeyCount = 1 + leftCount + rightCount;
   }

      virtual void SetLeft(BSTNode* newLeftChild) override {
      AVLNode::SetLeft(newLeftChild);
      UpdateSubtreeKeyCount();
   }

   virtual void SetRight(BSTNode* newRightChild) override {
      AVLNode::SetRight(newRightChild);
      UpdateSubtreeKeyCount();
   }
};

#endif