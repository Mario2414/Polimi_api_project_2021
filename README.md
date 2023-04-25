# Polimi_api_project_2021

This is a project mandatory to get the bachelor degree at Politecnico di Milano. The project is assigned after the API course (Algoritmi e principi dell'informatica \ Algorithm and computer science principles) regarding the complexity of the code and the different known data structures.

The project every year consist of a task (different each year) to be completed in the most efficient way written in C, the mark is automatically assigned by an online tool based on temporal and spatial complexity.

I achieved the maximum score of 30/30 cum Laude, implementing a red-black tree and a min-heap and with a general efficient use of C, however the code written in this repository doesn't represent my current programming level (the following program was written about 2 years ago), was written before taking every the course of software engineering course and was not meant to be read by someone else, so it presents some bad practices and it is partially written in Italian.

In the following lines I proceed to describe in a more detailed way the task to solve and the method used, the assignment can be found in the pdf "ProvaFinale2021" and the code can be executed using the test.txt file.

The project consisted of realizing a ranking of different direct weighted graphs, the program always receive two parameters in input on the first row of the text file:
- d : the number of nodes in the graphs.
- k : the desired lenght of the ranking.

d, k and the number of graphs are representable with 32 bit integer.

After the first row can be found two types of command:
- "AggiungiGrafo" (AddGraph in english) followed by the adjacency matrix of a graph printed line by line with values separaby a comma.
- "TopK" considering graphs from the start of the program until the topk command: print the indexes of the k graphs having the smallest value of the following metric: sum of the shortest path between the node 0 and all the other reachable node from 0 of the graph, if there are multiple graphs with the same metric value, priority is given to the first ones to arrive, distances of nodes that are not reachable from 0 are considered to be zero, the k indices are printed, on a single line, separated by a space, in any order.

To complete the task i implemented:
- Djikstra using a minheap to extract the node with the minimum distance and an array to keep track of the distance of the nodes from the source node.
- A red-black three to keep track of the topK graphs in an efficient way.






