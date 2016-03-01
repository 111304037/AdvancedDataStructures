#include<iostream>
#include<cstring>
#include<ctime>
#include"TreapNode.h"
using namespace std;

class Treap
{
private:
	TreapNode *root;
	bool usedPriority[RAND_MAX];
	void LeftRotate(TreapNode *);
	void RightRotate(TreapNode *);
	void PreOrderTPPrint(TreapNode *);
	void InOrderTPPrint(TreapNode *);
	void RotateTPPrint(TreapNode *,int);
	void SufOrderTPPrint(TreapNode *);
	void DeleteNoOrOneChildTPNode(TreapNode *,TreapNode *);
	void ModifyTreap(TreapNode *);
	int SetNodePriority();
public:
	Treap();
	void InsertTreap(int);
	bool DeleteTreap(int);
	bool UpdataTreap(int,int);
	TreapNode *FindTreap(int);
	void PreOrderTPPrint();
	void InOrderTPPrint();
	void RotateTPPrint();
	void SufOrderTPPrint();
};

Treap::Treap()
{
	memset(usedPriority,false,sizeof(usedPriority));
	this->root=NULL;
} 

/**************************************************************
*��������
*����ֵ������
*���ܣ�����δʹ�õ��������Ϊ���ȼ�
***************************************************************/
int Treap::SetNodePriority()
{
	int val;
	while(usedPriority[val=rand()]);
	usedPriority[val]=true;
	return val;
}

/**************************************************************
*�������������Ľڵ�
*����ֵ����
*���ܣ�����
***************************************************************/
void Treap::LeftRotate(TreapNode *tempTPNode)
{
	TreapNode *rChild=tempTPNode->rightChild;
	if(NULL==rChild)return;
	if(NULL!=tempTPNode->parent)//��Ϊ���ڵ�
	{
		if(tempTPNode->parent->leftChild==tempTPNode)
			tempTPNode->parent->leftChild=rChild;
		else 
			tempTPNode->parent->rightChild=rChild;
	}
	rChild->parent=tempTPNode->parent;
	tempTPNode->parent=rChild;
	if(rChild->leftChild!=NULL)
		rChild->leftChild->parent=tempTPNode;
	tempTPNode->rightChild=rChild->leftChild;
	rChild->leftChild=tempTPNode;
	if(NULL==rChild->parent)
		this->root=rChild;
}

/**************************************************************
*�������������Ľڵ�
*����ֵ����
*���ܣ�����
***************************************************************/
void Treap::RightRotate(TreapNode *tempTPNode)
{
	TreapNode *lChild=tempTPNode->leftChild;
	if(NULL==lChild)return;
	if(NULL!=tempTPNode->parent)//��Ϊ���ڵ�
	{
		if(tempTPNode->parent->rightChild==tempTPNode)
			tempTPNode->parent->rightChild=lChild;
		else 
			tempTPNode->parent->leftChild=lChild;
	}
	lChild->parent=tempTPNode->parent;
	tempTPNode->parent=lChild;
	if(lChild->rightChild!=NULL)
		lChild->rightChild->parent=tempTPNode;
	tempTPNode->leftChild=lChild->rightChild;
	lChild->rightChild=tempTPNode;
	if(NULL==lChild->parent)
		this->root=lChild;
}

/**************************************************************
*�������������ڵ�
*����ֵ����
*���ܣ��������ȼ���С����������
***************************************************************/
void Treap::ModifyTreap(TreapNode *tempTPNode)
{
	TreapNode *parTempTPNode=tempTPNode->parent;
	while(parTempTPNode!=NULL&&parTempTPNode->priority>tempTPNode->priority)//���ڸ��׽ڵ����ȼ�
	{
		if(tempTPNode==parTempTPNode->leftChild)
			RightRotate(parTempTPNode);
		else LeftRotate(parTempTPNode);
		parTempTPNode=tempTPNode->parent;
	}
}

/**************************************************************
*������������Ԫ��
*����ֵ����
*���ܣ�����ǰԪ�ز���Treap
***************************************************************/
void Treap::InsertTreap(int tempKey)
{
	TreapNode *pre=NULL,*cur=this->root;
	while(cur!=NULL)
	{
		pre=cur;
		if(cur->key>tempKey)//tempKey�嵽������
			cur=cur->leftChild;
		else cur=cur->rightChild;//�嵽������
	}
	TreapNode *tempTPNode=new TreapNode(tempKey,SetNodePriority());
	tempTPNode->parent=pre;
	if(pre==NULL)//�������Ϊ���ڵ�
	{
		this->root=tempTPNode;
	}
	else if(pre->key>tempTPNode->key)
		pre->leftChild=tempTPNode;
	else pre->rightChild=tempTPNode;
	ModifyTreap(tempTPNode);//����
}

/**************************************************************
*������������Ԫ��
*����ֵ�����ز���Ԫ����Treap�е�λ��
*���ܣ����ҵ�ǰԪ���Ƿ���Treap
***************************************************************/
TreapNode *Treap::FindTreap(int tempKey)
{
	TreapNode *cur=this->root;
	while(cur!=NULL)
	{
		if(cur->key==tempKey)
			break;
		else if(cur->key>tempKey)
			cur=cur->leftChild;
		else cur=cur->rightChild;
	}
	return cur;
}

/**********************************************************
*������pre��ɾ���ڵ�ĸ��ڵ㣬cur��ɾ���ڵ�
*����ֵ����
*���ܣ�ɾ�����Һ�����Ϊ�յ����
************************************************************/
void Treap::DeleteNoOrOneChildTPNode(TreapNode *pre,TreapNode *cur)
{
	if(NULL==cur->leftChild&&NULL==cur->rightChild)//���Һ���Ϊ��
	{
		if(NULL==pre)
			this->root=NULL;
		else if(pre->leftChild==cur)
			pre->leftChild=NULL;
		else pre->rightChild=NULL;
		delete cur;
	}
	else if(cur->rightChild!=NULL)//����������Ϊ��
	{
		if(NULL==pre)
		{
			this->root=cur->rightChild;
			cur->rightChild->parent=NULL;
		}
		else if(pre->leftChild==cur)
		{
			pre->leftChild=cur->rightChild;
			cur->rightChild->parent=pre;
		}
		else 
		{
			pre->rightChild=cur->rightChild;
			cur->rightChild->parent=pre;
		}
		delete cur;
	}
	else if(cur->leftChild!=NULL)//����������Ϊ��
	{
		if(NULL==pre)
		{
			this->root=cur->leftChild;
			cur->leftChild->parent=NULL;
		}
		else if(pre->leftChild==cur)
		{
			pre->leftChild=cur->leftChild;
			cur->leftChild->parent=pre;
		}
		else
		{
			pre->rightChild=cur->leftChild;
			cur->leftChild->parent=pre;
		}
		delete cur;
	}
}


/**********************************************************
*��������ɾ���ڵ�Ԫ��
*����ֵ����
*���ܣ�ɾ��Ԫ��������
************************************************************/
bool Treap::DeleteTreap(int tempKey)
{
	TreapNode *pre=NULL,*cur=root;
	while(cur!=NULL)//Ѱ�Ҵ�ɾ��Ԫ��
	{
		if(cur->key==tempKey)
			break;
		else
		{
			pre=cur;
			if(cur->key>tempKey)
				cur=cur->leftChild;
			else cur=cur->rightChild;
		}
	}
	if(NULL==cur)return false;
	if(NULL==cur->leftChild||NULL==cur->rightChild)
		DeleteNoOrOneChildTPNode(pre,cur);
	else //������������Ϊ��
	{
		TreapNode *rPre=cur,*rCur=cur->rightChild;//�ҵ���������СԪ��
		bool isLeft;
		while(rCur->leftChild!=NULL)
		{
			rPre=rCur;
			rCur=rCur->leftChild;
		}
		cur->key=rCur->key;//ֱ�����Ԫ�أ����������ȼ�
		if(rPre->leftChild==rCur)
			isLeft=true;
		else isLeft=false;
		DeleteNoOrOneChildTPNode(rPre,rCur);
		if(isLeft)
			ModifyTreap(rPre->leftChild);
		else ModifyTreap(rPre->rightChild);
	}
	return true;
}

/**********************************************************
*���������޸Ľڵ�Ԫ�ء��޸ĺ��Ԫ��
*����ֵ�������޸��Ƿ�ɹ�
*���ܣ��޸ĺ���
************************************************************/
bool Treap::UpdataTreap(int oldKey,int newKey)
{
	if(DeleteTreap(oldKey))
	{
		InsertTreap(newKey);
		return true;
	}
	return false;
}

/**********************************************************
*��������ǰ�������ڵ�
*����ֵ����
*���ܣ�ǰ�����Treap
************************************************************/
void Treap::PreOrderTPPrint(TreapNode *tempTPNode)
{
	if(NULL==tempTPNode)
		return ;
	cout<<"("<<tempTPNode->key<<","<<tempTPNode->priority<<")   ";
	PreOrderTPPrint(tempTPNode->leftChild);
	PreOrderTPPrint(tempTPNode->rightChild);
}
void Treap::PreOrderTPPrint()
{
	PreOrderTPPrint(this->root);
}

/**********************************************************
*��������ǰ�������ڵ�
*����ֵ����
*���ܣ��������Treap
************************************************************/
void Treap::InOrderTPPrint(TreapNode *tempTPNode)
{
	if(NULL==tempTPNode)
		return ;
	InOrderTPPrint(tempTPNode->leftChild);
	cout<<"("<<tempTPNode->key<<","<<tempTPNode->priority<<")   ";
	InOrderTPPrint(tempTPNode->rightChild);
}
void Treap::InOrderTPPrint()
{
	InOrderTPPrint(this->root);
}

/**********************************************************
*��������ǰ�������ڵ�
*����ֵ����
*���ܣ��������Treap
************************************************************/
void Treap::SufOrderTPPrint(TreapNode *tempTPNode)
{
	if(NULL==tempTPNode)
		return ;
	SufOrderTPPrint(tempTPNode->leftChild);
	SufOrderTPPrint(tempTPNode->rightChild);
	cout<<"("<<tempTPNode->key<<","<<tempTPNode->priority<<")   ";
}
void Treap::SufOrderTPPrint()
{
	SufOrderTPPrint(this->root);
}

/**********************************************************
*��������ǰ�������ڵ㣬��������
*����ֵ����
*���ܣ���ת��ӡTreap
************************************************************/
void Treap::RotateTPPrint(TreapNode *tempTPNode,int tempColumn)
{
	if(NULL==tempTPNode)
		return ;
	RotateTPPrint(tempTPNode->leftChild,tempColumn+1);
	for(int i=0;i<tempColumn;i++)
		cout<<"    ";
	cout<<"("<<tempTPNode->key<<","<<tempTPNode->priority<<")"<<endl;
	RotateTPPrint(tempTPNode->rightChild,tempColumn+1);
}
void Treap::RotateTPPrint()
{
	RotateTPPrint(this->root,0);
}


void Menu()
{
	int val,choice,newVal;
	Treap myTreap;
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
		myTreap.InsertTreap(val);
	}
	else if(2==choice)
	{
		cin>>val;
		if(myTreap.DeleteTreap(val))
			cout<<"ɾ���ɹ�!"<<endl;
		else cout<<"ɾ��ʧ��!"<<endl;
	}
	else if(3==choice)
	{
		cin>>val>>newVal;
		if(myTreap.UpdataTreap(val,newVal))
			cout<<"�޸ĳɹ�!"<<endl;
		else cout<<"�޸�ʧ��!"<<endl;
	}
	else if(4==choice)
	{
		cin>>val;
		if(NULL!=myTreap.FindTreap(val))
			cout<<"���ҳɹ�!"<<endl;
		else cout<<"����ʧ��!"<<endl;
	}
	else if(5==choice)
	{
		cout<<endl<<"*****************************"<<endl;
	cout<<endl<<"==========ǰ��=============="<<endl;
	myTreap.PreOrderTPPrint();
	cout<<endl<<"==========����================"<<endl;
	myTreap.InOrderTPPrint();
	cout<<endl<<"==========����==============="<<endl;
	myTreap.SufOrderTPPrint();
	cout<<endl<<"==========�Գ�+��ת==============="<<endl;
	myTreap.RotateTPPrint();
	cout<<endl<<"*****************************"<<endl;
	}
	else return ;
	}
}


int main()
{
	while(true)
		 Menu();
	system("pause");
	return 0;
}