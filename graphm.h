// --------------------- graphm.h -----------------------------------------
//
// Ethan Thomas
// ------------------------------------------------------------------------
// --Purpose: Implement Dijkstra's shortest path algorithm by reading in a
//   data file consisting of many lines and be able to find the shoretest
//   distance between any nodes. Then display the distance and path from 
//   every node to to every other node.
// ------------------------------------------------------------------------
// Assumptions: 
// --All input data is assumed to be correctly formatted.
// --GraphM class does not know about GraphL class, but both classes know
//   NodeData class.
// --This is a weighted graph.
// --Max node input will be 100, but since index 0 is not used, constant is set
//   to 101 (MAXNODES_M).
// --Also assumes user might misuse class by calling displayAll() without 
//   calling findShortestPath(). To mitigate error, adding or removing an edge
//   will also call findShortestPath().
// ------------------------------------------------------------------------

#ifndef GRAPHM_H
#define GRAPHM_H
#include <fstream>
#include <iostream>
#include <string>
#include <climits>
#include <iomanip>
#include "nodedata.h"


const int MAXNODES_M = 101; //constant size for T and C

class GraphM
{

public:
	GraphM();
	~GraphM();

	void buildGraph(ifstream& infile);

	bool insertEdge(const int& source, const int& destination, const int& distance);
	bool removeEdge(const int& source, const int& destination);

	void findShortestPath();

	void display(const int& source, const int& destination) const;
	void displayAll() const;



private:

	void makeEmpty();
	void resetVisited();	

	int findMinVertex(const int& source) const;
	void setWeight(const int& source, const int& v);

	void displayPath(const int& source, const int& destination) const;
	void displayPathDescrip(const int& source, const int& destination)const;
	void displaySource(const int& source) const;	

	struct TableType
	{
		bool visited;          // whether node has been visited         
		int dist;              // shortest distance from source known so far         
		int path;              // previous node in path of min dist      
	};

	NodeData data[MAXNODES_M];              // data for graph nodes       
	int C[MAXNODES_M][MAXNODES_M];         // Cost array, the adjacency matrix     
	int size;                             // number of nodes in the graph     
	TableType T[MAXNODES_M][MAXNODES_M]; // stores visited, distance, path

	
};
#endif // !GRAPHM_H
