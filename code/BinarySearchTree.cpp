#include <iostream>
#include <cstdlib>
#include <vector>
#include <limits>

//header file for methods
#include "BinarySearchTree.h"
///////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////

//constructor
BinarySearchTree::BinarySearchTree(){
    root = NULL;
}
//destructor
BinarySearchTree::~BinarySearchTree(){
    destroyTree(root);
}

////////////////////////////////////////////////////////////////////////////// 
//checking da tree and removing min/max
bool BinarySearchTree::isEmpty(){
    return root == NULL;
}

// Returns the farthest left node in the tree, representing the minimum number
BinarySearchTree::node* BinarySearchTree::findMin(node* x){
    while(x->left != NULL)
        x = x->left;
    return x;
}

// Returns the farthest right node in the tree, representing the maximum number
BinarySearchTree::node* BinarySearchTree::findMax(node* x){
    while(x->right != NULL)
        x = x->right;
    return x;
}

// Removes the farthest-left tree node
void BinarySearchTree::removeMin(){
    treeDelete(findMin(root));
}

// Removes the farthest-right tree node
void BinarySearchTree::removeMax(){
    treeDelete(findMax(root));
}


//////////////////////////////////////////////////////////////////////////////
//tree walks

// Prints out the tree with root-first priority
void BinarySearchTree::preOrderTreeWalk(node* x){
    if(x != NULL){
        std::cout << " " << x->key << " ";
        if(x->left) inOrderTreeWalk(x->left);
        if(x->right)inOrderTreeWalk(x->right);
    }
}

// Prints out the tree going left node first, then local roots, then right nodes
// (Sorted order of the tree)
void BinarySearchTree::inOrderTreeWalk(node* x){
    if(x != NULL){
        if(x->left) inOrderTreeWalk(x->left);
        std::cout << " " << x->key << " ";
        if(x->right)inOrderTreeWalk(x->right);
    }
}

// Prints out the tree with leaf-first priority
void BinarySearchTree::postOrderTreeWalk(node* x){
    if(x != NULL){
        if(x->left) inOrderTreeWalk(x->left);
        if(x->right)inOrderTreeWalk(x->right);
        std::cout << " " << x->key << " ";
    }
}

//secondary inorder tree walk to be more verbose with flight manager. 
void BinarySearchTree::inOrderTreeWalk_flightName(node* x){
    if(x != NULL){
        if(x->left) inOrderTreeWalk_flightName(x->left);
        std::cout << " Flight " << x->data << "\t::\tlanding in " << x->key << " minutes.\n";
        if(x->right)inOrderTreeWalk_flightName(x->right);
    }
}
//////////////////////////////////////////////////////////////////////////////
//insert, delete, and dictionary ops (with helper functions)

// Inserts nodes in a tree by comparing the keys of the node to be inserted and the 
// Current iterating node.
void BinarySearchTree::treeInsert(int key){
    node* z = new node();
    z->key = key;
    z->left = NULL;
    z->right = NULL;
    z->parent = NULL;

    node* y = NULL;
    node* x = root;

    // if the inserting node < current tree node, go left
    // else go right
    while(x != NULL){
        y = x;
        if(z->key < x->key)
            x = x->left;
        else x = x->right;
    }

    // Links the inserted node with the adjacent existing nodes
    z->parent = y;
    if(y == NULL)
        root = z;
    else if(z->key < y->key)
        y->left = z;
    else y->right = z;
}

//overload to include string input
void BinarySearchTree::treeInsert(int key, std::string data){
    node* z = new node();
    z->key = key;
    z->data = data;
    z->left = NULL;
    z->right = NULL;
    z->parent = NULL;

    node* y = NULL;
    node* x = root;

    while(x != NULL){
        y = x;
        if(z->key < x->key)
            x = x->left;
        else x = x->right;
    }
    z->parent = y;
    if(y == NULL)
        root = z;
    else if(z->key < y->key)
        y->left = z;
    else y->right = z;
}

// Deletes the specified node in the tree
// Updated adjacent nodes and edges
void BinarySearchTree::treeDelete(node* z){
    if(z->left == NULL)
        transplant(z, z->right);
    else if(z->right == NULL)
        transplant(z, z->left);
    else {
        node* y = findMin(z->right);
        if(y != z->right){
            transplant(y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        transplant(z, y);
        y->left = z->left;
        y->left->parent = y;
    }
}

// A node successor is the node with the smallest value above the value of a given node
// This represents the BST equivalent of the next sorted value
BinarySearchTree::node* BinarySearchTree::treeSuccessor(node* x){
    if(x->right != NULL)
        return findMin(x->right);
    else{
        node* y = x->parent;
        while(y != NULL && x == y->right){
            x = y;
            y = y->parent;
        }
        return y;
    }
}

// A node's predecessor is the node with the greatest value below the value of a given node
// This represents the BST equivalent of the previous sorted value. 
BinarySearchTree::node* BinarySearchTree::treePredecessor(node* x){
    if(x->left != NULL)
        return findMax(x->left);
    else{
        node* y = x->parent;
        while(y != NULL && x == y->left){
            x = y;
            y = y->parent;
        }
        return y;
    }
}

// Uses the BST property to binarily search for a given node or value. 
BinarySearchTree::node* BinarySearchTree::treeSearch(node* x, int key){      //iterative search
    while(x != NULL && key != x->key){
        if(key < x->key)
            x = x->left;
        else x = x->right;
    }
    return x;
}

// Utility funtion to replace a subtree with another subtree
void BinarySearchTree::transplant(node* u, node* v){
    if(u->parent == NULL)           //if U has no parent
        root = v;                   //  V is the root
    else if(u == u->parent->left)   //else if u is a left child
        u->parent->left = v;        //  v replaces u
    else u->parent->right = v;      // else u is a right child, v replaces u
    if(v != NULL)                   // if v is null
        v->parent = u->parent;      //  v's parent becomes u's parent
}

//helper function to validate user input
bool checkCin(){
    if(std::cin.fail()){
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::min(), '\n');

        return false;
    }
    return true;
}
//////////////////////////////////////////////////////////////////////////////
//
//COMMENTED OUT FOR LINKING PURPOSES
//
//////////////////////////////////////////////////////////////////////////////
/* <= remove to test methods. 
int main(){
    using namespace std;

    BinarySearchTree bst;
    int choice, key;

    while(true){
        cout << endl << "\n";
        cout <<  "Binary Search Tree Example \n";
        cout << " ----------------------------- \n";
        cout << " 1.  Insert a Node \n";
        cout << " 2.  Delete a Node\n";
        cout << " 3.  Search for a key\n";
        cout << " 4.  Pre-Order Traversal \n";
        cout << " 5.  Post-Order Traversal \n";
        cout << " 6.  In-Order Traversal\n";
        cout << " 7.  Find Max\n";
        cout << " 8.  Remove Max\n";
        cout << " 9.  Find Min\n";
        cout << " 10. Remove Min\n";
        cout << " 11. Successor\n";
        cout << " 12. Predecessor\n";
        cout << " 13. Exit\n";
        cout << " Enter your choice : \n";
        cin >> choice;

        switch(choice){
            case 1: 
                cout << "\nEnter key to be Inserted (integer value) : ";
                cin >> key;
                if(!checkCin())
                    std::cerr << "Error: invalid input. Please try again...\n" << std::endl;
                else{
                    bst.treeInsert(key);
                    cout << "\n " << key << " was successfully inserted!";
                }
                break;

            case 2:   
                cout << "\nEnter key to be deleted (integer value) : ";
                cin >> key;
                if(!checkCin())
                    std::cerr << "Error: invalid input. Please try again...\n" << std::endl;
                else{
                    if(bst.treeSearch(bst.root, key) != NULL){
                        bst.treeDelete(bst.treeSearch(bst.root, key));
                        cout << "\n " << key << " was successfully deleted!";
                    }
                    else cout << "\n " << key << " could not be found. . .\n";
                }
                break;

            case 3: 
                cout << "\nEnter key to search for in the BS-tree : ";
                cin >> key;
                if(!checkCin())
                    std::cerr << "Error: invalid input. Please try again...\n" << std::endl;
                else{
                    if(bst.treeSearch(bst.root, key) != NULL){
                        cout << bst.treeSearch(bst.root, key)->key << " was found!\n";
                        if(bst.treeSearch(bst.root, key)->parent != NULL) cout << bst.treeSearch(bst.root, key)->key << "->parent:  " << bst.treeSearch(bst.root, key)->parent->key << "\n";
                        if(bst.treeSearch(bst.root, key)->left != NULL)   cout << bst.treeSearch(bst.root, key)->key << "->left: " << bst.treeSearch(bst.root, key)->left->key << "\n";
                        if(bst.treeSearch(bst.root, key)->right != NULL)  cout << bst.treeSearch(bst.root, key)->key << "->right: " << bst.treeSearch(bst.root, key)->right->key << "\n";
                    }
                    else cout << key << " was not found. . .\n";
                }
                break;
            
            case 4:
                cout << " Pre-Order Traversal \n";
                cout << " --------------------\n";
                bst.preOrderTreeWalk(bst.root);
                break;
            
            case 5:
                cout << "\n Post-Order Traversal \n";
                cout << " --------------------\n";
                bst.postOrderTreeWalk(bst.root);
                break;

            case 6:
                cout << "\n In-Order Traversal \n";
                cout << " --------------------\n";
                bst.inOrderTreeWalk(bst.root);
                break;

            case 7:
                cout << "\n Max key found is: ";
                cout << bst.findMax(bst.root)->key << "\n";
                break;

            case 8:
                cout << "\n Max key " << bst.findMax(bst.root)->key;
                bst.removeMax();
                cout << " was removed. . .\n";
                break;

            case 9:
                cout << "\n Min key found is: ";
                cout << bst.findMin(bst.root)->key << "\n";
                break;

            case 10:
                cout << "\n Min key " << bst.findMin(bst.root)->key;
                bst.removeMin();
                cout << " was removed. . .\n";
                break;
                
            case 11:
                cout << "Please insert key to find the successor of : ";
                cin >> key;
                if(!checkCin())
                    std::cerr << "Error: invalid input. Please try again...\n" << std::endl;
                else{
                    if(bst.treeSearch(bst.root, key) != NULL){
                        cout << "\nThe Predecessor of the node containing " << key << " is ";
                        cout << bst.treeSuccessor(bst.treeSearch(bst.root, key))->key << "\n";
                    }
                    else cout << key << " could not be found. . .\n";
                }
                break;

            case 12:
                cout << "Please insert key to find the predecessor of : ";
                cin >> key;
                if(!checkCin())
                    std::cerr << "Error: invalid input. Please try again...\n" << std::endl;
                else{
                    if(bst.treeSearch(bst.root, key) != NULL){
                        cout << "\nThe Predecessor of the node containing " << key << " is ";
                        cout << bst.treePredecessor(bst.treeSearch(bst.root, key))->key << "\n";
                    }
                    else cout << key << " could not be found. . .\n";
                }
                break;

            case 13:
                system("pause");
                return 0;
                break;
            
            default:
                cout << "Invalid choice\n";
                break;
        }
    }
}
*/