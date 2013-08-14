#include "HuffmanTree.h"
#include <queue>
#include "Huffman.h"
#include "HuffmanQueue.cpp"

int derp()
{
	//testing huffmanqueue
	cout << "what";

	HuffmanQueue<HuffmanTreeNode, NodeComp> queue;
	
	Huffman tm;

	map<char, int> TextMap = tm.GetMap();
	map<char, int>::iterator it = tm.GetIterator();
	//priority_queue<HuffmanTreeNode*, deque<HuffmanTreeNode*>, NodeComp> queue;
	HuffmanTreeNode *t;

	for(it = TextMap.begin(); it!=TextMap.end(); it++)
	{
		t = new HuffmanTreeNode(it->first, it->second);
		queue.push(t);
	}

	do
	{

		HuffmanTreeNode *temp;
		HuffmanTreeNode * ref1 = queue.top();
		queue.pop();
		if(!queue.empty())
		{
			HuffmanTreeNode * ref2 = queue.top();
			queue.pop();
			temp = new HuffmanTreeNode(NULL, ref1->getFreq() + ref2->getFreq());
			temp->SetLeftNode(ref1);
			temp->SetRightNode(ref2);
		}else
		{
			temp = new HuffmanTreeNode(NULL, ref1->getFreq());
			temp->SetLeftNode(ref1);
			temp->SetRightNode(NULL);
		}

		queue.push(temp);

	}while(queue.size()!=1);

	HuffmanTree* tree = new HuffmanTree(queue.top());

	tree->BuildMap(queue.top());
	//tree->GetChars(queue.top());

	cout << "Printing Map \n";
	tree->printMap();

	string x = tree->Encrypt("go go gophers");

	cout<<"Encrypting 'go go gophers' . :: "<<x<<endl<<endl;

	tree->Compress(x);


	cout<<"Decrypting '"<<x<<"' . :: "<<tree->Decrypt(x)<<endl;

	system("pause");
	return 0;
}