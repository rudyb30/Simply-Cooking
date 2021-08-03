#include <iostream>
#include <queue>
#include <istream>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <iomanip>
#include "RedBlackTree.h"
#include "Logic.hpp"
#include "BST.h"
using namespace std;

//function that returns information to interface 


vector<string> splitString(string ingredientData)
{
    //function that breaks the ingredients string into a vector of ingredients
    stringstream sstream(ingredientData);
    vector<string> ingredients;
    string ingredient;
    int count = 0;
    char delimiter = '\'';

    getline(sstream, ingredient, delimiter);
    while (getline(sstream, ingredient, delimiter))
    {
        if (count % 2 == 0)
        {
            ingredients.push_back(ingredient);
        }
        count++;
    }

    return ingredients;
}

template<class T>
void merge(std::vector<T>& myVec, std::vector<T>& left, std::vector<T>& right) {
    int sizeL = left.size(), sizeR = right.size();
    int i = 0, j = 0, k = 0;

    while (i < sizeL && j < sizeR) {
        if (left[i] <= right[j]) {
            myVec[k] = left[i];
            i++;
        }
        else {
            myVec[k] = right[j];
            j++;
        }
        k++;
    }

    while (i < sizeL) {
        myVec[k] = left[i];
        i++;
        k++;
    }

    while (j < sizeR) {
        myVec[k] = right[j];
        j++;
        k++;
    }
}

template<class T>
void mergeSort(std::vector<T>& myVec) {
    // base case
    if (myVec.size() <= 1)
        return;
    int midLen = myVec.size() / 2;
    std::vector<T> leftSUb(myVec.begin(), myVec.begin() + midLen);
    std::vector<T> rightSUb(myVec.begin() + midLen, myVec.end());

    mergeSort(leftSUb);
    mergeSort(rightSUb);

    merge(myVec, leftSUb, rightSUb);
}


int binarySearch(std::vector<std::string>& myVec, string index, int begin, int end) {
    if (end >= begin) {
        //calculate midPoint
        int mid = begin + (end - begin) / 2; //this ensures overflow does not occur
        if(myVec[mid].size() >= index.size()){
        if (myVec[mid].find(index) != string :: npos)
            //attempting find function with sub strings
            return mid;
        }
    
        //this will only recurse the elements to the right of the median.
        if (index > myVec[mid])
        {
            return binarySearch(myVec, index, mid + 1, end);
        }
        //this will only recurse the elements to the left of the median.
        return binarySearch(myVec, index, begin, mid - 1);
    }
    return -1;
}


double IngredientsFound(vector<string> ingredients, vector<string> prioritizedIngredients)
{

    double score = 0.0;

    if (ingredients.size() <= prioritizedIngredients.size()) {
        //call merge sort
        mergeSort(ingredients);
        for (int i = 0; i < prioritizedIngredients.size(); ++i) {
            if (binarySearch(ingredients, prioritizedIngredients.at(i), 0, ingredients.size() - 1) != -1)
                score += 1;
        }
    }
    else
    {
        mergeSort(prioritizedIngredients);
        for (int i = 0; i < ingredients.size(); ++i) {
            if (binarySearch(prioritizedIngredients, ingredients.at(i), 0, prioritizedIngredients.size() - 1) != -1)
                score += 1;
        }
    }

    return score;
}

double allergicIngredientsFound(double relationValue, vector<string> ingredients, vector<string> allergicIngredients)
{//Rudy: why is this different than prioritized ingredients??
    if (ingredients.size() <= allergicIngredients.size()) {
        //call merge sort
        mergeSort(ingredients);
        for (int i = 0; i < allergicIngredients.size(); ++i) {
            if (binarySearch(ingredients, allergicIngredients.at(i), 0, ingredients.size() - 1) != -1)
            {
                return 0;
            }
        }
    }
    else
    {
        mergeSort(allergicIngredients);
        for (int i = 0; i < ingredients.size(); ++i) {
            if (binarySearch(allergicIngredients, ingredients.at(i), 0, allergicIngredients.size() - 1) != -1)
            {
                return 0;
            }
        }
    }
    return relationValue;

}

vector<string> breakInfo(string info)
{
    //function that breaks the row into parts and returns a vector with each part

    vector <string> infoParts;
    string delimiter = ";";
    size_t pos = 0;
    std::string temp;
    while ((pos = info.find(delimiter)) != std::string::npos)
    {
        temp = info.substr(0, pos);
        infoParts.push_back(temp);
        info.erase(0, pos + delimiter.length());
    }
    infoParts.push_back(info);

    return infoParts;
}

const char * buildBook(RedBlackTree tree, BinarySearchTree bstTree, vector<string> prioritizedIngredients,vector<string> allergicIngredients, bool treeType){
  //this function holds the main logic of the program searches and handles csv data 
    vector<string> ingredients;
    string results;
    ifstream infile;//if a relative path causes problems hard type it
    infile.open("/Users/rudyberry/Library/Developer/Xcode/DerivedData/Cooking-dksuqqikqfcdnsekmfzvznvclqnz/Build/Products/Debug-iphonesimulator/UpdatedData.csv");//if a relative path causes problems hard type it
    string data;
    string allInfo;
    vector<string> infoParts;

    double relationValue = 0;
    double allergyValue = 0;
    int cap = 0;

    
    while (getline(infile, data)) {


        allInfo = data;
        infoParts = breakInfo(allInfo);//function to split the entire row into parts
        ingredients = splitString(infoParts[9]);

if(prioritizedIngredients.size() > 0)
        relationValue = IngredientsFound(ingredients, prioritizedIngredients);
        
        if(allergicIngredients.size() > 0)
        allergyValue = IngredientsFound(ingredients, allergicIngredients);
        
           if(relationValue == prioritizedIngredients.size() && allergyValue == 0) {
               
               if(!treeType){
               tree.insert(stoi(infoParts[1]), infoParts[0], infoParts[2], infoParts[9], infoParts[8], relationValue);
               }
               if(treeType){
                   bstTree.insert(stoi(infoParts[1]), infoParts[0], infoParts[2], infoParts[9], infoParts[8]);
               }
               cap++;
           }
       
        if(cap > 3)
           break;

        infoParts.clear();
    }

    if(!treeType)
    results = tree.printInOrder();
    if(treeType)
    results = bstTree.printInOrder();
    const char * resultTest = results.c_str();
    if(cap == 0)
        return "No recipes found. Please check your spelling!";
    
    else
        return resultTest;
}



const char* getRecipes (const char * ingredientList, const char * allergyList)
{//Main C++ logic to be called in swift
    /* NOTE: this would ideally be conatainers of strings with c wrappers to handle the conversion but for this project we will only use primitive types*/
    const char * buildBook(RedBlackTree tree, BinarySearchTree bstTree, vector<string> prioritizedIngredients,vector<string> allergicIngredients, bool treeType);
    RedBlackTree redTree;
    BinarySearchTree binaryTree;
    const char * result;
    bool type = true;
    //false = red black tree
    //true = binary search tree
    
    vector<string> ingredients = breakInfo(string(ingredientList));
    vector<string> allergicIngredients = breakInfo(string(allergyList));
    
     result = buildBook(redTree, binaryTree, ingredients, allergicIngredients, type);
    
    return result;
}

