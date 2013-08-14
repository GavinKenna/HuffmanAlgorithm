#include "HuffmanTree.h"
#include "Huffman.h"
#include <sstream>

HuffmanTree::HuffmanTree(HuffmanTreeNode *root)
{
	this->node = root;
}

HuffmanTree::HuffmanTree(){}

HuffmanTree::~HuffmanTree(void)
{
	DeleteTree(this->node);
}
void HuffmanTree::DeleteTree(HuffmanTreeNode* n)
{
	if(n->GetLeftNode() != NULL && n->GetLeftNode()->GetData()==NULL)
	{
		DeleteTree(n->GetLeftNode());
	}else if(n->GetLeftNode()->GetData()!=NULL)
	{
		delete n->GetLeftNode();
	}

	if(n->GetRightNode()!=NULL && n->GetRightNode()->GetData()==NULL)
	{
	}else if(n->GetRightNode()->GetData()!=NULL)
	{
		delete n->GetRightNode();
	}

}

HuffmanTreeNode * HuffmanTree::GetNode()
{
	return this->node;
}

//Builds The Encoding Map
void HuffmanTree::BuildMap(HuffmanTreeNode* treeNode)
{
	static string steps = "";
	if(treeNode->IsLeaf())
	{
		EncodeingMap[treeNode->GetData()] = steps;
	}

	if(treeNode->GetLeftNode()!=NULL)
	{
		steps+='0';
		BuildMap(treeNode->GetLeftNode());
		steps = steps.substr(0, steps.size()-1);
	}

	if(treeNode->GetRightNode()!=NULL)
	{
		steps+='1';
		BuildMap(treeNode->GetRightNode());
		steps = steps.substr(0, steps.size()-1);
	}
}

string HuffmanTree::Encode(string msg)
{
	string encrypted;
	for(int i = 0 ; i < msg.size() ;  i++)
	{
		encrypted += EncryptChar(msg.at(i));
	}

	return encrypted;
}

string HuffmanTree::EncryptChar(char c)
{
	return EncodeingMap[c];
}


string HuffmanTree::Decrypt(string msg)
{
	int start = 0;
	int end = 0;
	string text = "";
	char c;

	do{
		c = FindChar(msg.substr(start, end-start));
		if( c != NULL)
		{
			text+=c;
			start = end;
		}else{
			end++;
		}

	}while(start!=msg.size());

	return text;
}

string HuffmanTree::Decrypt(string msg, HuffmanTree *tree)
{
	int start = 0;
	int end = 0;
	string text = "";
	char c;

	do{
		c = FindChar(msg.substr(start, end-start),tree);
		if( c != NULL)
		{
			text+=c;
			start = end;
		}else{
			end++;
		}

	}while(start!=msg.size());

	return text;
}

char HuffmanTree::FindChar(string value, HuffmanTree *tree)
{



	for (it = tree->EncodeingMap.begin(); it!=tree->EncodeingMap.end(); ++it )
	{
		if (it->second == value)
		{
			return it->first;
		}
	}

	return NULL;
}


char HuffmanTree::FindChar(string value)
{



	for (it = EncodeingMap.begin(); it!=EncodeingMap.end(); ++it )
	{
		if (it->second == value)
		{
			return it->first;
		}
	}

	return NULL;
}

void HuffmanTree::printMap()
{
	map<char, string>::iterator it;
	for(it = EncodeingMap.begin(); it!=EncodeingMap.end(); it++)
	{
		//cout << it->first << " :: " << it->second<<endl;
	}

}

string HuffmanTree::DecompressWithoutMap(string textFileName,map<char, int> TextMap)
{
	ifstream textFile(textFileName, ios::binary); //fstream::binary

	textFile.unsetf(ios_base::skipws);

	HuffmanTreeNode *tn;
	HuffmanQueue<HuffmanTreeNode, NodeComp> hqueue;
	for(map<char, int>::iterator i = TextMap.begin(); i!=TextMap.end(); i++)
	{
		tn = new HuffmanTreeNode(i->first, i->second);
		hqueue.push(tn);
	}

	Huffman huff;
	HuffmanTree* tree = huff.BuildHuffmanTree(hqueue);
	tree->BuildMap(hqueue.top());
	string decompress; //The decompress message to be returned
	string bin; //The converted binary, which will be used to return the full message

	
	unsigned int padding = 0; //How many trailing zeros were added to the message to pad it out into 8bits

	stringstream ss;
	string buffer;
	if(textFile)
	{
		ss<<textFile.rdbuf();
		textFile.close();
	}
	buffer=ss.str();
	
	unsigned char temp;
	for(int i = 0 ; i < buffer.length() ; i++)
	{
		temp = buffer[i];
		bin+=ConvertFromChar(temp);
	}
	const char paddingTemp = temp; //The last character is the amount of padding added
	padding = atoi(&paddingTemp);
	bin.erase(bin.size()-8, 8); //Remove padding from file

	if(padding>0)
	{
		int pos = (bin.size())-(padding-1);
		bin.erase(pos, padding); //delete all the added padding
	}


	int offset=0;
	for(int j = 0; j <= bin.size(); j++)
	{
		string selection(bin.begin()+offset, bin.begin()+j);// =  //y.at(p,j);//(y,p,j-p);
		
		for (it = tree->EncodeingMap.begin(); it!=tree->EncodeingMap.end(); ++it )
		{
			if(it->second==selection)
			{
				char b = it->first;
				decompress+=b;
				offset=j;
				selection="";
			}
		}

	}
	ofstream out("out.txt", ios::binary); //fstream
	out.unsetf(ios_base::skipws);
	out<<decompress;
	out.close();
	return decompress;

}

string HuffmanTree::Decompress(string textFileName)
{
	//ifstream textFile("out.txt"); // provide the name of the file here
	ifstream textFile(textFileName, ios::binary); //fstream::binary

	textFile.unsetf(ios_base::skipws);

	int count;
	textFile>>count;
	textFile.ignore();
	map<char, int> TextMap;

	for(int i = 0 ; i < count ; i++)
	{
		char chr;
		int freq;

		textFile.get(chr);
		//textFile.ignore();
		textFile>>freq;
		textFile.ignore();

		TextMap[chr] = freq;
	}

	HuffmanTreeNode *tn;
	HuffmanQueue<HuffmanTreeNode, NodeComp> hqueue;
	for(map<char, int>::iterator i = TextMap.begin(); i!=TextMap.end(); i++)
	{
		tn = new HuffmanTreeNode(i->first, i->second);
		hqueue.push(tn);
	}

	Huffman huff;
	HuffmanTree* tree = huff.BuildHuffmanTree(hqueue);
	tree->BuildMap(hqueue.top());
	string decompress; //The decompress message to be returned
	string bin; //The converted binary, which will be used to return the full message

	
	unsigned int padding = 0; //How many trailing zeros were added to the message to pad it out into 8bits

	stringstream ss;
	string buffer;
	if(textFile)
	{
		ss<<textFile.rdbuf();
		textFile.close();
	}
	buffer=ss.str();
	
	unsigned char temp;
	for(int i = 0 ; i < buffer.length() ; i++)
	{
		temp = buffer[i];
		bin+=ConvertFromChar(temp);
	}
	const char paddingTemp = temp; //The last character is the amount of padding added
	padding = atoi(&paddingTemp);
	bin.erase(bin.size()-8, 8); //Remove padding from file

	if(padding>0)
	{
		int pos = (bin.size())-(padding-1);
		bin.erase(pos, padding); //delete all the added padding
	}


	int offset=0;
	for(int j = 0; j <= bin.size(); j++)
	{
		string selection(bin.begin()+offset, bin.begin()+j);// =  //y.at(p,j);//(y,p,j-p);
		
		for (it = tree->EncodeingMap.begin(); it!=tree->EncodeingMap.end(); ++it )
		{
			if(it->second==selection)
			{
				char b = it->first;
				decompress+=b;
				offset=j;
				selection="";
			}
		}

	}
	ofstream out("out.txt", ios::binary); //fstream
	out.unsetf(ios_base::skipws);
	out<<decompress;
	out.close();
	return decompress;

}

void HuffmanTree::CompressWithoutMap(string input)
{
	string compressed = input;
	int size = 0;
	signed char current;
	string toConvert;
	int currentChar;
	string converted;
	ofstream out("comp.txt", ios::binary); //fstream
	out.unsetf(ios_base::skipws);

	for(int i = 0 ; i < input.size();  i++)
	{
		if(toConvert.size() < 8)
		{
			toConvert += input.at(i);
			if(toConvert.size() == 8)
			{
				current = ConvertToChar(toConvert);
				out << current;
				//out.close();
				toConvert = "";
			}
		}
	}

	int padding = 0;
	if(toConvert.size() > 0)
	{
		for(int i = toConvert.size(); i < 8; toConvert+= '0')
		{ 
			padding++;
			if(toConvert.size() == 8)
			{
				current = ConvertToChar(toConvert);
				out << current;
				//out.flush();
				//out.close();
				break;
			}
		}
	}
	out<<padding;
	out.close();
	cout << "Saves as comp.txt \n";
}

void HuffmanTree::Compress(string input, map<char, int> TextMap) //Compress with map
{
	string compressed = input;
	int size = 0;
	signed char current;
	string toConvert;
	int currentChar;
	string converted;
	ofstream out("comp.txt", ios::binary); //fstream
	out.unsetf(ios_base::skipws);

	out<<this->EncodeingMap.size()<<endl; //added endl
	for (map<char, int>::iterator i = TextMap.begin(); i!=TextMap.end(); ++i )
	{
		out<<i->first<<i->second<<endl; //added endl
	}

	for(int i = 0 ; i < input.size();  i++)
	{
		if(toConvert.size() < 8)
		{
			toConvert += input.at(i);
			if(toConvert.size() == 8)
			{
				current = ConvertToChar(toConvert);
				out << current;
				//out.close();
				toConvert = "";
			}
		}
	}

	int padding = 0; //how many zeros padded in to make 8bits
	if(toConvert.size() > 0)
	{
		for(int i = toConvert.size(); i < 8; toConvert+= '0')
		{ 
			padding++;
			if(toConvert.size() == 8)
			{
				current = ConvertToChar(toConvert);
				out << current;
				//out.flush();
				//out.close();
				break;
			}
		}
	}

	out<<padding;
	out.close();
}

unsigned char HuffmanTree::ConvertToChar(string toConvert)
{
	//cout << "Converting "  << toConvert << endl;
	unsigned char converted = ' ';

	int totalValue = 0;
	for(int i = 0; i < 8; i++)
	{
		if(toConvert.at(i) == '1')
		{
			totalValue += pow(2.0, 7-i);
		}
	}

	converted = totalValue;
	//	cout << toConvert << " converted to " << (int)converted << "::" << converted << endl;
	if(converted == 65)
	{
		//cout<<"hello"<<endl;
	}
	return converted;
}

string HuffmanTree::ConvertFromChar(unsigned char toConvert)
{
	//cout << "Converting "  << toConvert << endl;
	string converted = "";
	int total = toConvert;
	for(int i = 0 ; i <8 ; i++)
	{
		if(total-pow(2.0, 7-i) >=0) 
		{
			total-=pow(2.0, 7-i);

			converted+='1';
		}else{
			converted+='0';
		}
	}


	return converted;
}

void HuffmanTree::writeEncodedFile(string encodedMessage)
{
	fstream out("encoded.txt");
	out << encodedMessage;
	out.close();
	cout << "Saved as encoded.txt \n\n";
}

void HuffmanTree::writeDecodedFile(string DecodedMessage)
{
	fstream out("out.txt");
	out << DecodedMessage;
	out.close();
	cout << "Saved as out.txt \n\n";
}

void HuffmanTree::readEncodedFile( string fileName )
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
		//cout << message;
		textFile.close();
		string decoded = this->Decrypt(message);
		cout << endl;
		cout << decoded;
		cout << endl;
		cout << "Saving Decoded File As out.txt\n";
		this->writeDecodedFile(decoded);
	}

}
