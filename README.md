# CS 225 Final Project: Congressional Correlation
### Team Members:
* Kyle Kenmotsu 
* Joe Ku 
* Nathan Kim 
* Neil Prabhu 

## Introduction
For a given Congress member, which other Congress members do they tend to work/sponsor bills with?
We used the publicly available GovInfo Bulk Data dataset (as accessed on 3/25/2022), which stores information about every bill introduced in Congress since 2003, in order to build a graph relationship of Congress members.

## Deliverables
* [Output & Results](https://github.com/neil784/CongressionalCorrelation/blob/main/results.md)
* [Presentation Slides](https://docs.google.com/presentation/d/1S1UwxRnkpKOwtoovxOivmun0rX-Jcvfp40Y9z3kJScg/edit?usp=sharing)

## File Description and Contents
### Code Files
* **XMLParser**: Extracts the sponsors and cosponsors from the original dataset (3 GB) downloaded from GovInfo Bulk Data and writes them to a condensed bill_sponsors.csv file (Only done once in the beginning of project)

* **graphs**: Builds an adjacency list from the condensed bill_sponsors.csv file 

* **DFS**: Implementation of DFS Traversal

* **Dijkstra**: Implementation of Dijkstra's Algorithm

* **Tarjan**: Implementation of Tarjan's Algorithm

* **Utils**: Miscellaneous functions for UI and legislator metadata

* **main**: UI Functionality and algorithm execution

* **tests**: Test cases for all functions and features
### CSV Files
* **nameToBioGuideID.csv**: Contains all legislator names along with their BioGuide ID
* **bill_sponsors.csv**: Contains the full set of sponsors and cosponsors extracted from GovInfo Bulk Data (106,634 lines of data)
* **billSponsorsSample.csv**: Contains a subset of sponsors and cosponsors from bill_sponsors.csv (50 lines of data)
* **billSponsors25000.csv**: Contains a subset of sponsors and cosponsors from bill_sponsors.csv (25,000 lines of data)
* **billSponsors50000.csv**: Contains a subset of sponsors and cosponsors from bill_sponsors.csv (50,000 lines of data)
* **billSponsorsUser**: Contains an example of a user-created CSV to import (50 lines of data)
* **billSponsor25000User**: Contains an example of a user-created CSV to import (25,000 lines of data)

## Instructions For Use
Clone our repository using the following link:
```
https://github-dev.cs.illinois.edu/cs225-sp22/kkenm2-jsku2-nrkim2-nprabh8.git
```
To compile the program, run the command:
```
make
```
To execute the program, run the command:
```
./bin/exec
```
The main screen will prompt you to either import your own correctly formatted CSV dataset or continue with the standard already-implemented CSV dataset: 

![image](https://media.github-dev.cs.illinois.edu/user/14278/files/31bf8f26-25eb-4c93-9e04-d62b1547a8b0)

*NOTE: It may take several minutes for the data to import. This is a trade-off we made in terms of time complexity in order to increase the speed of our algorithms. 

Once dataset selection is complete, the homescreen should be displayed:

![image](https://media.github-dev.cs.illinois.edu/user/14278/files/9fd9e219-b773-463f-b2ae-f9aab5808950)



Feel free to play around with all provided features!
## Test Cases
To compile the test cases, run the command:
```
make tests
```
To execute the test cases, run the command:
```
./bin/tests
```
Our test cases assess:
* Data imporation
* Graph construction
* DFS accuracy
* DFS edge classification
* Dijkstra's algorithm accuracy
* Tarjan's algorithm accuracy
* Miscellaneous features accuracy

## References
* [Depth-first search](https://en.wikipedia.org/wiki/Depth-first_search)
* [Dijkstra's algorithm](https://en.wikipedia.org/wiki/Dijkstra%27s_algorithm)
* [Tarjan's algorithm](https://en.wikipedia.org/wiki/Tarjan%27s_strongly_connected_components_algorithm)
