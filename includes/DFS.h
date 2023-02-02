#pragma once

#include <map>
#include <string>

#include "graphs.h"

using std::map;
using std::string;

class DFS {
  public:
    enum class EdgeStatus { DISCOVERY, BACK, UNEXPLORED };

    /**
      * Constructor for the DFS object. 
      *  
      * @param g The CongressGraph graph to run the algorithm on. 
      */
    DFS(CongressGraph g);

    /**
      * Function for traversing the graph. 
      *  
      * @param g The CongressGraph graph to run the algorithm on.
      * @param startingVertex The vertex to start the algorithm on.
      */
    void traverse(CongressGraph g, string startingVertex);
    
    /**
      * Function that outputs whether a particular vertex has been visited. 
      *  
      * @param vertex The vertex to check. 
      */
    bool isVertexVisited(string vertex);

    /**
      * Function that outputs if a particular edge is considered Discovery, Back, or Unexplored. 
      *  
      * @param e The edge to check. 
      */
    EdgeStatus getEdgeStatus(Edge e);

  private:
    CongressGraph g;
    map<string, bool> visitedVertices;
    map<Edge, EdgeStatus> visitedEdges;
    int numDiscoveryEdges = 0;
};