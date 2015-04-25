#ifndef VERTEX_H
#define VERTEX_H
#include"Graph.h"
template <class Item> class Graph<Item>::Vertex{
	public:
		LinkedList<Edge>* edges; //List of Adjacent Vertices to a vertex
		Item data;
		Vertex() {edges=new LinkedList<Edge>();marked=false;} 
		Vertex(const Item & d)     {data=d;edges=new LinkedList<Edge>();marked=false;}
		void getAdjacentVertices(int v[],const unordered_map<Item,int> &index) const;	/** fill the List with a set of adjacent vertices to a given vertex */
		void markVertex(); //mark a vertex given a key
		bool isMarked() const;
		
		/**checks if vertex has adjacent vertices*/
		bool hasAdj()const{return !edges->isEmpty();}

		/**connects 2 vertices with an Edge*/	
		int getWeightTo(const Vertex & v)const; //returns the weight of the Edge from "this" vertex to a given vertex
		
		bool marked;  //used when traversing the Graph

		//overloading << Operator for printing
		friend ostream &operator<<(ostream &out, Vertex v) {
			out<<v.data;
		return out;
		}
	};

template<class Item> int Graph<Item>::Vertex::getWeightTo(const Vertex & v)const{

	for (LinkedList<Edge>::ListIterator iter=this->edges->begin();iter!=nullptr;iter++)
	{
		if(((*iter).destination)->data== v.data)    //compare the given vertex to the destination vertex of each edge
			return(*iter).weight;
	}
	return -1;
}

template<class Item> bool Graph<Item>::Vertex::isMarked()const{
		return this->marked==true;
}

	template<class Item> void Graph<Item>::Vertex::markVertex(){
		this->marked=true;
		ENSURE0(this->isMarked());	//Ensure Vertex is marked
}
	template<class Item> void Graph<Item>::Vertex::getAdjacentVertices(int* a,const unordered_map<Item,int> &index)const{
		int i=0;
		for(LinkedList<Edge>::ListIterator iter=this->edges->begin();iter!=nullptr;iter++){  //iterator of Edge
			a[i++]=index.at(((*iter).destination->data));     //edge.destination returns index to vertex	
		}
	}

#endif