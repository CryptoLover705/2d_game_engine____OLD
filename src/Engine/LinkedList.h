/*
	Linked List Class:
	Very clever linked list. (Hell to code)
	The tail of the list points to the head, visually forming a circle of nodes.
	This method allows the head pointer to be changed in one line of code excluding the validity check of the node pointer to change the head to
	I doubt there are any performance differences between this circular linked list and a 'normal' linear linked list.
	Created on: 4/7/2014
	By: Khalid Aleem
*/

#pragma once

#include <iostream>
#include <stdlib.h>

template<class T>
struct LinkedNode
{
	T x;
	LinkedNode *next;
};

template<class T>
class LinkedList
{
private:
	LinkedNode<T>* h_node;

public:
	LinkedList(void);
	~LinkedList(void);
	LinkedNode<T>* push_front(T value);
	LinkedNode<T>* push_back(T value);
	void set_head(LinkedNode<T>* node);
	LinkedNode<T>* get_head();
	void remove(LinkedNode<T>* node);

	/// TODO: Create proper iteration in contrast to lambda functions.
	template<typename IterF>
	void iterate(IterF iterfunction);

	int length;
};


template<class T>
LinkedList<T>::LinkedList()
{
	h_node = nullptr;
	length=0;
}

template<class T>
LinkedList<T>::~LinkedList()
{
	LinkedNode<T>* conductor = h_node;
	while(conductor->next != h_node)
	{
		conductor = conductor->next;
		delete conductor;
	}
	delete h_node;
}

template<class T>
LinkedNode<T>* LinkedList<T>::push_back(T value)
{
	LinkedNode<T>* conductor = h_node;


	if(h_node == nullptr)
	{
		h_node = new LinkedNode<T>;
		h_node->x = value;
		h_node->next = h_node;
		length++;
		return h_node;
	}

	while(conductor->next != h_node)
	{
		conductor = conductor->next;
	}

	conductor->next = new LinkedNode<T>;
	conductor->next->x = value;
	conductor->next->next = h_node;
	length++;
	return conductor->next;
}

template<class T>
LinkedNode<T>* LinkedList<T>::push_front(T value)
{
	if(h_node == nullptr)
	{
		h_node = new LinkedNode<T>;
		h_node->x = value;
		h_node->next = h_node;
		length++;
		return h_node;
	}

	LinkedNode<T>* old_h = h_node;
	h_node = new LinkedNode<T>;
	h_node->x = value;
	h_node->next = old_h;
	length++;

	LinkedNode<T>* conductor = old_h;
	while(conductor->next != old_h)
	{
		conductor = conductor->next;
	}
	conductor->next = h_node;
	return h_node;
}

template<class T>
void LinkedList<T>::set_head(LinkedNode<T>* node)
{
	LinkedNode<T>* conductor = h_node;
	int i=0;
	while ( conductor->next != node || conductor->next != h_node)
	{
		conductor = conductor->next;

		if(i > length)
			return;
		i++;
	}
	h_node = node;
}

template<class T>
LinkedNode<T>* LinkedList<T>::get_head()
{
	return h_node;
}

template<class T>
void LinkedList<T>::remove(LinkedNode<T>* node)
{
	LinkedNode<T>* conductor = h_node;
	LinkedNode<T>* prev_node;
	int i=0;
	while ( conductor->next != node || conductor->next != h_node)
	{
		prev_node = conductor;
		conductor = conductor->next;

		/// TODO: i>length check should not be necessary? (But apparently it is)
		if(i > length)
			return;
		i++;
	}
	if(conductor->next == h_node)
	{
		return;
	}
	/// TODO: Figure out why an extra ->next is required.
	prev_node->next->next = conductor->next->next;
	if(node == h_node)
	{
		h_node = conductor->next->next;
	}
	delete node;
	length--;
}

template<class T>
template<typename IterF>
void LinkedList<T>::iterate(IterF iterfunction)
{
	LinkedNode<T>* conductor = h_node;
	if(h_node != nullptr && h_node->x != nullptr)
	{
		iterfunction(h_node, h_node->x);
		while ( conductor->next != h_node )
		{
			iterfunction(conductor->next, conductor->next->x);
			conductor = conductor->next;
		}
	}
}
