#include<iostream>
#include<algorithm>
#include"AVLTreeNode.h"
using namespace std;

class AVLTree
{
private:
	AVLTreeNode *root;
	AVLTreeNode *Search(int,AVLTreeNode *);
	AVLTreeNode *LeftRotate(AVLTreeNode *);
	AVLTreeNode *LeftAndRightRotate(AVLTreeNode *);
	AVLTreeNode *RightRotate(AVLTreeNode *);
	AVLTreeNode *RightAndLeftRotate(AVLTreeNode *);
	int GetHeight(AVLTreeNode *);
	void PreOrderPrint(AVLTreeNode *);
	void InOrderPrint(AVLTreeNode *);
	void SufOrderPrint(AVLTreeNode *);
	void RotatePrint(AVLTreeNode *,int);
	AVLTreeNode *Insert(int,AVLTreeNode *);
	AVLTreeNode *Delete(bool&,int,AVLTreeNode *);
public:
	AVLTree();
	void Insert(int);
	bool Search(int);
	bool Delete(int);
	bool Updata(int,int);
	void PreOrderPrint();
	void InOrderPrint();
	void SufOrderPrint();
	void RotatePrint();
};


AVLTree::AVLTree()
{
	root=NULL;
}

/*********************************************
*��������ǰ�ڵ�
*����ֵ����ǰ�ڵ�߶�
*���ܣ����ص�ǰ�ڵ�߶�
**********************************************/
int AVLTree::GetHeight(AVLTreeNode *tempNode)
{
	return NULL==tempNode?-1:tempNode->height;
}

/*********************************************
*������������Ԫ�أ���ǰ�ڵ�
*����ֵ��Ԫ�����ڽڵ�
*���ܣ�����Ԫ�����ڽڵ�
**********************************************/
AVLTreeNode *AVLTree::Search(int tempKey,AVLTreeNode *tempNode)
{
	if(NULL==tempNode)
		return NULL;
	else if(tempKey==tempNode->key)
		return tempNode;
	else if(tempKey<tempNode->key)
		return Search(tempKey,tempNode->leftChild);
	return Search(tempKey,tempNode->rightChild);
}
bool AVLTree::Search(int tempKey)
{
	if(NULL==Search(tempKey,root))
		return false;
	return true;
}

/*********************************************
*��������ǰ�ڵ�
*����ֵ����ǰ�������ڵ�
*���ܣ�������ƽ��
**********************************************/
AVLTreeNode *AVLTree::LeftRotate(AVLTreeNode *tempNode)
{
	AVLTreeNode *lChildNode=tempNode->rightChild->leftChild,*newRoot=tempNode->rightChild;
	tempNode->rightChild->leftChild=tempNode;
	tempNode->rightChild=lChildNode;
	tempNode->height=max(GetHeight(tempNode->leftChild),GetHeight(tempNode->rightChild))+1;
	if(NULL!=tempNode->rightChild)
	tempNode->rightChild->height=max(GetHeight(tempNode->rightChild->leftChild),GetHeight(tempNode->rightChild->rightChild))+1;
	return newRoot;
}

/*********************************************
*��������ǰ�ڵ�
*����ֵ����ǰ�������ڵ�
*���ܣ�������ƽ��
**********************************************/
AVLTreeNode *AVLTree::RightRotate(AVLTreeNode *tempNode)
{
	AVLTreeNode *rChildNode=tempNode->leftChild->rightChild,*newRoot=tempNode->leftChild;
	tempNode->leftChild->rightChild=tempNode;
	tempNode->leftChild=rChildNode;
	tempNode->height=max(GetHeight(tempNode->leftChild),GetHeight(tempNode->rightChild))+1;
	if(NULL!=tempNode->leftChild)
	tempNode->leftChild->height=max(GetHeight(tempNode->leftChild->leftChild),GetHeight(tempNode->leftChild->rightChild))+1;
	return newRoot;
}

/*********************************************
*��������ǰ�ڵ�
*����ֵ����ǰ�������ڵ�
*���ܣ���������������ƽ��
**********************************************/
AVLTreeNode *AVLTree::LeftAndRightRotate(AVLTreeNode *tempNode)
{
	tempNode->leftChild=LeftRotate(tempNode->leftChild);
	return RightRotate(tempNode);
}

/*********************************************
*��������ǰ�ڵ�
*����ֵ����ǰ�������ڵ�
*���ܣ���������������ƽ��
**********************************************/
AVLTreeNode *AVLTree::RightAndLeftRotate(AVLTreeNode *tempNode)
{
	tempNode->rightChild=RightRotate(tempNode->rightChild);
	return LeftRotate(tempNode);
}

/*********************************************
*������������Ԫ��,��ǰ�ڵ�
*����ֵ����ǰ�������ڵ�
*���ܣ�����Ԫ�ص���ǰ�ڵ������
**********************************************/
AVLTreeNode *AVLTree::Insert(int tempKey,AVLTreeNode *tempNode)
{
	if(NULL==tempNode)
	    return tempNode=new AVLTreeNode(tempKey);
	else 
	{
		if(tempKey==tempNode->key)
			return tempNode;
		else if(tempKey<tempNode->key)
			tempNode->leftChild=Insert(tempKey,tempNode->leftChild);
		else tempNode->rightChild=Insert(tempKey,tempNode->rightChild);
	}
	//tempNode->height=max(GetHeight(tempNode->leftChild),GetHeight(tempNode->rightChild))+1;
	if(2==GetHeight(tempNode->leftChild)-GetHeight(tempNode->rightChild))
	{
		if(tempKey<tempNode->leftChild->key)
			tempNode=RightRotate(tempNode);
		else tempNode=LeftAndRightRotate(tempNode);
	}
	else if(-2==GetHeight(tempNode->leftChild)-GetHeight(tempNode->rightChild))
	{
		if(tempKey>tempNode->rightChild->key)
			tempNode=LeftRotate(tempNode);
		else tempNode=RightAndLeftRotate(tempNode);
	}
	tempNode->height=max(GetHeight(tempNode->leftChild),GetHeight(tempNode->rightChild))+1;
	return tempNode;
}
void AVLTree::Insert(int tempKey)
{
	root=Insert(tempKey,root);
}

/*********************************************
*��������ɾ��Ԫ��,��ǰ�ڵ�
*����ֵ����ǰ�������ڵ�
*���ܣ�ɾ��Ԫ��
**********************************************/
AVLTreeNode *AVLTree::Delete(bool &isDelSucceed,int tempKey,AVLTreeNode *tempNode)
{
	if(NULL==tempNode)
		return NULL;
	else 
	{
		if(tempKey==tempNode->key)
		{
			if(NULL==tempNode->rightChild)
			{
				AVLTreeNode *cur=tempNode;
				tempNode=tempNode->leftChild;
				delete cur;
				isDelSucceed=true;
				return tempNode;
			}
			else//�ҵ���������С��Ԫ�ش��棬Ȼ��ɾ�� 
			{
				AVLTreeNode *cur=tempNode->rightChild;
				while(cur->leftChild!=NULL)
					cur=cur->leftChild;
				tempNode->key=cur->key;
				tempNode->rightChild=Delete(isDelSucceed,cur->key,tempNode->rightChild);
			}
		}
		else if(tempKey<tempNode->key)
			tempNode->leftChild=Delete(isDelSucceed,tempKey,tempNode->leftChild);
		else tempNode->rightChild=Delete(isDelSucceed,tempKey,tempNode->rightChild);

		if(-2==GetHeight(tempNode->leftChild)-GetHeight(tempNode->rightChild))//ɾ�������������ϵ�
		{
			if(GetHeight(tempNode->rightChild->rightChild)>=GetHeight(tempNode->rightChild->leftChild))
				tempNode=LeftRotate(tempNode);
			else tempNode=RightAndLeftRotate(tempNode);
		}
		else if(2==GetHeight(tempNode->leftChild)-GetHeight(tempNode->rightChild))
		{
			if(GetHeight(tempNode->leftChild->leftChild)>=GetHeight(tempNode->leftChild->rightChild))
				tempNode=RightRotate(tempNode);
			else tempNode=LeftAndRightRotate(tempNode);
		}
		tempNode->height=max(GetHeight(tempNode->leftChild),GetHeight(tempNode->rightChild))+1;
	}
	return tempNode;
}
bool AVLTree::Delete(int tempKey)
{
	bool isDelSucceed=false;
	root=Delete(isDelSucceed,tempKey,root);
	return isDelSucceed;
}

/**********************************************************
*���������޸Ľڵ�Ԫ�ء��޸ĺ��Ԫ��
*����ֵ�������޸��Ƿ�ɹ�
*���ܣ��޸ĺ���
************************************************************/
bool AVLTree::Updata(int oldKey,int newKey)
{
	if(Delete(oldKey))
	{
		Insert(newKey);
		return true;
	}
	return false;
}

/**********************************************************
*��������ǰ�������ڵ�
*����ֵ����
*���ܣ�ǰ��������������
************************************************************/
void AVLTree::PreOrderPrint(AVLTreeNode *tempNode)
{
	if(NULL==tempNode)
		return ;
	cout<<tempNode->key<<"    ";
	PreOrderPrint(tempNode->leftChild);
	PreOrderPrint(tempNode->rightChild);
}
void AVLTree::PreOrderPrint()
{
	PreOrderPrint(this->root);
}

/**********************************************************
*��������ǰ�������ڵ�
*����ֵ����
*���ܣ�����������������
************************************************************/
void AVLTree::InOrderPrint(AVLTreeNode *tempNode)
{
	if(NULL==tempNode)
		return ;
	InOrderPrint(tempNode->leftChild);
	cout<<tempNode->key<<"   ";
	InOrderPrint(tempNode->rightChild);
}
void AVLTree::InOrderPrint()
{
	InOrderPrint(root);
}

/**********************************************************
*��������ǰ�������ڵ�
*����ֵ����
*���ܣ�������������������
************************************************************/
void AVLTree::SufOrderPrint(AVLTreeNode *tempNode)
{
	if(NULL==tempNode)
		return ;
	SufOrderPrint(tempNode->leftChild);
	SufOrderPrint(tempNode->rightChild);
	cout<<tempNode->key<<"    ";
}
void AVLTree::SufOrderPrint()
{
	SufOrderPrint(root);
}

/**********************************************************
*��������ǰ�������ڵ㣬��������
*����ֵ����
*���ܣ���ת��ӡAVL��
************************************************************/
void AVLTree::RotatePrint(AVLTreeNode *tempNode,int tempColumn)
{
	if(NULL==tempNode)
		return ;
	RotatePrint(tempNode->leftChild,tempColumn+1);
	for(int i=0;i<tempColumn;i++)
		cout<<"    ";
	cout<<"---"<<tempNode->key<<endl;
	RotatePrint(tempNode->rightChild,tempColumn+1);
}
void AVLTree::RotatePrint()
{
	RotatePrint(root,0);
}

void Menu()
{
	int val,choice,newVal;
	AVLTree myAVLTree;
	while(true)
	{
	do
	{
	cout<<"&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&"<<endl;
	cout<<"       1.����"<<endl;
	cout<<"       2.ɾ��"<<endl;
	cout<<"       3.�޸�"<<endl;
	cout<<"       4.����"<<endl;
	cout<<"       5.��ʾ"<<endl;
	cout<<"       6.����"<<endl;
	cout<<"���������ѡ��[ ]\b\b";
	cin>>choice; 
	}while(choice!=1&&choice!=2&&choice!=3&&choice!=4&&choice!=5&&choice!=6);
	if(1==choice)
	{
		cin>>val;
		myAVLTree.Insert(val);
	}
	else if(2==choice)
	{
		cin>>val;
		if(myAVLTree.Delete(val))
			cout<<"ɾ���ɹ�!"<<endl;
		else cout<<"ɾ��ʧ��!"<<endl;
	}
	else if(3==choice)
	{
		cin>>val>>newVal;
		if(myAVLTree.Updata(val,newVal))
			cout<<"�޸ĳɹ�!"<<endl;
		else cout<<"�޸�ʧ��!"<<endl;
	}
	else if(4==choice)
	{
		cin>>val;
		if(NULL!=myAVLTree.Search(val))
			cout<<"���ҳɹ�!"<<endl;
		else cout<<"����ʧ��!"<<endl;
	}
	else if(5==choice)
	{
		cout<<endl<<"*****************************"<<endl;
	cout<<endl<<"==========ǰ��=============="<<endl;
	myAVLTree.PreOrderPrint();
	cout<<endl<<"==========����================"<<endl;
	myAVLTree.InOrderPrint();
	cout<<endl<<"==========����==============="<<endl;
	myAVLTree.SufOrderPrint();
	cout<<endl<<"==========�Գ�+��ת==============="<<endl;
	myAVLTree.RotatePrint();
	cout<<endl<<"*****************************"<<endl;
	}
	else return ;
	}
}

int main()
{
	while(true)
		Menu();
	return 0;
}

