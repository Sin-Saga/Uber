#ifndef LIST_H
#define LIST_H
#include <iostream>
using namespace std;
template<class T>
class Node
{
private:
	string data;
	double distance;
	Node<T> *next;
public:
	Node()
	{
		next = NULL;
		data = "NULL";
		distance = 0;
	}
	Node(string element)
	{
		next = NULL;
		data = element;
		distance = 0;
	}
	string getData()
	{
		return data;
	}
	double getdistance()
	{
		return distance;
	}
	void Setdata(string data)
	{
		data = data;
	}
	void Setdistance(double dist)
	{
		distance = dist;
	}
	Node<T>* GetNext()
	{
		return next;
	}
	void SetNext(Node<T> *x)
	{
		next = x;
	}
    ~Node()
	{
		delete next;
	}

	
};

template <class T>
class List
{
private:
	Node<T> *first;
public:
	List()
	{
		first = NULL;
	}
	Node<T>* getfirst()
	{
		return first;
	}
	void setfirst(Node<T>* n)
	{
		first = n;
	}
	void Insert(Node<T> * element)                     //Inserting Nodes By taking Node as A parameter 
	{
		if (first == NULL)
		{
			first = element;
		}
		else
		{
			Node<T>*temp = first;
			while (temp->GetNext() != NULL)
			{
				temp = temp->GetNext();
			}
			temp->SetNext(element);
		}
	}
	bool search(string element)                         //Searching That Node exist or not in Singly Linked List
	{
		bool ans = false;
		if (first == NULL)
		{
			return ans = false;
		}
		Node<T>*temp = first;
		while (temp!=NULL)
		{
			if (temp->getData()==element)
			{
				ans = true;
			}
			temp = temp->GetNext();
		}
			return ans;
	}
	void print()                                         //Print Singly Linked List with Numbering
	{
		int i = 0;
		Node<T>*temp = first;
		while (temp != NULL)
		{
			cout << "(" << i << ")" << temp->getData() << '\n';
			temp = temp->GetNext();
			i++;
		}
	}
	~List()
	{
		delete first;
	}
};
#endif 