#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>


//edge representation of the graph
struct Edge
{
int src,dest,weight;
};

//graph representation
struct Graph
{
int V,E;
struct Edge *edge ;
};

//create a graph
struct Graph* creategraph(int V,int E)
{
struct Graph* newgraph=new Graph();
newgraph->E=E;
newgraph->V=V;
newgraph->edge=new Edge[E];
return newgraph;
}

//declare a global variable i
int i;

//add an edge to graph
struct Graph* addedge(Graph *graph,int src,int dest,int weight)
{
	if(i==graph->E)
		return 0;
	else
graph->edge[i].src=src;
graph->edge[i].dest=dest;
graph->edge[i].weight=weight;
i++;
return graph;
}

//print distance array
void displaydist(int arr[], int size) {
	int i;
	std::ofstream outfile;
		outfile.open("result.txt",std::ios_base::app);

	for(i = 0; i < size; i ++) {
		outfile<<arr[i]<<",";
	}
	outfile.close();
}

//print path
void display(int arr[], int size) {
	int i;
	std::ofstream outfile;
	outfile.open("result.txt",std::ios_base::app);
		for(i = 0; i < 1; i ++)
		{
		outfile<<arr[i];
		}
		//if(arr[i]!=0)
		for(i=1;i<size;i++)
		{	if(arr[i]!=0)
			{
		outfile<<"->"<<arr[i];
			}
		}

		outfile<<"\n";
		outfile.close();
		}


//bellman ford implementation
// The main function that finds shortest distances from src to
// all other vertices using Bellman-Ford algorithm.  The function
// also detects negative weight cycle
void BellmanFord(struct Graph* graph, int src)
{
    int V = graph->V;
    int E = graph->E;

    int dist[V];
    int pre[V];

    // Step 1: Initialize distances from src to all other vertices
    // as INFINITE
    for (int i = 0; i < V; i++)
    {
        dist[i]= INT_MAX;
        pre[i]=0;
    }
    dist[src] = 0;

    // Step 2: Relax all edges |V| - 1 times.
        for (int i = 1; i < V-1;i++)
        {
            for (int j = 0; j <E;j++)
            {
                int u = graph->edge[j].src;
                int v = graph->edge[j].dest;
                int weight = graph->edge[j].weight;
                if (dist[u] != INT_MAX &&  dist[v]>dist[u] + weight )
                {
                	dist[v] = dist[u] + weight;
                	pre[v]=u;
                	display(pre,V);
                }
            }
        }

        // Step 3: check for negative-weight cycles.

        for (int j = 0; j < E; j++)
        {
            int u = graph->edge[j].src;
            int v = graph->edge[j].dest;
            int weight = graph->edge[j].weight;
            if (dist[u] != INT_MAX && dist[v]>dist[u] + weight)
                printf("Negative Loop detected");
        }

        displaydist(dist,V);
        	return;
}



//use command line arguments to provide the file name of the graph as an input parameter to the complied program
int main(int argc, char *argv[]) {
  int array[500][500];

  std::ifstream file( argv[1]  );
  std::string line;
  int dest = 0;
  int src = 0;
  struct Graph* graph;

  while(std::getline(file,line,'\n'))
  {
    std::istringstream iss( line );
    std::string weight;
    while( std::getline( iss, weight, ',' ) )
      {
        array[src][dest] = atoi( weight.c_str() );
      // std::cout << weight<<" ";
        dest = dest+1;
      }
    src = src+1;
    dest = 0;
    std::cout<<std::endl;
  }
  graph=creategraph(src,src*src);

  for(int j=0;j<src;j++)
  {
	   for(int k=0;k<src;k++)
	  {
		   if(array[j][k]!=0)
		   addedge(graph,j,k,array[j][k]);
	  }
  }

  BellmanFord(graph,0);

 	return 0;
	}
