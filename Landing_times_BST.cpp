////////////////////////////////////////////////////////
// Flight management program by Carlos Rangel
// Made for CSE310 to study and implement BSTree
///////////////////////////////////////////////////////

#include <iostream>
#include <cstdlib>
#include <vector>
#include <limits>
#include "BinarySearchTree.h"

#define DOTLINE  " ----------------------------------------\n"

static bool checkCin(){
    if(std::cin.fail()){
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::min(), '\n');

        return false;
    }
    return true;
}

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

    BinarySearchTree bst;
    string input_s;
    char input;
    int landingTime, timeGap;
    string flightName;

    cout << " Welcome to the Plane Landing System! \n";
    cout << DOTLINE;
        
        
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
            //flush cin
            

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

                //checking for the timeGap (K) constraint. 
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

            //withdraw landing request
            //I was gonna do removal by searching landing time
            //but thought that would be weird in a real setting so 
            //i overloaded treeSearch to work with inputted strings
            case 'B':
                cout << " Flight names and landing times:\n";
                cout << DOTLINE;
                bst.inOrderTreeWalk_flightName(bst.root);
                cout << " Please enter Landing time of the flight to remove: ";
                while(true){
                        cin >> landingTime;
                        if(!checkCin()){
                            cout << " ERROR:: Invalid input!\n";
                            cout << " Please enter Landing Time (Enter an integer): ";
                        }
                        else break;
                    }
                
                if(bst.treeSearch(bst.root, landingTime) == NULL){
                    cout << " ERROR:: Flight Not fould!";
                    break;
                }
                else {
                    cout << " Flight " << bst.treeSearch(bst.root, landingTime)->data;
                    bst.treeDelete(bst.treeSearch(bst.root, landingTime));
                    cout << " has been deleted.\n";
                }
                break;
                
            case 'C':
                cout << " Flight names and landing times:\n";
                cout << DOTLINE;
                bst.inOrderTreeWalk_flightName(bst.root);
                break;
                
            case '?':
                printMenu();
                break;

            case 'Q':
                system("pause");
                return 0;
                break;
                
            default:
                cout << " ERROR:: Invalid input!\n";
                cout << " Please try again. . .\n\n";
                break;
        }
    }
}