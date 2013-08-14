#include <fstream>
#include <map>
#include <string>
#include <iostream>
#include "HuffmanTree.h"
#include "HuffmanQueue.h"

using namespace std;

class Huffman
{
public:
	Huffman(void);
	Huffman(string text);
	~Huffman(void);
	void MakeQueue();
	void CreateMap();
	void CreateMap(string textFileName);
	void readMap();
	map<char, int>::iterator GetIterator();
	map<char, int> GetMap();
	HuffmanTree* BuildHuffmanTree(HuffmanQueue<HuffmanTreeNode, NodeComp> &hqueue);
	static void readTextFile( string fileName );
	string message;
private:
	map<char, int> TextMap;
	map<char, int>::iterator it;
};
