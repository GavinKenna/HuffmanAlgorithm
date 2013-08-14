/**
    @author Gavin Kenna
    @author Seán Lynch
*/


#include "HuffmanTreeNode.h"


HuffmanTreeNode::HuffmanTreeNode(char temp, int freq)
{
	this->freq = freq;
	this->data = temp;
	this->leftNode = NULL;
	this->rightNode = NULL;
}


HuffmanTreeNode::~HuffmanTreeNode(void)
{
	delete this->leftNode;
	delete this->rightNode;
}

bool HuffmanTreeNode::IsLeaf()
{
	if(this->leftNode==NULL && this->rightNode == NULL)
	{
		return true;
	}else
	{
		return false;
	}
}

int HuffmanTreeNode::getFreq()
{
	return this->freq;
}

void HuffmanTreeNode::SetLeftNode(HuffmanTreeNode * temp)
{
	this->leftNode = temp;
}

void HuffmanTreeNode::SetRightNode(HuffmanTreeNode * temp)
{
	this->rightNode = temp;
}

HuffmanTreeNode * HuffmanTreeNode::GetLeftNode()
{
	if(this->leftNode==NULL)
	{
		return NULL;
	}else{
		return this->leftNode;}
}

HuffmanTreeNode * HuffmanTreeNode::GetRightNode()
{
	if(this->rightNode==NULL)
	{
		return NULL;
	}else{
		return this->rightNode;
	}
}

char HuffmanTreeNode::GetData()
{
	return this->data;
}