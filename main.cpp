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
bool containsOnlyNumbers(string const& str){
    return str.find_first_not_of("0123456789") ==
        string::npos;
};

int main()
{
    AVLTree t;
    cout << "1: " << endl;
    t.insertHelper("Brandon", "1");

    t.printLevelOrder();
    cout << endl;
    cout << "2: " << endl;

    t.insertHelper("John Nino", "2");
    t.printLevelOrder();
    cout << endl;
    cout << "3: " << endl;

    t.insertHelper("soroush smells", "3");
    t.printLevelOrder();
    cout << endl;

    cout << "4: " << endl;

    t.insertHelper("Brandon nonya", "4");
    t.printLevelOrder();
    cout << endl;

    cout << "5: " << endl;

    t.insertHelper("John Nino", "5");
    t.printLevelOrder();
    cout << endl;

    cout << "6: " << endl;

    t.insertHelper("Jo Nino", "6");

    /*t.insertHelper("Jo little Nino", "7");
    t.insertHelper("willly Nino", "8");
    t.insertHelper("willly stinks", "9");*/



    t.printLevelOrder();
   /* //create tree
    AVLTree t;  

    //take in number of commands
   int commands = 0;
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
               if (ID.length() != 8 || !containsOnlyNumbers(ID) || t.containsIDHelper(ID)){
                   cout << "";
                   cout << "unsucessful" << endl;
                   continue;
               }
      
               t.insertHelper(name, ID);
               cout << "successful" << endl;
            }
            else {
                cout << "unsucessful" << endl;
                continue;
            }
        }

        //Print Commands
        else if (firstCommand == "printInorder") {
            if(t.getRoot() != NULL)
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
        else if (firstCommand == "remove") {
            string ID = command.substr(command.find(' ') + 1, command.length() - 1);
            if (ID.length() != 8 || !containsOnlyNumbers(ID)) {
                cout << "";
                cout << "unsucessful" << endl;
                continue;
            }

            t.removeID(ID);
            cout << "successful" << endl;
        }
        else if (firstCommand == "removeInorder") {
            int n = stoi(command.substr(command.find(' ') + 1, command.length() - 1));
            bool check = t.removeInOrder(n);
            if (check)
                cout << "successful" << endl;
        }
        else {
            cout << "unsuccessful" << endl;
        }
    }*/
   
}