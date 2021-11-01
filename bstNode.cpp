/*
 * bstNode.cpp
 *
 *  Created on: Oct 21, 2021
 *      Author: Chris Czerwinski and Anissa Spano
 */

#include <stdlib.h>
#include <iostream>
using namespace std;
#include "bstNode.hpp"
#include "Student.hpp"


//class bstNode{
//	bstNode* left;
//	bstNode* right;
//	bstNode* parent;
//	int height;
//	Student* student;
//public:
//	bstNode();
//	bstNode(string first, string last, int favNum, string joke);
//	~bstNode();
//	void printNode();
//};

	bstNode::bstNode(){
		left = NULL;
		right = NULL;
		parent = NULL;
		student = NULL;
		height = 0;
	}
	bstNode::bstNode(string first, string last, int favNum, string joke){
		left = NULL;
		right = NULL;
		parent = NULL;
		height = 1;
		student = new Student(first, last, favNum, joke);
	}
	void bstNode::printNode(){
		cout << "*************************************************"<<endl;
		cout << "Height of node: " << height;
		cout << ", Name: " <<student->last << " " << student->first << endl;
		cout << "Humor: " << student->joke <<endl;
		//cout << "Favorite number: " << student->fav_num <<endl;
		cout << "*************************************************"<<endl;

	}
	bstNode::~bstNode(){
		delete student;
		left = NULL;
		right = NULL;
		parent = NULL;
	}
