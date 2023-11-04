// priorityqueue.h
//
// TODO:  write this header comment
#pragma once

#include <iostream>
#include <sstream>
#include <string>
#include <set>
#include <algorithm>
#include <vector>

using namespace std;

template<typename T>
class priorityqueue {
private:
    struct NODE {
        int priority;  // used to build BST
        T value;  // stored data for the p-queue
        bool dup;  // marked true when there are duplicate priorities
        NODE* parent;  // links back to parent
        NODE* link;  // links to linked list of NODES with duplicate priorities
        NODE* left;  // links to left child
        NODE* right;  // links to right child
    };
    NODE* root;  // pointer to root node of the BST
    int size;  // # of elements in the pqueue
    NODE* curr;  // pointer to next item in pqueue (see begin and next)
    
public:
    //
    // default constructor:
    //
    // Creates an empty priority queue.
    // O(1)
    //
    priorityqueue() {
        root = nullptr;
        size = 0;
        curr = nullptr;
    }

    //clear() helper function to delete each nodes in the linked list
    void deleteLinkedList (NODE* pHead) {
      if (pHead == NULL) {
        return;
      }
      deleteLinkedList(pHead->link);
      delete pHead;
    }
    //clear() helper function this function clears the binary tree of
    //its allocated memory.
    void deletingTree (NODE* tree) {

      if (tree == NULL) {
          return;
      }
      
      deletingTree(tree->left);
      deletingTree(tree->right);
      //cout << "\n Deleting node: " << tree->value;
      if (tree->dup == true) {
        deleteLinkedList(tree);
      } else {
        delete tree;
      } 
    }

    //
    // operator=
    //
    // Clears "this" tree and then makes a copy of the "other" tree.
    // Sets all member variables appropriately.
    // O(n), where n is total number of nodes in custom BST
    //
    priorityqueue& operator=(const priorityqueue& other) {
        // TO DO: write this function.
        if (this == &other) {
          return *this;
        }
        size = other.size;
        curr = other.curr;
        deletingTree(root);

        root = other.root;

        return *this;

    }
    
    //
    // clear:
    //
    // Frees the memory associated with the priority queue but is public.
    // O(n), where n is total number of nodes in custom BST
    //
    void clear() {
        // TO DO: write this function.
        deletingTree(root);
    }
    
    //
    // destructor:
    //
    // Frees the memory associated with the priority queue.
    // O(n), where n is total number of nodes in custom BST
    //
    ~priorityqueue() {
        // TO DO: write this function.
        //(*this).clear();
    }


    //enqueue() helper function finds if the node that is being added
    //already exists within the BST PQ
    bool searchDuplicate (int priority) {
      NODE* cur = root;
      bool found = false;

      //search binary tree to see if the new node already exists
      
      while (cur != NULL) {
        if (cur->priority == priority) {
          cur->dup = true;
          found = true;
          break;
        } else if (priority < cur->priority) {
          cur = cur->left;
        } else {
          cur = cur->right;
        }
      }
      return found;
    }

    //enqueue() helper function this function is used to add a new node 
    //to the BST.
    void insertingNode (NODE*& newNode) {
      NODE* cur = root;

      while (cur != NULL) {
        if (newNode->priority < cur->priority) {
          if (cur->left == NULL) {
            cur->left = newNode;
            newNode->link = NULL;
            newNode->parent = cur;
            break;
          } else {
            cur = cur->left;
          }
        } else if (newNode->priority > cur->priority) {
          if (cur->right == NULL) {
            cur->right = newNode;
            newNode->link = NULL;
            newNode->parent = cur;
            break;
          } else {
            cur = cur->right;
          }
        } else if (newNode->priority == cur->priority) {
          
          while (cur->link != NULL) {
            cur = cur->link;
          }
          newNode->link = NULL;
          newNode->parent = cur;
          newNode->right = NULL;
          newNode->left = NULL;
          newNode->dup = true;
          cur->link = newNode;
          
          break;
        } else {
          cout << "Error didn't find spot to insert node to tree (enqueue function)/n";
        }
      }
      newNode->right = NULL;
      newNode->left = NULL;
      size++;
    }
    
    //
    // enqueue:
    //
    // Inserts the value into the custom BST in the correct location based on
    // priority.
    // O(logn + m), where n is number of unique nodes in tree and m is number of
    // duplicate priorities
    //
vector<int> allPriorities;
    void enqueue(T value, int priority) {
        
        
        // TO DO: write this function.
      NODE* newNode = new NODE;
      newNode->priority = priority;
      allPriorities.push_back(priority);
      newNode->value = value;
      if (size == 0) {
        
        newNode->dup = false;
        newNode->parent = NULL;
        newNode->left = NULL;
        newNode->right = NULL;
        newNode->link = NULL;
        size++;
        root = newNode;
        return;
      }
      
      newNode->dup = searchDuplicate(priority);
      insertingNode(newNode);
    }

  //dequeue() helper function this is used to find the left most node
  //in the BST
  void leftMostNode (NODE* tree, NODE*& leftNode) {
    if (tree->left == NULL) {
      leftNode = tree;
      return;
    }
    leftMostNode(tree->left, leftNode);
  }

  //dequeue() helper function this is used to handle cases of when there
  //is a linked list within the node that is being dequeued
  void dequeueLL (NODE* leftNode) {
    NODE* parentNode = leftNode->parent;
    //cycles out each node as the root node of the tree when there is
    //no other parentNodes
    if (parentNode == NULL) {
      if (leftNode->link != NULL) {
        root = leftNode->link;
        leftNode->link->parent = NULL;
      } else {
        root = NULL;
      }
    } else {
      //dequeueing node to the left of the parent node
      if (parentNode->left == leftNode) {
        if (leftNode->link != NULL) {
          parentNode->left = leftNode->link;
          leftNode->link->parent = parentNode;
          if (leftNode->right != NULL) {
            //rerouting the pointers to connect correctly
            leftNode->link->right = leftNode->right;
            leftNode->right->parent = leftNode->link;
          }
        }
        //dequeueing node to the right of parent node
        }
      if (leftNode->link->link == NULL) {
        leftNode->link->dup = false;
      }
    }
  }
  //dequeue() this function is used to handle any other cases other than
  // when there is a linked list at the node that is being dequeued.
  void dequeueNoLL (NODE* leftNode) {
    //made to help keep track of everything rather than
    //having a lot of arrows
    NODE* parentNode = leftNode->parent;

    //checks if parent is NULL so we can remake the root node
    if (parentNode == NULL) {
      if (leftNode->right != NULL) {
        root = leftNode->right;
        leftNode->right->parent = NULL;
      } else {
        //if there are no more nodes in the tree to be used as the root
        root = NULL;
      }
      //all other cases without a linked list node as leftNode
    } else {
      if (parentNode->left == leftNode) {
        if (leftNode->right != NULL) {
          parentNode->left = leftNode->right;
          leftNode->right->parent = parentNode;
        } else {
          parentNode->left = leftNode->right;
        }
        //when the node being dequeued is to the right of the parent/*
      }
    }
  }

    //
    // dequeue:
    //
    // returns the value of the next element in the priority queue and removes
    // the element from the priority queue.
    // O(logn + m), where n is number of unique nodes in tree and m is number of
    // duplicate priorities
    //
  T dequeue() {
        
        
    // TO DO: write this function.
    NODE* leftNode;
    leftMostNode(root, leftNode);
    if (root != NULL) {
      T valueOut = leftNode->value;
      if (leftNode->dup) {
        dequeueLL(leftNode);
      } else {
        dequeueNoLL(leftNode);
      }
      size--;
      //cout << valueOut << endl;
      delete leftNode;
      return valueOut;
    } else if (root == NULL) {
      return "empty tree";
    }
    

     // TO DO: update this return
    }
    
    //
    // Size:
    //
    // Returns the # of elements in the priority queue, 0 if empty.
    // O(1)
    //
    int Size() {
        return size; // TO DO: update this return
    }


  //This function is used to initialize the curr pointer to the left
  //most node within the tree.
    void movingCurr (NODE* tree) {
      if (tree->left == NULL) {
        curr = tree;
        return;
      }
      movingCurr(tree->left);
    }
    
    //
    // begin
    //
    // Resets internal state for an inorder traversal.  After the
    // call to begin(), the internal state denotes the first inorder
    // node; this ensure that first call to next() function returns
    // the first inorder node value.
    //
    // O(logn), where n is number of unique nodes in tree
    //
    // Example usage:
    //    pq.begin();
    //    while (tree.next(value, priority)) {
    //      cout << priority << " value: " << value << endl;
    //    }
    //    cout << priority << " value: " << value << endl;
    void begin() {
        // TO DO: write this function.
      movingCurr(root);
    }

  //next() helper function this function goes down the right subtree of
  //a node then stops at its left most node
    void rightSubtreeNode (NODE* temp) {
      if (temp->left == NULL) {
        curr = temp;
        return;
      }
      //cout << "Hello 2\n";
      rightSubtreeNode(temp->left);
      
    }
  //next() helper function this function goes up the BST to find a node
  //which is greater than the curr node in terms of the priority integer
  //value
    void parentNodes (NODE* temp, int tempPriority) {
      
      while (temp->priority <= tempPriority) {
        temp = temp->parent;
      }
      curr = temp;
    }
  //next() helper function this function goes into the linked list of a
  //node that has dup = true on it then iterates through it and returns
  //back to the start of the list and increments down a node
  void dupTrue (NODE* temp, int tempPriority) {
    //if statement to increment only once per call on the function.
    if (temp->link != NULL) {
      temp = temp->link;
      curr = temp;
      //return to leave function after updating curr
      return;
    } 
    //once the linked list's end has been reached return back to the beginning on the list
    //using the the parent pointer and only iterating when the priority is the same
    if (temp->link == NULL) {
      //max used to stop iterating and stop calling next function
      int max = *max_element(allPriorities.begin(), allPriorities.end());
      if (temp->priority == max) {
        return;
      }
      while (temp->parent != NULL && temp->parent->priority == tempPriority) {
        temp = temp->parent;
        //cout << "Hello 5\n";
      }
      
      //cout << "Hello 6\n";
      //need to increment away to prevent getting into a infinite loop
      if (temp->right != NULL) {
        //if the right subtree of the node at the start of the linked is is not NULL go down it
        rightSubtreeNode(temp->right);
      } else {
        //if the right subtree is null go up the parent pointers until it finds a priority
        //number that is greater than the priority in the linked list
        parentNodes(temp->parent, temp->priority);
      }
    }
  }

  //next() helper function
    

    //
    // next
    //
    // Uses the internal state to return the next inorder priority, and
    // then advances the internal state in anticipation of future
    // calls.  If a value/priority are in fact returned (via the reference
    // parameter), true is also returned.
    //
    // False is returned when the internal state has reached null,
    // meaning no more values/priorities are available.  This is the end of the
    // inorder traversal.
    //
    // O(logn), where n is the number of unique nodes in tree
    //
    // Example usage:
    //    pq.begin();
    //    while (pq.next(value, priority)) {
    //      cout << priority << " value: " << value << endl;
    //    }
    //    cout << priority << " value: " << value << endl;
    //
    bool next(T& value, int &priority) {
      NODE* temp = curr;
      int max = *max_element(allPriorities.begin(), allPriorities.end());

      //cout << curr->priority << " " << "value: " << curr->value << endl;
      
      if (curr->priority == max && curr->link == NULL) {
        value = curr->value;
        priority = curr->priority;
        return false;
      } else if (temp->dup == true) {
        //cout << "1\n";
        value = curr->value;
        priority = curr->priority;
        dupTrue(temp, temp->priority);
        return true;
      } else if (curr->right != NULL) {
        //cout << "2\n";
        value = curr->value;
        priority = curr->priority;
        rightSubtreeNode(temp->right);
        return true;
      } else {
        //cout << "3\n";
        value = curr->value;
        priority = curr->priority;
        parentNodes(temp->parent, temp->priority);
        
        return true;
      }
      return false;
         // TO DO: update this return
    }

  //toString() helper function this function is used to iterate through
  //the BST in order from lowest priority integer value to the greatest.
    void inorderTraversal (ostream& output, NODE* cur) {
      
      if (cur == NULL) {
        return;
      }
      
      inorderTraversal(output, cur->left);
      output << cur->priority << " value: " << cur->value << "\n";
      NODE* temp;
      
      if (cur->dup == true) {
        temp = cur;
      }
      
      while (cur->dup == true && temp->link != NULL) {
        temp = temp->link;
        output << temp->priority << " value: " << temp->value << "\n";
      }
      inorderTraversal(output, cur->right);
    }
    
    //
    // toString:
    //
    // Returns a string of the entire priority queue, in order.  Format:
    // "1 value: Ben
    //  2 value: Jen
    //  2 value: Sven
    //  3 value: Gwen"
    //
    string toString() {
        
        
        // TO DO: write this function
      string str = "";
      NODE* cur = root;

      stringstream madeString;

      //NOTE:: CHANGE COUT TO SSTREAM LATER
      inorderTraversal(madeString, cur);
      str = madeString.str();
      
      return str; // TO DO: update this return
    }

  //peek() helper function this is used to iterate to the left most node
  //node in the tree and update a reference parameter accordingly.
  void peekHelper (NODE* tree, NODE*& peekedSpot) {
      if (tree->left == NULL) {
        peekedSpot = tree;
        return;
      }
      peekHelper (tree->left, peekedSpot);
    }
    
    //
    // peek:
    //
    // returns the value of the next element in the priority queue but does not
    // remove the item from the priority queue.
    // O(logn + m), where n is number of unique nodes in tree and m is number of
    // duplicate priorities
    //
    T peek() {
        NODE* peekedSpot;
        peekHelper(root, peekedSpot);
        // TO DO: write this function.
        T valueOut = peekedSpot->value;
        return valueOut; // TO DO: update this return
    }
    
    //
    // ==operator
    //
    // Returns true if this priority queue as the priority queue passed in as
    // other.  Otherwise returns false.
    // O(n), where n is total number of nodes in custom BST
    //
//****** referenced from geeks for geeks comparing two BSTs for 
//equavalence. This function checks each node in the BST to see if it
//has the same values accross both of them.
  int isIdentical ( NODE* root1,  NODE* root2) const {
    if (root1 == NULL && root2 == NULL) {
      return 1;
    } else if (root1 == NULL || root2 == NULL) {
      return 0;
    } else {
      if (root1->value == root2->value &&
          isIdentical(root1->left, root2->left) && 
          isIdentical(root1->right, root2->right)) {
        return 1;
      } else
        return 0;
    }
  }

    //Checks for equivalence between two BSTs.
    bool operator==(const priorityqueue& other) const {
        // TO DO: write this function.
      if (isIdentical(root, other.root) && size == other.size) {
        return true; // TO DO: update this return
      } else {
        return false; // TO DO: update this return
      }
    }
    
    //
    // getRoot - Do not edit/change!
    //
    // Used for testing the BST.
    // return the root node for testing.
    //
    void* getRoot() {
        return root;
    }
};
