This program solves the traveling salesman problem using depth first-search. Given a properly formatted 
input file the program will read in a file containing the number of vertices/places, the names of the
vertices/places, and the weight of all of the edges from each vertex and stores it in a graph ADT.
Depth first search is then used to find the shortest hamiltonian path given an origin of 0, or the first
city that was read in to the graph. To run the program use the 'make' or 'make all' commands and all of the
necessary files will be compiled and linked to create an executable. You can run the executble from the
command line with the desired command-line options as specified:
 -v: Enables verbose printing
 -u specifies teh graph to be undirected
 -i infile: specify the input file path containing the cities and edges of a graph (default is stdin)
 -o outfile: specify the output fie path to print to (default is stdout)
