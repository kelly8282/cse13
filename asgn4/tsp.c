#include "graph.h"
#include "path.h"
#include "stack.h"
#include "vertices.h"

#include <ctype.h>
#include <inttypes.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define PROMPT "hvui:o:"
#define BLOCK  4096
//defining and including everything we need

uint32_t r_count = 0; //recursive count
uint32_t c_count = 0; //cities count

void DFS(Graph *G, uint32_t v, Path *current, Path *shortest, char *cities[], FILE *outfile,
    bool verbose) {
    uint32_t anything = 0; //temporary value that we can store our pop value into
    r_count = r_count + 1; //incrementing our recursive count each time function is ran
    graph_mark_visited(G, v); //mark v as visited so there's no repeated values
    path_push_vertex(current, v, G); //building onto the path with our vertex
    if (path_length(shortest) > 0
        && path_length(current) >= path_length(
               shortest)) { //early break if our current path is longer or equal to the path
        path_pop_vertex(current, &anything, G); //pop vertex
        graph_mark_unvisited(G, v); //mark the vertex as unvisited for the future
        return; //exit
    }
    if (path_vertices(current) == graph_vertices(G)
        && graph_edge_weight(G, v, START_VERTEX)
               > 0) { //checks to see if the current path has every vertex in it and that the current vertex connects to the beginning vertex
        path_push_vertex(current, START_VERTEX, G); //adding start vertex to the end of the path
        if (verbose == true) { //print out the path if it's verbose
            path_print(current, outfile, cities);
        }
        if (path_length(shortest) == 0
            || path_length(current) < path_length(
                   shortest)) { //set the path to be the shortest path if this is the first path found or it is shorter than the previous shortest path
            path_copy(shortest, current);
        }
        path_pop_vertex(current, &anything, G); //remove start vertex from the path
    }
    for (uint32_t i = 0; i < graph_vertices(G); i++) { //for loop to loop through every vertex
        if (graph_has_edge(G, v, i) == true
            && graph_visited(G, i)
                   == false) { //checks all vertices that the current vertices connects to and hasn't been visited yet
            DFS(G, i, current, shortest, cities, outfile,
                verbose); //recursively calls on DFS from that vertex
        }
    }

    path_pop_vertex(current, &anything, G); //pops the vertex
    graph_mark_unvisited(G, v); //marks the vertex as unvisited for the future
    return;
}

bool isNumber(char *s) { //function to check if this is a number by iterating through each character
    while (*s != '\0') {
        if (isdigit(*s) == false) {
            return false;
        }
        s = s + 1;
    }

    return true;
}

int main(int argc, char **argv) {
    int opt = 0; //setting opt
    FILE *infile = stdin; //creating infile
    FILE *outfile = stdout; //creating outfile
    bool verbose = false; //creating verbose boolean
    char **cities; //creating my cities double pointer
    bool help = false; //setting my help boolean
    bool undirected = false; //setting my undirected boolean
    while ((opt = getopt(argc, argv, PROMPT))
           != -1) { //using getopt to see which test cases are ran by user
        switch (opt) { //test cases
        case 'h': help = true; break;
        case 'v': verbose = true; break;
        case 'u': undirected = true; break;
        case 'i': infile = fopen(optarg, "r"); break;
        case 'o': outfile = fopen(optarg, "w"); break;
        }
    }
    if (help
        == true) { //when h command is called this if function will run the helper function that describes each command
        printf("SYNOPSIS\n");
        printf("  Traveling Salesman Problem using DFS.\n");

        printf("USAGE\n");
        printf("  ./tsp [-u] [-v] [-h] [-i infile] [-o outfile]\n");

        printf("OPTIONS\n");
        printf("  -u             Use undirected graph.\n");
        printf("  -v             Enable verbose printing.\n");
        printf("  -h             Program usage and help.\n");
        printf("  -i infile      Input containing graph (default: stdin)\n");
        printf("  -o outfile     Output of computed path (default: stdout)\n");
        return 0;
    }

    char readline[BLOCK]; //define the read buffer

    fgets(readline, BLOCK, infile); //fgets the first line from the file
    readline[strlen(readline) - 1] = '\0'; //removes the newline at the end of the line
    if (isNumber(readline) == false) { //checks that the line only contins numbers
        fprintf(stderr, "Error: malformed number of vertices.\n"); //error message
        return 1; //exit
    }
    c_count = atoi(readline); //parse the line into an integer and stores it to c_count

    cities = (char **) calloc(c_count, sizeof(char *)); //allocate memory to cities
    for (uint32_t i = 0; i < c_count; i++) { //loops through c_count
        fgets(readline, BLOCK, infile); //reads the next line
        readline[strlen(readline) - 1] = '\0'; //remove the new line at the end of the line
        cities[i] = strdup(readline); //duplicate the line into cities so it doesn't get overwritten
    }

    Graph *graph = graph_create(c_count, undirected); //creates our graph
    while (fgets(readline, BLOCK, infile)) { //reads the rest of the file line by line
        readline[strlen(readline) - 1] = '\0'; //remove the next line at the end of the line
        char *num = strtok(readline, " "); //tokenizes to make the line be split by spaces
        uint32_t vals[3]; //declare an array for values
        int i = 0; //setting a value used to know how many numbers has been parsed
        while (num != NULL) { //as long as the token is value, continue parsing
            if (isNumber(num) == false) { //checks if input is not a number
                fprintf(stderr, "Error: malformed edge.\n"); //error message
                return 1; //exit
            }
            vals[i] = atoi(num); //parses a string into an integer
            i = i + 1; //increment i
            num = strtok(NULL, " "); //retreive the next token seperated by space
        }
        if (i != 3) { //checks if more or less than three is read from the line
            fprintf(stderr, "Error: malformed edge.\n"); //errpr message
            return 1; //exit
        }
        graph_add_edge(graph, vals[0], vals[1], vals[2]); //adding the edge from the parsed value
    }

    Path *current = path_create(); //creating our current path
    Path *shortest = path_create(); //creating our shortest path
    DFS(graph, START_VERTEX, current, shortest, cities, outfile,
        verbose); //calling the recursive function to search for the most optimal path
    if (c_count < 2) { //checks if there are less than two cities
        printf("There's nowhere to go.\n"); //message
    } else {
        if (path_length(shortest) == 0) { //checks to see if we found a valid path
            printf("No hamiltonian path found.\n"); //message
        }

        else { //print the valid path that was found
            path_print(shortest, outfile, cities);
        }
        printf("Total recursive calls: %d\n", r_count); //prints the total recursve calls made
    }

    //everything below is freeing memory
    graph_delete(&graph);
    path_delete(&current);
    path_delete(&shortest);
    for (uint32_t i = 0; i < c_count; i++) {
        free(cities[i]);
    }
    free(cities);
    if (infile != stdin) {
        fclose(infile);
    }
    if (outfile != stdout) {
        fclose(outfile);
    }
}
