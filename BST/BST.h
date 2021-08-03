#pragma once
#include <iostream>
#include <queue>
#include "TreeNode.h"
using namespace std;

class BinarySearchTree {
public:
   TreeNode * root; // Represents root of the RedBlack tree, or the root node of a subtree.

    BinarySearchTree(); // Constructor
  TreeNode* search(int recipeNumber); // Searches for a specific value
    void insert(int recipeNumber, string recipeName, string minutes, string ingredients, string steps); // Inserts a new node into the tree.
    void inorder(TreeNode* node, string &s);
    string printInOrder(); // Sets up to print in order traversal of tree.
private:
    string splitString (string ingredientData);
};


BinarySearchTree::BinarySearchTree()
{
    root = NULL; // Initializes root to NULL.
} // Time complexity is O(1).

TreeNode* BinarySearchTree::search(int recipeNumber)
{
   TreeNode* temp = root; // A temp node is set at the root.
    while (temp != NULL) // Recurve through tree until temp == NULL
    {
        if (recipeNumber < temp->val) // Case where recipeNumber is smaller than value at temp
        {
            if (temp->left == NULL) // No more nodes to left of current node, so break. Current node is smallest recipeNumber.
            {
                break;
            }
            else // Otherwise, recurve through left.
            {
                temp = temp->left;
            }
        }
        else if (recipeNumber == temp->val) // Current node matches temp->val, so break and return this node.
        {
            break;
        }
        else // Case where recipeNumber is larger than value at temp.
        {
            if (temp->right == NULL) // No more nodes to right of current node, so break. Current node is largest recipeNumber.
            {
                break;
            }
            else // Otherwise, recurve through right.
            {
                temp = temp->right;
            }
        }
    }
    return temp;
} // Worst case time complexity is O(n), or O(height of the tree) for BST search and insertion. Assumes only one node in each height level of the tree.

void BinarySearchTree::insert(int recipeNumber, string recipeName, string minutes, string ingredients, string steps)
{
    TreeNode * newNode = new TreeNode(recipeNumber, recipeName, minutes, ingredients, steps); // Creates a new node in the tree.
    if (root == NULL) // if root is NULL, just insert a new value at the root.
    {
        root = newNode;
    }
    else
    {
        TreeNode* temp = search(recipeNumber); // Search for nonexistent recipeNumber to traverse through the tree.
        if (temp->val == recipeNumber)
        { // Case where value to insert already exists.
            return;
        } // Otherwise...

        if (recipeNumber < temp->val) // If recipeNumber is smaller than temp->val, newNode is to the left of temp.
        {
            temp->left = newNode;
        }
        else // If recipeNumber is larger than temp->val, newNode is to the right of temp.
        {
            temp->right = newNode;
        }
    }
} // Worst case time complexity is O(n), or O(height of the tree) for BST search and insertion. Assumes only one node in each height level of the tree.

void BinarySearchTree::inorder(TreeNode* node, string &s)
{
    if (node == NULL) // Case where node is NULL and that we're past the leaf of a tree.
    {
        return; // Then we return because we have nothing left to traverse.
    }
    inorder(node->left,s); // Recurve first through the left most nodes of the tree.
     s+= "✔︎" + node->recipeTitle + "\n" +"Time " + "▷ "+node->recipeTime + " " + "minutes" +"\n" + "Ingredients " + "▷ "+splitString(node -> recipeIngredients)  + "\n" + "\n" +"Instructions " + "▷ " + splitString(node->recipeDescription) + "\n\n";
     // This just prints out their numbers, but we could set it up to print out their names.
    inorder(node->right, s); // Recurses through the right most nodes of the tree.
        
}
string BinarySearchTree::printInOrder()
{
        string x = "";
        inorder(root, x);
    
    return x;
} // O(# of nodes(recipes) in BST * node->ingredients.size()) in worst case as it calls on that function.

string BinarySearchTree::splitString (string ingredientData){
        //function that breaks the ingredients string into a vector of ingredients
        stringstream sstream(ingredientData);
        string ingredients = "";
        string ingredient;
        int count = 0;
        char delimiter = '\'';

        getline(sstream, ingredient, delimiter);
        while (getline(sstream, ingredient, delimiter))
        {
            if (count % 2 == 0)
            {
                ingredients += ingredient + ", ";
            }
            count++;
        }

        return ingredients.erase(ingredients.size() - 2);
    }
