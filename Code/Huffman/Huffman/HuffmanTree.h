/**
    @author Gavin Kenna
    @author Seán Lynch
*/


#pragma once
#include "HuffmanTreeNode.h"
#include <iostream>
#include <map>
#include <fstream>

using namespace std;

class HuffmanTree
{
public:
	HuffmanTree(HuffmanTreeNode*);
	HuffmanTree();
	~HuffmanTree(void);
	void DeleteTree(HuffmanTreeNode *);
	HuffmanTreeNode* GetNode();

	char HuffmanTree::FindChar(string value, HuffmanTree *tree);
	string HuffmanTree::Decrypt(string msg, HuffmanTree *tree);
	void HuffmanTree::CompressWithoutMap(string input);

	void BuildMap(HuffmanTreeNode*);

	string Encode(string);
	string EncryptChar(HuffmanTreeNode* treeNode, char c);
	string EncryptChar( char c);
	string Decrypt(string msg);
	void readTextFile(string fileName);
	void writeEncodedFile(string encodedMessage);
	void readEncodedFile(string fileName);
	char FindChar(string value);
	void printMap();
	unsigned char ConvertToChar(string toConvert);
	string ConvertFromChar(unsigned char toConvert);
	void Compress(string input, map<char, int> TextMap);
	string Decompress(string textFileName);
	string DecompressWithoutMap(string textFileName,map<char, int> TextMap);
	void writeDecodedFile(string DecodedMessage);
private:
	HuffmanTreeNode * node;
	map<char, string> EncodeingMap;
	map<char, string>::iterator it;
};

