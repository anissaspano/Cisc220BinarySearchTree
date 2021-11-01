/*
 * bst.cpp
 *
 *  Created on: Oct 21, 2021
 *      Author: Chris Czerwinski and Anissa Spano
 */

#include "bst.hpp"
#include <stdlib.h>
#include <iostream>
using namespace std;
#include "bstNode.hpp"


//class bst {
//	bstNode *root;
//
//public:
//	bst();
//	bst(string f, string l, int n, string j);
//	bool insert(string f, string l, int n, string j);
//	bstNode *find(string l, string f);
//	void printTreeIO();
//	void printTreeIO(bstNode *n);
//	void printTreePre();
//	void printTreePre(bstNode *n);
//	void printTreePost();
//	void printTreePost(bstNode *n);
//	void clearTree();
//	void clearTree(bstNode *tmp);
//	bstNode *removeNoKids(bstNode *tmp);
//	bstNode *removeOneKid(bstNode *tmp, bool leftFlag);
//	bstNode *remove(string f, string l);
//	void setHeight(bstNode *n);
	bst::bst() { // empty constructor
		root = NULL;
	}

	bst::bst(string f, string l, int n, string j) { // constructor that forms the root
		root = new bstNode(f,l,n,j);
	}
	bool bst::insert(string f, string l, int n, string j){
		bstNode *parent, *tmp;
		if (root == NULL){
			root = new bstNode(f,l,n,j);
			setHeight(root);
			return true;
		}else{
			tmp = root;
			bool lastMove; //false for left true for right
			while (tmp!=NULL){
				parent = tmp;
				if(l>parent->student->last){
					tmp = parent->right;
					lastMove = true;
				}else if(l<parent->student->last){
					tmp = parent->left;
					lastMove = false;
				}else if(f>parent->student->first){
					tmp = parent->right;
					lastMove = true;
				}else{
					tmp = parent->left;
					lastMove = false;
				}
			}// get tmp to a NULL value
			tmp = new bstNode(f,l,n,j);
			if(lastMove){
				parent->right = tmp;
				tmp->parent = parent;
			}else{
				parent->left = tmp;
				tmp->parent = parent;
			}
			tmp->height = 1;
			setHeight(tmp);
			return true;
		}
		return false;
	}

	bstNode* bst::find(string l, string f){
		bstNode* tmp = root;
		int ct = 1;
		while(tmp!= NULL && (tmp->student->last!=l || tmp->student->first != f)){
			if(l>tmp->student->last){
				tmp = tmp->right;
			}else if(l<tmp->student->last){
				tmp = tmp->left;
			}else if(f>tmp->student->first){
				tmp = tmp->right;
			}else{
				tmp = tmp->left;
			}ct++;
		}
		if(tmp==NULL){
			cout<<"Not in Tree :(" <<endl;
			return tmp;
		}
		tmp->printNode();
		cout << "found in " << ct << " comparisons" << endl;
		return tmp;
	}

	void bst::printTreeIO(bstNode *n){
		if (n==NULL){
			return;
		}
		else{
			printTreeIO(n->left);
			n->printNode();
			printTreeIO(n->right);
		}
	}

	void bst::printTreePre(bstNode *n){
		if(n==NULL){
			return;
		}
		else{
			n->printNode();
			printTreePre(n->left);
			printTreePre(n->right);
		}
	}

	void bst::printTreePost(bstNode *n){
		if(n==NULL){
			return;
		}
		else{
			printTreePost(n->left);
			printTreePost(n->right);
			n->printNode();
		}
	}
	bstNode* bst::remove(string l, string f){
		bstNode *tmp = find(l,f);
		int childCt = 0;
		bool leftFlag;
		leftFlag= tmp->left!=NULL?true:false;
		childCt = leftFlag?childCt+1:childCt;
		childCt = tmp->right!=NULL?childCt+1:childCt;
		if(childCt==0){
			return removeNoKids(tmp);
		}else if(childCt==1){
			return removeOneKid(tmp,leftFlag);
		}else if(childCt==2){
			//find rightmost node of left subtree
			bstNode *tmpReplace;
			tmpReplace = tmp->left;
			bool tmpReplaceLeft = true; //if tmpReplace is on the left
			while(tmpReplace->right!=NULL) {
				tmpReplace = tmpReplace->right;
				tmpReplaceLeft = false;
			}
			bool tmpFlag = tmp->parent->right==tmp?true:false;//tmpFlag true if tmp is on right
			bool replaceChild = tmpReplace->left!=NULL?1:0;
			//tmpReplace = rightmost node of left subtree
			//replaceChild true if tmpReplace has child
			bstNode *setHeightNode;
			if(tmpReplaceLeft){
				//tmpReplace on left w/ no child and w/ child. They are the same
				tmpReplace->right = tmp->right;
				tmpReplace->right->parent = tmpReplace;
				tmpReplace->parent = tmp->parent;
				setHeightNode = tmpReplace;
			}
			else if(!tmpReplaceLeft && !replaceChild){
				//tmpReplace on right w/o child
				tmpReplace->right = tmp->right;
				tmpReplace->right->parent = tmpReplace;
				tmpReplace->left = tmp->left;
				tmpReplace->left->parent = tmpReplace;
				setHeightNode = tmpReplace->parent;
				tmpReplace->parent->right = NULL;
				tmpReplace->parent = tmp->parent;
			}
			else{
				//tmpReplace on right w/ child
				tmpReplace->left->parent = tmpReplace->parent;
				setHeightNode = tmpReplace->parent;
				tmpReplace->parent->right = tmpReplace->left;
				tmpReplace->left = tmp->left;
				tmpReplace->left->parent = tmpReplace;
				tmpReplace->right = tmp->right;
				tmpReplace->right->parent = tmpReplace;
				tmpReplace->parent = tmp->parent;
			}
			if(tmpFlag){
				tmpReplace->parent->right = tmpReplace;
			}else{
				tmpReplace->parent->left = tmpReplace;
			}
			tmp->parent = NULL;
			tmp->left = NULL;
			tmp->right = NULL;
			setHeight(setHeightNode);
			cout << "sending " << setHeightNode->student->last << " into setHeight" << endl;
			return tmp;
		}
	}	
	bstNode* bst::removeNoKids(bstNode *tmp){
		bstNode *parent = tmp->parent;
		if (tmp->parent->left == tmp) { //node on left
			tmp->parent->left = NULL;
			tmp->parent = NULL;
		}
		else {
			tmp->parent->right = NULL; //node on right
			tmp->parent = NULL;
		}
		if(parent!=NULL){
			setHeight(parent);
			cout << "sending " << parent->student->last << " into setHeight" << endl;
		}
		return tmp;
	}
	bstNode* bst::removeOneKid(bstNode *tmp,bool leftFlag){
		//leftFlag == true - the child is on the left
		bool tmpFlag = tmp->parent->right == tmp? true: false; //true if tmp is on right
		bstNode *child = leftFlag?tmp->left:tmp->right;
		if (leftFlag && tmpFlag) { //tmp right, child left
			tmp->parent->right = tmp->left;
			tmp->left->parent = tmp->parent;
			tmp->left = NULL;
		}
		else if (leftFlag && !tmpFlag) { //tmp left, child left
			tmp->parent->left = tmp->left;
			tmp->left->parent = tmp->parent;
			tmp->left = NULL;
		}
		else if (!leftFlag && tmpFlag) { //tmp right, child right
			tmp->parent->right = tmp->right;
			tmp->right->parent = tmp->parent;
		}
		else { //tmp left, child right
			tmp->parent->left = tmp->right;
			tmp->right->parent = tmp->parent;
		}
		tmp->parent = NULL;
		setHeight(child);
		cout << "sending " << child->student->last << " into setHeight" << endl;
		return tmp;
	}



	void bst::clearTree() { //clears out an old tree
		if (root == NULL) {
			cout << "Tree already empty" << endl;
		}
		else {
			cout << endl << "Clearing Tree:" << endl;
			clearTree(root);
			root = NULL;
		}
	}

	void bst::clearTree(bstNode *tmp) {
		if (tmp == NULL) {
			return;
		}
		else {
			clearTree(tmp->left);
			clearTree(tmp->right);
			tmp->printNode();
			delete(tmp);
		}
	}
	void bst::printTreeIO() { // Just the start – you must write the recursive version
		if (root == NULL ) {
			cout << "Empty Tree" << endl;
		}
		else {
			cout << endl<<"Printing In Order:" <<endl;
			printTreeIO(root);
		}
	}
	void bst::printTreePre() {
		if (root == NULL ) {
			cout << "Empty Tree" << endl;
		}
		else {
			cout << endl<<"Printing PreOrder:" <<endl;
			printTreePre(root);
		}
	}
	void bst::printTreePost() {
		if (root == NULL ) {
			cout << "Empty Tree" << endl;
		}
		else {
			cout << endl<<"Printing PostOrder:" <<endl;
			printTreePost(root);
		}
	}
	void bst::setHeight(bstNode *n){
		if(n==NULL){
			return;
		}
		int childCt = 0;
		childCt=n->left==NULL?childCt:childCt+1;
		childCt=n->right==NULL?childCt:childCt+1;
		switch(childCt){
		case 2:
			n->height = n->right->height>n->left->height?n->right->height+1:n->left->height+1;
			break;
		case 1:
			n->height = n->right==NULL?n->left->height+1:n->right->height+1;
			break;
		case 0:
			n->height = 1;
			break;
		}
		setHeight(n->parent);
	}
