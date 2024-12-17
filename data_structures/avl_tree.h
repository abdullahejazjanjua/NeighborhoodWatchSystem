#ifndef AVLTREE_H
#define AVLTREE_H

#include <iostream>
#include <algorithm>

using namespace std;

template <typename T>
struct Node_tree 
{
    T obj; // The object storing details
    int key;
    Node_tree* left;
    Node_tree* right;
    int height;

    Node_tree(T object, int k) : obj(object), key(k), left(nullptr), right(nullptr), height(1) {}
};


template <typename T>
class AVL {
private:
    Node_tree<T>* root;

    int getHeight(Node_tree<T>* node) {
        return node ? node->height : 0;
    }

    int getBalanceFactor(Node_tree<T>* node) {
        return node ? getHeight(node->left) - getHeight(node->right) : 0;
    }

    Node_tree<T>* leftRotate(Node_tree<T>* x) {
        Node_tree<T>* y = x->right;
        Node_tree<T>* T2 = y->left;

        y->left = x;
        x->right = T2;

        y->height = 1 + max(getHeight(y->left), getHeight(y->right));
        x->height = 1 + max(getHeight(x->left), getHeight(x->right));

        return y;
    }


    Node_tree<T>* rightRotate(Node_tree<T>* y) {
        Node_tree<T>* x = y->left;
        Node_tree<T>* T2 = x->right;

        x->right = y;
        y->left = T2;

        y->height = 1 + max(getHeight(y->left), getHeight(y->right));
        x->height = 1 + max(getHeight(x->left), getHeight(x->right));

        return x;
    }


    Node_tree<T>* add(Node_tree<T>* node, T val, int key) {
        if (!node) return new Node_tree<T>(val, key);

        if (key < node->key) {
            node->left = add(node->left, val, key);
        } else if (key > node->key) {
            node->right = add(node->right, val, key);
        }

        node->height = 1 + max(getHeight(node->left), getHeight(node->right));

        int balance = getBalanceFactor(node);

        if (balance > 1 && key < node->left->key) {
            return rightRotate(node);
        }
        if (balance > 1 && key > node->left->key) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
        if (balance < -1 && key > node->right->key) {
            return leftRotate(node);
        }
        if (balance < -1 && key < node->right->key) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    Node_tree<T>* retrieveResident(Node_tree<T>* node, int key) 
    {
        if (node == NULL) 
        {
            return NULL; // Not found
        }

        if (node->key == key) 
        {
            return node; // Node found
        }

        if (key < node->key) 
        {
            return retrieveResident(node->left, key); 
        } 
        else 
        {
            return retrieveResident(node->right, key);  
        }
    }

   


    void preOrder(Node_tree<T>* node) 
    {
        if (!node) return;
        node->obj.print_details(); // Call the object's function
        preOrder(node->left);
        preOrder(node->right);
    }

    Node_tree<T>* deleteNode(Node_tree<T>* node, int key) 
    {
        if (!node) return node;

        if (key < node->key) 
        {
            node->left = deleteNode(node->left, key);
        } 
        else if (key > node->key) 
        {
            node->right = deleteNode(node->right, key);
        } 
        else 
        {
            if (!node->left || !node->right) 
            {
                Node_tree<T>* temp = node->left ? node->left : node->right;
                delete node;
                return temp;
            }

            Node_tree<T>* temp = inOrderPredecessor(node);
            node->val = temp->val;
            node->key = temp->key;
            node->left = deleteNode(node->left, temp->key);
        }

        node->height = 1 + max(getHeight(node->left), getHeight(node->right));
        int balance = getBalanceFactor(node);

        if (balance > 1 && getBalanceFactor(node->left) >= 0) 
        {
            return rightRotate(node);
        }
        if (balance > 1 && getBalanceFactor(node->left) < 0) 
        {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
        if (balance < -1 && getBalanceFactor(node->right) <= 0) 
        {
            return leftRotate(node);
        }
        if (balance < -1 && getBalanceFactor(node->right) > 0) 
        {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    Node_tree<T>* inOrderPredecessor(Node_tree<T>* node) 
    {
        node = node->left;
        while (node->right) {
            node = node->right;
        }
        return node;
    }

public:

    AVL() : root(nullptr) {}

    void insert(T val, int key) 
    {
        root = add(root, val, key);
    }

    void traverseTree() 
    {
        preOrder(root);
    }

    void deletion(int key) 
    {
        root = deleteNode(root, key);
    }
    Node_tree<T>* getResidentInfo(int key, bool GetObject=false) 
    {
        Node_tree<T>* result = retrieveResident(root, key);
        if (result) 
        {
            if(GetObject)
            {
                return result;
            }
            else
            {
                result->obj.introduceNeightbour();
                return nullptr;
            }
        } 
        else 
        {
            cout << "\nSeems like you have gone out of this neighbourhood\n";
            return nullptr;
        }
    }


};

#endif