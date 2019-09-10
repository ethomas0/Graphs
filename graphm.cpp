// --------------------- graphm.cpp -----------------------------------------
//
// Ethan Thomas
//
// --------------------------------------------------------------------------
#include "graphm.h"

// -----------------------Default Constructor--------------------------------
// --Constructs an empty table and initializes all values using makeEmpty().
// --------------------------------------------------------------------------
GraphM::GraphM()
{
	makeEmpty();
}

// ---------------------------MakeEmpty--------------------------------------
// --Helper function that initializes all C and T values.
// --Sets size to 0.
// --------------------------------------------------------------------------
void GraphM::makeEmpty()
{
	size = 0;

	for (int i = 0; i < MAXNODES_M; i++)
	{
		for (int j = 0; j < MAXNODES_M; j++)
		{
			C[i][j] = INT_MAX;
			T[i][j].visited = false;
			T[i][j].dist = INT_MAX;
			T[i][j].path = 0;

		}
	}
}

// --------------------------Destructor--------------------------------------
// --Needed so instances are deleteted properly.
// --------------------------------------------------------------------------
GraphM::~GraphM()
{
	
}

// ----------------------buildGraph()----------------------------------------
// --Builds up graph node information and adjacency matrix of edges
//   between each node reading from a file.
// --If nodeCount <= 0 or nodeCount > MAXNODES_M then buildgraph does nothing.
// --Assumes instance(*this) may not be empty when buildGraph() is called.
// --Uses insertEdge to verify data and insert if data is valid.
// --------------------------------------------------------------------------
void GraphM::buildGraph(ifstream& infile)
{
	int nodeCount = 0;
	infile >> nodeCount; //reads in node size

	if (nodeCount > 0 && nodeCount < MAXNODES_M) //verifys size is within range
	{
		if (this->size != 0) //in case *this already has data
		{
			makeEmpty();
		}

		size = nodeCount; // sets size

		string description = "";
		getline(infile, description);		// grab a line off file

		for (int i = 1; i <= this->size; i++)
		{
			this->data[i].setData(infile);	// set each node name
		}

		int source = 0, destination = 0, distance = 0;

		while ((infile >> source >> destination >> distance) && source != 0)	//read file and levarge as a bool and checks eof
		{
			if (!insertEdge(source, destination, distance)) // inserts or prints out error statement
			{
				std::cout << "Error: Could not insert edge (" << source << ", " <<
					destination << ") with cost of " << distance << std::endl;
			}
		}
	}
	

	
}

// ---------------------insertEdge()-----------------------------------------
// --First verifys data is valid (validData), if true then inserts an edge 
//   into a graph between 2 given nodes and returns true(validInput).
// --If false then does nothing and returns false(validInput).
// --------------------------------------------------------------------------
bool GraphM::insertEdge(const int& source, const int& destination, const int& distance)
{
	bool validInput = (source > 0 && source <= size && distance >= 0 &&
		destination > 0 && destination <= size && source != destination); //checks if data is valid

	if (validInput)    // input is within matrix bounds
	{
		C[source][destination] = distance;         // update cell with cost
		findShortestPath();						  // used to mitigate user error
	}

	return validInput;
}

// ---------------------removeEdge()-----------------------------------------
// --First verifys data is valid (validInput), if true then removes an edge
//   between 2 given nodes and returns true(validData).
// --If false then does nothing and returns false(validInput).
// --------------------------------------------------------------------------
bool GraphM::removeEdge(const int& source, const int& destination)
{
	bool validInput = (source > 0 && source <= size &&
		destination > 0 && destination <= size && source != destination); // checks if data is valid

	if (validInput)    // input is within matrix bounds
	{
		C[source][destination] = INT_MAX;         // update cell with cost
		findShortestPath();
	}

	return validInput;
}

// ----------------------findShortestPath()----------------------------------
// --Finds the shortest path between every node to every other node
//   in the graph using Dijkstra's algorithm.
// --Uses helper functions resetVisited(), findMinVertex, and setWeight().
// --------------------------------------------------------------------------
void GraphM::findShortestPath()
{
	

	int numVisits = 0, v = 0;

	this->resetVisited(); // resets visits to false

	for (int source = 1; source <= size; ++source)
	{
		numVisits = 0;
		T[source][source].dist = 0;

		while (numVisits < size)
		{
			v = findMinVertex(source); //find smallest value
			T[source][v].visited = true;
			++numVisits;
			setWeight(source, v); //set current shorest path
		}
	} 
	
}

// ----------------------resetVisited()-------------------------------------
// --Helper function that resets T distance values to infinity, path to 0, and
//   visited to false for every.
// --------------------------------------------------------------------------
void GraphM::resetVisited()
{
	for (int i = 1; i <= this->size; i++)
	{
		for (int j = 1; j <= this->size; j++)
		{
			T[i][j].dist = INT_MAX;
			T[i][j].path = 0;
			T[i][j].visited = false;
		}
	}
}

// ----------------------findMinVertex()-------------------------------------
// --Helper function that finds a vertex for the shortest path.
// --------------------------------------------------------------------------
int GraphM::findMinVertex(const int& source) const
{
	int v = 0;

	for (int i = 1; i <= size; ++i)
	{
		if (!T[source][i].visited) // checks if it has been visited
		{
			if (T[source][i].dist < T[source][v].dist) // if not compares distance
			{
				v = i;
			}
		}
	}

	return v; // returns shorter distance vertex
}

// ----------------------setWeight()-----------------------------------------
// --Helper function that sets the current shortest path information on all
//   nodes adjacent to the visited node.
// --------------------------------------------------------------------------
void GraphM::setWeight(const int& source, const int& v)
{
	for (int w = 1; w <= size; ++w)
	{
		if (!T[source][w].visited && C[v][w] < INT_MAX &&
			T[source][v].dist < INT_MAX) //hasen't been visited and values are less than infinite
		{
			if (T[source][w].dist > (T[source][v].dist + C[v][w])) //finds smaller value
			{
				T[source][w].dist = T[source][v].dist + C[v][w];
				T[source][w].path = v;
			}
		}
	}
}

// ------------------------display()-----------------------------------------
// --Displays the full path and distance bewtween 2 specified nodes.
// --Uses helper functions displaypath() and displayPathNodes().
// --------------------------------------------------------------------------
void GraphM::display(const int& source, const int& destination) const
{
	

	if (T[source][destination].dist < INT_MAX) // prints path
	{
		std::cout.width(4);
		std::cout << right << source;
		std::cout.width(8);
		std::cout << destination;
		std::cout.width(8);
		std::cout << T[source][destination].dist;
		std::cout << "        ";
		displayPath(source, destination);
		std::cout << destination << endl; 
		displayPathDescrip(source, destination);
	}
	else // no path
	{
		std::cout.width(4);
		std::cout << right << source;
		std::cout.width(8);
		std::cout << destination << "      " << "----";
	}
	
	std::cout << std::endl;
}

// ------------------------displayPath()-------------------------------------
// --Helper function that displays full path and distance between 2 nodes.
// --------------------------------------------------------------------------
void GraphM::displayPath(const int& source, const int& destination) const
{
	if (T[source][destination].path != 0)
	{
		displayPath(source, T[source][destination].path);
		std::cout << T[source][destination].path << ' ';
	}
}

// ------------------------displayPathNodes()--------------------------------
// --Helper function that displays description of path.
// --------------------------------------------------------------------------
void GraphM::displayPathDescrip(const int& source, const int& destination) const
{
	if (source != destination && T[source][destination].path > 0)
	{
		displayPathDescrip(source, T[source][destination].path);
	}

	// prints the descriptions
	std::cout << data[destination] << std::endl;
}

// ------------------------displayAll()-------------------------------------
// --Prints out a list of all nodes and their adjacencies. Prints shortest
//   and distance from every node to every other node.
// --Uses helper function displaySource().
// --------------------------------------------------------------------------
void GraphM::displayAll() const
{
	//setting up print output
	std::cout.width(26);
	std::cout << left << "Description";
	std::cout.width(11);
	std::cout << "From node";
	std::cout.width(9);
	std::cout << "To node";
	std::cout.width(12);
	std::cout << "Dijkstra's";
	std::cout.width();
	std::cout << "Path" << std::endl;

	for (int source = 1; source <= size; ++source)
	{
		displaySource(source); //helper function call for each node
	} 

	std::cout << std::endl;
}

// ------------------------displaySource()------------------------------------
// --Helper function that prints all the nodes that have paths from a 
//   specified node.
// --------------------------------------------------------------------------
void GraphM::displaySource(const int& source) const
{
	std::cout.width(32);
	std::cout << left << data[source] << std::endl;

	for (int dest = 1; dest <= size; ++dest)
	{
		if (dest != source) // if it doesn't equal itself
		{
			std::cout.width(35);
			std::cout << right << source;
			std::cout.width(5);
			std::cout << dest;
			cout.width(14);

			if (T[source][dest].dist == INT_MAX) // no path exsists
			{
				std::cout << "----" << std::endl;
			}
			else //path exsists
			{
				std::cout << T[source][dest].dist;
				std::cout.width();
				std::cout << "    ";
				displayPath(source, dest);
				std::cout << dest << std::endl;
			}
		}
	}
}




