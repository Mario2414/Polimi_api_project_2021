# Polimi_api_project_2021

This project is mandatory to obtain the bachelor's degree at Politecnico di Milano. The project is assigned after the API course (Algoritmi e principi dell'informatica \ Algorithm and computer science principles) regarding the complexity of the code and the different known data structures.

The project consists of a task (different each year) to be completed in the most efficient way, written in C. The mark is automatically assigned by an online tool based on temporal and spatial complexity.

I achieved the maximum score of 30/30 cum laude, implementing a red-black tree and a minheap, and with a generally efficient use of C. However, the code written in this repository doesn't represent my current programming level (the following program was written about 2 years ago). It was written before taking the software engineering course, and was not meant to be read by someone else, so it presents some bad practices and is partially written in Italian.

In the following lines, I will describe in a more detailed way the task to be solved and the method used. The assignment can be found in the PDF file "ProvaFinale2021", and the code can be tested using the "test.txt" file or the the input and (expected) output files in the open_tests folder.

The project consisted of creating a ranking of different direct weighted graphs. The program always receives two parameters in input on the first row of the text file:

- d: the number of nodes in the graphs.
- k: the desired length of the ranking.
d, k, and the number of graphs are representable with 32-bit integers.

After the first row, two types of commands can be found:

- "AggiungiGrafo" (AddGraph in English) followed by the adjacency matrix of a graph printed line by line with values separated by a comma.
- "TopK": considering graphs from the start of the program until the TopK command, print the indices of the k graphs having the smallest value of the following metric: the sum of the shortest path between the node 0 and all the other reachable nodes from 0 of the graph. If there are multiple graphs with the same metric value, priority is given to the ones that were added first. Distances of nodes that are not reachable from 0 are considered to be zero. The indices of the k graphs are printed on a single line, separated by a space, in any order.

To complete the task, I implemented:

- Dijkstra using a minheap to extract the node with the minimum distance, and an array to keep track of the distance of the nodes from the source node.
- A red-black tree to keep track of the TopK graphs in an efficient way.





