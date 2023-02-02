#include "../catch/catch.hpp"
#include "../includes/graphs.h"
#include "../includes/DFS.h"
#include "../includes/Dijkstra.h"
#include "../includes/Tarjan.h"
#include "../includes/Utils.h"

#include <string>
#include <vector>
#include <iostream>
#include <map>

using std::string;
using std::vector;
using std::cout;
using std::endl;
using std::map;
using std::pair;

void compareEdges(vector<Edge> edges, vector<Edge> soln) {
    REQUIRE(edges.size() == soln.size());

    for (size_t idx = 0; idx < edges.size(); ++idx) {
        REQUIRE(edges.at(idx) == soln.at(idx));
    }
}

void checkAllVertices(CongressGraph g, DFS d) {
    for (string vertex : g.getVertices()) {
        REQUIRE(d.isVertexVisited(vertex));
    }
}

// =============================================== //
// --------------- TEST CASE BASIC --------------- //
// =============================================== //

TEST_CASE("add/remove single edge", "[Basic]") {
    CongressGraph g;
    g.insertVertex("a");
    g.insertVertex("b");
    g.insertEdge("a", "b");
    vector<Edge> edges = g.incidentEdges("a");
    vector<Edge> soln_edges;
    soln_edges.push_back(Edge("a", "b"));
    compareEdges(edges, soln_edges);
    g.removeEdge("a", "b");
    vector<Edge> edges2 = g.incidentEdges("a");
    vector<Edge> soln_edges2 = {};
    compareEdges(edges2, soln_edges2);
}

TEST_CASE("add double edge", "[Basic]") {
    CongressGraph g;
    g.insertVertex("a");
    g.insertVertex("b");
    g.insertEdge("a", "b");
    g.insertEdge("a", "b");
    vector<Edge> edges = g.incidentEdges("a");
    vector<Edge> soln_edges;
    Edge e("a", "b");
    ++e.weight;
    soln_edges.push_back(e);
    compareEdges(edges, soln_edges);
}

TEST_CASE("remove vertex", "[Basic]") {
    CongressGraph g;
    g.insertVertex("a");
    g.insertVertex("b");
    g.insertVertex("c");
    g.insertEdge("a", "b");
    g.insertEdge("a", "c");
    vector<Edge> edges = g.incidentEdges("a");
    vector<Edge> soln_edges;
    soln_edges.push_back(Edge("a", "c"));
    soln_edges.push_back(Edge("a", "b"));
    compareEdges(edges, soln_edges);
    g.removeVertex("c");
    vector<Edge> soln_edges2;
    soln_edges2.push_back(Edge("a", "b"));
    edges = g.incidentEdges("a");
    compareEdges(edges, soln_edges2);
}

TEST_CASE("import data", "[Basic]") {
    CongressGraph g;
    g.importDataTest("tests/testGraph1.csv");
    vector<Edge> edges = g.incidentEdges("a");
    vector<Edge> soln_edges;
    soln_edges.push_back(Edge("a", "c"));
    soln_edges.push_back(Edge("a", "b"));
    compareEdges(edges, soln_edges);
    vector<Edge> edges_b = g.incidentEdges("b");
    vector<Edge> soln_edges_b;
    soln_edges_b.push_back(Edge("b", "c"));
    compareEdges(edges_b, soln_edges_b);
    vector<Edge> edges_c = g.incidentEdges("c");
    vector<Edge> soln_edges_c;
    compareEdges(edges_c, soln_edges_c);
}

TEST_CASE("check sample of bill sponsors for correct weights", "[Basic]") {
    CongressGraph g;
    g.importDataTest("tests/billSponsorsSample.csv");
    vector<Edge> edges = g.incidentEdges("C000640");
    vector<Edge> soln_edges;
    soln_edges.push_back(Edge("C000640", "A000358"));
    soln_edges.push_back(Edge("C000640", "O000164"));
    Edge e("C000640", "B001135");
    ++e.weight;
    soln_edges.push_back(e);
    compareEdges(edges, soln_edges);
}

// ============================================= //
// --------------- TEST CASE DFS --------------- //
// ============================================= //

TEST_CASE("DFS simple", "[DFS]") {
    CongressGraph g;
    g.insertVertex("a");
    g.insertVertex("b");
    g.insertEdge("a", "b");
    DFS d(g);
    checkAllVertices(g, d);
    REQUIRE(d.getEdgeStatus(Edge("a", "b")) == DFS::EdgeStatus::DISCOVERY);
}


TEST_CASE("DFS discovery vs. back", "[DFS]") {
    CongressGraph g;
    g.importDataTest("tests/DFSdiscoveryBack.csv");
    
    DFS d(g);
    checkAllVertices(g, d);
    REQUIRE(d.getEdgeStatus(Edge("a", "b")) == DFS::EdgeStatus::DISCOVERY);
    REQUIRE(d.getEdgeStatus(Edge("b", "c")) == DFS::EdgeStatus::BACK);
    REQUIRE(d.getEdgeStatus(Edge("a", "c")) == DFS::EdgeStatus::DISCOVERY);
    REQUIRE(d.getEdgeStatus(Edge("c", "a")) == DFS::EdgeStatus::BACK);
}


TEST_CASE("DFS multiple components", "[DFS]") {
    CongressGraph g;
    g.importDataTest("tests/DFSMultipleComponents.csv");
    
    DFS d(g);
    checkAllVertices(g, d);
    REQUIRE(d.getEdgeStatus(Edge("a", "b")) == DFS::EdgeStatus::DISCOVERY);
    REQUIRE(d.getEdgeStatus(Edge("b", "a")) == DFS::EdgeStatus::BACK);
    REQUIRE(d.getEdgeStatus(Edge("c", "d")) == DFS::EdgeStatus::DISCOVERY);
    REQUIRE(d.getEdgeStatus(Edge("d", "c")) == DFS::EdgeStatus::BACK);
}


TEST_CASE("DFS bill sponsors sample", "[DFS]") {
    CongressGraph g;
    g.importDataTest("tests/billSponsorsSample.csv");

    DFS d(g);
    checkAllVertices(g, d);
    REQUIRE(d.getEdgeStatus(Edge("B000013", "R000575")) == DFS::EdgeStatus::DISCOVERY);
}


// ================================================== //
// --------------- TEST CASE DIJKSTRA --------------- //
// ================================================== //

TEST_CASE("Dijkstra Self Check", "[Dijkstra]") {
    CongressGraph g;
    g.insertVertex("A");

    Dijkstra d;
    vector<string> path = d.findShortestPath(g, "A", "A");
    int connectivity = d.getConnectivityRating(g, "A", "A");
    vector<string> soln_path = {"A"};
    int soln_connectivity = 0;
    REQUIRE(path == soln_path);
    REQUIRE(connectivity == soln_connectivity);
}

/**  Graph Visual
  *
  *  A -----> B -----> C  
  * 
  */
TEST_CASE("Dijkstra Simple", "[Dijkstra]") {
    CongressGraph g;
    g.insertVertex("A");
    g.insertVertex("B");
    g.insertVertex("C");

    g.insertEdge("A", "B");
    g.insertEdge("B", "C");

    Dijkstra d;
    vector<string> path = d.findShortestPath(g, "A", "C");
    int connectivity = d.getConnectivityRating(g, "A", "C");
    vector<string> soln_path = {"A", "B", "C"};
    int soln_connectivity = 2;
    REQUIRE(path == soln_path);
    REQUIRE(connectivity == soln_connectivity);

}

/**  Graph Visual
  *
  *  A -----> B 
  *  |        |
  *  |        |
  *  |        |
  *  V        V
  *  D <----- C 
  * 
  */
TEST_CASE("Dijkstra Medium", "[Dijkstra]") {
    CongressGraph g;
    g.insertVertex("A");
    g.insertVertex("B");
    g.insertVertex("C");
    g.insertVertex("D");  

    g.insertWeightedEdge("A", "B", 5);
    g.insertWeightedEdge("B", "C", 1);
    g.insertWeightedEdge("C", "D", 1);
    g.insertWeightedEdge("A", "D", 11);

    Dijkstra d;

    vector<string> path = d.findShortestPath(g, "A", "D");
    int connectivity = d.getConnectivityRating(g, "A", "D");
    vector<string> soln_path = {"A", "D"};
    int soln_connectivity = 11;
    REQUIRE(path == soln_path);
    REQUIRE(connectivity == soln_connectivity);    
}

/**  Graph Visual (From Lecture 33, Same Weights and Edges)
  * 
  *  A -----> B -----> C
  *  |^\      /   ---^ |
  *  |  \    /   /     |
  *  |   D <-   /      |
  *  V         /       V
  *  F -----> E <----- H
  *   \     --^        |
  *    \   /           |
  *     V /            |
  *     G <------------/
  * 
  */
TEST_CASE("Dijkstra Hard", "[Dijkstra]") {
    CongressGraph g;
    g.insertVertex("A");
    g.insertVertex("B");
    g.insertVertex("C");
    g.insertVertex("D");
    g.insertVertex("E");
    g.insertVertex("F");
    g.insertVertex("G");
    g.insertVertex("H");

    g.insertWeightedEdge("D", "A", 3);
    g.insertWeightedEdge("A", "B", 10);
    g.insertWeightedEdge("B", "C", 7);
    g.insertWeightedEdge("E", "C", 6);
    g.insertWeightedEdge("B", "D", 5);
    g.insertWeightedEdge("G", "E", 2);
    g.insertWeightedEdge("F", "E", 5);
    g.insertWeightedEdge("H", "E", 3);
    g.insertWeightedEdge("A", "F", 7);
    g.insertWeightedEdge("H", "G", 5);
    g.insertWeightedEdge("F", "G", 4);
    g.insertWeightedEdge("C", "H", 4);

    Dijkstra d;

    vector<string> path = d.findShortestPath(g, "A", "B");
    int connectivity = d.getConnectivityRating(g, "A", "B");
    vector<string> soln_path = {"A", "B"};
    int soln_connectivity = 10;
    REQUIRE(path == soln_path);
    REQUIRE(connectivity == soln_connectivity);

    path = d.findShortestPath(g, "A", "C");
    connectivity = d.getConnectivityRating(g, "A", "C");
    soln_path = {"A", "B", "C"};
    soln_connectivity = 17;
    REQUIRE(path == soln_path);
    REQUIRE(connectivity == soln_connectivity); 

    path = d.findShortestPath(g, "A", "D");
    connectivity = d.getConnectivityRating(g, "A", "D");
    soln_path = {"A", "B", "D"};
    soln_connectivity = 15;
    REQUIRE(path == soln_path);
    REQUIRE(connectivity == soln_connectivity);   

    path = d.findShortestPath(g, "A", "E");
    connectivity = d.getConnectivityRating(g, "A", "E");
    soln_path = {"A", "F", "E"};
    soln_connectivity = 12;
    REQUIRE(path == soln_path);
    REQUIRE(connectivity == soln_connectivity);  

    path = d.findShortestPath(g, "A", "F");
    connectivity = d.getConnectivityRating(g, "A", "F");
    soln_path = {"A", "F"};
    soln_connectivity = 7;
    REQUIRE(path == soln_path);
    REQUIRE(connectivity == soln_connectivity);    

    path = d.findShortestPath(g, "A", "G");
    connectivity = d.getConnectivityRating(g, "A", "G");
    soln_path = {"A", "F", "G"};
    soln_connectivity = 11;
    REQUIRE(path == soln_path);
    REQUIRE(connectivity == soln_connectivity);         

    path = d.findShortestPath(g, "A", "H");
    connectivity = d.getConnectivityRating(g, "A", "H");
    soln_path = {"A", "B", "C", "H"};
    soln_connectivity = 21;
    REQUIRE(path == soln_path);
    REQUIRE(connectivity == soln_connectivity);  
}

/**  Graph Visual
  *
  *  A -----> B        C  
  * 
  */
TEST_CASE("Dijkstra Disconnnected Simple", "[Dijkstra]") {
    CongressGraph g;
    g.insertVertex("A");
    g.insertVertex("B");
    g.insertVertex("C");

    g.insertEdge("A", "B");

    Dijkstra d;
    vector<string> path = d.findShortestPath(g, "A", "C");
    int connectivity = d.getConnectivityRating(g, "A", "C");
    vector<string> soln_path = {};
    int soln_connectivity = -1;
    REQUIRE(path == soln_path);
    REQUIRE(connectivity == soln_connectivity);    
}

/**  Graph Visual (From Lecture 33, Same Weights and Edges)
  * 
  *  A -----> B -----> C
  *  |^\      /   ---^ |
  *  |  \    /   /     |
  *  |   D <-   /      |
  *  V         /       V
  *  F -----> E <----- H
  *           ^        
  *           |         
  *           |         
  *           G 
  * 
  */
TEST_CASE("Dijkstra Disconnected Medium", "[Dijkstra]") {
    CongressGraph g;
    g.insertVertex("A");
    g.insertVertex("B");
    g.insertVertex("C");
    g.insertVertex("D");
    g.insertVertex("E");
    g.insertVertex("F");
    g.insertVertex("G");
    g.insertVertex("H");

    g.insertWeightedEdge("D", "A", 3);
    g.insertWeightedEdge("A", "B", 10);
    g.insertWeightedEdge("B", "C", 7);
    g.insertWeightedEdge("E", "C", 6);
    g.insertWeightedEdge("B", "D", 5);
    g.insertWeightedEdge("G", "E", 2);
    g.insertWeightedEdge("F", "E", 5);
    g.insertWeightedEdge("H", "E", 3);
    g.insertWeightedEdge("A", "F", 7);
    g.insertWeightedEdge("C", "H", 4);

    Dijkstra d;

    vector<string> path = d.findShortestPath(g, "A", "G");
    int connectivity = d.getConnectivityRating(g, "A", "G");
    vector<string> soln_path = {};
    int soln_connectivity = -1;
    REQUIRE(path == soln_path);
    REQUIRE(connectivity == soln_connectivity); 
}

// ================================================ //
// --------------- TEST CASE TARJAN --------------- //
// ================================================ // 

TEST_CASE("Tarjan simple 1", "[Tarjan]") {
    CongressGraph g;
    g.insertVertex("a");
    g.insertVertex("b");
    g.insertVertex("c");
    g.insertVertex("d");
    g.insertVertex("e");
    g.insertEdge("a", "b");
    g.insertEdge("b", "c");
    g.insertEdge("c", "d");
    g.insertEdge("c", "e");
    g.insertEdge("d", "a");
    g.insertEdge("e", "a");

    Tarjan test(g);
    test.SCC();

    vector<vector<string>> soln_scc = {{"d", "e", "c", "b", "a"}};
    vector<vector<string>> actual_scc = test.getSCC();
    REQUIRE(actual_scc == soln_scc);

    CongressGraph h;
    h.importDataTest("tests/TarjanTests/testTJ_1.csv");

    Tarjan test_1(h);
    test_1.SCC();

    REQUIRE(test_1.getSCC() == soln_scc);
}

TEST_CASE("Tarjan simple 2", "[Tarjan]") {
    CongressGraph g;
    g.importDataTest("tests/TarjanTests/testTJ_2.csv");

    Tarjan test(g);
    test.SCC();

    vector<vector<string>> soln_scc = {{{"8", "9"}, {"7"}, {"5", "4", "6"}, {"1", "2", "3", "0"}}};
    vector<vector<string>> actual_scc = test.getSCC();
    REQUIRE(actual_scc == soln_scc);
}

TEST_CASE("Tarjan simple 3", "[Tarjan]") {
    CongressGraph g;
    g.importDataTest("tests/TarjanTests/testTJ_3.csv");

    Tarjan test(g);
    test.SCC();

    vector<vector<string>> soln_scc = {{{"6"}, {"5"}, {"4"}, {"3"}, {"2", "1", "0"}}};
    vector<vector<string>> actual_scc = test.getSCC();
    REQUIRE(actual_scc == soln_scc);

    vector<std::string> a = test.getSCCbySenator("6");
    vector<std::string> test_a = {"6"};
    REQUIRE(a == test_a);
    vector<std::string> b = test.getSCCbySenator("5");
    vector<std::string> test_b = {"5"};
    REQUIRE(b == test_b);
    vector<std::string> c = test.getSCCbySenator("4");
    vector<std::string> test_c = {"4"};
    REQUIRE(c == test_c);
    vector<std::string> d = test.getSCCbySenator("3");
    vector<std::string> test_d = {"3"};
    REQUIRE(d == test_d);
    vector<std::string> e = test.getSCCbySenator("2");
    vector<std::string> test_e = {"2", "1", "0"};
    REQUIRE(e == test_e);
    vector<std::string> f = test.getSCCbySenator("1");
    REQUIRE(f == test_e);
    vector<std::string> h = test.getSCCbySenator("0");
    REQUIRE(h == test_e);
}

TEST_CASE("Tarjan threshold 1", "[Tarjan]") {
    CongressGraph g;
    g.importDataTest("tests/TarjanTests/testTJT_1.csv");

    Tarjan test(g);
    test.SCC();
    vector<vector<string>> soln_scc = {{"c", "d", "b", "a"}};
    vector<vector<string>> actual_scc = test.getSCC();
    REQUIRE(actual_scc == soln_scc);

    Tarjan test2(g, 2);
    test2.SCC();
    vector<vector<string>> soln_scc2 = {{"c", "b", "a"}, {"d"}};
    vector<vector<string>> actual_scc2 = test2.getSCC();
    REQUIRE(actual_scc2 == soln_scc2);
}

// ========================================================= //
// --------------- TEST CASE NUM CONNECTIONS --------------- //
// ========================================================= //

TEST_CASE("Num Connections 1", "[Num Connections]") {
    CongressGraph g;
    g.insertVertex("A");
    g.insertVertex("B");
    g.insertVertex("C");

    g.insertEdge("A", "B");
    g.insertEdge("B", "C");

    int numConnections1 = numConnections(g, "A");
    int numConnections2 = numConnections(g, "B");

    REQUIRE(numConnections1 == 1);
    REQUIRE(numConnections2 == 1);
}

TEST_CASE("Num Connections 2", "[Num Connections]") {
    CongressGraph g;
    g.insertVertex("A");
    g.insertVertex("B");
    g.insertVertex("C");
    g.insertVertex("D");
    g.insertVertex("E");
    g.insertVertex("F");
    g.insertVertex("G");
    g.insertVertex("H");

    g.insertWeightedEdge("D", "A", 3);
    g.insertWeightedEdge("A", "B", 10);
    g.insertWeightedEdge("B", "C", 7);
    g.insertWeightedEdge("E", "C", 6);
    g.insertWeightedEdge("B", "D", 5);
    g.insertWeightedEdge("G", "E", 2);
    g.insertWeightedEdge("F", "E", 5);
    g.insertWeightedEdge("H", "E", 3);
    g.insertWeightedEdge("A", "F", 7);
    g.insertWeightedEdge("H", "G", 5);
    g.insertWeightedEdge("F", "G", 4);
    g.insertWeightedEdge("C", "H", 4);

    int numConnections1 = numConnections(g, "A");
    int numConnections2 = numConnections(g, "E");

    REQUIRE(numConnections1 == 2);
    REQUIRE(numConnections2 == 1);       
}

// ============================================================ //
// --------------- TEST CASE SPONSORED TOGETHER --------------- //
// ============================================================ // 

TEST_CASE("Num Bills Sponsored Together 1", "[Sponsored Together]") {
    CongressGraph g;
    g.insertVertex("A");
    g.insertVertex("B");
    g.insertVertex("C");

    g.insertEdge("A", "B");
    g.insertEdge("B", "C");

    int numBills = numBillsSponsoredTogether(g, "A", "B");

    REQUIRE(numBills == 1);
}

TEST_CASE("Num Bills Sponsored Together 2", "[Sponsored Together]") {
    CongressGraph g;
    g.insertVertex("A");
    g.insertVertex("B");
    g.insertVertex("C");

    g.insertWeightedEdge("A", "B", 12);
    g.insertWeightedEdge("B", "C", 8);

    int numBills = numBillsSponsoredTogether(g, "A", "B");

    REQUIRE(numBills == 12);
}

TEST_CASE("Num Bills Sponsored Together 3", "[Sponsored Together]") {
    CongressGraph g;
    g.insertVertex("A");
    g.insertVertex("B");
    g.insertVertex("C");
    g.insertVertex("D");
    g.insertVertex("E");
    g.insertVertex("F");
    g.insertVertex("G");
    g.insertVertex("H");

    g.insertWeightedEdge("D", "A", 3);
    g.insertWeightedEdge("A", "B", 10);
    g.insertWeightedEdge("B", "C", 7);
    g.insertWeightedEdge("E", "C", 6);
    g.insertWeightedEdge("B", "D", 5);
    g.insertWeightedEdge("G", "E", 2);
    g.insertWeightedEdge("F", "E", 5);
    g.insertWeightedEdge("H", "E", 3);
    g.insertWeightedEdge("A", "F", 7);
    g.insertWeightedEdge("H", "G", 5);
    g.insertWeightedEdge("F", "G", 4);
    g.insertWeightedEdge("C", "H", 4);  

    int numBills1 = numBillsSponsoredTogether(g, "G", "E");
    int numBills2 = numBillsSponsoredTogether(g, "A", "C");

    REQUIRE(numBills1 == 2);
    REQUIRE(numBills2 == 0);
}

TEST_CASE("Num Bills Sponsored Together 4") {
    CongressGraph g;
    g.insertVertex("A");
    g.insertVertex("B");

    g.insertWeightedEdge("A", "B", 4);
    g.insertWeightedEdge("B", "A", 2);

    int numBills1 = numBillsSponsoredTogether(g, "A", "B");
    int numBills2 = numBillsSponsoredTogether(g, "B", "A");

    REQUIRE(numBills1 == 6);
    REQUIRE(numBills2 == 6);
}

// ========================================================== //
// --------------- TEST CASE BIO-NAME CONVERT --------------- //
// ========================================================== //

TEST_CASE("Bio_To_Name", "[Bio_Name Convert]") {
    string name1 = bio_To_Name("A000374");
    string soln_name1 = "\nThe name corresponding to the BioGuide ID A000374 is \"Abraham, Ralph Lee (Republican - Louisiana)\"\n";

    string name2 = bio_To_Name("A0000510");
    string soln_name2 = "\nLegislator not found\n";

    REQUIRE(name1 == soln_name1);
    REQUIRE(name2 == soln_name2);
}

TEST_CASE("Name_To_Bio", "[Bio_Name Convert]") {
    string bioID1 = name_To_Bio("Abdnor, James");
    string soln_bioID1 = "\nThe BioGuide ID corresponding to the name Abdnor, James is A000009\n";

    string bioID2 = name_To_Bio("Abraham, Ralph Lee");
    string soln_bioID2 = "\nThe BioGuide ID corresponding to the name Abraham, Ralph Lee is A000374\n";

    string bioID3 = name_To_Bio("Adams, Alma S.");
    string soln_bioID3 = "\nThe BioGuide ID corresponding to the name Adams, Alma S. is A000370\n";

    string bioID4 = name_To_Bio("Kim, Nathan");
    string soln_bioID4 = "\nLegislator not found\n";

    REQUIRE(bioID1 == soln_bioID1);
    REQUIRE(bioID2 == soln_bioID2);
    REQUIRE(bioID3 == soln_bioID3);
    REQUIRE(bioID4 == soln_bioID4);
}