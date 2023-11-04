// mymap.h
#pragma once

#include <iostream>
#include <sstream>
#include <map>

using namespace std;

template<typename keyType, typename valueType>
class mymap {
 private:
    struct NODE {
        keyType key;  // used to build BST
        valueType value;  // stored data for the map
        NODE* left;  // links to left child
        NODE* right;  // links to right child
        int nL;  // number of nodes in left subtree
        int nR;  // number of nodes in right subtree
        bool isThreaded;
    };
    NODE* root;  // pointer to root node of the BST
    int size;  // # of key/value pairs in the mymap

    //
    // iterator:
    // This iterator is used so that mymap will work with a foreach loop.
    //
    struct iterator {
     private:
        NODE* curr;  // points to current in-order node for begin/end

     public:
        iterator(NODE* node) {
            curr = node;
        }

        keyType operator *() {
            return curr -> key;
        }

        bool operator ==(const iterator& rhs) {
            return curr == rhs.curr;
        }

        bool operator !=(const iterator& rhs) {
            return curr != rhs.curr;
        }

        bool isDefault() {
            return !curr;
        }

        void operatorHelper () {

        }
        //
        // operator++:
        //
        // This function should advance curr to the next in-order node.
        // O(logN)
        //
        iterator operator++() {


            // TODO: write this function.
            if (curr != NULL) {
                if (curr->isThreaded) {
                    curr = curr->right;
                    return iterator(curr);
                }
                if (!curr->isThreaded) {
                    curr = curr->right;
                    if (curr != NULL) {
                        while (curr->left != NULL) {
                        curr = curr->left;
                        }
                    }
                    
                    
                return iterator(curr);
                }
            }
            

            return iterator(nullptr);  // TODO: Update this return.
        }
    };

 public:
    //
    // default constructor:
    //
    // Creates an empty mymap.
    // Time complexity: O(1)
    //
    mymap() {
        root = nullptr;
        size = 0;
    }


    //This function is a helper function of the copy constructor and the equal operator functions it uses preorder traversal and the
    //put function to properly copy a tree of the other mymap.
    void copyHelper (const NODE* other) {
        if (other == nullptr) {
            return;
        }
        put(other->key, other->value);

        copyHelper(other->left);
        if (!other->isThreaded) {
            copyHelper(other->right);
        }
    }

    //
    // copy constructor:
    //
    // Constructs a new mymap which is a copy of the "other" mymap.
    // Sets all member variables appropriately.
    // Time complexity: O(nlogn), where n is total number of nodes in threaded,
    // self-balancing BST.
    //
    mymap(const mymap& other) {
        root = nullptr;
        size = 0;
        copyHelper(other.root);

    }

    //
    // operator=:
    //
    // Clears "this" mymap and then makes a copy of the "other" mymap.
    // Sets all member variables appropriately.
    // Time complexity: O(nlogn), where n is total number of nodes in threaded,
    // self-balancing BST.
    //
    mymap& operator=(const mymap& other) {
        clear();
        copyHelper(other.root);
        return *this;
    }

    // clear helper function deletes the tree in post order traversal and increments the size down with each deletion.
    void deletingTree (NODE* cur) {
        if (cur == NULL) {
            return;
        }      
        deletingTree(cur->left);
        if (!cur->isThreaded && cur->right != nullptr) {
            deletingTree(cur->right);
        }
        size--;
        delete(cur);
    }

    // clear:
    //
    // Frees the memory associated with the mymap; can be used for testing.
    // Time complexity: O(n), where n is total number of nodes in threaded,
    // self-balancing BST.
    //
    void clear() {
        NODE* cur = root;
        deletingTree(cur);
        root = nullptr;
    }

    //
    // destructor:
    //
    // Frees the memory associated with the mymap.
    // Time complexity: O(n), where n is total number of nodes in threaded,
    // self-balancing BST.
    //
    ~mymap() {
        clear();
    }

    
    /*
    put function helper to place nodes in the BST when the node being inserted is not the root node
    */
   void insertingNode (NODE*& newNode) {

        NODE* cur = root;
        while (cur != NULL) {
            if (newNode->key < cur->key) {
                cur->nL = cur->nL + 1;
                if (cur->left == nullptr) {
                    cur->left = newNode;
                    newNode->isThreaded = true;
                    newNode->right = cur;
                    size++;
                    break;
                } else {
                    cur = cur->left;
                }
            } else if (newNode->key > cur->key) {
                cur->nR = cur->nR + 1;
                if (cur->isThreaded == true) {
                    newNode->right = cur->right;
                    newNode->isThreaded = true;
                    cur->isThreaded = false;
                    cur->right = newNode;
                    size++;
                    break;
                } else if (cur->right == nullptr) {
                    cur->right = newNode;
                    size++;
                    break;
                } else {
                    cur = cur->right;
                }
            } else if (newNode->key == cur->key) {
                cur->value = newNode->value;
                delete(newNode);
                break;
            }
        }
   }

    //
    // put:
    //
    // Inserts the key/value into the threaded, self-balancing BST based on
    // the key.
    // Time complexity: O(logn + mlogm), where n is total number of nodes in the
    // threaded, self-balancing BST and m is the number of nodes in the
    // sub-tree that needs to be re-balanced.
    // Space complexity: O(1)
    //
    void put(keyType key, valueType value) {


        // TODO: write this function.
        NODE* newNode = new NODE;
        newNode->key = key;
        newNode->value = value;
        newNode->left = nullptr;
        newNode->right = nullptr;
        newNode->nL = 0;
        newNode->nR = 0;
        newNode->isThreaded = false;
        if (size == 0) {
            size++;
            root = newNode;
            return;
        }
        insertingNode(newNode);

    }
    

    //
    // contains:
    // Returns true if the key is in mymap, return false if not.
    // Time complexity: O(logn), where n is total number of nodes in the
    // threaded, self-balancing BST
    //
    bool contains(keyType key) {

        NODE* cur = root;
        while (cur != nullptr) {
            if (key < cur->key) {
                cur = cur->left;
            } else if (key > cur->key) {
            // there is no right pointer in traditional traversal:
                if (cur->isThreaded) {
                    cur = nullptr;
                 } else {
                    cur = cur->right;
                }
            } else if (key == cur->key) {
                return true;
            }
        }
        return false;
        // TODO: write this function.
        // TODO: Update this return.
    }

    //
    // get:
    //
    // Returns the value for the given key; if the key is not found, the
    // default value, valueType(), is returned (but not added to mymap).
    // Time complexity: O(logn), where n is total number of nodes in the
    // threaded, self-balancing BST
    //
    valueType get(keyType key) {
        // TODO: write this function.
        NODE* cur = root;
        while (cur != nullptr) {
            if (key < cur->key) {
                cur = cur->left;
            } else if (key > cur->key) {
            // there is no right pointer in traditional traversal:
                if (cur->isThreaded) {
                    cur = nullptr;
                 } else {
                    cur = cur->right;
                }
            } else if (key == cur->key) {
                return cur->value;
            }
        }
        return valueType();
    }

    //
    // operator[]:
    //
    // Returns the value for the given key; if the key is not found,
    // the default value, valueType(), is returned (and the resulting new
    // key/value pair is inserted into the map).
    // Time complexity: O(logn + mlogm), where n is total number of nodes in the
    // threaded, self-balancing BST and m is the number of nodes in the
    // sub-trees that need to be re-balanced.
    // Space complexity: O(1)
    //
    valueType operator[](keyType key) {

        NODE* cur = root;
        while (cur != nullptr) {
            if (key < cur->key) {
                cur = cur->left;
            } else if (key > cur->key) {
                if (cur->isThreaded) {
                    cur = nullptr;
                 } else {
                    cur = cur->right;
                }
            } else if (key == cur->key) {
                return cur->value;
            }
        }
        put(key, valueType());
        return valueType();  // TODO: Update this return.
    }

    //
    // Size:
    //
    // Returns the # of key/value pairs in the mymap, 0 if empty.
    // O(1)
    //
    int Size() {
        return size;  // TODO: Update this return.
    }

    //
    // begin:
    //
    // returns an iterator to the first in order NODE.
    // Time complexity: O(logn), where n is total number of nodes in the
    // threaded, self-balancing BST
    //
    iterator begin() {

        NODE* curr = root;
        while (curr->left != NULL) {
            curr = curr->left;
        }
        // TODO: write this function.


        return iterator(curr);  // TODO: Update this return.
    }

    //
    // end:
    //
    // returns an iterator to the last in order NODE.
    // this function is given to you.
    // 
    // Time Complexity: O(1)
    //
    iterator end() {
        return iterator(nullptr);
    }

    /*
    toString() helper function this is used to build the string of the output using string stream.
    */
    void inorderTraversal (ostream &output, NODE* cur) {
        if (cur == NULL) {
            return;
        }
        inorderTraversal(output, cur->left);
        output << "key: " << cur->key << " value: " << cur->value << "\n";
        if (!cur->isThreaded) {
            inorderTraversal(output, cur->right);
        }
    }

    //
    // toString:
    //
    // Returns a string of the entire mymap, in order.
    // Format for 8/80, 15/150, 20/200:
    // "key: 8 value: 80\nkey: 15 value: 150\nkey: 20 value: 200\n
    // Time complexity: O(n), where n is total number of nodes in the
    // threaded, self-balancing BST
    //
    string toString() {


        // TODO: write this function.
        stringstream myString;
        NODE* cur = root;
        inorderTraversal(myString, cur);
        string str = myString.str();
        return str;
        // TODO: Update this return.
    }

    void inOrdertoVector (NODE* cur, vector<NODE*> &madeVector) {
        if (cur == NULL) {
            return;
        }
        inOrdertoVector(cur->left, madeVector);
        madeVector.push_back(cur);
        if (!cur->isThreaded) {
            inOrdertoVector(cur->right, madeVector);
        }
    }
    //
    // toVector:
    //
    // Returns a vector of the entire map, in order.  For 8/80, 15/150, 20/200:
    // {{8, 80}, {15, 150}, {20, 200}}
    // Time complexity: O(n), where n is total number of nodes in the
    // threaded, self-balancing BST
    //
    vector<NODE*> toVector() {

        NODE* cur = root;
        vector<NODE*> madeVector;
        inOrdertoVector(cur, madeVector);
        return madeVector;  // TODO: Update this return.
    }


    void preOrderBalanceCheck (ostream &output, NODE* cur) {
        if (cur == NULL) {
            return;
        }
        output << "key: " << cur->key << ", nL:" << cur->nL << ", nR:" << cur->nR << endl;
        preOrderBalanceCheck(output, cur->left);
        if (!cur->isThreaded) {
            preOrderBalanceCheck(output, cur->right);
        }
    }
};
