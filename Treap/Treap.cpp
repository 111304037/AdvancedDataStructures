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
*参数：无
*返回值：整形
*功能：产生未使用的随机数作为优先级
***************************************************************/
int Treap::SetNodePriority()
{
	int val;
	while(usedPriority[val=rand()]);
	usedPriority[val]=true;
	return val;
}

/**************************************************************
*参数：待左旋的节点
*返回值：空
*功能：左旋
***************************************************************/
void Treap::LeftRotate(TreapNode *tempTPNode)
{
	TreapNode *rChild=tempTPNode->rightChild;
	if(NULL==rChild)return;
	if(NULL!=tempTPNode->parent)//不为根节点
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
*参数：待右旋的节点
*返回值：空
*功能：右旋
***************************************************************/
void Treap::RightRotate(TreapNode *tempTPNode)
{
	TreapNode *lChild=tempTPNode->leftChild;
	if(NULL==lChild)return;
	if(NULL!=tempTPNode->parent)//不为根节点
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
*参数：待调整节点
*返回值：空
*功能：根据优先级按小顶堆来调整
***************************************************************/
void Treap::ModifyTreap(TreapNode *tempTPNode)
{
	TreapNode *parTempTPNode=tempTPNode->parent;
	while(parTempTPNode!=NULL&&parTempTPNode->priority>tempTPNode->priority)//大于父亲节点优先级
	{
		if(tempTPNode==parTempTPNode->leftChild)
			RightRotate(parTempTPNode);
		else LeftRotate(parTempTPNode);
		parTempTPNode=tempTPNode->parent;
	}
}

/**************************************************************
*参数：带插入元素
*返回值：空
*功能：将当前元素插入Treap
***************************************************************/
void Treap::InsertTreap(int tempKey)
{
	TreapNode *pre=NULL,*cur=this->root;
	while(cur!=NULL)
	{
		pre=cur;
		if(cur->key>tempKey)//tempKey插到左子树
			cur=cur->leftChild;
		else cur=cur->rightChild;//插到左子树
	}
	TreapNode *tempTPNode=new TreapNode(tempKey,SetNodePriority());
	tempTPNode->parent=pre;
	if(pre==NULL)//若插入的为根节点
	{
		this->root=tempTPNode;
	}
	else if(pre->key>tempTPNode->key)
		pre->leftChild=tempTPNode;
	else pre->rightChild=tempTPNode;
	ModifyTreap(tempTPNode);//调整
}

/**************************************************************
*参数：带查找元素
*返回值：返回查找元素在Treap中的位置
*功能：查找当前元素是否在Treap
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
*参数：pre待删除节点的父节点，cur待删除节点
*返回值：空
*功能：删除左右孩子有为空的情况
************************************************************/
void Treap::DeleteNoOrOneChildTPNode(TreapNode *pre,TreapNode *cur)
{
	if(NULL==cur->leftChild&&NULL==cur->rightChild)//左右孩子为空
	{
		if(NULL==pre)
			this->root=NULL;
		else if(pre->leftChild==cur)
			pre->leftChild=NULL;
		else pre->rightChild=NULL;
		delete cur;
	}
	else if(cur->rightChild!=NULL)//若右子树不为空
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
	else if(cur->leftChild!=NULL)//若左子树不为空
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
*参数：待删除节点元素
*返回值：空
*功能：删除元素主函数
************************************************************/
bool Treap::DeleteTreap(int tempKey)
{
	TreapNode *pre=NULL,*cur=root;
	while(cur!=NULL)//寻找待删除元素
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
	else //左右子树都不为空
	{
		TreapNode *rPre=cur,*rCur=cur->rightChild;//找到右子树最小元素
		bool isLeft;
		while(rCur->leftChild!=NULL)
		{
			rPre=rCur;
			rCur=rCur->leftChild;
		}
		cur->key=rCur->key;//直接填充元素，不复制优先级
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
*参数：待修改节点元素、修改后的元素
*返回值：返回修改是否成功
*功能：修改函数
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
*参数：当前子树根节点
*返回值：空
*功能：前序遍历Treap
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
*参数：当前子树根节点
*返回值：空
*功能：中序遍历Treap
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
*参数：当前子树根节点
*返回值：空
*功能：后序遍历Treap
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
*参数：当前子树根节点，缩进列数
*返回值：空
*功能：翻转打印Treap
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
	cout<<"       1.插入"<<endl;
	cout<<"       2.删除"<<endl;
	cout<<"       3.修改"<<endl;
	cout<<"       4.查找"<<endl;
	cout<<"       5.显示"<<endl;
	cout<<"       6.返回"<<endl;
	cout<<"请输入你的选项[ ]\b\b";
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
			cout<<"删除成功!"<<endl;
		else cout<<"删除失败!"<<endl;
	}
	else if(3==choice)
	{
		cin>>val>>newVal;
		if(myTreap.UpdataTreap(val,newVal))
			cout<<"修改成功!"<<endl;
		else cout<<"修改失败!"<<endl;
	}
	else if(4==choice)
	{
		cin>>val;
		if(NULL!=myTreap.FindTreap(val))
			cout<<"查找成功!"<<endl;
		else cout<<"查找失败!"<<endl;
	}
	else if(5==choice)
	{
		cout<<endl<<"*****************************"<<endl;
	cout<<endl<<"==========前序=============="<<endl;
	myTreap.PreOrderTPPrint();
	cout<<endl<<"==========中序================"<<endl;
	myTreap.InOrderTPPrint();
	cout<<endl<<"==========后续==============="<<endl;
	myTreap.SufOrderTPPrint();
	cout<<endl<<"==========对称+旋转==============="<<endl;
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