#ifndef EDGE_H
#define EDGE_H
#include "Graph.h"
//Edge inner class Implementation
template <class Item> class Graph<Item>::Edge{
	public:
		Vertex *source,*destination;  //only the destination is actually needed 
		int weight;
		Edge():source(nullptr),destination(nullptr),weight(0){}
		Edge(Vertex* from, Vertex* to, int weight){source=from;destination=to;this->weight=weight;}

		// << operator overloading for printing
		friend ostream &operator<<(ostream &out,const Edge &e) {
			out<<*(e.source)<<"-"<<e.weight<<"->"<<*(e.destination);
		return out;
	}
};

#endif