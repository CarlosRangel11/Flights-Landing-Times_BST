////////////////////////////////////////////////////////
// Flight management program by Carlos Rangel
// Made for CSE310 to study and implement BSTree
///////////////////////////////////////////////////////

#include <iostream>
#include <cstdlib>
#include <vector>
#include <limits>
#include "BinarySearchTree.h"

// used for formatting
#define DOTLINE  " ----------------------------------------\n"

// Used to check for input validation when using Cin
// Returns false if cin has not received the proper input type
// Returns true otherwise
static bool checkCin(){
    if(std::cin.fail()){
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::min(), '\n');

        return false;
    }
    return true;
}

// Prints the menu (duh)
static void printMenu(){
    using namespace std;
    
    cout << DOTLINE;
    cout << " A. Request Landing\n";
    cout << " B. Withdraw landing request\n";
    cout << " C. List landing times & flight Numbers\n";
    cout << " ?. Print this menu\n";
    cout << " Q. Exit\n\n";

}

int main(){
    using namespace std;

    BinarySearchTree bst;       // Create BST on the stack
    string input_s;             // Formats the char to use in switch
    char input;
    int landingTime, timeGap;
    string flightName;

    cout << " Welcome to the Plane Landing System! \n";
    cout << DOTLINE;
        
    // Loops until timeGap is initialized
    while(true){
        cout << " To begin, please initialize the time gap for landing requests: ";
        cin >> timeGap;
        if(!checkCin()){
            cout << " ERROR:: Invalid input!\n";
            cout << " Please enter an integer to initialize the time gap for landing requests.\n "; 
        }
        else break;
    }
        
    cout << " The inputted time gap is " << timeGap << "\n" << endl;

    while(true){
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        printMenu();
        cout << " Input: ";
        input = getchar();
        input = toupper(input);
        

        switch(input){

            //request a landing
            case 'A':
                cout << " Making a plane landing request. Please enter the following:\n";
                cout << " Plane Flight Number: ";
                cin >> flightName;

                //checking input
                cout << " Landing Time (integers): ";
                while(true){
                    cin >> landingTime;
                    if(!checkCin()){
                        cout << " ERROR:: Invalid input!\n";
                        cout << " Please enter Landing Time (Enter an integer): ";
                    }
                    else break;
                }


                bst.treeInsert(landingTime, flightName);

                //checking for the timeGap (K) constraint using predecessors and successors (basically highest/lowest next values in BSTrees)
                // If the landing time between 2 sorted nodes in the tree is less than timeGap, do not allow the plane to land
                if(bst.treeSuccessor(bst.treeSearch(bst.root, landingTime)) != NULL)
                    if( abs(bst.treeSearch(bst.root, landingTime)->key - bst.treeSuccessor(bst.treeSearch(bst.root, landingTime))->key) < timeGap){
                        cout << "successor: " << bst.treeSearch(bst.root, landingTime)->key - bst.treeSuccessor(bst.treeSearch(bst.root, landingTime))->key << "\n";
                        cout << "\n The time gap between " << landingTime << " and flight ";
                        cout << bst.treeSuccessor(bst.treeSearch(bst.root, landingTime))->data << "(" << bst.treeSuccessor(bst.treeSearch(bst.root, landingTime))->key << ") is too small!\n";
                        cout << " Plane request denied!\n";
                        bst.treeDelete(bst.treeSearch(bst.root, landingTime));
                        break;
                    }

                if(bst.treePredecessor(bst.treeSearch(bst.root, landingTime)) != NULL)
                    if( abs(bst.treeSearch(bst.root, landingTime)->key - bst.treePredecessor(bst.treeSearch(bst.root, landingTime))->key) < timeGap){
                        cout << "predecessor: " << bst.treeSearch(bst.root, landingTime)->key - bst.treePredecessor(bst.treeSearch(bst.root, landingTime))->key << "\n";;
                        cout << "\n The time gap between " << landingTime << " and flight";
                        cout << bst.treePredecessor(bst.treeSearch(bst.root, landingTime))->data << "(" << bst.treePredecessor(bst.treeSearch(bst.root, landingTime))->key << ") is too small!\n";
                        cout << " Plane request denied!\n";
                        bst.treeDelete(bst.treeSearch(bst.root, landingTime));
                        break;
                    }
                cout << "\n Plane " << bst.treeSearch(bst.root, landingTime)->data << " was added!\n";
                break;

            // withdraw landing request
            // Weird dynamic because the BST works off of landing times to sort the nodes
            // In the real world, you can still sort it like that, but for edu. purposes (assignment requirements)
            // You input the landing time of the plane to remove, rather than the flight name. 
            case 'B':
                cout << " Flight names and landing times:\n";
                cout << DOTLINE;

                // Prints the Tree in sorted order (inorder) to choose the landing times
                bst.inOrderTreeWalk_flightName(bst.root);

                // Validates input of the landing time to 
                cout << " Please enter Landing time of the flight to remove: ";
                while(true){
                    cin >> landingTime;
                    if(!checkCin()){
                        cout << " ERROR:: Invalid input!\n";
                        cout << " Please enter Landing Time (Enter an integer): ";
                    }
                    else break;
                }
                
                // Checks if that landing time has been found
                if(bst.treeSearch(bst.root, landingTime) == NULL){
                    cout << " ERROR:: Flight Not fould!";
                    break;
                }

                // If it was found, delete the flight.
                else {
                    cout << " Flight " << bst.treeSearch(bst.root, landingTime)->data;
                    bst.treeDelete(bst.treeSearch(bst.root, landingTime));
                    cout << " has been deleted.\n";
                }
                break;

            // Prints the current flights in the BST    
            case 'C':
                cout << " Flight names and landing times:\n";
                cout << DOTLINE;
                bst.inOrderTreeWalk_flightName(bst.root);
                break;
                
            // prints the menu
            case '?':
                printMenu();
                break;

            // Exit
            case 'Q':
                system("pause");
                return 0;
                break;
                
            // Other input besides this one
            default:
                cout << " ERROR:: Invalid input!\n";
                cout << " Please try again. . .\n\n";
                break;
        }
    }
}