#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <iostream>
#include <fstream>

#include <skepu>

int no_of_nodes;
int edge_list_size;
FILE *fp;

//Structure to hold a node information
struct Node
{
	int starting;
	int no_of_edges;
};

////////////////////////////////////////////////////////////////////////////////
// Implementation based on https://canyilu.github.io/teaching/appd-fall-2016/tp3/tp3.pdf
////////////////////////////////////////////////////////////////////////////////

// This solution does not work well for one node with a large amount of edges.
// Especially if it is separated from the source node.

skepu::multiple<int, bool>
map_cost_based(skepu::Index1D ind, skepu::Vec<Node> nodes, skepu::Vec<int> graph_edges, skepu::Vec<int> cost)
{
	int index = ind.i;
	if (cost[index] == -1)
	{
		for (int i = nodes(index).starting; i < (nodes(index).starting + nodes(index).no_of_edges); i++)
		{
			int id = graph_edges(i);
			if(cost[id] != -1)
			{
				return skepu::ret(cost[id] + 1, true);
			}
		}
	}
	return skepu::ret(cost[index], false);
}

bool stopping_condition(bool a, bool b)
{
	return (a || b);
}


////////////////////////////////////////////////////////////////////////////////
// Main Program
////////////////////////////////////////////////////////////////////////////////

void BFSGraph(int argc, char** argv);


int main( int argc, char** argv) 
{
	no_of_nodes=0;
	edge_list_size=0;
	BFSGraph( argc, argv);
}

void Usage(int argc, char**argv){

fprintf(stderr,"Usage: %s <input_file> <backend_spec>\n", argv[0]);

}
////////////////////////////////////////////////////////////////////////////////
//Apply BFS on a Graph Using SkePU
////////////////////////////////////////////////////////////////////////////////
void BFSGraph( int argc, char** argv) 
{

    char *input_f;
	if(argc!=3){
	Usage(argc, argv);
	exit(0);
	}
	
	input_f = argv[1];

	auto spec = skepu::BackendSpec{skepu::Backend::typeFromString(argv[2])};
	skepu::setGlobalBackendSpec(spec);

	printf("Reading File\n");
	//Read in Graph from a file
	fp = fopen(input_f,"r");
	if(!fp)
	{
		printf("Error Reading graph file\n");
		return;
	}

	fscanf(fp,"%d",&no_of_nodes);

	skepu::Vector<Node> graph_nodes(no_of_nodes);

	int start, edgeno;   
	// initalize the memory
	for( unsigned int i = 0; i < no_of_nodes; i++) 
	{
		fscanf(fp,"%d %d",&start,&edgeno);
		Node node;
		node.starting = start;
		node.no_of_edges = edgeno;
		graph_nodes[i] = node;
	}

	//read the source node from the file
	int source = 0;
	fscanf(fp,"%d",&source);
	source=0; // Left over from Rodinia implementation

	fscanf(fp,"%d",&edge_list_size);

	int id,edge_cost;

	skepu::Vector<int> graph_edges(edge_list_size);
	for(int i=0; i < edge_list_size ; i++)
	{
		fscanf(fp,"%d",&id);
		fscanf(fp,"%d",&edge_cost); // Left over from original Rodinia implementation
		graph_edges[i] = id;
	}

	if(fp)
		fclose(fp);    

	printf("Read File\n");

	skepu::Vector<int> cost(no_of_nodes, -1);

	cost[source] = 0;

	auto map_inst = skepu::Map<0>(map_cost_based);
	skepu::Vector<int> res_cost(no_of_nodes);
	skepu::Vector<bool>res_bools(no_of_nodes);
	auto reduce_inst = skepu::Reduce(stopping_condition);
	reduce_inst.setStartValue(0);
	printf("After instance initilization\n");

	int k=0;
	bool cont = true;
	printf("Start traversing the tree\n");

	//Call the Kernel untill all no new nodes are discovered
	do
	{
		if (k % 2 == 0)
		{
			map_inst(res_cost, res_bools, graph_nodes, graph_edges, cost);
			cont = reduce_inst(res_bools);
		}
		else
		{
			map_inst(cost, res_bools, graph_nodes, graph_edges, res_cost);
			cont = reduce_inst(res_bools);
		}
		
		k++;
	}
	while(cont);

	std::cout << "result \n";

	std::ofstream MyFile("skepu4096result.txt");

	if (k % 2 == 0)
	{
		for (int i = 0; i < no_of_nodes; i++)
		{
			MyFile << i << ") cost:" << res_cost[i] << "\n";
		}
	}
	else
	{
		for (int i = 0; i < no_of_nodes; i++)
		{
			MyFile << i << ") cost:" << cost[i] << "\n";
		}
	}
	
}