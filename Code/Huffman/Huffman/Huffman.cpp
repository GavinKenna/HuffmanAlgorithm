#include "Huffman.h"
#include "HuffmanQueue.cpp"

Huffman::Huffman(void)
{
	
}

Huffman::Huffman( string TextFileName )
{
	this->CreateMap(TextFileName);
}

Huffman::~Huffman(void)
{
}


void Huffman::CreateMap()
{
	ifstream textFile("in.txt", ios::binary); // provide the name of the file here
	string message;
	char currentChar = ' ';
	while (!textFile.eof())
	{

		textFile.get(currentChar);

		if(textFile.eof())
		{
			break;
		}
		//cout << currentChar << endl;
		if(TextMap.count(currentChar))
		{
			TextMap[currentChar]++;
		}
		else
		{
			TextMap[currentChar] = 1;
		}
		message += currentChar;
	}

	this->message = message;
	//cout << message;
}

void Huffman::CreateMap(string textFileName)
{
	ifstream textFile(textFileName); // provide the name of the file here
	string message;
	char currentChar = ' ';
	while (!textFile.eof())
	{

		textFile.get(currentChar);

		if(textFile.eof())
		{
			break;
		}
		//cout << currentChar << endl;
		if(TextMap.count(currentChar))
		{
			TextMap[currentChar]++;
		}
		else
		{
			TextMap[currentChar] = 1;
		}

		message += currentChar;
	}

	this->message = message;

	cout << "Uncompressed Text: \n \n";
	//cout << message;
	cout << "\n\n";
}

void Huffman::readTextFile( string fileName )
{
	ifstream textFile(fileName); // provide the name of the file here
	if(!textFile.is_open())
	{
		cout << "File Doesnt Exist \n";
		//return;
	}
	else
	{
	string message;
	char currentChar = ' ';
	while (!textFile.eof())
	{

		textFile.get(currentChar);

		if(textFile.eof())
		{
			break;
		}
		message += currentChar;
	}
	cout << message << endl;

	textFile.close();
	}
}


void Huffman::readMap()
{
	for(it = TextMap.begin(); it!=TextMap.end(); it++)
	{
		//cout << it->first << " occurs: " << it->second << " Times" << endl;
	}
}


map<char, int>::iterator Huffman::GetIterator()
{
	return this->it;
}

map<char, int> Huffman::GetMap()
{
	return this->TextMap;
}

HuffmanTree* Huffman::BuildHuffmanTree(HuffmanQueue<HuffmanTreeNode, NodeComp> &hqueue)
{
	do
	{
		HuffmanTreeNode *temp;
		HuffmanTreeNode * ref1 = hqueue.top();
		hqueue.pop();
		if(!hqueue.empty())
		{
			HuffmanTreeNode * ref2 = hqueue.top();
			hqueue.pop();
			temp = new HuffmanTreeNode(NULL, ref1->getFreq() + ref2->getFreq());
			temp->SetLeftNode(ref1);
			temp->SetRightNode(ref2);
		}else
		{
			temp = new HuffmanTreeNode(NULL, ref1->getFreq());
			temp->SetLeftNode(ref1);
			temp->SetRightNode(NULL);
		}

		hqueue.push(temp);

	}while(hqueue.size()!=1);

	HuffmanTree* tree = new HuffmanTree(hqueue.top());

	return tree;
}

