/**
    @author Gavin Kenna
    @author Seán Lynch
*/


#pragma once
#include <iostream>
#include <string>

template<class DATATYPE, class COMPARE>
class HuffmanQueue
{
public:
	HuffmanQueue(void);
	~HuffmanQueue(void);
	void push(DATATYPE *data);
	void pop();
	bool empty();
	DATATYPE *top();
	void print();
	int size();

private:
	int _size;
	class Node{
		friend class HuffmanQueue;
	private:
		DATATYPE *data;
		Node *next;
	public:
		Node(DATATYPE *data)
		{
			this->data = data;
		}
		Node(){}
	};
	Node *root;
	void bubblesort();
	void selectionsort();
};

