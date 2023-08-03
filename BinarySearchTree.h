#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H

#include <iostream>
#include <cstdlib>
#include <string>
#include <limits>

class BinarySearchTree{
    private:
        class node{
            public:
                node* left;
                node* right;
                node* parent;
                int key;
                std::string data;
        };
        void destroyTree(node* x){
            if(x != NULL){
                destroyTree(x->left);
                destroyTree(x->right);
                delete x;
            }
        }

    public:
        node* root;
        BinarySearchTree();
        ~BinarySearchTree();
        bool isEmpty();
        BinarySearchTree::node* findMin(node* x);
        void removeMin();
        BinarySearchTree::node* findMax(node* x);
        void removeMax();

        void preOrderTreeWalk(node*);
        void inOrderTreeWalk(node*);
        void postOrderTreeWalk(node*);

        void inOrderTreeWalk_flightName(node*);

        void treeInsert(int);
        void treeInsert(int, std::string);
        void treeDelete(node* z);
        BinarySearchTree::node* treeSuccessor(node*);
        BinarySearchTree::node* treePredecessor(node*);
        BinarySearchTree::node* treeSearch(node* x, int key);
        void transplant(node* u, node* v);

};
#endif // BINARYSEARCHTREE_H
