#include "HuffmanQueue.h"
#include "HuffmanTreeNode.h"

template<class DATATYPE, class COMPARE>
HuffmanQueue<DATATYPE, COMPARE>::HuffmanQueue(void)
{
	_size = 0;
	this->root = NULL;
}

template<class DATATYPE, class COMPARE>
HuffmanQueue<DATATYPE, COMPARE>::~HuffmanQueue(void)
{
	 Node *temp;
	 while (this->root) {
                temp = root;
                root = root->next;
                delete temp;
    }
	 
}

template<class DATATYPE, class COMPARE>
void HuffmanQueue<DATATYPE, COMPARE>::push(DATATYPE *data)
{
	// IntNode *newNode = new IntNode(number);
	//newNode->next = this->head;
	//  head = newNode;
	_size++;
	Node *temp = new Node(data);

	temp->next = root;
	root = temp;
	if(_size<=10)
	{
		bubblesort();
	}else{
		selectionsort();
	}
}

template<class DATATYPE, class COMPARE>
void HuffmanQueue<DATATYPE, COMPARE>::pop()
{
	if(!empty())
	{
		this->root=this->root->next;
		_size--;
	}
}

template<class DATATYPE, class COMPARE>
bool HuffmanQueue<DATATYPE, COMPARE>::empty()
{
	return _size==0;
}

template<class DATATYPE, class COMPARE>
DATATYPE *HuffmanQueue<DATATYPE, COMPARE>::top()
{
	return this->root->data;
}

template<class DATATYPE, class COMPARE>
int HuffmanQueue<DATATYPE, COMPARE>::size()
{
	return this->_size;
}

template<class DATATYPE, class COMPARE>
void HuffmanQueue<DATATYPE, COMPARE>::bubblesort()
{
	COMPARE *comp = new COMPARE();

	Node *temp = this->root;
	Node *prev = this->root;
	bool clean;

	while(temp->next!=NULL)
	{
		do{
			if(!(comp->operator()(temp->data, temp->next->data)))
			{
				clean = false;
				if(temp==root)
				{
					Node *next = temp->next;
					temp->next = next->next;
					next->next = temp;
					root = next;
				}else{
					Node *next = temp->next;
					temp->next = next->next;
					next->next = temp;
					prev->next = next;
				}
				temp = root;
				prev = root;
			}else{
				clean = true;
			}

		}while(!clean);
		if(temp->next!=NULL){
			prev = temp;
			temp = temp->next;
		}
	}
	delete comp;
}

template<class DATATYPE, class COMPARE>
void HuffmanQueue<DATATYPE, COMPARE>::selectionsort()
{
	COMPARE *comp = new COMPARE();
	Node *temp = this->root;
	Node *prev = this->root;
	Node *j = NULL;
	DATATYPE *first = NULL;
	Node *t = NULL;
	bool clean = true;
	while(temp->next!=NULL)
	{
		t = temp;
		j = temp->next;
		while(j!=NULL)
		{
			if((comp->operator()(j->data, t->data)))
			{
				t = j;
			}
			j=j->next;
		}

		DATATYPE *x = t->data;
		t->data = temp->data;
		temp->data = x;

		temp = temp->next;
	}
	delete comp;

}




template<class DATATYPE, class COMPARE>
void HuffmanQueue<DATATYPE, COMPARE>::print()
{
	Node *temp = root;

	while(!temp)
	{
		cout<<temp->data<<endl;
		temp = temp->next;
	}
}