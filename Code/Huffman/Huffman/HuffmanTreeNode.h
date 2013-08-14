#pragma once
#include <iostream>
#include <string>

using namespace std;

class HuffmanTreeNode
{
	friend class NodeComp;
	friend class HuffmanTree;
public:
	HuffmanTreeNode(char, int);
	~HuffmanTreeNode(void);
	int getFreq();
	bool IsLeaf();
	void SetRightNode(HuffmanTreeNode*);
	void SetLeftNode(HuffmanTreeNode*);
	HuffmanTreeNode * GetLeftNode();
	HuffmanTreeNode * GetRightNode();
	char GetData();
private:
	int freq;
	char data;
	HuffmanTreeNode *rightNode;
	HuffmanTreeNode *leftNode;

};

class NodeComp {
public:
bool operator()( HuffmanTreeNode* node1,  HuffmanTreeNode* node2)
{
	bool temp = node1->freq <= node2->freq;
	return temp;
}
};

