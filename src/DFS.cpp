#include "DFS.h"

#include <iostream>
#include <stack>

using std::pair;
using std::cout;
using std::endl;
using std::stack;

DFS::DFS(CongressGraph g) {
    for (string vertex : g.getVertices()) {
        if (visitedVertices.count(vertex) == 0) {
            traverse(g, vertex);
            cout << "Retraversing\n";
        }
    }
    cout << "Finished traversing through " << g.getVertices().size() << " different legislators, Found " << numDiscoveryEdges << " discovery edges" << endl;
}
        
void DFS::traverse(CongressGraph g, string startingVertex) {
    if (!g.vertexExists(startingVertex)) {
        cout << "vertex " + startingVertex + " does not exist, cannot traverse" << endl;
        return;
    }

    stack<string> verticesToTraverse;
    verticesToTraverse.push(startingVertex);
    visitedVertices.insert(pair<string, bool>(startingVertex, true));

    while (!verticesToTraverse.empty()) {
        string currVertex = verticesToTraverse.top();
        verticesToTraverse.pop();
        
        for (Edge e : g.incidentEdges(currVertex)) {
            if (!isVertexVisited(e.cosponsor_id)) {
                visitedEdges.insert(pair<Edge, DFS::EdgeStatus>(e, DFS::EdgeStatus::DISCOVERY));
                visitedVertices.insert(pair<string, bool>(e.cosponsor_id, true));
                numDiscoveryEdges++;
                if (numDiscoveryEdges % 100 == 0) {
                    cout << "Discovery edges traversed: " << numDiscoveryEdges << endl;
                }
                verticesToTraverse.push(e.cosponsor_id);
            } else if (visitedEdges.count(e) == 0) {
                visitedEdges.insert(pair<Edge, DFS::EdgeStatus>(e, DFS::EdgeStatus::BACK));
            }
        }
    }
    
}

bool DFS::isVertexVisited(string vertex) {
    return visitedVertices.count(vertex) != 0;
}

DFS::EdgeStatus DFS::getEdgeStatus(Edge e) {
    if (visitedEdges.count(e) == 0) {
        return DFS::EdgeStatus::UNEXPLORED;
    }
    return visitedEdges.at(e);
}