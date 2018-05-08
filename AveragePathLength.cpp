/* Description: A program to calculate the average path length between any two nodes in a network
 * Author: Freya Murphy
 */

 #include <vector>
 #include <string>
 #include <fstream>
 #include <sstream>
 #include <iostream>

using namespace std;
 // Step 1: Read the network into an adjacency matrix.
 // Step 2: Calculate shortest path between each pair of nodes using breadth-first search.
 // Step 3: Calculate the average path length.
/* For testing */

/* For testing */
void displayVector(vector<int> v) {
  for(int i = 0; i < v.size(); i++) {
    cout << v.at(i) << " ";
  }
  cout << endl;
}

/* For testing */
void displayMatrix(vector< vector<int> > matrix) {
  for (int i = 0; i < matrix.size(); i++) {
    for (int j = 0; j < matrix.at(0).size(); j++) {
      cout << matrix.at(i).at(j) << " ";
    }
    cout << endl;
  }
  cout << endl;
}

/* Create a square matrix with values initialised to 0.
 * Inputs:  number of nodes in the network
 * Outputs: empty matrix
 */
vector< vector<int> > initialiseMatrix(int numberOfNodes) {
  vector<int> innerVector = vector<int>(numberOfNodes, 0);
  vector< vector<int> > matrix = vector< vector<int> >(numberOfNodes, innerVector);

  return matrix;
}

/* Read the network into an adjacency matrix
 * The file must be in the form: node1 node2
 * Inputs:  adjacencyMatrix to read into
 *          fileName of data file
 * Outputs: Adjacency matrix for network (a 2D vector)
*/
vector< vector<int> > readNetwork(vector< vector<int> > adjacencyMatrix, string fileName) {

  // The line of text to be read from the file
  string line;

  // When the node values are read they will be strings
  string strNode1;
  string strNode2;

  // Represents one character in the line
  char currChar;

  // To store the values in the adjacency matrix they must be converted to ints
  int node1;
  int node2;

  // Open the file for reading
  ifstream inputFile(fileName);

  // Check that the file was opened correctly
  if (inputFile.is_open()) {

    // Read one line at a time
    while ( getline(inputFile, line) ) {
      strNode1 = "";
      strNode2 = "";

      // Read node 1
      int i = 1;
      // Start with the first character
      currChar = line.at(0);
      // Read until the first space
      while (currChar != ' ') {
        // Add this character to the string
        strNode1 += currChar;
        // Get the next character
        currChar = line.at(i);
        i++;
      }
      //cout << "Node 1 is " << strNode1 << endl;

      // Skip over the space
      currChar = line.at(i);
      i++;

      // Read node 2
      while (i < line.size()) {
        strNode2 += currChar;
        currChar = line.at(i);
        i++;
      }
      //cout << "Node2 is " << strNode2 << endl;

      // Convert string values from the file to int values for the vector
      stringstream convertToInt;
      convertToInt << strNode1;
      convertToInt >> node1;
      convertToInt.clear();
      convertToInt << strNode2;
      convertToInt >> node2;

      // NodeIDs in the datafile start from 1 but the adjacency matrix starts at 0
      node1 --;
      node2 --;

      // Store the edge in the adjacency matrix
      adjacencyMatrix.at(node1).at(node2) += 1;
    }

  }
  else {
    cout << "Unable to open " << fileName << " for reading." << endl;
  }
  // Return the adjacencyMatrix
  return adjacencyMatrix;
}

/* Find node with smallest assigned distance
 * Inputs:  visited - list specifying which nodes have been visited
 *          distances - currently assigned distances to the nodes
 * Outputs: nodeID of unvisited node with smallest distance
 */
int findMinimumNode(vector<int> visited, vector<int> distances) {

  int minVal;
  int minPos = -1;

  // Find the first unvisited node
  int i = 0;
  bool hasBeenVisited = true;
  while (hasBeenVisited && i < visited.size()) {
    if (visited.at(i) == 0 && distances.at(i) != -1) {
      hasBeenVisited = false;
    }
    i++;
  }

  minPos = i-1;
  minVal = distances.at(minPos);

  // Find the minimum unvisited value that is not -1
  for (int j = i; j < distances.size(); j++) {

    if (visited.at(j) == 0) {

      if (distances.at(j) != -1) {

        if (distances.at(j) < minVal) {
          minVal = distances.at(j);
          minPos = j;
        }

      }
    }
  }

  if (minPos == -1) {
    // An unvisited, distanced node cannot be found.
    // Find the first unvisited node.
    hasBeenVisited = true;
    int k = 0;
    while (hasBeenVisited) {
      if (visited.at(k) == 0) {
        hasBeenVisited = false;
        minPos = k;
      }
      k++;
    }
  }

  return minPos;
}

/* Calculate the shortest path a starting node and all other nodes in the network
 * Inputs:  Starting node ID
 *          adjacencyMatrix of network
 * Outputs: List of distances from starting node to each other node
 */
vector<int> dijkstra(int startNode, vector< vector<int> > adjacencyMatrix) {
  int numberOfNodes = adjacencyMatrix.size();
  // The distance to each node in the network, initialised to -1
  vector<int> distances = vector<int>(numberOfNodes, -1);
  // A list of nodes which have been visited (0 = unvisited, 1 = visited)
  vector<int> visited = vector<int>(numberOfNodes, 0);
  // The number of nodes which have been visited
  int numberVisited = 0;
  // The current node being computed
  int currNode;

  // Store distance to start node as 0
  distances.at(startNode) = 0;

  // While there are still nodes to visit
  while (numberVisited < numberOfNodes) {

    // Get the unvisited node with the smallest currently assigned distance
    currNode = findMinimumNode(visited, distances);

    // Find unvisited nodes i adjacent to currNode
    for (int i = 0; i < numberOfNodes; i++) {
      if (adjacencyMatrix.at(currNode).at(i) > 0 && visited.at(i) == 0) {
        // Calculate the distance to i
        int distanceToi = distances.at(currNode) + 1;

        // If the distance to i has not been computed or is greater than the newly calculated distance
        if (distances.at(i) == -1 || distances.at(i) > distanceToi) {
          // Store distance to i
          distances.at(i) = distanceToi;
        }

      }

    }

    // Mark currNode as visited
    visited.at(currNode) = 1;
    numberVisited++;

  }
  return distances;
}

/* Calculate the shortest path between each pair of nodes in the network.
 * Inputs: Adjacency matrix of network
 * Outputs: 2D vector of distances
 */
vector< vector<int> > calculateShortestPaths(vector< vector<int> > adjacencyMatrix) {
  // Matrix of distances for all nodes
  vector< vector<int> > distancesMatrix;
  // List of distances for one node
  vector<int> distancesVector;

  // For each node
  for (int i = 0; i < adjacencyMatrix.size(); i++) {
    cout << "Calculating distances for node " << i << " ..." << endl;
    // Get the distance from this node to all other nodes
    distancesVector = dijkstra(i, adjacencyMatrix);

    /* testing */
    //displayVector(distancesVector);

    // Add these distances to the matrix
    distancesMatrix.push_back(distancesVector);
  }

  cout << "Finished calculating distances. " << endl;
  return distancesMatrix;
}

/* Returns true if a node has degree > 0 and false otherwise.
 * Inputs:  adjacency matrix
 *          nodeID of node to be tested
 * Outputs: true / false
 */
bool nodeIsConnected(vector< vector<int> > adjacencyMatrix, int node) {
  cout << "Determining whether node " << node << " is connected." << endl;
  for (int i = 0; i < adjacencyMatrix.size(); i++) {
    if (adjacencyMatrix.at(i).at(node) > 0) {
      //cout << "node " << node << " is connected." << endl;
      return true;
    }
  }

  for (int i = 0; i < adjacencyMatrix.at(0).size(); i++) {
    if (adjacencyMatrix.at(node).at(i) > 0) {
      //cout << "node " << node << " is connected." << endl;
      return true;
    }
  }
  //cout << "node " << node << " is not connected." << endl;
  return false;
}

/* Calculate the average path length for the network
 * Inputs: Adjacency matrix of network
 * Outputs: Average path length
 */
double calculateAveragePathLength(vector< vector<int> > adjacencyMatrix) {
  vector< vector<int> > distances = calculateShortestPaths(adjacencyMatrix);
  int numberOfNodes = adjacencyMatrix.size();
  int distanceSum = 0;
  // Count the number of nodes which have been discarded
  int unconnectedNodes = 0;

  // Calculate which nodes are not connected.
  vector<bool> isConnected = vector<bool>(adjacencyMatrix.size(), false);
  for (int i = 0; i < isConnected.size(); i++)
  {
    isConnected.at(i) = nodeIsConnected(adjacencyMatrix, i);
    if (!isConnected.at(i))
    {
      unconnectedNodes++;
    }
  }


  // Sum all the distances
  for(int i = 0; i < numberOfNodes; i++) {
    if (isConnected.at(i))
    {
      for(int j = 0; j < numberOfNodes; j++) {
          // Do not include nodes which have 0 degree
          if (isConnected.at(j)) {
            // Do not count the distance from a node to itself
            // distance = -1 means the distance to the node has not been computed
            //  i.e. it cannot be reached from this node.
            if (i != j && distances.at(i).at(j) != -1) {
              //cout << "Summing distances..." << endl;
              distanceSum += distances.at(i).at(j);
            }
          }
      }
    }
  }
  cout << "Unconnected nodes: " << unconnectedNodes << endl;

  cout << "Calulating average..." << endl;
  double dNumNodes = static_cast<double>(numberOfNodes - unconnectedNodes);
  double dDist = static_cast<double>(distanceSum);
  double denominator = dNumNodes * (dNumNodes - 1);
  double averagePathLength = dDist / denominator;

  cout << "Finished :)" << endl;
  return averagePathLength;
}

/* Main function */
int main(int argc, char* argv[]) {
  if (argc != 3)
  {
    cout << "Usage: " << argv[0] << " INPUT_FILE NUMBER_OF_NODES" << endl;
    return 1;
  }

  int numberOfNodes;
  stringstream convertToInt;
  convertToInt << argv[2];
  convertToInt >> numberOfNodes;
  //int numberOfNodes = argv[2];
  string dataFile = argv[1];

  vector< vector<int> > adjacencyMatrix = initialiseMatrix(numberOfNodes);
  adjacencyMatrix = readNetwork(adjacencyMatrix, dataFile);
  double averagePathLength = calculateAveragePathLength(adjacencyMatrix);
  cout << endl << "The average path length for " << dataFile << " is " << averagePathLength << endl;
  return 0;
}
