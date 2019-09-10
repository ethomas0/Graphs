// ----------------------graphl.h------------------------------------------
//
// Ethan Thomas
// 
// ------------------------------------------------------------------------
// Purpose: 
//  --Implement Dijkstra's shortest path algorithm by reading in a
//    data file consisting of many lines and be able to find the all the
//    paths.  Then display the path from every node to to every
//    other node.
// ------------------------------------------------------------------------
// Assumptions: 
// --All input data is assumed to be correctly formatted.
// --GraphL class does not know about GraphM class, but it does know about
//   NodeData class.
// --This is an unweighted graph.
// --Max node input will be 100, but since index 0 is not used, constant is set
//   to 101 (MAXNODES_L).
// ------------------------------------------------------------------------


#ifndef GRAPHL_H
#define GRAPHL_H

#include "nodedata.h"
#include <iostream>
#include <iomanip>
#include <fstream>


int const MAXNODES_L = 101; //constant size for adjNodeList

class GraphL
{
public:
	GraphL();
	~GraphL();

	void buildGraph(ifstream& infile);

	

	void displayGraph()const;
	void depthFirstSearch();



private:

	void makeEmpty();
	void deleteAll();
	bool insertEdge(const int& source, const int& destination);
	void resetVisted();
	void dfsHelper(const int& vertex);
	

	int size;
	struct EdgeNode;
	struct GraphNode
	{
		EdgeNode* edgeHead;
		NodeData* data;
		bool visited;
	};

	struct EdgeNode
	{
		int adjGraphNode;
		EdgeNode* nextEdge;
	};

	GraphNode adjNodeList[MAXNODES_L];

	

};
#endif // !GRAPHL_H

