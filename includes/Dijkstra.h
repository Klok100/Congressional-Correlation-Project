#pragma once

#include "graphs.h"

#include <map>
#include <string>
#include <tuple>

using std::map;
using std::string;
using std::tuple;

class Dijkstra {
    public:
        /**
          * Function that calculates the path and distance to every vertex from a given starting vertex.
          *  
          * @param g A graph of sponsors and co-sponsors. 
          * @param start The sponsor/co-sponsor that will serve as the starting point.
          * @return A tuple that contains a map of the distances and a map of the paths to each vertex.
          */
        tuple<map<string, double>, map<string, int>, map<string, string>> getDistancePaths(CongressGraph g, string start);

        /**
          * Function that returns the shortest path to a given vertex from a given starting vertex. 
          *  
          * @param g A graph of sponsors and co-sponsors.
          * @param start The sponsor/co-sponsor that will serve as the starting point.
          * @param end The sponsor/co-sponsor that will serve as the ending point.
          * @return A vector that contains the order of each vertex in the path read from left to right.
          */       
        vector<string> findShortestPath(CongressGraph g, string start, string end);

        /**
          * Function that returns the connectivity rating to an ending vertex from a given starting vertex.
          *  
          * @param g A graph of sponsors and co-sponsors.
          * @param start The sponsor/co-sponsor that will serve as the starting point.
          * @param end The sponsor/co-sponsor that will serve as the ending point.
          * @return The total connectivity rating from the starting vertex to the ending vertex.
          */        
        int getConnectivityRating(CongressGraph g, string start, string end);
};