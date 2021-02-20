#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include <skepu>

struct Node
{
	int starting;
	int no_of_edges;
};

bool kernel1_graph_mask(skepu::Region1D<bool> r, skepu::Vec<Node> graph_nodes,
						skepu::Vec<int> graph_edges, skepu::Vec<bool> graph_mask, skepu::Vec<bool> updating_graph_mask,
						skepu::Vec<bool> graph_visited, skepu::Vec<int> cost)
{
    /*
	for(int i = graph_nodes(index.i).starting; i < (graph_nodes(index.i).starting + graph_nodes(index.i).no_of_edges); i++)
	{
		int id = graph_edges(i);
		if(!graph_visited(id))
		{
			cost(id) = cost(index.i) + 1;
			updating_graph_mask(id) = true;	
		}
	}
    */
	return false;
}

bool kernel1_test(skepu::Region1D<bool> r, skepu::Vec<Node> nodes, skepu::Vec<int> graph_edges, skepu::Vec<bool> updating_graph_mask,
						skepu::Vec<bool> graph_visited, skepu::Vec<int> cost)
{
	int index = r.oi;
	if (r(0)){
		for (int i = nodes(index).starting; i < (nodes(index).starting + nodes(index).no_of_edges); i++){
			int id = graph_edges(i);
			if(!graph_visited(id)){
				cost(id) = cost(index) + 1;
				updating_graph_mask(id) = true;
			}
		}
	}
	return false;
}

int main(int argc, char* argv[])
{
	if (argc < 6)
	{
		if(!skepu::cluster::mpi_rank())
			std::cout << "Usage: " << argv[0] << "size backend\n";
		exit(1);
	}
	
	const size_t size = std::stoul(argv[1]);
	auto spec = skepu::BackendSpec{skepu::Backend::typeFromString(argv[2])};
	skepu::setGlobalBackendSpec(spec);
	
	


	skepu::Vector<Node> graph_nodes(size);
	skepu::Vector<bool> graph_mask(size); 
	skepu::Vector<bool> updating_graph_mask(size);
	skepu::Vector<bool> graph_visited(size);

    skepu::Vector<int> graph_edges(size);
    skepu::Vector<int> cost(size);
	
	

    auto instance = skepu::MapOverlap(kernel1_test);
    instance.setOverlap(0);
    instance.setEdgeMode(skepu::Edge::None);
	skepu::Vector<bool> kernel1_res(size);

	instance(kernel1_res, graph_mask, graph_nodes, graph_edges, updating_graph_mask, graph_visited, cost);
}