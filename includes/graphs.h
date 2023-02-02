#pragma once

#include <map>
#include <memory>
#include <string>
#include <vector>

using std::string;
using std::map;
using std::vector;

struct Edge {
    string sponsor_id;
    string cosponsor_id;
    int weight = 1; //number of bills submitted where the Congress member is listed as a cosponsor

    Edge(string sp_id, string co_id) {
        sponsor_id = sp_id;
        cosponsor_id = co_id;
    }

    Edge(string sp_id, string co_id, int weight_) {
        sponsor_id = sp_id;
        cosponsor_id = co_id;
        weight = weight_;
    }

    bool operator==(const Edge& other) const;
    bool operator<(const Edge& other) const;
};

class CongressGraph {
  public:
    /**
      * Function that inserts a vertex into the graph. 
      *  
      * @param sponsor_id The vertex to insert. 
      */
    void insertVertex(string sponsor_id);

    /**
      * Function that removes a vertex from the graph. 
      *  
      * @param sponsor_id The vertex to remove. 
      */
    void removeVertex(string sponsor_id);

    /**
      * Function that returns a vector of all vertices in the graph.  
      * 
      * @return A vector of all vertices in the graph.
      */
    vector<string> getVertices();

    /**
      * Function that inserts an edge from the sponsor to the cosponsor. 
      *  
      * @param sponsor_id The sponsor/origin of the edge to insert. 
      * @param cosponsor_id The cosponsor/destination of the edge to insert.
      */
    void insertEdge(string sponsor_id, string cosponsor_id);

    /**
      * Function that removes the edge between a sponsor and cosponsor. 
      *  
      * @param sponsor_id The sponsor/origin of the edge to remove. 
      * @param cosponsor_id The cosponsor/destination of the edge to remove.
      */
    void removeEdge(string sponsor_id, string cosponsor_id);

    /**
      * Function that returns a vector of all incident edges from a sponsor. 
      *  
      * @param sponsor_id The sponsor to return incident edges. 
      * @return A vector of all incident edges from a given sponsor.
      */
    vector<Edge> incidentEdges(string sponsor_id);

    /**
      * Function that outputs whether a particular sponsor exists. 
      *  
      * @param sponsor_id The sponsor to check. 
      * @return A boolean values that says if a given sponsor exists.
      */
    bool vertexExists(string sponsor_id);

    /**
      * Function that extracts values from the inputted file and stores them into a map. 
      *  
      * @param filename The file to extract data from. 
      */
    void importData(std::string filename);

    /**
      * Function that extracts values from the inputted file and stores them into a map. 
      *  
      * @param filename The file to extract data from. 
      * 
      * Note: This function is only used for testing purposes.
      */
    void importDataTest(std::string filename);    

    /**
      * Function that inserts a weighted edge from the sponsor to the cosponsor. 
      *  
      * @param sponsor_id The sponsor/origin of the edge to insert. 
      * @param cosponsor_id The cosponsor/destination of the edge to insert.
      * @param weight The weight of the edge to insert.
      * 
      * Note: This function is only used for testing purposes.
      */
    void insertWeightedEdge(string sponsor_id, string cosponsor_id, int weight);

  private:
    map<string, vector<Edge>> adj_list; //key is a sponsor's bioGuideID, value is a vector containing all of their connections to cosponsors
};

