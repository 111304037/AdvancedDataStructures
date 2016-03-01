#include<iostream>
using namespace std;

/**********************************
*功能:防止头文件多次包含
**********************************/
#ifndef TREAPNODE_H
#define TREAPNODE_H

class TreapNode
{
public:
	TreapNode *leftChild;
	TreapNode *rightChild;
	TreapNode *parent;
	int key;
	int priority;
	TreapNode(int tempKey,int tempPriority)
	{
		this->priority=tempPriority;
		this->key=tempKey;
		this->leftChild=NULL;
		this->rightChild=NULL;
		this->parent=NULL;
	}
};

#endif TREAPNODE_H