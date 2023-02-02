# Meeting Log Records #

## Meeting on 3/29/22 ##
### Notetaker: Joe Ku ###
Set up a coding environment for the final project. This involved figuring out how to run the development environment on each members’ machine (either using docker or fastx). We also created the Makefile and compiled a simple “Hello World!” program. Imported rapidXML to assist with extracting data. Configured test suite and ran simple test to check functionality

## Meeting on 4/5/2022 ##
### Notetaker: Nathan Kim ###
This week, we utilized the imported rapidXML library to parse through each of the BILLSTATUS xml files. We will be scraping each bill for its sponsor and following cosponsors which will be stored in a CSV file via each person’s bioguideID. As a result, every person will have a unique ID that can be mapped back to their name without taking up any extra space to actually store the name. As for tangible progress, we figured out how to parse through an entire XML file to obtain the data that we need. In addition, we also determined how to iterate through each xml file. 

## Meeting on 4/12/2022 ##
### Notetaker: Neil Prabhu ###
This week, we were able to utilize our process from last week to iterate through each xml file and extract the sponsors and co-sponsors, but in every file in every folder. Furthermore, we were able to skip over files which do not exist because our upper limit was the max files in all of the folders. Lastly we considered how we were going to store our graph, and ultimately decided to use an adjacency list. Additionally, we decided our graph would be directed since Tarjan’s algorithm requires it. 

## Meeting on 4/19/2022 ##
### Notetaker: Neil Prabhu ###
This week, we were able to extract all of the sponsors and cosponsors from all downloaded files into a single csv file. Moving forward, we will use this csv to build our graph, rather than pulling the data from the 2GB zip file. From that compacted csv file, Joe and Neil worked on pairing the sponsor and subsequent cosponsers to push into our graph structure. For the graph structure itself, Kyle worked on the insertEdge(), removeEdge(), insertVertex(), removeVertex(), and incidentEdge() methods. Nathan was in quarantine since he had covid-19.

## Meeting on 4/26/2022 ##
### Notetaker: Neil Prabhu ###
This week, Kyle implemented the DFS algorithm, as well as wrote test cases for DFS, Dijkstra’s and Tarjan’s algorithm. We realized that we needed a min heap implementation since the one provided from the standard template library was not suitable because we needed to change values of the edges in the middle of the heap. Therefore, Nathan worked on the min heap implementation and dijkstra’s implementation. Joe worked on Tarjan's algorithm implementation. Neil worked on the readme file and documentation for functions. 

## Meeting on 5/3/2022 ##
### Notetaker: Nathan Kim ###
This week, we all finished and combined our implementations of our DFS, Dijkstra's, and Tarjan's algorithms in main.cpp where we also set up the completed framework of our UI. We then made specific changes to each algorithm to either improve their runtimes or functionality. So, Kyle changed the DFS implementation from a recursive implementation to one that uses a stack, since it kept timing out when we ran it on our completed dataset. In addition, Nathan modified the Dijkstra's algorithm implementation so that now it would be inverted. This means that it will search for the shortest path with the highest weighted edges instead of the smallest weighted edges. This is because a higher weighted edge means that two legislators are more connected rather than less connected. Nathan also worked on including additional functions/features such as bio_To_Name(), name_To_Bio(), numConnections(), and numBillsSponsoredTogether(). Then, Joe modified the Tarjan's algorithm implementation, so that it now accepts a user-inputted tolerance level when checking for strongly connected components. Finally, Neil worked a lot on creating and improving the UI, for example by creating a clean loading bar that corresponds to the progress of the data importation.  He also heavily contributed to our write-up, including results.md and the readme file. 
