//
//  LinkedList.h
//  Bonus Assignment
//  MergeSort in Linked List
//  Created by Haitham Khedr on 3/4/15.
//  Copyright (c) 2015 Haitham Khedr. All rights reserved.
//

#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include <iostream>
using namespace std;

template <class Item>
class LinkedList {
private:
    class Node;  //inner class Node
    Node* head,*tail;
    int numberOfItems;
    Node* mergeSort(Node* head);
    Node* merge(Node* a,Node* b);
    Node* split(Node* head);     //Alternating Split
  
public:
    LinkedList():head(nullptr),tail(nullptr),numberOfItems(0){}
	LinkedList(const LinkedList<Item> &src); //Copy constructor
	int getNumberOfItems()const;
    void addAtFront(Item item);
    void addAtEnd(Item item);
    void removeFirst();
    void removeLast();
	Item getFirst()const;
	Item getLast() const;
    void printall();
    void sort();
	bool find(Item key) const;
	bool isEmpty(){return numberOfItems==0;}
	void listToArray(Item a[]);
	class ListIterator;
	ListIterator begin(){return ListIterator(head);}
	ListIterator end(){return ListIterator(tail);}
	void clear() {
		while(!this->isEmpty())
		this->removeFirst();
	}
    ~LinkedList();
};

template<class Item> class LinkedList<Item>::Node{

public:
    Item data;
    Node* next;
    Node():next(nullptr){}
    Node(Item item):data(item),next(nullptr){}
};

template <class Item>void LinkedList<Item>::addAtFront(Item item) {
    Node* temp=new Node(item);
    if(head==nullptr){    //empty list
        head=temp;
        tail=head;
    }
    else{
        temp->next=head;
        head=temp;
    }
   
    numberOfItems++;
}
template <class Item> LinkedList<Item>::LinkedList(const LinkedList <Item> &src):numberOfItems(0), head(nullptr), tail(nullptr) {
	Node* current = src.head;
    while (current != NULL) {
        this->addAtEnd(current->data);
        current = current->next;
	}
}

template <class Item> void LinkedList<Item>::addAtEnd(Item item){
    Node* temp =new Node(item);
    if(head==nullptr){ //empty list
        head=temp;
        tail=head;
    }
    else{
    tail->next=temp;
    tail=temp;
    }
    numberOfItems++;
}
template <class Item>void LinkedList<Item> ::printall(){
    Node* temp=head;
    while(temp!=nullptr){
        cout<<temp->data<<endl;   //operator overloading should be used in different classes
        temp=temp->next;
    }
}
template <class Item>int LinkedList<Item> ::getNumberOfItems()const{
	return numberOfItems;
}
template <class Item>Item LinkedList<Item> ::getFirst()const{
	return head->data;
}
template <class Item>Item LinkedList<Item> ::getLast()const{
	return tail->data;
}

template <class Item>void LinkedList<Item>::removeFirst() {
    Node* temp=head;
    if(temp==nullptr)return;  //in case of empty list
    head=head->next;
    delete temp;
    numberOfItems--;
}

template <class Item> void LinkedList<Item>::removeLast() {
    Node* temp=head;
    while(temp !=nullptr){
        if(temp->next ==tail){
            delete tail;
            temp->next=nullptr;
            tail=temp;
            numberOfItems--;
            return;
        }
        temp=temp->next;
    }
    return;
}
template <class Item>void LinkedList<Item>:: sort() {
    
   this->head=mergeSort(this->head);
    
}
template <class Item>bool LinkedList<Item>::find(Item key) const{
	Node* temp=head;
	while(temp!=null){
		if(temp->data == key)
			return true;

		temp=temp->next;
	}
	return false;
}
template <class Item>typename LinkedList<Item>::Node* LinkedList<Item>::mergeSort(Node* head){
    Node* list2;
    if(head==nullptr) return nullptr ;
    else if (head->next==nullptr)return head;
    else{
    list2=split(head);
    return merge(mergeSort(head),mergeSort(list2));
    }
}


template <class Item> typename LinkedList<Item>::Node* LinkedList<Item>::split(Node *head){
    Node* list1;
    Node* list2;
    if(head==nullptr || head->next==nullptr)
        return nullptr;
    list1=head;
    list2=list1->next;
    list1->next=list2->next;
    list2->next=split(list2->next);
    return list2;
}

template <class Item> typename LinkedList<Item>::Node* LinkedList<Item> ::merge(Node *a, Node *b) {
    
    Node* first = nullptr;
    if (a == NULL)      //if list a is empty
        return b;
    else if (b==NULL)   //if list b is empty
        return a;
    if (a->data <= b->data) //compare  a and b
    {
        first = a;
        if(a->next !=nullptr)
            tail=a->next;           //update new tail
        first->next = merge(a->next, b);
     
       
    }
    else
    {
        first = b;
        if(b->next!=nullptr)
        tail=b->next;
        first->next = merge(a, b->next);
        
    }
    return first;

}
template <class Item> void LinkedList<Item>::listToArray(Item a[]){
	Node* temp=head;
	int i=0;
	while(temp!=nullptr){
		a[i++]=temp->data;
		temp=temp->next;
	}
}
template <class Item> LinkedList<Item>::~LinkedList(){
	clear();
}

template<class Item> class LinkedList<Item>::ListIterator{
private:
	Node* node;
public:
	ListIterator(Node* n=nullptr) :node(n){}
	bool hasNext() {

		if (node->next == nullptr) {
                return false;
            }
            return true;
	}
	void operator++() { node = node->next; }
    void operator++(int unused) { node = node->next; }
	bool operator!=(const ListIterator& other) { return node != other.node; }
	Item& operator*() const { return node->data; }
};

#endif
 


