#include<iostream>
using namespace std;

/**********************************
*����:��ֹͷ�ļ���ΰ���
**********************************/
#ifndef AVLTREENODE_H
#define AVLTREENODE_H


struct AVLTreeNode
{
	int key;
	int height;
	AVLTreeNode *leftChild;
	AVLTreeNode *rightChild;
	AVLTreeNode(int tempKey)
	{
		height=0;
		key=tempKey;
		leftChild=NULL;
		rightChild=NULL;
	}
};

#endif AVLTREENODE_H