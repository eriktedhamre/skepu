#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include <skepu>

#define MAX_THREADS_PER_BLOCK 512

int no_of_nodes;
int edge_list_size;
FILE *fp;

//Structure to hold a node information
struct Node
{
	int starting;
	int no_of_edges;
};

struct cost_index
{
	
};


////////////////////////////////////////////////////////////////////////////////
// User functions
////////////////////////////////////////////////////////////////////////////////

void kernel1(skepu::Index1D index, skepu::Region1D<Node> r, skepu::Vector<int> graph_edges, skepu::Vector<bool> graph_mask,
			skepu::Vector<bool> updating_graph_mask, skepu::Vector<bool> graph_visited, skepu::Vector<int> cost, int no_of_nodes)
{
	if(graph_mask[index.i])
	{
		graph_mask[index.i] = false;
		for(int i = r(0).starting; i <(r(0).no_of_edges + r(0).starting); i++)
		{
			int id = graph_edges[i];
			if(!graph_visited[id])
			{
				cost[id]=cost[index.i]+1;
				updating_graph_mask[id]=true;
			}
		}
	}
}

// Using graph_mask as input and result
bool kernel1_graph_mask(skepu::Region1D<bool> r, skepu::Vector<Node> graph_nodes,
						skepu::Vector<int> graph_edges, skepu::Vector<bool> graph_mask, skepu::Vector<bool> updating_graph_mask,
						skepu::Vector<bool> graph_visited, skepu::Vector<int> cost)
{
	int index = r.oi;
	for(int i = graph_nodes(index).starting; i < (graph_nodes(index).starting + graph_nodes(index).no_of_edges); i++)
	{
		int id = graph_edges(i);
		if(!graph_visited(id))
		{
			cost(id) = cost(index) + 1;
			updating_graph_mask(id) = true;
		}
	}
	return false;
}
/*
skepu::multiple<bool, skepu::Vec<int>, skepu::Vec<int>>
kernel1_test(skepu::Region1D<bool> r, skepu::Vec<Node> nodes, skepu::Vec<int> graph_edges, skepu::Vec<bool> updating_graph_mask,
						skepu::Vec<bool> graph_visited, skepu::Vec<int> cost)
{
	int index = r.oi;
	if (r(0)){
		for (int i = nodes(index).starting; i < (nodes(index).starting + nodes(index).no_of_edges); i++){
			int id = graph_edges(i);
			// id is the connecting node
			// So from current node to id for the connecting node

			// Need to update cost of connecting node to current node + 1
			// Also add the connecting node to frontier(updating_graph_mask)
			// Use multi-variat return functions to return all three matrices
			
			if(!graph_visited(id)){
				cost(id) = cost(index) + 1;
				updating_graph_mask(id) = true;
			}
		}
	}
	return false;
}
*/



bool kernel2_test(skepu::Region1D<bool> r, skepu::Vec<bool> updating_graph_mask,
			skepu::Vec<bool> graph_visited, bool *over)
{
	int index = r.oi;
	if(updating_graph_mask[index])
	{
		graph_visited[index] = true;
		*over = true;
		updating_graph_mask[index] = false;
		return true;
	}
	return r(0);
}


////////////////////////////////////////////////////////////////////////////////
// Implementation based on https://canyilu.github.io/teaching/appd-fall-2016/tp3/tp3.pdf
////////////////////////////////////////////////////////////////////////////////

// Need to find a stopping condition

// returns (vector<int> cost,vector<bool> visited)
skepu::multiple<int, bool>
cost_based(skepu::Region1D<int> r, skepu::Vec<Node> nodes, skepu::Vec<int> graph_edges,
				skepu::Vec<bool> graph_visited, skepu::Vec<int> cost)
{
	int index = r.oi;
	if (r(0) == -1)
	{
		for(int i = nodes(index).starting; i < (nodes(index).starting + nodes(index).no_of_edges); i++)
		{
			int id = graph_edges(i);
			if(graph_visited(id)){
				return(cost[id] + 1, true);
			}
		}
	}
	return (-1, false);
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
//Apply BFS on a Graph using CUDA
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

	int source = 0;

	fscanf(fp,"%d",&no_of_nodes);

	int num_of_blocks = 1;
	int num_of_threads_per_block = no_of_nodes;

	//Make execution Parameters according to the number of nodes
	//Distribute threads across multiple Blocks if necessary
	if(no_of_nodes>MAX_THREADS_PER_BLOCK)
	{
		num_of_blocks = (int)ceil(no_of_nodes/(double)MAX_THREADS_PER_BLOCK); 
		num_of_threads_per_block = MAX_THREADS_PER_BLOCK; 
	}

	// allocate host memory
	//Node* h_graph_nodes = (Node*) malloc(sizeof(Node)*no_of_nodes);
	skepu::Vector<Node> graph_nodes(no_of_nodes);
	//bool *h_graph_mask = (bool*) malloc(sizeof(bool)*no_of_nodes);
	skepu::Vector<bool> graph_mask(no_of_nodes); 
	//bool *h_updating_graph_mask = (bool*) malloc(sizeof(bool)*no_of_nodes);
	skepu::Vector<bool> updating_graph_mask(no_of_nodes);
	//bool *h_graph_visited = (bool*) malloc(sizeof(bool)*no_of_nodes);
	skepu::Vector<bool> graph_visited(no_of_nodes);

	int start, edgeno;   
	// initalize the memory
	for( unsigned int i = 0; i < no_of_nodes; i++) 
	{
		fscanf(fp,"%d %d",&start,&edgeno);
		Node node;
		node.starting = start;
		node.no_of_edges = edgeno;
		graph_nodes[i] = node;
		//graph_nodes[i].starting = start;
		//graph_nodes[i].no_of_edges = edgeno;
		graph_mask[i]=false;
		updating_graph_mask[i]=false;
		graph_visited[i]=false;
	}

	//read the source node from the file
	fscanf(fp,"%d",&source);
	source=0;

	//set the source node as true in the mask
	graph_mask[source]=true;
	graph_visited[source]=true;

	fscanf(fp,"%d",&edge_list_size);

	int id,edge_cost;
	//int* h_graph_edges = (int*) malloc(sizeof(int)*edge_list_size);
	skepu::Vector<int> graph_edges(edge_list_size);
	for(int i=0; i < edge_list_size ; i++)
	{
		fscanf(fp,"%d",&id);
		fscanf(fp,"%d",&edge_cost);
		graph_edges[i] = id;
	}

	if(fp)
		fclose(fp);    

	printf("Read File\n");

	// allocate mem for the result on host side
	//int* h_cost = (int*) malloc( sizeof(int)*no_of_nodes);
	skepu::Vector<int> cost(no_of_nodes);
	for(int i=0;i<no_of_nodes;i++)
		cost[i]=-1;
	cost[source]=0;

	int k=0;
	printf("Start traversing the tree\n");
	bool stop = true;

	
	auto kernel1_instance = skepu::MapOverlap(kernel1_test);
	kernel1_instance.setOverlap(0);
	skepu::Vector<bool> kernel1_res(no_of_nodes);
	
	auto kernel2_instance = skepu::MapOverlap(kernel2_test);
	kernel2_instance.setOverlap(0);
	skepu::Vector<bool> kernel2_res(no_of_nodes);
	
	

	//Call the Kernel untill all the elements of Frontier are not false
	do
	{
		
		//if no thread changes this value then the loop stops
		stop=false;
		/*
		cudaMemcpy( d_over, &stop, sizeof(bool), cudaMemcpyHostToDevice) ;
		Kernel<<< grid, threads, 0 >>>( d_graph_nodes, d_graph_edges, d_graph_mask, d_updating_graph_mask, d_graph_visited, d_cost, no_of_nodes);
		// check if kernel execution generated and error
		*/
		kernel1_instance(kernel1_res, graph_mask, graph_nodes, graph_edges, updating_graph_mask, graph_visited, cost);
		graph_mask = kernel1_res;


		/*
		Kernel2<<< grid, threads, 0 >>>( d_graph_mask, d_updating_graph_mask, d_graph_visited, d_over, no_of_nodes);
		// check if kernel execution generated and error
		cudaMemcpy( &stop, d_over, sizeof(bool), cudaMemcpyDeviceToHost);
		*/
		kernel2_instance(kernel2_res, graph_mask, updating_graph_mask, graph_visited, &stop);
		graph_mask = kernel2_res;
		k++;
	}
	while(stop);

	for (int i = 0; i < no_of_nodes; i++)
	{
		std::cout << "i: "<< i << " cost: " << cost[i] << "\n";
	}
	
}