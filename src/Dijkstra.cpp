#include "Dijkstra.h"

#include <iostream>
#include <map>
#include <limits>
#include <string>
#include <queue>
#include <tuple>
#include <algorithm>

using std::cout;
using std::map;
using std::string;
using std::priority_queue;
using std::tuple;
using std::get;
using std::reverse;

tuple<map<string, double>, map<string, int>, map<string, string>> Dijkstra::getDistancePaths(CongressGraph g, string start) {
    tuple<map<string, double>, map<string, int>, map<string, string>> dist_connected_path;
    map<string, double> dist;
    map<string, int> connect_rating;
    map<string, string> prev;
    
    vector<string> vertices = g.getVertices();

    for (string vertex : vertices) {
        dist[vertex] = std::numeric_limits<double>::max();
        connect_rating[vertex] = std::numeric_limits<int>::max();
        prev[vertex] = "NULL";
    }
    dist[start] = 0;
    connect_rating[start] = 0;

    priority_queue<string> p_queue;
    p_queue.push(start);

    while (!p_queue.empty()) {
        string curr_vertex = p_queue.top();
        p_queue.pop();
        double curr_dist = dist[curr_vertex];
        int curr_connected = connect_rating[curr_vertex];
        
        vector<Edge> neighbors = g.incidentEdges(curr_vertex);
        for (Edge edge : neighbors) {
            string co_sponsor = edge.cosponsor_id;
            double weight = edge.weight;
            double co_dist = dist[co_sponsor];
            double distance = curr_dist + 1/weight;
            int connectivity = curr_connected + weight;

            if (distance < co_dist) {
                dist[co_sponsor] = distance;
                connect_rating[co_sponsor] = connectivity;
                prev[co_sponsor] = curr_vertex;
                p_queue.push(co_sponsor);
            }
        }
    }
  
    dist_connected_path = make_tuple(dist, connect_rating, prev);
    return dist_connected_path;
}

vector<string> Dijkstra::findShortestPath(CongressGraph g, string start, string end) {
    vector<string> path;
    if (!g.vertexExists(start)) {
        return path;
    }
    if (!g.vertexExists(end)) {
        return path; 
    }

    if (start == end) {
        path.push_back(start);
        return path;
    }

    tuple<map<string, double>, map<string, int>, map<string, string>> dist_connected_path = getDistancePaths(g, start);
    map<string, string> paths = get<2>(dist_connected_path);

    path.push_back(end);
    string next = end;
    while(next != "NULL") {
        next = paths[next];
        if (next == "NULL") {
            break;
        }
        path.push_back(next);
    }
    reverse(path.begin(), path.end());

    if (path[0] == end) {
        vector<string> empty;
        return empty;
    }

    return path;
} 

int Dijkstra::getConnectivityRating(CongressGraph g, string start, string end) {
    if (!g.vertexExists(start)) {
        return -2;
    }
    if (!g.vertexExists(end)) {
        return -2;
    }
    
    if (start == end) {
        return 0;
    }

    int connectivity;
    tuple<map<string, double>, map<string, int>, map<string, string>> dist_connected_path = getDistancePaths(g, start);
    map<string, int> connect_rating = get<1>(dist_connected_path);
    connectivity = connect_rating[end];

    if (connectivity == std::numeric_limits<int>::max()) {
        return -1;
    }

    return connectivity;
}