#include "Huffman.h"
#include "HuffmanQueue.h"
#include "HuffmanQueue.cpp"

using namespace std;

void menu();

int main()
{
	cout << "----------------------------------------------------------\n";
	cout << "------------------ADS Huffman Trees CA--------------------\n";
	cout << "----------------------------------------------------------\n";
	cout << "-Authors												  \n";
	cout << "-X00083664 - Gavin Kenna								  \n";
	cout << "-X00071239 - Sean Lynch								  \n";
	cout << "----------------------------------------------------------\n";
	cout << "-Tasks 1-5												  \n";
	cout << "-Option 2 will read in and encoded, the encoded        \n";
	cout << "-file is saved as encoded.txt, this is then read in \n";
	cout << "-, decoded and saved to out.txt, 	  \n";
	cout << "-you can then either open the file normally or read it	 \n";
	cout << "-by using option 1	\n";
	cout << "--------------------------------------------------------- \n";
	cout << "-Tasks 6-7												  \n";
	cout << "-Option 3 will read in a file, compress it and \n";
	cout << "-save it as comp.txt. \n";
	cout << "-Option 4 to read it back in and it will be saved\n";
	cout << "-as out.txt\n";
	cout << "--------------------------------------------------------- \n";
	cout << "-Tasks 8													\n";
	cout << "-Option 5 to read in a file, compress it and add the map to \n";
	cout << "-the header of the file.";
	cout << "-Option 6 to read it back in and it will be saved\n";
	cout << "-as out.txt\n";
	cout << "--------------------------------------------------------- \n\n";
	cout << "-Be sure to remove remove content from comp.txt before\n";
	cout << "-compressing different files\n";

	
	menu();

	return 0;
}

void menu()
{
	Huffman noWriting;
	HuffmanQueue<HuffmanTreeNode, NodeComp> hqueue;
	HuffmanTree* tree = new HuffmanTree();
	map<char, int> TextMap;
	bool running = true;
	do 
	{
		int choice;
		string textFileName;
		cout << "Please Select An Option \n";
		cout << "1: Read File\n";
		cout << "2: Encode File And Read Encoded File \n";
		cout << "3: Compress File \n";
		cout << "4: Decompress File(Run Only After Running 3)  \n";
		cout << "5: Compress File With Map \n";
		cout << "6: Read Compressed File With Map \n";
		cout << "7: Quit\n";

		cout << "Please Enter Your Choice: ";
		cin >> choice;

		if(choice == 1)
		{
			cout << "Please Enter The Name Of The File You Wish To Read \n";
			cout << "Remember To Include .txt \n";
			cin >> textFileName;
			cout << endl;
			noWriting.readTextFile(textFileName);
			cout << endl;
		}
		else if(choice == 2)
		{
			cout << "Please Enter The Name Of The File You Wish To Encode \n";
			cout << "Remember To Include .txt \n";
			cin >> textFileName;

			cout << "Original Text \n\n";
			cout << endl;
			Huffman Writing(textFileName);
			cout << endl;
			cout << "Text Size: " << Writing.message.length() * 8 << " Bytes \n\n";

			map<char, int> TextMap = Writing.GetMap();
			map<char, int>::iterator it = Writing.GetIterator();
			HuffmanTreeNode *t;

			for(it = TextMap.begin(); it!=TextMap.end(); it++)
			{
				t = new HuffmanTreeNode(it->first, it->second);
				hqueue.push(t);
			}

			tree = Writing.BuildHuffmanTree(hqueue);

			tree->BuildMap(hqueue.top());

			string x = tree->Encode(Writing.message);

			cout << "Compressed Text \n\n";
			cout << endl;
			cout << x;
			cout << endl;

			cout << "\n\nCompressed Text Size: " << x.length() << " Bytes \n\n";

			cout << "Writing compressed text to file \n";

			tree->writeEncodedFile(x);

			cout << "Reading encoded file \n";

			tree->readEncodedFile("encoded.txt");

		}
		else if(choice == 3)
		{
			
			cout << "Please Enter The Name Of The File You Wish To Compress \n";
			cout << "Remember To Include .txt \n";
			cin >> textFileName;

			cout << "Original Text \n\n";
			cout << endl;
			Huffman Writing(textFileName);
			cout << endl;
			cout << "Text Size: " << Writing.message.length() * 8 << " Bytes \n\n";

			TextMap = Writing.GetMap();
			map<char, int>::iterator it = Writing.GetIterator();
			HuffmanTreeNode *t;

			for(it = TextMap.begin(); it!=TextMap.end(); it++)
			{
				t = new HuffmanTreeNode(it->first, it->second);
				hqueue.push(t);
			}

			tree = Writing.BuildHuffmanTree(hqueue);

			tree->BuildMap(hqueue.top());

			string x = tree->Encode(Writing.message);

			cout << "Compressing File" << endl;
			tree->CompressWithoutMap(x);
			
		}
		else if(choice == 4)
		{
			cout << "Please Enter The Name Of The File You Wish To Decompress \n";
			cout << "Remember To Include .txt \n";
			cin >> textFileName;
			cout<<endl<<endl;

			cout<<tree->DecompressWithoutMap(textFileName,TextMap)<<endl<<endl;
		}
		else if(choice == 5)
		{
			
			cout << "Please Enter The Name Of The File You Wish To Compress \n";
			cout << "Remember To Include .txt \n";
			cin >> textFileName;

			cout << "Original Text \n\n";
			cout << endl;
			Huffman Writing(textFileName);
			cout << endl;
			cout << "Text Size: " << Writing.message.length() * 8 << " Bytes \n\n";

			map<char, int> TextMap = Writing.GetMap();
			map<char, int>::iterator it = Writing.GetIterator();
			HuffmanTreeNode *t;

			for(it = TextMap.begin(); it!=TextMap.end(); it++)
			{
				t = new HuffmanTreeNode(it->first, it->second);
				hqueue.push(t);
			}

			tree = Writing.BuildHuffmanTree(hqueue);

			tree->BuildMap(hqueue.top());

			string x = tree->Encode(Writing.message);

			cout << "Compressing File" << endl;
			tree->Compress(x, TextMap);

		}
		else if(choice == 6)
		{
			cout << "Please Enter The Name Of The File You Wish To Decompress \n";
			cout << "Remember To Include .txt \n";
			cin >> textFileName;
			cout<<endl<<endl;

			cout<<tree->Decompress(textFileName)<<endl<<endl;
		}
		else if(choice == 7)
		{
			running = false;
		}
		else
		{
			cout << "Please choose a valid option: (1-6)\n";	
		}
	} while (running == true);
}


