#pragma once
#include <iostream>
#include <queue>
#include "Color.h"
#include "TreeNode.h"
using namespace std;

class RedBlackTree {
public:
    TreeNode* root; // Represents root of the RedBlack tree, or the root node of a subtree.

    RedBlackTree(); // Constructor
    void leftRotate(TreeNode* node); // Left rotates a node.
    void rightRotate(TreeNode* node); // Right rotates a node.
    void swapColors(TreeNode* node1, TreeNode* node2); // Swaps the colors between two nodes.
    void swapValues(TreeNode* replacingNode, TreeNode* node); // Swaps the values between two nodes.
    void fixRedToRed(TreeNode* node); // Fixes the case where two red nodes are connected
    TreeNode* successor(TreeNode* x); // Finds a node that does not have a left child to be the next successor node for a node that is to be deleted, when 2 children nodes exist.
    TreeNode* BSTreplace(TreeNode* x); // Finds a node that replaces a node that is to be deleted.
    void deleteNode(TreeNode* node); // Deletes this particular node in the tree.
    void fixDoubleBlack(TreeNode* x); // Fixes the case where two black nodes would be or are next to each other in the tree.
    TreeNode* search(int recipeNumber); // Searches for a specific value
    void
    insert(int recipeNumber, string recipeTitle, string recipeTime, string recipeIngredients, string recipeDescription,
           double d); // Inserts a new node into the tree.
    void deleteNodeValue(int recipeNumber); // Deletes the node with the given recipeNumber
    void inorder(TreeNode* node, string &s); // Recurves through tree in an inorder traversal.
   string printInOrder(); // Sets up to print in order traversal of tree.
private:
    string splitString(string ingredientData);
};

RedBlackTree::RedBlackTree()
{
    root = NULL; // Initializes root to NULL.
}

void RedBlackTree::leftRotate(TreeNode* node)
{
    TreeNode* newParent = node->right; // The new parent is initialized to be the node's right child. This is to help with rotation.
    if (node == root) // If the current node is the root, we update it to become the newParent.
    {
        root = newParent;
    }

    node->moveDown(newParent); // We move down the node's newParent to help with the rotation.

    // We set node's right to newParent's left.
    node->right = newParent->left;
    if (newParent->left != NULL) // Case where newParent's left node is not NULL.
    {
        newParent->left->parent = node; // Set the parent node of newParent's left to node.
    }

    newParent->left = node; // Finally, set newParent's left to node to complete the rotation.
}

void RedBlackTree::rightRotate(TreeNode* node)
{
    TreeNode* newParent = node->left; // The new parent is initialized to be the node's left child. This is to help with rotation.
    if (node == root) // If the current node is the root, we update it to become the newParent.
    {
        root = newParent;
    }

    node->moveDown(newParent); // We move down the node's newParent to help with the rotation.

    // We set node's left child to newParent's right child.
    node->left = newParent->right;
    
    if (newParent->right != NULL) // Case where newParent's right child is not NULL.
    {
        newParent->right->parent = node; // Set the parent node of newParent's right child to node.
    }

    newParent->right = node; // Finally, set newParent's right child to node to complete the rotation.
}

void RedBlackTree::swapColors(TreeNode* node1, TreeNode* node2)
{
    Color temp; // Declare a temp color and initialize it to node1's color.
    temp = node1->color;
    node1->color = node2->color; // Set node1's color to node2's and node2's color to temp to complete the swap.
    node2->color = temp;
}

void RedBlackTree::swapValues(TreeNode* replacingNode, TreeNode* node)
{
    int temp; // Declare a temp integer and initialize it to replacingNode's val.
    temp = replacingNode->val;
    replacingNode->val = node->val; // Set replacingNode's val to node's val and node's val to temp to complete the swap.
    node->val = temp;
}

void RedBlackTree::fixRedToRed(TreeNode* node)
{
    if (node == root) // Case where node is just the root. Makes it black and returns.
    {
        node->color = Black;
        return;
    }

    // We initialize parent, grandparent, and uncle
    TreeNode* parent = node->parent;
    TreeNode* grandparent = parent->parent;
    TreeNode* uncle = node->uncle();

    if (parent->color != Black)  // For case where the color of the parent is not black, but red.
    {
        if (uncle != NULL && uncle->color == Red)  // Case where uncle exists and that its color is red.
        {
            // uncle red, perform recoloring and recurse
            parent->color = Black;
            uncle->color = Black; // Set the parent and uncle colors to black and the grandparent's color to red.
            grandparent->color = Red;
            fixRedToRed(grandparent); // Recurve at the grandparent's node until the tree is fixed.
        }
        else // Otherwise if the uncle's color is Black, perform rotations.
        {
            // Else perform LR, LL, RL, RR
            if (parent->isOnLeft()) // Case where parent has a left child
            {
                if (node->isOnLeft()) // Case where node has a left child.
                { // This is a left right case for rotations.
                    swapColors(parent, grandparent); // We swap the colors of the parent and the grandparent to balance the tree.
                }
                else // Otherwise the node doesn't have a left child.
                { // This is a left left case for rotations.
                    leftRotate(parent); // We left rotate the parent and swap colors between the current node and the grandparent.
                    swapColors(node, grandparent);
                }
                rightRotate(grandparent); // After either case, we rightRotate the grandparent.
            }
            else // Otherwise, the parent has a right child.
            {
                if (node->isOnLeft()) // Case where node has a left child.
                { // This is a right left case for rotations.
                    rightRotate(parent); // We right rotate the parent and swap colors between the current node and the grandparent.
                    swapColors(node, grandparent);
                }
                else // Otherwise the node has a right child.
                { // This is a right right case for rotations
                    swapColors(parent, grandparent); // We swap the colors of the parent and the grandparent to balance the tree.
                }
                leftRotate(grandparent); // After either case, we leftRotate the grandparent to balance the tree.
            }
        }
    }
}

TreeNode* RedBlackTree::successor(TreeNode* node)
{
    TreeNode* temp = node; // We initialize a temp node to the current node.
    while (temp->left != NULL) // We loop through the tree until we are at the temp node's left most node
    {
        temp = temp->left;
    }
    return temp; // We return the temp node as it is the successor node.
}

TreeNode* RedBlackTree::BSTreplace(TreeNode* node)
{
    if (node->left != NULL && node->right != NULL) // Case where node has both a left child and a right child.
    { // Basically, the case where a node has 2 children
        return successor(node->right); // We return the successor of node's right child.
    }
    if (node->left == NULL && node->right == NULL) // Case where node doesn't have a left child and a right child.
    { // Basically, the case where a node is a leaf in the tree.
        return NULL; // We return NULL as there is no existing child node to return.
    }

    // For cases where node only has one child.
    if (node->left != NULL) // Case where node has a left child.
    {
        return node->left; // We return node's left child then.
    }
    else // Otherwise, the node has a right child.
    {
        return node->right; // We return node's right child then
    }
}

void RedBlackTree::deleteNode(TreeNode* node)
{
    TreeNode* replacingNode = BSTreplace(node);

    // nodeAndReplacingNodeBlack returns true when the replacingNode exists and when the colors of both node and replacingNode are black.
    bool nodeAndReplacingNodeBlack = ((replacingNode == NULL || replacingNode->color == Black) && (node->color == Black));
    TreeNode* parent = node->parent; // We set node's parent to be a separate parent node.

    if (replacingNode == NULL) // Case where replacingNode is NULL and doesn't exist.
    {
        if (node == root)  // Case where node is the root of the tree.
        {
            root = NULL; // Then we simply make the root NULL to delete the node.
        }
        else // Otherwise, replacingNode exists and is not NULL.
        {
            if (nodeAndReplacingNodeBlack) // Case where bool is true.
            {
                fixDoubleBlack(node); // Then node is a leaf, and we need to fix the tree to ensure both node and replacingNode are not black.
            }
            else // Otherwise, bool is false and at least one of the nodes is red.
            {
                if (node->sibling() != NULL) // Case where a sibling node exists.
                {
                    node->sibling()->color = Red; // Then we make the sibling node's color Red.
                }
            }
            if (node->isOnLeft()) // Case where node is the left child of a parent.
            {
                parent->left = NULL; // Then we set the parent's left child to NULL.
            }
            else // Otherwise the node is not the left child of a parent.
            {
                parent->right = NULL; // Then we set the parent's right child to NULL
            }
        }
        delete node; // node is not connected to anything now, so we can safely delete it and return the function.
        return;
    }

    if (node->left == NULL || node->right == NULL) // Case where at least 1 of the node's children doesn't exist.
    {
        // For when node has only one child.
        if (node == root) // Case where node is the root of the tree.
        {
            // v is root, assign the value of u to v, and delete u
            node->val = replacingNode->val; // We assign node's val or the root's val with replacingNode's val.
            node->left = NULL;
            node->right = NULL; // We assign the left and right children of node (the root here) to NULL.
            delete replacingNode; // replacingNode is no longer needed so we can delete replacingNode.
        }
        else // Otherwise, node is not the root of the tree.
        {
            // Detach v from tree and move u up
            if (node->isOnLeft()) // Case where node is the left child of a parent.
            {
                parent->left = replacingNode; // Then we set the parent's left child to now be replacingNode.
            }
            else // Otherwise, node is the right child of a parent.
            {
                parent->right = replacingNode; // Then we set the parent's right child to now be replacingNode.
            }
            delete node; // We have no more need for node and it's been safely replaced, so we can safely delete node.

            replacingNode->parent = parent; // We set the parent of replacingNode to parent now.
            if (nodeAndReplacingNodeBlack) // Case where node and replacingNode were both black.
            {
                fixDoubleBlack(replacingNode); // Since replacingNode is still black, we recurse through the function at replacingNode.
            }
            else // Otherwise, at least one of those nodes' colors is Red.
            {
                replacingNode->color = Black; // Then, we set replacingNode's color to Black.
            }
        }
        return; // After, we return the function.
    }
    swapValues(replacingNode, node); // Then we swap the values of replacingNode and node and recurve through the function with replacingNode.
    deleteNode(replacingNode);
}

void RedBlackTree::fixDoubleBlack(TreeNode* node)
{
    if (node == root) // Case where node is the root of the tree.
    {
        return; // Just return because there's no need to replace this node
    }

    TreeNode* sibling = node->sibling();
    TreeNode* parent = node->parent; // We initialize a node's sibling and parent as distinct nodes.
    if (sibling == NULL) // Case where a sibling node does not exist.
    {
        fixDoubleBlack(parent); // Then two black nodes are pushed all the way up in the tree and we need to fix the tree now from the parent node.
    }
    else // Otherwise, a sibling node exists.
    {
        if (sibling->color == Red) // Case where the sibling node's color is Red.
        {
            // Sibling red
            parent->color = Red;
            sibling->color = Black; // To fix the double black in the tree, we set the parent's color to red and the sibling's color to Black.
            if (sibling->isOnLeft()) // Case where the sibling node is the left child of the parent.
            {
                rightRotate(parent); // Then we rightRotate the parent.
            }
            else // Otherwise the sibling node is the right child of the parent.
            {
                leftRotate(parent); // Then we leftRotate the parent
            }
            fixDoubleBlack(node); // Then we recurve through the tree again at the same node to perfrom the case where the sibling's node is Black.
        }
        else // Otherwise, the sibling node's color is Black.
        {
            if (sibling->hasRedChild())  // Case where at least one of the sibling node's children is red.
            {
                if (sibling->left != NULL && sibling->left->color == Red) // Case where a sibling's left child exists and where its color is red.
                {
                    if (sibling->isOnLeft()) // Case where the sibling node is the left child of a parent
                    { // This is a left left case for rotations.
                        sibling->left->color = sibling->color; // We set sibling's left child's color to sibling's color.
                        sibling->color = parent->color; // We set sibling's color to parent's color.
                        rightRotate(parent); // We rightRotate the parent.
                    }
                    else  // Otherwise, the sibling node is a right child of a parent.
                    { // This is a right left case for rotations.
                        sibling->left->color = parent->color; // We set the sibling's left child's color to the parent's color.
                        rightRotate(sibling); // We rightRotate the sibling.
                        leftRotate(parent); // We leftRotate the parent.
                    }
                }
                else
                { // Otherwise a sibling's right child exists and its color is red.
                    if (sibling->isOnLeft())  // Case where the sibling node is the left child of a parent.
                    { // This is a left right case for rotations.
                        sibling->right->color = parent->color; // We set the sibling's right child's color to the parent's color.
                        leftRotate(sibling); // We leftRotate the sibling.
                        rightRotate(parent); // We rightRotate the parent.
                    }
                    else // Otherwise, the sibling node is the right child of a parent.
                    { // This is a right right case for rotations.
                        sibling->right->color = sibling->color; // We set the sibling's right child's color to the sibling's color.
                        sibling->color = parent->color; // We set the sibling's color to the parent's color.
                        leftRotate(parent); // We leftRotate the parent.
                    }
                }
                parent->color = Black; // Regardless of which child is red, we then set the parent's color to black.
            }
            else // Otherwise, none of the sibling's node's children are red and both children are black.
            {
                sibling->color = Red; // We set the sibling node's color to Red.
                if (parent->color == Black) // Case where the parent's color is Black.
                {
                    fixDoubleBlack(parent); // Then we need to recurve the function and fixDoubleBlack in the parent node.
                }
                else // Otherwise, the parent's color is Red and we need to set it to Black.
                {
                    parent->color = Black;
                }
            }
        }
    }
}

TreeNode* RedBlackTree::search(int recipeNumber)
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
}

void RedBlackTree::insert(int recipeNumber, string recipeTitle, string recipeTime, string recipeIngredients,
                          string recipeDescription,
                          double d)
{
    TreeNode* newNode = new TreeNode(recipeNumber, recipeTitle, recipeTime, recipeIngredients, recipeDescription); // Creates a new node in the tree.
    if (root == NULL) // if root is NULL, just insert a new value at the root.
    {
        newNode->color = Black; // Color of the newNode is set to Black and the root becomes the newNode.
        root = newNode;
    }
    else
    {
        TreeNode* temp = search(recipeNumber); // Search for nonexistent recipeNumber to traverse through the tree.
        if (temp->val == recipeNumber)
        { // Case where value to insert already exists.
            return;
        } // Otherwise...

        newNode->parent = temp; // The parent of newNode becomes temp, cause temp is at the bottom of the tree for insertion here.

        if (recipeNumber < temp->val) // If recipeNumber is smaller than temp->val, newNode is to the left of temp.
        {
            temp->left = newNode;
        }
        else // If recipeNumber is larger than temp->val, newNode is to the right of temp.
        {
            temp->right = newNode;
        }

        fixRedToRed(newNode); // We check that two red nodes aren't connected and fix it if it exists.
    }
}

void RedBlackTree::deleteNodeValue(int recipeNumber)
{
    if (root == NULL) // Case where root is NULL
    {
        return; // The tree is empty, so just return.
    }
    TreeNode* node = search(recipeNumber); //, * u; // Sets node to the node with the recipeNumber to delete that node if the node exists.
    if (node->val != recipeNumber) // Case where the node with the recipNumber does not exist. Then just return.
    {
        return;
    }
    deleteNode(node); // We move on to delete the node.
}

void RedBlackTree::inorder(TreeNode* node, string &s)
{
    if (node == NULL) // Case where node is NULL and that we're past the leaf of a tree.
    {
        return; // Then we return because we have nothing left to traverse.
    }
    inorder(node->left,s); // Recurve first through the left most nodes of the tree.
     s+= "✔︎" + node->recipeTitle + " Time " + "▷ "+node->recipeTime + " " + "minutes" +"\n" + "Ingredients " + "▷ "+splitString(node -> recipeIngredients)  + "\n" + "Instructions " + "▷ " +splitString(node->recipeDescription) + "\n\n";
     // This just prints out their numbers, but we could set it up to print out their names.
    inorder(node->right, s); // Recurses through the right most nodes of the tree.
    
    
}
string RedBlackTree::printInOrder()
{
    string x;

    if (root == NULL) // Case where tree is empty.
    {
        return "No Results";
    }
    else // Otherwise tree is not empty.
    {
        inorder(root, x);
    }

    return x;
}

string RedBlackTree::splitString (string ingredientData){
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
