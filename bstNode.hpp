/*
 * bstNode.hpp
 *
 *  Created on: Oct 21, 2021
 *      Author: Chris Czerwinski and Anissa Spano
 */

#ifndef BSTNODE_HPP_
#define BSTNODE_HPP_
#include <iostream>
#include <stdlib.h>
using namespace std;

#include "Student.hpp"

class bstNode{
	friend class bst; //check w yarrington
	bstNode* left;
	bstNode* right;
	bstNode* parent;
	int height;
	Student* student;
public:
	bstNode();
	bstNode(string first, string last, int favNum, string joke);
	~bstNode();
	void printNode();
};




#endif /* BSTNODE_HPP_ */
