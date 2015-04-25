/**
	Graph.h
	Purpose: Representation of The Graph data structure
	@author Haitham Khedr
	@version 1.0 17/04/2015
*/

#ifndef GRAPH_H
#define GRAPH_H
#include "LinkedList.h"
#include "dbc.h"
#include "stack.h"
#include <unordered_map>
#include<queue>
#include<functional>
#include"InedexedMinHeap.h"
#define inf 1000000


template <class Item>
class Graph {
	private:
	class Edge;	  /**private inner class Represents edges between vertices*/
	class Vertex; /**private inner class represents Graph's Vertices*/
	void clearMarks();
	void connect(int v1,int v2,int weight){vertices[v1].edges->addAtEnd(Edge(&vertices[v1],&vertices[v2],weight));}
	const static int capacity=50;
	int size; //number of vertices
	int getIndex(const Item &t) const; /** returns the index of the vertex which hold the item.All classes using the graph should overload == operator*/
	std::unordered_map<Item,int> index;
	Vertex* vertices;
public:
	Graph(){size=0;vertices=new Vertex[capacity];}
	~Graph();
	bool isEmpty() const;
	bool isFull() const;
	void addVertex(const Item &t);	 /** Add new vertex to the graph*/
	void addEdge(const Item &from,const Item &to, int weight);	/** Add an edge between 2 existing vertices in the graph*/
	int  getWeight(const Item& from,const Item &to) const;		/** returns the Weight of the edge */
	bool DFS(const Item& start,const Item& key);
	void Graph<Item>::getShortestPath(Item start);
	void displayAdjacentVertices(const Item &v)const; 
	
};



//Vertex Inner Class Implementation

template<class Item> bool Graph<Item>::isEmpty() const{
	return size==0;
}
template<class Item> bool Graph<Item>::isFull() const{
	return size==capacity;
}
template<class Item> void Graph<Item>::addVertex(const Item &t) {
	REQUIRE0(!this->isFull()); //require that graph is not full
	REQUIRE0(index.count(t)==0);     //require that the key is not found
	vertices[size]=Vertex(t);
	index[t]=size++;
	ENSURE0(index.count(t)!=0);  //ensures vertex is added 
}
template<class Item> void Graph<Item>::addEdge(const Item &from,const Item &to, int weight) {
	REQUIRE0(index.count(from)!=0 || index.count(to)!=0);  // the source and destinationination vertices exists
	int source=getIndex(from);
	int destination =getIndex(to);
	connect(source,destination,weight);
}
template <class Item> int Graph<Item>::getWeight(const Item& from,const Item &to) const{
	REQUIRE0(index.count(from)!=0 || index.count(to)!=0); // the source and destinationination vertices exists
	REQUIRE0(vertices[getIndex(from)].hasAdj());
	int source=getIndex(from);
	int destination =getIndex(to);
	return vertices[source].getWeightTo(vertices[destination]);
}

template<class Item> bool Graph<Item>::DFS(const Item& start,const Item& key){  
	REQUIRE0(!this->isEmpty());
	REQUIRE0(index.count(start)!=0 || index.count(start)!=0) ;  //start vertex and desired vertex is found ...Lol :)
	Vertex* initial=&(vertices[getIndex(start)]);
	Vertex* required=&(vertices[getIndex(key)]);
	bool found =false;
	Stack<Vertex> stack=Stack<Vertex>();
	this->clearMarks();
	initial->markVertex();
	stack.push(*initial);
	while(!stack.isEmpty()){
		Vertex v=stack.pop();
		if(v.data==required->data)
			return true;
		else{
			int numberOfAdj=v.edges->getNumberOfItems();
			int* adj=new int[numberOfAdj];   //array of indices pointing to adjacent vertices
			v.getAdjacentVertices(adj,index);
			for (int i=0;i<numberOfAdj;i++)
			{
				Vertex adjacent=vertices[ adj[i] ];
				if(!adjacent.isMarked()){
					adjacent.markVertex();
					stack.push(adjacent);
				}
			}
			delete [] adj;
		}
	}
	return false; 
}

 template<class Item>  int Graph<Item>::getIndex(const Item &t)const {
	REQUIRE0(!this->isEmpty());
	return index.at(t);
}

	template<class Item> void Graph<Item>::clearMarks(){
		REQUIRE0(!this->isEmpty());
		for(int i=0;i<size;i++){
			vertices[i].marked=false;
			ENSURE0(vertices[i].marked==false);
		}
}
	
	
	template<class Item> void Graph<Item>::displayAdjacentVertices(const Item &item)const{
		REQUIRE0(!this->isEmpty());
		REQUIRE0(getIndex(item)!=-1);
		int index=getIndex(item);
		Vertex v=vertices[index];
		if(v.hasAdj()){
			(v.edges)->printall();  //print all edges
		}
	}
	template <class Item> Graph<Item>::~Graph(){
		for(int i=0;i<size;i++)
			delete vertices[i].edges;

		delete [] vertices;
	}
	template<class Item> void Graph<Item>::getShortestPath(Item start)
{
	clearMarks();
	int counter = 0;
	int s = getIndex(start);
	int dist[capacity];
	Vertex parent[capacity];
	for(int i=0; i<size; i++)   //initialize The array of distances & parents
	{
		dist[i] = inf;
		parent[i] = Vertex();
	}
	dist[s] = 0;
	//typedef pair<int, int> P;
	//priority_queue<P,vector<P>, greater<P> > pq;
	IndexMinHeap<int> pq=IndexMinHeap<int>();
	//pair<int, int> p (dist[s], s);
	//pq.push(p);
	for(int i=0; i<size; i++) 
	{
		pq.insert(i,dist[i]);
	}

	while(!pq.isEmpty())
	{
		pair<int, int> v(pq.minKey(),pq.minIndex());
		pq.delMin();
		vertices[v.second].markVertex(); //mark the popped vertex
		counter++;
		if(vertices[v.second].hasAdj())
		{	
			int arraySize=vertices[v.second].edges->getNumberOfItems();
			int* adj=new int[arraySize];
			vertices[v.second].getAdjacentVertices (adj, index);
			//release
			for(int i=0; i<vertices[v.second].edges->getNumberOfItems(); i++)
			{
				int adjIndex=adj[i];
				if(!vertices[adjIndex].isMarked()) //check if it is not popped before
				{
					int dvw = vertices[v.second].getWeightTo(vertices[adjIndex]);  //weight from source to adjacent node
					if(v.first + dvw < dist[adjIndex])
					{
						dist[adjIndex] = v.first + dvw;
						parent[adjIndex] = vertices[v.second];
						pq.decreaseKey(adjIndex, dist[adjIndex]);
					}
				}
			}
			delete [] adj;
		}

	}
	for (int i=0; i<size; i++){
		if(vertices[i].data == start)
			continue;
		if(dist[i]==inf){
			cout<<start<<" is not connected to "<<vertices[i]<<endl;
			continue;
		}
		cout << "Distance from " << start << " to " << vertices[i] << " is " <<dist[i] <<endl;
	}
}


#endif