# Results
---------------
## Depth-First Search
### Output
The program traverses the graph in a depth-first search traversal and outputs the number of legislators visited as well as the number of edges that were classified as a discovery edge.

![image](https://media.github-dev.cs.illinois.edu/user/14278/files/f24c9b22-2d16-489e-bd85-183b6f1c6455)

### Efficiency
Runtime: O(V + E)

Space: O(V)

### Tests
Our test cases for Depth-First Search tests:
* Simple graph traversal
* Edge classification (discovery vs back)
* Multiple components traversal
* Traversal of a small subset of the full dataset

---------------
## Dijkstra's Algorithm
### Output
Given Legislator 1 (start) and Legislator 2 (end), the program outputs the shortest path between the two, as well as the connectivity rating between them (the connectivity rating is based on the total number of bills sponsored on the path between the two legislators).


![image](https://media.github-dev.cs.illinois.edu/user/14278/files/6adc4276-e897-49c8-bc6f-9d8e25f52b8a)


### Findings
The output paths from our datase appeared as expected; primarily, we found that two legislators that were of the same party and were typically associated with each other had paths of length 1 or 2. Two such senators are Senate Majority Leader Chuck Schumer (S000148) and Senate Majority Whip Dick Durbin (D000563).

![image](https://media.github-dev.cs.illinois.edu/user/14278/files/bf43805b-24e0-45c7-a46d-0b043742919d)

Legislators that have exclusively worked in separate houses have a shortest path that utilizes legislators who have worked in both houses. The path from Chuck Schumer to Speaker of the House Nancy Pelosi (P000197) includes Kirsten Gillibrand (G000555) and Ed Markey (M000133), who have worked in both houses of Congress.

![image](https://media.github-dev.cs.illinois.edu/user/14278/files/8bc04f68-e45d-4cbd-b252-28e87736822f)

Interestingly, we found that in some cases, it was possible to find a path from a current legislator to a past legislator but not in the other direction. One example of this is the path from Sara Jacobs (J000305), a freshman member of the House of Representatives in 2021, to Paul G. Kirk, Jr. (K000374), one of the shortest-tenured Congress members (only serving from 2009-2010).

![image](https://media.github-dev.cs.illinois.edu/user/14278/files/b30efc9f-3c4c-48c1-a95d-92026bcc93b9)
![image](https://media.github-dev.cs.illinois.edu/user/14278/files/eaf0b870-2815-4912-bbd7-668f692caaa8)

### Efficiency
Runtime: O((V + E) logV)

Space: O(V + E)

### Tests
Our test cases for Dijkstra's Algorithm tests:
* Starting node and ending node is the same
* Simple connected graph path
* Medium connected graph path
* Hard graph path
* Simple disconnected graph path
* Medium disconnected graph path

---------------
## Tarjan's Algorithm
### Output
For any given legislator, the program outputs all strongly connected legislators as determined by the weighted, directed graph.

![image](https://media.github-dev.cs.illinois.edu/user/14278/files/8ccc6e95-3657-4d4b-878b-f931d5d28fb2)

### Findings
We expected the size of the strongly connected components to decrease as the threshold increased; we also expected those smaller SCCs to contain more ideologically aligned Congress members. Our results aligned with this expectation; the most obvious example of this is with Senate Majority Leader Chuck Schumer (S000148). The size of the SCC containing the senator decreased as we increased t from 50 to 60 to 70:
![Screenshot (507)](https://media.github-dev.cs.illinois.edu/user/14308/files/9d05fb1f-ad02-4a9b-89e2-53d819984d45)
![Screenshot (508)](https://media.github-dev.cs.illinois.edu/user/14308/files/62f2a761-42e8-457a-b4ef-a1241b80b937)
![Screenshot (509)](https://media.github-dev.cs.illinois.edu/user/14308/files/d473cd16-eb22-4d51-9c99-51f7f652984e)

At t = 70, the only legislators within the SCC (besides Schumer himself) are: Hillary Clinton (C001041), Kirsten Gillibrand (G000555), Ed Markey (M000133), Elizabeth Warren (W000817), and Richard Blumenthal (B001277). These are all strongly Democratic legislators with long tenures.

### Efficiency
Runtime: O(V + E)

Space: O(V)

### Tests
Our test cases for Tarjan's Algorithm tests:
* Various cases for strongly connected components

---------------
## Additional Features
### Output
In addition to the three algorithms described above, we implemented:

* A feature to output the total number of cosponsors that a legislator has achieved across all of the bills they have submitted:
![image](https://media.github-dev.cs.illinois.edu/user/14278/files/27abead8-0147-4df6-ac24-f284a1c79dba)
    * Runtime: O(deg(V))

* A feature to output the number of bills two legislators have collaborated together on:
 ![image](https://media.github-dev.cs.illinois.edu/user/14278/files/5b2ef1c4-2214-40fc-ada3-c08738d018e7)
     * Runtime: O(deg(V))
 
* A feature to output the name of the legislator given their BioGuide ID:
![image](https://media.github-dev.cs.illinois.edu/user/14278/files/6e620236-a734-4f2b-ae63-b511ae808d51)
    * Runtime: O(n) where n is the total number of lines in the namesToBioGuideID.csv file

* A feature to output the BioGuide ID of the legislator given their full name:
![image](https://media.github-dev.cs.illinois.edu/user/14278/files/3bbce889-d8b3-480f-854c-b3c5139c3e9b)
    * Runtime: O(n) where n is the total number of lines in the namesToBioGuideID.csv file


### Tests
Our test cases for the miscellaneous features tests:

* Accuracy of the number of bills outputted when given a legislator
* Accuracy of the number of bills outputted when given two legislators (collaboration)
* Accuracy of the legislator's BioGuide ID when given a full name
* Accuracy of the legislator's name outputted when given a BioGuide ID

---------------
## Conclusion

Generally, our algorithms showed that legislators tend to cosponsor bills with other members within the same party and house of Congress. However, our large strongly connected components suggest that legislators sponsor many bills in general and that some bills include many cosponsors, which leads to a dense graph that reaches across party lines and time periods. In the process, we explored different ways to respresent these connections in memory, as well as alterations to algorithms that might improve their efficiency and their usefulness in interpreting our data.
