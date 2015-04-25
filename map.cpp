// inter city map.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include"vertex.cpp"
#include"Edge.cpp"
#include<string>
#include "stack.h"
#include <queue>
#include"rapidxml.hpp"
#include<fstream>
#include <vector>
#include"InedexedMinHeap.h"
using namespace std;

void readGraphML(vector<string>& vertices ,vector<pair<pair<string,string>,int> > & edges){
		rapidxml::xml_document<> doc;
	ifstream file("Graph.xml");
	stringstream buffer;
	buffer << file.rdbuf();
	file.close();
	string content(buffer.str());
	doc.parse<0>(&content[0]);
	rapidxml::xml_node<> *pRoot = doc.first_node();
	for(rapidxml::xml_node<> *pNode=pRoot->first_node(); pNode; pNode=pNode->next_sibling())
{
	char* v="vertex";
	if(*(pNode->name())==*v){
		vertices.push_back(pNode->first_attribute()->value());
	}
	else{
		string from=pNode->first_attribute()->value();
		string to=pNode->first_attribute()->next_attribute()->value();
		int weight=atoi(pNode->first_attribute()->next_attribute()->next_attribute()->value());
		pair<string,string> p(from,to);
		edges.push_back( pair< pair<string,string>,int> (p,weight));
	}

}
}
int main(){
/*	try{
	const int size=10;
	 int strings[size] = { 10, 8, 9, 11, 7 ,5, 4, 50, 1, 2 };

	 IndexMinHeap<int> pq(size);
        for (int i = 0; i < size; i++) {
            pq.insert(i, strings[i]);
        }

        // delete and print each key
        while (!pq.isEmpty()) {
			int i = pq.minIndex();
			pq.delMin();
            cout<<strings[i];
        }
        cout<<endl;

        // reinsert the same strings
        for (int i = 0; i < size; i++) {
            pq.insert(i, strings[i]);
        }

	}catch(DesignByContractException& e){
		cout<<(string)e<<endl;
	}*/

	vector<string> vertices;
	vector<pair<pair<string,string>,int> > edges;
	
	
	try{
		readGraphML(vertices,edges);
		Graph<string> g=Graph<string>();
		for(int i=0;i<(int)vertices.size();i++)
			g.addVertex(vertices[i]);
		for(int i=0;i<(int)edges.size();i++)
			g.addEdge(edges[i].first.first,edges[i].first.second,edges[i].second);
		for(int i=0;i<(int)vertices.size();i++)
			g.displayAdjacentVertices(vertices[i]);

		g.getShortestPath(vertices[1]);
		
	}catch(DesignByContractException &e){
		cout<<(string)e<<endl;
	} 
	/*try{
	string c="Cairo";
	string a="Alexandria";
	string m="Mansoura";
	string t="Tanta";
	g.addVertex(c);
	g.addVertex(m);
	g.addVertex(t);
	g.addVertex(a);
	g.addEdge(c,a,250);
	g.addEdge(c,m,270);
	g.addEdge(a,t,100);
	g.addEdge(m,c,300);
	g.displayAdjacentVertices(c);
	g.displayAdjacentVertices(a);
	g.displayAdjacentVertices(m);
	

	cout<<g.getWeight(c,a)<<endl;
	if(g.DFS(m,a))
		cout<<"true"<<endl;
	else
		cout<<"false"<<endl;
	g.getShortestPath(c);
	}catch(DesignByContractException &e){
		cout<<(string)e<<endl;
	} */

	system("pause");
	return 1;
}  