// --------------------- graphl.cpp -----------------------------------------
//
// Ethan Thomas
//
// --------------------------------------------------------------------------
#include "graphl.h"

// -----------------------Default Constructor--------------------------------
// --Constructs an empty table and initializes all values using makeEmpty().
// --------------------------------------------------------------------------
GraphL::GraphL()
{
	makeEmpty();
}

// ---------------------------MakeEmpty--------------------------------------
// --Helper function that initializes adjNodeList values.
// --Sets size to 0.
// --------------------------------------------------------------------------
void GraphL::makeEmpty()
{
	size = 0;

	for (int i = 0; i < MAXNODES_L; i++)
	{
		adjNodeList[i].visited = false;
		adjNodeList[i].edgeHead = nullptr;
		adjNodeList[i].data = nullptr;
	}
}

// ----------------------------Destructor------------------------------------
// --Deletes all allocated memory using helper function deleteAll().
// --------------------------------------------------------------------------
GraphL::~GraphL()
{
	deleteAll();
}

// ----------------------------Destructor------------------------------------
// --Helper function that deletes all allocated memory.
// --------------------------------------------------------------------------
void GraphL::deleteAll()
{
	if (size > 0)
	{
		// traverses the entire graph array up to the size of the graph
		for (int i = 1; i <= size; i++)
		{
			// the head of the list
			EdgeNode* current = adjNodeList[i].edgeHead;
			delete adjNodeList[i].data;

			// deletes each node in the list
			while (current != nullptr)
			{
				// makes sure to keep connection after deleting current node
				EdgeNode* next = current->nextEdge;
				delete current;
				current = next;
			}

			adjNodeList[i].edgeHead = nullptr;
			adjNodeList[i].visited = false;
		}
		size = 0;
	}
}

// --------------------- buildGraph() -----------------------------------------
// --Builds up graph node information and adjacency list of edges between each
//   node reading from a data file.
// --Assumes instance(*this) may not be empty when buildGraph() is called.
// --Uses helper function insertEdge().
// --------------------------------------------------------------------------
void GraphL::buildGraph(ifstream & infile)
{
	int nodeCount = 0;
	infile >> nodeCount; // takes in amount of nodes

	if (nodeCount > 0 && nodeCount < MAXNODES_L) // verfiys it is within range
	{
		if (this->size != 0) // if *this is not empty
		{
			deleteAll();
		}

		size = nodeCount; // set size

		string description = "";
		getline(infile, description);

		for (int i = 1; i <= size; i++) // insert edge names
		{
			adjNodeList[i].data = new NodeData;
			adjNodeList[i].data->setData(infile);
		} 

		int source = 0, destination = 0;

		while ((infile >> source >> destination) && source != 0) // read in file and leverage as a bool and check for eof
		{
			if (!insertEdge(source, destination)) // try and insert, if false print out error statement
			{
				std::cout << "Error: Could not insert edge (" << source << ", " << 
					destination << std::endl;
			}
		}
	}
}

// ---------------------insertEdge()-----------------------------------------
// --Helper function for buildGraph().
// --First verifys data is valid (validData), if true then inserts an edge 
//   into a graph between 2 given nodes and returns true(validInput).
// --If false then does nothing and returns false(validInput).
// --------------------------------------------------------------------------
bool GraphL::insertEdge(const int & source, const int & destination)
{
	bool validInput = (source > 0 && source <= size &&     // validate input
					   destination > 0 && destination <= size && source != destination);
	if (validInput)    // input is within list bounds
	{
		EdgeNode* tempPtr = new EdgeNode;
		tempPtr->adjGraphNode = destination;
		tempPtr->nextEdge = nullptr;

		// connects the new edge node to the adjacency list, always adding to front
		EdgeNode* next = adjNodeList[source].edgeHead;
		adjNodeList[source].edgeHead = tempPtr;
		tempPtr->nextEdge = next;
	} // end if (success)

	return validInput;

}

// ---------------------displayGraph()---------------------------------------
// --Prints each node description and all paths in the graph.
// --------------------------------------------------------------------------
void GraphL::displayGraph() const
{
	EdgeNode* current;      // for edge list traversal

	std::cout << std::endl << "Graph:" << std::endl;

	for (int i = 1; i <= size; i++)
	{
		std::cout << "Node" << i << "          "
			<< *adjNodeList[i].data << std::endl; // print description

		current = adjNodeList[i].edgeHead;

		while (current != nullptr) // print paths
		{
			std::cout << "  edge  " << i << "  " << current->adjGraphNode << std::endl;
			current = current->nextEdge;
		}
		
		std::cout << std::endl;
	} 

	std::cout << std::endl;
}

// ---------------------depthFirstSearch()-----------------------------------
// --Makes a depth-first search and prints each node in depth-first order.
// --Uses helper functions resetVisited() and dfsHelper().
// --------------------------------------------------------------------------
void GraphL::depthFirstSearch()
{
	resetVisted(); // resets visits

	cout << endl << "Depth-first ordering: ";

	for (int vertex = 1; vertex <= size; vertex++)
	{
		if (!adjNodeList[vertex].visited) //if not visited
		{
			dfsHelper(vertex); // call helper function
		}
	} 

	cout << endl << endl;
}

// -------------------------resetVisited()-----------------------------------
// --Helper function that resets all adjNodeList.visited to false. 
// --------------------------------------------------------------------------
void GraphL::resetVisted()
{
	for (int i = 1; i < MAXNODES_L; i++)
	{
		adjNodeList[i].visited = false;
	}
}

// ---------------------------dfsHelper()------------------------------------
// --Helper function for depthFirstSearch(). Recursively finds the
//   depthFirstSearch
// --------------------------------------------------------------------------
void GraphL::dfsHelper(const int& vertex)
{
	EdgeNode* current = adjNodeList[vertex].edgeHead;

	adjNodeList[vertex].visited = true;
	cout << vertex << ' ';

	while (current != nullptr)
	{
		if (!adjNodeList[current->adjGraphNode].visited)
		{
			dfsHelper(current->adjGraphNode);
		}

		current = current->nextEdge;
	}
}



