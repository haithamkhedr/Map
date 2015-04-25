#ifndef MINHEAP_H
#define MINHEAP_H

#include<iostream>
#include"dbc.h"

template<class Item>
class IndexMinHeap {
private:
    int capacity;
	int* index;  //index to pos in heap
	Item* keys;  
	int* heap;   //the heap contains indices not keys
	int size;
	void swap(int i ,int j);
	void siftUp(int i);
	void siftDown(int i);
public:
		IndexMinHeap(int max) ;
		IndexMinHeap() ;
		bool isEmpty()const;
		bool contains(int i)const; /** checks if i is an index in the heap */
		int getSize()const;
		void insert(int i, Item key);
		int minIndex()const{return heap[0];} 
		Item minKey()const{return keys[heap[0]];}
		void delMin();
		void decreaseKey(int i, Item key);
};

template<class Item> IndexMinHeap<Item>::IndexMinHeap(int max){
	REQUIRE0(max >0);
	this->capacity=max;
	index=new int[capacity];
	keys=new Item[capacity];
	heap=new int[capacity];
	size=0;
	for(int i=0;i<capacity;i++)
		index[i]=-1;
}
template<class Item> IndexMinHeap<Item>::IndexMinHeap(){
	this->capacity=100;
	index=new int[capacity];
	keys=new Item[capacity];
	heap=new int[capacity];
	size=0;
	for(int i=0;i<capacity;i++)
		index[i]=-1;
}
template<class Item> bool IndexMinHeap<Item>::isEmpty()const{
	return size==0;
}
template<class Item> bool IndexMinHeap<Item>::contains(int i)const{
	REQUIRE0(i>=0 && i<capacity);
	return index[i]!=-1;	
}
template<class Item> int IndexMinHeap<Item>::getSize()const{
	return size;
}

template<class Item> void IndexMinHeap<Item>::insert(int i, Item key){
	REQUIRE0(i>=0 && i<capacity);
	REQUIRE0(!contains(i));
	keys[i]=key;
	index[i]=size;
	heap[size]=i;
	siftUp(size);
	size++;
}
template<class Item> void IndexMinHeap<Item>::delMin(){
	REQUIRE0(!isEmpty());
	int min=heap[0];
	swap(0,size-1);
	size--;
	siftDown(0);
	keys[min]=Item(); 
	index[min]=-1;   //delete index
}
template<class Item> void IndexMinHeap<Item>::swap(int i,int j){
	REQUIRE0(i>=0 && i<capacity &&j>=0 &&j<capacity);
	int temp = heap[i];
	heap[i] = heap[j]; 
	heap[j] = temp;
	index[heap[i]] = i; 
	index[heap[j]] = j;
}
template<class Item> void IndexMinHeap<Item>::decreaseKey(int i, Item key){
	REQUIRE0(i>=0 && i<capacity);
	REQUIRE0(contains(i));
	REQUIRE0(key<keys[i]);
	keys[i]=key;
	siftUp(index[i]);
}
template<class Item> void IndexMinHeap<Item>::siftUp(int i){
	while(i>0 && keys[heap[(i-1)/2]]>keys[heap[i]]){
		swap(i,(i-1)/2);
		i=(i-1)/2;
	}
}
template<class Item> void IndexMinHeap<Item>::siftDown(int i){
	while(2*i+1 <size){
		int left=2*i+1 ;
		int minIndex=i;
		int right=2*i +2;
		if(keys[heap[minIndex]]>keys[heap[left]])
			minIndex=left;
		if(right<size && keys[heap[right]]<keys[heap[minIndex]])
			minIndex=right;
		if(minIndex==i)break;
		swap(i,minIndex);
		i=minIndex;
	}

}
#endif