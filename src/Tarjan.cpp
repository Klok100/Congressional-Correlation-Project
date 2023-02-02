#include "Tarjan.h"
#include "graphs.h"

#include <iostream>
#include <list>
#include <stack>
#include <map>
#include <unordered_map>
#include <utility>
#define NIL -1

using std::map;
using std::pair;
using std::stack;
using std::list;
using std::vector;
using std::cout;
using std::endl;

Tarjan::Tarjan(CongressGraph g) {
    data = g.getVertices();

    V = data.size();

    vector<Edge> edges;
    
    for (std::string m : data) {
        vector<Edge> edg = g.incidentEdges(m);
        for (Edge o : edg) {
            edges.push_back(o);
        }
    }

    for (Edge p : edges) {
        if ( adj.find(p.sponsor_id) == adj.end() ) {
            adj.insert(std::pair<std::string, std::vector<std::string>>(p.sponsor_id, std::vector<std::string>{p.cosponsor_id}));
        } else {
            std::vector<std::string> store_ = adj[p.sponsor_id];
            bool found = false;
            for (unsigned i = 0; i < store_.size(); i++) {
                if (store_[i] == p.cosponsor_id) {
                    found = true;
                    break;
                }
            }
            adj[p.sponsor_id].push_back(p.cosponsor_id);
        }
    }
}

Tarjan::Tarjan(CongressGraph g, int threshold) {
    data = g.getVertices();

    V = data.size();

    vector<Edge> edges;
    
    for (std::string m : data) {
        vector<Edge> edg = g.incidentEdges(m);
        for (Edge o : edg) {
            if (o.weight >= threshold) {
                edges.push_back(o);
            }
        }
    }

    for (Edge p : edges) {
        if ( adj.find(p.sponsor_id) == adj.end() ) {
            adj.insert(std::pair<std::string, std::vector<std::string>>(p.sponsor_id, std::vector<std::string>{p.cosponsor_id}));
        } else {
            std::vector<std::string> store_ = adj[p.sponsor_id];
            bool found = false;
            for (unsigned i = 0; i < store_.size(); i++) {
                if (store_[i] == p.cosponsor_id) {
                    found = true;
                    break;
                }
            }
            adj[p.sponsor_id].push_back(p.cosponsor_id);
        }
    }

}

/** A recursive function that finds and prints strongly connected components using DFS traversal
  *
  * @param u                The vertex to be visited next
  * @param disc             Stores discovery times of visited vertices
  * @param low              earliest visited vertex (the vertex with minimum
  *                         discovery time) that can be reached from subtree
  *                         rooted with current vertex
  * @param st               To store all the connected ancestors (could be part
  *                         of SCC)
  * @param stackMember      bit/index map for faster check whether
  *                         a node is in stack
  */

void Tarjan::SCCUtil(std::string u, map<std::string, int> * disc, map<std::string, int> * low, stack<std::string> *st, map<std::string, bool> * stackMember)
{
    // A static variable is used for simplicity, we can avoid use
    // of static variable by passing a pointer.
    static int time = 0;
 
    // Initialize discovery time and low value
    disc->at(u) = low->at(u) = ++time;
    st->push(u);
    stackMember->at(u) = true;

    // Go through all vertices adjacent to this
    for (unsigned i = 0; i < adj[u].size(); i++)
    {
        std::string v = adj[u][i]; // v is current adjacent of 'u'
 
        // If v is not visited yet, then recur for it
        if (disc->at(v) == -1)
        {
            SCCUtil(v, disc, low, st, stackMember);
 
            // Check if the subtree rooted with 'v' has a
            // connection to one of the ancestors of 'u'
            low->at(u) = std::min(low->at(u), low->at(v));
        }
 
        // Update low value of 'u' only of 'v' is still in stack
        // (i.e. it's a back edge, not cross edge).
        else if (stackMember->at(v) == true)
        {
            low->at(u) = std::min(low->at(u), disc->at(v));
        }
    }
    // head node found, pop the stack and print an SCC
    std::string w = ""; // To store stack extracted vertices
    if (low->at(u) == disc->at(u))
    {
        vector<std::string> this_scc;
        while (st->top() != u)
        {
            w = st->top();
            this_scc.push_back(w);
            stackMember->at(w) = false;
            st->pop();
        }
        w = st->top();
        this_scc.push_back(w);
        stackMember->at(w) = false;
        st->pop();
        scc_.push_back(this_scc);
    }
}

// The function to do DFS traversal. It uses SCCUtil()
void Tarjan::SCC()
{
    map<std::string, int> *disc = new map<std::string, int>();
    map<std::string, int> *low = new map<std::string, int>();
    map<std::string, bool> *stackMember = new map<std::string, bool>();
    stack<std::string> *st = new stack<std::string>();
 
    // Initialize disc and low, and stackMember map
    for (unsigned v = 0; v < data.size(); v++)
    {
        // cout << "inserting nil values for " << data[v] << endl;
        disc->insert(std::pair<std::string, int>(data[v], NIL));
        low->insert(std::pair<std::string, int>(data[v], NIL));
        stackMember->insert(std::pair<std::string, bool>(data[v], false));
    }
 
    // Call the recursive helper function to find strongly
    // connected components in DFS tree with vertex 'i'
    for (unsigned i = 0; i < data.size(); i++)
    {
        if (disc->at(data[i]) == NIL) {
            // cout << "calling SCCUtil on " << data[i] << endl;
            SCCUtil(data[i], disc, low, st, stackMember);
        }
    }
    delete disc;
    delete low;
    delete stackMember;
    delete st;

    // unordered_map to quickly be able to find senator's scc
    for (unsigned i = 0; i < scc_.size(); i++) {
        for (unsigned j = 0; j < scc_[i].size(); j++) {
            string curr_senator = scc_[i][j];
            if (sen_SCC.find(curr_senator) == sen_SCC.end()) {
                std::pair<std::string, vector<std::string>> this_pair;
                this_pair = std::make_pair(curr_senator, scc_[i]);
                sen_SCC.insert (this_pair);
            }
        }
    }
}

vector<vector<std::string>> Tarjan::getSCC() {
    return scc_;
}

vector<std::string> Tarjan::getSCCbySenator(std::string senator) {
    return sen_SCC[senator];
}  