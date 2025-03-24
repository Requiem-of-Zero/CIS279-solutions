#ifndef BSTCHECKER_H
#define BSTCHECKER_H
using namespace std;
#include "Node.h"
#include <stack>
#include <tuple>
#include <unordered_set>

class BSTChecker {
public:
    static Node* CheckBSTValidity(Node* rootNode) {
        if (!rootNode) return nullptr;
        unordered_set<Node*> visitedSet;

        // Stack stores (current node, minNode, maxNode)
        stack<tuple<Node*, Node*, Node*> > nodeStack;
        nodeStack.push(make_tuple(rootNode, nullptr, nullptr));

        // Implementation of iterative DFS  
        while (!nodeStack.empty()) {
            auto currentTuple = nodeStack.top();
            nodeStack.pop();

            Node* node = get<0>(currentTuple);
            Node* minNode = get<1>(currentTuple);
            Node* maxNode = get<2>(currentTuple);

            if (visitedSet.find(node) != visitedSet.end()) {
                return node;  // Found a cycle!
            }

            // Mark current node as visited
            visitedSet.insert(node);

            if ((minNode && node->key <= minNode->key) || 
                (maxNode && node->key >= maxNode->key)) {
                return node; // Found a BST rule violation
            }

            if (node->left) {
                if (visitedSet.find(node->left) != visitedSet.end()) {
                    return node->left;  // Left child reappears in ancestor chain
                }
                nodeStack.push(make_tuple(node->left, minNode, node));
            }

            if (node->right) {
                if (visitedSet.find(node->right) != visitedSet.end()) {
                    return node->right;  // Right child reappears in ancestor chain
                }
                nodeStack.push(make_tuple(node->right, node, maxNode));
            }
        }

        return nullptr; // No violations found
    }
};

#endif
