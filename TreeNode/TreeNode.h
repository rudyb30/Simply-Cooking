#pragma once
#include <iostream>
#include <queue>
#include "Color.h"
using namespace std;

class TreeNode {
public:
    string recipeTitle;
    string recipeTime;
    string recipeIngredients;
    string recipeDescription;
    int relationVal;
    int val; // The value of a node
    Color color; // The color of a node.
    TreeNode* left;
    TreeNode* right;
    TreeNode* parent; //

    TreeNode(int val, string recipeTitle, string recipeTime, string recipeIngredients, string recipeDescription); // Constructor for TreeNode.
    TreeNode* uncle(); // Returns the pointer of a node's uncle.
    bool isOnLeft(); // Checks if node is on the left.
    TreeNode* sibling(); // Returns the pointer of a node's sibling.
    void moveDown(TreeNode* newParent); // Moves a node down and moves a node newParent, in its place.
    bool hasRedChild(); // Checks if a node's child's color is Red.
};

TreeNode::TreeNode(int val, string recipeTitle, string recipeTime, string recipeIngredients, string recipeDescription) : val(val), recipeTitle(recipeTitle), recipeTime(recipeTime), recipeIngredients(recipeIngredients),
recipeDescription(recipeDescription)
{
    parent = NULL;
    left = NULL;
    right = NULL; // Parent, left and right nodes are initialized to NULL,
    Color Red; // During insertion, the color of the node is set to Red.
}

TreeNode* TreeNode::uncle()
{
    // Case where no parent or grandparent exists. If neither exists, then return NULL because no uncle exists then.
    if (parent == NULL || parent->parent == NULL)
    {
        return NULL;
    }

    if (parent->isOnLeft()) // Case where a parent node has a left child.
    { // Then the uncle will be to the right of the grandparent.
        return parent->parent->right;
    }
    else // Case where a parent node does not have a left child.
    {
        return parent->parent->left; // Then the uncle will be to the left of the grandparent.
    }
}

bool TreeNode::isOnLeft()
{ // returns true if a node is specifically a left child of a parent.
    return this == parent->left;
}

    // returns pointer to sibling
TreeNode* TreeNode::sibling()
{
    if (parent == NULL) // Case where parent is NULL
    {
        return NULL; // Then return NULL because if no parent exists than no sibling exists.
    }
    if (isOnLeft()) // Case where a parent has a child to its left
    {
        return parent->right; // Then the sibling is classified as the parent's right child.
    }
    return parent->left; // Otherwise, the sibling is classified as the parent's left child.
}

void TreeNode::moveDown(TreeNode* newParent)
{
    if (parent != NULL) // Case where a parent node exists.
    {
        if (isOnLeft()) // Case where the newParent node has a child node to its left.
        { // Then the left child node becomes the newParent.
            parent->left = newParent;
        }
        else // Otherwise, the newParent node has a child to its right.
        { // Then the right child node becomes the newParent.
            parent->right = newParent;
        }
    }
    newParent->parent = parent; // newParent's parent node is set to the current parent node.
    parent = newParent; // The current parent node is then set to newParent, completing the moving down in the tree.
}

bool TreeNode::hasRedChild()
{ // Returns true if at least one of a node's children's colors is red. Otherwise, it returns false.
    return (left != NULL && left->color == Red) || (right != NULL && right->color == Red);
}
