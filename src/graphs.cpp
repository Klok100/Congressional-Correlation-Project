#include "graphs.h"

#include <iostream>
#include <fstream>

using std::cout;
using std::endl;
using std::pair;

/* ANSI Color Guides */
//   std::string red = "\033[1;31m";
//   std::string green = "\033[1;32m";
//   std::string end_color = "\033[0m";

bool Edge::operator==(const Edge& other) const {
    return sponsor_id == other.sponsor_id && cosponsor_id == other.cosponsor_id && weight == other.weight;
}

bool Edge::operator<(const Edge& other) const {
    return sponsor_id != other.sponsor_id ? sponsor_id < other.sponsor_id : cosponsor_id < other.cosponsor_id;
}

void CongressGraph::insertVertex(string sponsor_id) {
    if (vertexExists(sponsor_id)) {
        return;
    }

    adj_list.insert(pair<string, vector<Edge>>(sponsor_id, vector<Edge>()));
}

void CongressGraph::removeVertex(string sponsor_id) {
    if (!vertexExists(sponsor_id)) {
        cout << "Vertex does not exist, cannot delete" << endl;
        return;
    }

    //remove the key from the adj list, then remove any edges for which this Congress member is a cosponsor
    adj_list.erase(sponsor_id);
    for (auto it1 = adj_list.begin(); it1 != adj_list.end(); ++it1) {
        removeEdge(it1->first, sponsor_id);
    }
}

vector<string> CongressGraph::getVertices() {
    vector<string> to_return;

    for (auto it1 = adj_list.begin(); it1 != adj_list.end(); ++it1) {
        to_return.push_back(it1->first);
    }

    return to_return;
}

void CongressGraph::insertEdge(string sponsor_id, string cosponsor_id) {
    if (!vertexExists(sponsor_id)) {
        cout << "Sponsor does not exist, cannot insert edge" << endl;
        return;
    }

    //if cosponsor does not yet exist, add them to the adj list
    if (!vertexExists(cosponsor_id)) {
        insertVertex(cosponsor_id);
    }

    //iterate through the sponsor's vector of connections to see if they already have a connection with the cosponsor
    for (auto it = adj_list.at(sponsor_id).begin(); it != adj_list.at(sponsor_id).end(); ++it) {
        if (it->cosponsor_id == cosponsor_id) {
            ++it->weight;
            return;
        }
    }

    //if no connection found, insert a new connection at the front of the vector
    adj_list.at(sponsor_id).insert(adj_list.at(sponsor_id).begin(), Edge(sponsor_id, cosponsor_id));
}

void CongressGraph::removeEdge(string sponsor_id, string cosponsor_id) {
    if (!vertexExists(sponsor_id)) {
        cout << "Sponsor does not exist, cannot remove edge" << endl;
        return;
    }

    //iterate through the sponsor's list of connections to find and delete the cosponsor, if it exists
    for (auto it = adj_list.at(sponsor_id).begin(); it != adj_list.at(sponsor_id).end(); ++it) {
        if (it->cosponsor_id == cosponsor_id) {
            adj_list.at(sponsor_id).erase(it);
            return;
        }
    }
}

vector<Edge> CongressGraph::incidentEdges(string sponsor_id) {
    if (!vertexExists(sponsor_id)) {
        cout << "Vertex does not exist, cannot return incident edges" << endl;
        return vector<Edge>();
    }
    
    return adj_list.at(sponsor_id);
}

bool CongressGraph::vertexExists(string sponsor_id) {
    return adj_list.count(sponsor_id) != 0;
}

void CongressGraph::importData(string filename) {
    std::ifstream ifsCount(filename);
    if (!ifsCount.is_open()) {
        cout << "File does not exist, cannot import" << endl;
        return;
    }

    int num_lines = 0;
    string line = "";
    if (ifsCount.is_open()) {
        while (ifsCount.peek() != EOF) {
            getline(ifsCount, line);
            num_lines++;
        }
    }
    
    std::ifstream ifs(filename);
    if (!ifs.is_open()) {
        cout << "File does not exist, cannot import" << endl;
        return;
    }

    int line_count = 0;
    while (std::getline(ifs, line)) {
        line_count++;
        //cout << line_count << "\n";
        double percentage = (100 * line_count) / num_lines;
        int line_divider = num_lines / 20;

        if ((line_count == 1) || (line_count % line_divider == 0)) {
            system("clear");
            cout << "   Importing Data" << endl;
            cout << "    " << percentage << "% complete" << endl;
            for (int i = 0; i < percentage / 5; i++) {
                std::cout << "\033[1;32m" << "=" << "\033[0m";
            }
            for (int i = percentage / 5; i < 20; i++) {
                std::cout << "\033[1;31m" << "=" << "\033[0m";
            }
            std::cout << std::endl;
        } 

        if (line_count == num_lines) {
            system("clear");
            cout << "   Importing Data" << endl;
            cout << "    " << 100 << "% complete" << endl;
            for (int i = 0; i < 20; i++) {
                std::cout << "\033[1;32m" << "=" << "\033[0m";
            }
            std::cout << std::endl;
        }
        string key;
        vector<string> cosponsors;
        bool passed_first = false;
        string this_member = "";
        for (auto &ch : line) {
            if (ch == ',') {
                if (!passed_first) {
                    key = this_member;
                    insertVertex(key);
                    passed_first = true;
                } else {
                    insertEdge(key, this_member);
                }
                this_member = "";
                continue;
            }
            this_member.push_back(ch);
        }
    }
}

// This function only exists for testing purposes only
void CongressGraph::importDataTest(string filename) {
    std::ifstream ifs(filename);
    if (!ifs.is_open()) {
        cout << "File does not exist, cannot import" << endl;
        return;
    }
    string line = "";
    while (std::getline(ifs, line)) {
        string key;
        vector<string> cosponsors;
        bool passed_first = false;
        string this_member = "";
        for (auto &ch : line) {
            if (ch == ',') {
                if (!passed_first) {
                    key = this_member;
                    insertVertex(key);
                    passed_first = true;
                } else {
                    insertEdge(key, this_member);
                }
                this_member = "";
                continue;
            }
            this_member.push_back(ch);
        }
    }
}

// This function only exists for testing purposes only
void CongressGraph::insertWeightedEdge(string sponsor_id, string cosponsor_id, int weight) {
    if (!vertexExists(sponsor_id)) {
        cout << "Sponsor does not exist, cannot insert edge" << endl;
        return;
    }

    //if cosponsor does not yet exist, add them to the adj list
    if (!vertexExists(cosponsor_id)) {
        insertVertex(cosponsor_id);
    }

    //insert a new weighted connection at the front of the vector
    adj_list.at(sponsor_id).insert(adj_list.at(sponsor_id).begin(), Edge(sponsor_id, cosponsor_id, weight));
}
   
