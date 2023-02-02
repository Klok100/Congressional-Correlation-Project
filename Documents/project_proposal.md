# Final Project Proposal #

## Leading Question ##

For a given Congress member, which other Congress members do they tend to work/sponsor bills with? What information can be revealed through an investigation into legislators’ sponsorship activities? We will use Dijkstra’s Algorithm to find “paths of legislators” between Congress members; the vertices and edges in the path represent which legislators have common sponsorship partners and tend to have similar ideologies. In addition, we will use Tarjan’s strongly connected components algorithm to determine coalitions of similar legislators. This algorithm will utilize a depth-first search traversal to achieve said solution. 

## Dataset Acquisition and Processing ##

Data Format: We will use the publicly available GovInfo Bulk Data dataset (as accessed on 3/25/2022). From this dataset, we plan to use the Bill Status XML files, which store information about every bill introduced in Congress since 2003 and are freely available to download as .zip folders. We plan to use only the names and Biographical Directory member IDs of the sponsors/cosponsors of each bill, so while the complete dataset is divided into 20 folders with ~100-200 MB each, we plan for the actual space we use for our graph to be significantly smaller than the total size of these files.

## Data Correction ##

We will parse the XML files using the RapidXML library. We plan to exclude any bills without a sponsor but do not anticipate that there will be many, if any. Since we are only importing 1-2 fields from each XML file, we believe that data correction will be an expedited process.

## Data Storage ##

We will store the dataset as a weighted adjacency list, where each edge represents a connection between Congress members and the weight is how many bills they have sponsored together. This will be a directed graph, where the main sponsor is the origin of an edge and the cosponsors are each a destination. Bills without a cosponsor will be registered as a loop on the lone sponsor. Since adjacency lists are O(E+V) in space complexity, we believe that our graph will be O(E+V), where V is the number of vertices and E is the number of edges (or more specifically, O(|legislators| + |cosponsorships|), which will be no greater than O(|legislators|^2).


## Graph Algorithms ##

### Dijkstra’s shortest path ###
**Function Inputs:** Two legislators to connect (represented by two nodes in the graph)

**Function Outputs:** Shortest path between given nodes, printed into a stream as the next legislator in the path and the number of bills cosponsored, followed by a delimiter

**Function Efficiency:**
*Time:* O((V+E) log(V)) where E is the number of edges and V is the number of vertices

*Space:* O(V+E)

### Depth-First Search (traversal) ###
**Function Inputs:** A legislator to search for (represented by a starting node)

**Function Outputs:** A preordering of legislators visited by the traversal originating from the starting node

**Function Efficiency:**
*Time:* O(E + V) where E is the number of edges and V is the number of vertices

*Space:* O(V)

### Tarjan’s strongly connected components ###
**Function Inputs:** The graph adjacency list

**Function Outputs:** A partition of the graph into groups of legislators that are “strongly connected” (i.e. have similar bill sponsorship histories) as separate groups of names, printed into a stream

**Function Efficiency:**
*Time:* O(E + V) where E is the number of edges and V is the number of vertices

*Space:* O(V)

## Timeline ##

April 1st: Parse data into manageable format/set-up environment

April 8th: Implement DFS

April 15th (mid-project check in): Implement Dijkstra’s Algorithm

April 22nd: Implement Tarjan’s Algorithm

April 29th: Testing/finishing touches

May 6th: Presentation

