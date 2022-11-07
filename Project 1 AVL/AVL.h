#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <queue>
#include <cstdlib>
#pragma once
using namespace std;

class Node {
public:
    int height, val;
    string name, ID;
    Node* left;
    Node* right;
    Node() : val(0), left(nullptr), right(nullptr), name(""), height(1) {}
    Node(string x, string name) : val(stoi(x)), left(nullptr), right(nullptr), name(name), height(1), ID(x) {}
    Node(string x, Node* left, Node* right, string name) : val(stoi(x)), ID(x), left(left), right(right), name(name), height(1) {}
};

class AVLTree {
private:
    Node* root = nullptr;
    bool check = false;
    bool noID = true;
    bool noName = false;
    bool contains = false;
    vector<string> names;


    int getHeight(Node* root) {
        if (!root)
            return 0;
        return root->height;
    }
    //Insert function
    Node* insert(Node* root, string key, string name)
    {
        int balFactor = 1;
        if (root == nullptr)
            return new Node(key, name);
        else if (stoi(key) < root->val) {
            root->left = insert(root->left, key, name);
        }
        else if (stoi(key) > root->val) {
            root->right = insert(root->right, key, name);

        }

        root->height = max(getHeight(root->left), getHeight(root->right)) + 1;

        balFactor = getHeight(root->right) - getHeight(root->left);

        if (balFactor > 1) {
            balFactor = getHeight(root->right->right) - getHeight(root->right->left);

            if (balFactor <= -1) {
                root = rotateRightLeft(root);
            }
            else {
                root = rotateLeft(root);
            }

        }
        else if (balFactor < -1) {
            balFactor = getHeight(root->left->right) - getHeight(root->left->left);

            if (balFactor >= 1) {
                root = rotateLeftRight(root);

            }
            else {
                root = rotateRight(root);
            }
        }
        return root;
    }

public:
    AVLTree() {
        this->root = NULL;
    }
    AVLTree(AVLTree& newTree) {
        this->root = newTree.getRoot();
    }

    //Height and rotations are from stepnik/powepoints
    int height(Node* root) {
        // Get the height of the tree
        if (!root)
            return 0;
        else {
            int left = height(root->left);
            int right = height(root->right);
            if (left >= right) {
                return left + 1;
            }
            else
                return right + 1;
        }
    }
    Node* rotateLeft(Node* node)
    {
        Node* grandchild = node->right->left;
        Node* newParent = node->right;
        newParent->left = node;
        node->right = grandchild;
        node->height = 1 + max(getHeight(node->left), getHeight(node->right));
        newParent->height = 1 + max(getHeight(newParent->left), getHeight(newParent->right));
        return newParent;
    }

    Node* rotateRight(Node* node)
    {
        Node* grandchild = node->left->right;
        Node* newParent = node->left;
        newParent->right = node;
        newParent->right->left = grandchild;
        node->height = 1 + max(getHeight(node->left), getHeight(node->right));
        newParent->height = 1 + max(getHeight(newParent->left), getHeight(newParent->right));

        return newParent;
    }
    Node* rotateRightLeft(Node* node)
    {
        node->right = rotateRight(node->right);
        Node* root = rotateLeft(node);
        return root;
    }
    Node* rotateLeftRight(Node* node)
    {
        node->left = rotateLeft(node->left);
        Node* root = rotateRight(node);
        return root;
    }

    //Helper Functions to gain Access from Main
    void searchIDHelper(string term) {
        bool checker = containsID(this->root, term);
        if (!checker) {
            cout << "unsuccessful" << endl;
            return;
        }
        searchID(this->root, term);
    }
    void insertHelper(string name, string val) {
        this->root = insert(this->root, val, name);
    }
    void searchNameHelper(string name) {
        bool temp = searchName(this->root, name);
        if (!temp) {
            cout << "unsuccessful" << endl;
        }
    }
    void printInOrderHelper() {
        names.clear();
        printInOrder(this->root);
        for (int i = 0; i < names.size(); ++i) {
            if (i == names.size() - 1) {
                cout << names[i] << endl;
            }
            else
                cout << names[i] << ", ";
        }
    }
    void printPostOrderHelper() {
        names.clear();
        printPostOrder(this->root);
        for (int i = 0; i < names.size(); ++i) {
            if (i == names.size() - 1) {
                cout << names[i] << endl;
            }
            else
                cout << names[i] << ", ";
        }
    }
    void printPreOrderHelper() {
        names.clear();
        printPreOrder(this->root);
        for (int i = 0; i < names.size(); ++i) {
            if (i == names.size() - 1) {
                cout << names[i] << endl;
            }
            else
                cout << names[i] << ", ";
        }
    }
    void levelCountHelper() {
        printLevelCount(this->root);
    }
    bool containsIDHelper(string ID) {
        return containsID(this->root, ID);
    }

    //Search functions to find specific nodes based on names and IDs
    bool searchName(Node* root, string term) {
        if (root == NULL)
            return false;
        if (root->name == term) {
            cout << root->ID << endl;
            noName = true;
        }
        if (root->left != nullptr)
            searchName(root->left, term);
        if (root->right != nullptr)
            searchName(root->right, term);
        return noName;

    }
    Node* searchID(Node* root, string term) {
        if (root == NULL)
            return root;
        if (root->ID == term) {
            cout << root->name << endl;
            check = true;
            return root;
        }
        if (stoi(term) > root->val)
            searchID(root->right, term);

        else
            searchID(root->left, term);

        return NULL;
    }

    //Function to get the root of the tree
    Node* getRoot() {
        return this->root;
    }

    //find successor in case where deleting node with two children
    Node* findSuccessor(Node* root) {
        if (root->left == nullptr)
            return root;
        return findSuccessor(root->left);
    }

    //function to check if tree contains specific ID
    bool containsID(Node* root, string term) {
        while (root != NULL) {
            // pass right subtree as new tree
            if (stoi(term) > root->val)
                root = root->right;

            // pass left subtree as new tree
            else if (stoi(term) < root->val)
                root = root->left;
            else
                return true; // if the key is found return 1
        }
        return false;
    }

    //function to find the desired n node to delete
    string findNode(int n) {
        stack<Node*> s;
        Node* curr = root;
        int i = 0;
        while (curr != NULL || s.empty() == false)
        {
            /* Reach the left most Node of the
               curr Node */
            while (curr != NULL)
            {
                s.push(curr);
                curr = curr->left;
            }

            curr = s.top();
            s.pop();

            if (i == n) {
                return curr->ID;
            }
            curr = curr->right;
            ++i;
        }
        return "NULL";
    }

    //remove n node from the tree
    bool removeInOrder(int n) {
        string temp = findNode(n);
        if (temp == "NULL") {
            cout << "unsuccessful" << endl;
            return false;
        }
        removeID(temp);
        return true;
    }

    //called by remove ID to do the actual removing of a node with thatds
    //ID and it handles all the different cases
    Node* removeIDHelper(Node* root, string term) {
        if (root == NULL)
            return nullptr;
        else if (stoi(term) > root->val)
            root->right = removeIDHelper(root->right, term);
        else if (stoi(term) < root->val)
            root->left = removeIDHelper(root->left, term);
        else {
            //no children
            if (root->left == nullptr && root->right == nullptr) {
                delete root;
                return nullptr;
            }
            //one child
            else if (root->right == nullptr) {
                Node* temp = root->left;
                delete root;
                temp->height = 1 + max(getHeight(temp->left), getHeight(temp->right));
                return temp;
            }
            else if (root->left == nullptr) {
                Node* temp = root->right;
                delete root;
                temp->height = 1 + max(getHeight(temp->left), getHeight(temp->right));
                return temp;
            }
            //two children
            else {
                Node* temp = findSuccessor(root->right);
                //Store root vals in num so that I can use them to delete leaf successor
                root->ID = temp->ID;
                root->name = temp->name;
                root->val = temp->val;

                temp->ID = "0";
                temp->val = 0;
                root->right = removeIDHelper(root->right, temp->ID);
                root->height = 1 + max(getHeight(root->left), getHeight(root->right));
                return root;
            }
        }
        return root;


    }

    //calls helper to do the dirty work
    void removeID(string key) {
        bool target = containsID(this->root, key);
        if (!target) {
            return;
        }
        root = removeIDHelper(this->root, key);

    }


    //Taken and modified from Stepnik
    void printInOrder(Node* root)
    {
        if (root == NULL)
            return;

        printInOrder(root->left);
        names.push_back(root->name);
        printInOrder(root->right);
    }
    void printPostOrder(Node* root) {
        if (root == NULL)
            return;
        printPostOrder(root->left);
        printPostOrder(root->right);
        names.push_back(root->name);
    }
    void printPreOrder(Node* root) {
        if (root == NULL)
            return;

        names.push_back(root->name);
        printPreOrder(root->left);
        printPreOrder(root->right);
    }
    void printLevelCount(Node* root) { 
        if (!root)
            cout << 0 << endl;
        else
            cout << height(this->root) << endl;
    }


    ~AVLTree() {
    }
};
