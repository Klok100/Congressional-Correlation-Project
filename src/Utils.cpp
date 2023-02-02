#include "Utils.h"

#include "graphs.h"

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

using std::string;
using std::vector;
using std::cout;
using std::fstream;
using std::stringstream;
using std::ios;

string bio_To_Name(string bio_id) {
    vector<string> row;
    string line, word;
    fstream file ("bill_sponsors/nameToBioGuideID.csv", ios::in);
    if (file.is_open()) {
        while (getline(file, line)) {
            row.clear();
            line.insert(line.length() - 1, ",");
            stringstream str(line);

            while (getline(str, word, ',')) {
                row.push_back(word);
            }
            row[0] = row[0] + "," + row[1];
            row[1] = row[2];

            if (row[1] == bio_id) {
                string output = "\nThe name corresponding to the BioGuide ID " + bio_id + " is " + row[0] + "\n";
                return output;
            }
        }
    }
    return "\nLegislator not found\n";  
}

string name_To_Bio(string name) {
    vector<string> row;
    vector<string> subsection;
    string line, word;
    fstream file ("bill_sponsors/nameToBioGuideID.csv", ios::in);
    if (file.is_open()) {
        while (getline(file, line)) {
            row.clear();
            stringstream str(line);
            while (getline(str, word, ' ')) {
                row.push_back(word);
            }

            row[0] = row[0].substr(1);
            row[0] = row[0] + " " + row[1];            

            if (row[2][0] != '(') {
                row[0] = row[0] + " " + row[2];
            }

            stringstream str2(row[row.size() - 1]);
            while (getline(str2, word, ',')) {
                subsection.push_back(word);
            }

            string bio_id = subsection[subsection.size() - 1];
            bio_id = bio_id.substr(0,bio_id.length() - 1);

            if (row[0] == name) {
                string output = "\nThe BioGuide ID corresponding to the name " + name + " is " + bio_id + "\n";
                return output;
            }
        }
    }
    return "\nLegislator not found\n"; 
}

int numConnections(CongressGraph g, string legislator) { 
    if (!g.vertexExists(legislator)) {
        cout << "Legislator " << legislator << " does not exist\n";
        return -1;
    }
    vector<Edge> edges = g.incidentEdges(legislator);
    int numConnections = 0;
    for (Edge currEdge : edges) {
        numConnections++;
    }
    return numConnections;
}

int numBillsSponsoredTogether(CongressGraph g, string legislator1, string legislator2) {
    if (!g.vertexExists(legislator1) || !g.vertexExists(legislator2)) {
        cout << "One or more legislators do not exist\n";
        return -1;
    }

    vector<Edge> edges = g.incidentEdges(legislator1);
    unsigned int index;
    unsigned int totalWeight = 0;
    for (index = 0; index < edges.size(); index++) {
        if (edges[index].cosponsor_id == legislator2) {
            break;
        }
    }
    if (edges.size() != 0 && index != edges.size()) {
        Edge foundEdge = edges[index];
        totalWeight += foundEdge.weight;
    }
    
    edges = g.incidentEdges(legislator2);
    for (index = 0; index < edges.size(); index++) {
        if (edges[index].cosponsor_id == legislator1) {
            break;
        }
    }
    if (edges.size() != 0 && index != edges.size()) {
        Edge foundEdge = edges[index];
        totalWeight += foundEdge.weight;
    }

    return totalWeight;
}

bool printLegislatorValidation(CongressGraph g, string legislator) {
    if (!g.vertexExists(legislator)) {
        cout << "Legislator " << legislator << " does not exist\n";
        return false;
    } else {
        return true;
    }
}

void promptHome() {
    string choice;
    std::cout << std::endl << "Enter any key to return to homescreen" << std::endl;
    std::getline(std::cin, choice);  
}