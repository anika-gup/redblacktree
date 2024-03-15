// main.cpp

#include <iostream>
#include <cstring>
#include "node.h"
#include <fstream>

using namespace std;

// 0 is red, 1 is black (for node->getColor(););


void ADD(node* &root, node* &current, node* parent, node* grandparent, int data);
void PRINT(node* root, int count);
void rotateleft(node* &parent, node* &root);
void rotateright(node* &parent, node* &root);
int main() {

  /*
    // testing basic stuff
  node* root = new node(24);
  root->setColor(0);
  cout << root->getColor() << endl;
  cout << root->getValue() << endl;
  */

  int quit =0;
  node* root = NULL;

  while (quit==0) {
    cout << "options are:  ADD   READ   PRINT   QUIT" << endl;
    char input[50];

    cin >> input;

    if (strcmp(input, "ADD")==0) {
      cout << "What number do you want to add?" << endl;
      int n;
      cin >> n;
      ADD(root, root, root, root, n);
    }
    else if (strcmp(input, "READ")==0) {
      cout << "what's the name of your file" << endl;
      char fileName[30];
      cin >> fileName;

      ifstream fin;
      fin.open(fileName);
      int inpt;
      while(fin>>inpt) {
	ADD(root, root, root, root, inpt);
      }
    }

    else if (strcmp(input, "PRINT")==0) {
      // print
      PRINT(root, 0);
    }

    else if (strcmp(input, "QUIT")==0) {
      quit = 1;
    }


  }
  
  return 0;
}


void ADD(node* &root, node* &current, node* parent, node* grandparent, int data) {
  //  cout << "in the adding function." << endl;
  //cout << "adding: " << data << endl;

  
  // REMINDER: 0 is red, 1 is black
  //cout << "printing" << endl;
  //PRINT(root, 0);
  //base cases
  if (!root) {

    // case 1, where root is empty
    root = new node(data);
    root->setParent(NULL);
    root->setColor(1);
  }

  else if (current==NULL) {

    // adding the node in 
    current = new node(data);
    current->setColor(0);
    if (current->getValue() < parent->getValue()) {
      parent->setLeft(current);
      // current->setParent(parent);
    }
    else {
      parent->setRight(current);
     
    }
    current->setParent(parent);
    cout << data << "'s parent is: " << parent->getValue() << endl;

    //while
    node* currentNode=current;
    
    while (currentNode->getParent()->getColor()==0) {
      // if the parent is red, this violates property that current and parent can't both be red.
      // now check about if uncle is red or black



      //assigning uncle
      node* uncle = NULL;
      
      node* grandparent = currentNode->getParent()->getParent();
      node* parent = currentNode->getParent();

      if (grandparent==NULL) {
	break;
      }
      if (grandparent->getRight()==currentNode->getParent()) {
	uncle = grandparent->getLeft();
	// parent is to the right of the grandparent

	if (uncle!=NULL && uncle->getColor()==0) { // error is the else for null isn't good
	  //if (uncle->getColor()==0) {
	    // uncle is red, case 3.1
	    cout << "unnnnnnnncle  is red" << endl;
	    uncle->setColor(1);
	    parent->setColor(1);
	    parent->getParent()->setColor(0);
	    if (grandparent!=root) {
	      currentNode = grandparent;
	    }
	    
	
	else if (currentNode->getValue() < parent->getValue()) {
	  // current is ot the left of parent
	  rotateright(parent, root);
	  currentNode = parent;
	}
	else if (currentNode->getValue() > parent->getValue()) {
	  rotateleft(grandparent, root);
	  grandparent->setColor(0);
	  grandparent->getParent()->setColor(1);
	  
	}

	

      }

   }
      else {
	uncle = grandparent->getRight();
	if (uncle!=NULL && uncle->getColor()==0) {
	    uncle->setColor(1);
	    parent->setColor(1);
	    grandparent->setColor(0);
	    if (grandparent!=root) {
	      currentNode = grandparent;
	    }
	}

	else if (currentNode->getValue() < parent->getValue()) {

	  // case 3.2.3
	  // parent is left child of g, current is left of parent
	  
	  rotateright(grandparent, root);
	  grandparent->setColor(0);
	  grandparent->getParent()->setColor(1);
	}
	
	else {
	  rotateleft(parent, root);
	  currentNode = parent;
	}
        
      }

      root->setColor(1);


        

      

      //PRINT(current, 0);


      root->setColor(1);
      //cout << "yet another lovely day within the while loop!" << endl;
    }
    root->setColor(1);
    PRINT(root, 0);


  }



  
  //recursive cases

  // same as binary search tree:
  else if (data < current->getValue()) {
    node* l = current->getLeft();
    ADD(root, l,current, parent, data);
  }
  else {
    node* r = current->getRight();
    ADD(root, r, current, parent, data);
  }

  

  
  
  
  //return root;
}


void PRINT(node* root, int count) {

  /*for (int a=0; a<count; a++) {
    cout << '\t' ;
  }
  */
  
  if (root==NULL) {
    return;
  }
  if (root->getLeft()!=NULL) {
    PRINT(root->getLeft(), (count+1));
  }

  for (int b=0; b<count; b++) {
    cout << "\t";
  }

  cout << root->getValue() << "," << root->getColor() << endl;
  cout << endl;
  if (root->getRight()!=NULL) {
    PRINT(root->getRight(), (count+1));
  }



  
}


void rotateleft(node* &parent, node* & root) {
  

  
  node* up= parent->getParent();
  
  node* templeft = parent->getLeft();
  node* newparent = parent->getRight();
  node* templeftchild = NULL;
  if (parent->getRight()!=NULL) {
    templeftchild = parent->getRight()->getLeft();
  }
  //node* templeftchild = parent->getRight()->getLeft();

  if (up==NULL) {
    // this means the parent is the root
    root = newparent;
    root->setParent(NULL);
    cout << "setting new root:)" << endl;
    
  }
  else if (parent->getValue() > up->getValue() ) {
    // change up->setRight()
    up->setRight(newparent);
    newparent->setParent(up);
  }
  else {
    // change up->setLeft();
    up->setLeft(newparent);
    newparent->setParent(up);
  }
  newparent->setLeft(parent);
  parent->setParent(newparent);



  

  if (templeftchild!=NULL) {
    cout << "temp left chidl notnull: " << endl;
    cout << templeftchild->getValue() << endl;
    parent->setRight(templeftchild);
    templeftchild->setParent(parent);
  }

  else {
    cout << "setting parent right to null, parent is: " << parent->getValue() << endl;
    parent->setRight(NULL);
  }
  //  parent->setRight(NULL);
  

    
}

void rotateright(node* &parent, node* &root) {




  node* up = parent->getParent();

  node* newparent = parent->getLeft();

  node* temprightchild = newparent->getRight();
  if (up==NULL) {
    root = newparent;
    root->setParent(NULL);
    
  }

  else if (parent->getValue() > up->getValue()) {
    up->setRight(newparent);
    newparent->setParent(up);
  }
  else {
    up->setLeft(newparent);
    newparent->setParent(up);
  }


  newparent->setRight(parent);
  parent->setParent(newparent);
  if (temprightchild!=NULL) {
    parent->setLeft(temprightchild);
    temprightchild->setParent(parent);
  }

  else {
    parent->setLeft(NULL);
  }
  
}
