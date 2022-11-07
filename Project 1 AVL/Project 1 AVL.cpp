// Project 1 AVL.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include "AVL.h"
#include <iostream>
#include <string>
#include <cstring>
#include<sstream>
using namespace std;

//found online
bool containsOnlyLetters(string const& str) {
    return str.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ ") ==
        string::npos;
};
bool containsOnlyNumbers(string const& str) {
    return str.find_first_not_of("0123456789") ==
        string::npos;
};

int main()
{
    //create tree
    AVLTree t;

    //take in number of commands
    int commands = 0;
    cout << "Enter the number of commands: ";
    cin >> commands;
    string command;
    cin.ignore(1000, '\n');

    //execute commands based off input
    for (int i = 0; i < commands; ++i) {
        getline(cin, command);
        string firstCommand = command.substr(0, command.find(' '));

        //insert command
        if (firstCommand == "insert") {
            stringstream ss(command);
            string name = " ";
            string ID = " ";
            for (int j = 0; j < 2; ++j) {
                getline(ss, name, '\"');
            }
            if (containsOnlyLetters(name)) {
                for (int j = 0; j < 3; ++j) {
                    getline(ss, ID, '\"');
                }
                ID = ID.substr(1, ID.length() - 1);
                if (ID.length() != 8 || !containsOnlyNumbers(ID) || t.containsIDHelper(ID)) {
                    cout << "unsuccessful" << endl;
                    continue;
                }

                t.insertHelper(name, ID);
                cout << "successful" << endl;
            }
            else {
                cout << "unsuccessful" << endl;
                continue;
            }
        }

        //Print Commands
        else if (firstCommand == "printInorder") {
            if (t.getRoot() != NULL)
                t.printInOrderHelper();
        }
        else if (firstCommand == "printPostorder") {
            if (t.getRoot() != NULL)
                t.printPostOrderHelper();
        }
        else if (firstCommand == "printPreorder") {
            if (t.getRoot() != NULL)
                t.printPreOrderHelper();
        }
        else if (firstCommand == "printLevelCount") {
            t.levelCountHelper();
        }
        else if (firstCommand == "search") {
            //Execute search name or ID based on the input
            try {
                if (command.find("\"") == string::npos) {
                    string ID = command.substr(command.find(' ') + 1, command.length() - 1);
                    t.searchIDHelper(ID);
                }
                else {
                    string name = "";
                    stringstream ss(command);
                    for (int j = 0; j < 2; ++j) {
                        getline(ss, name, '\"');
                    }
                    t.searchNameHelper(name);

                }
            }
            catch (...) {
                cout << "unsuccessful" << endl;
                continue;
            }
        }
        else if (firstCommand == "remove") {
                string ID = command.substr(command.find(' ') + 1, command.length() - 1);
                if (ID.length() != 8 || !containsOnlyNumbers(ID) || !t.containsIDHelper(ID)) {
                    cout << "unsuccessful" << endl;
                    continue;
                }
                else {
                    t.removeID(ID);
                    cout << "successful" << endl;
                }
            }
        else if (firstCommand == "removeInorder") {
            try {
                int n = stoi(command.substr(command.find(' ') + 1, command.length() - 1));
                bool check = t.removeInOrder(n);
                if (check)
                    cout << "successful" << endl;
            }
            catch (...) {
                cout << "unsuccessful" << endl;
                continue; 
            }
        }
        else {
            cout << "unsuccessful" << endl;
        }
    }

}
