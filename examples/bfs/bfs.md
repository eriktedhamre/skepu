Implementation based on algorithm given in HiPC'07
paper "Accelerating Large Graph Algorithms on the GPU Using CUDA".

Uses Compact adjacency list notation.
One large array containing all the individual adjacency list.
With each node containing its starting position in the array as well as its number of edges.

Is a preprocess required like the minmax implementation.

for kernel1
Use graph_mask and update_graph_mask instead of graph_nodes.
Then use graph_nodes as random access

for kernel2
Use graph_visited or updating_graph_mask as input

might have to create a separate function to add to the cost matrix since this could potentially run into synchronization issues.
Or I might just be wrong.


/////////////////////////////////////////////////////////////////////////////////////////////////////

BFS:

I assume MapOverlap is not the preferred skeleton....if you have a better alternative I would welcome feedback.

The stopping condition in the original implementation uses a referenced bool that can be changed by any thread.
If the bool is not changed the loop stops.

The stopping conditions I came up with all require additional checks outside of the main SkePU-instances:

Checking if the cost matrix has changed between iterations every X:th iteration.
So a Matrix-Matrix comparison O(n) where n number of nodes. Of couse already visited nodes would not need to be checked. Some kind of Set or Sparse matrix could perhaps be useful to make it faster once a lot of the nodes have been visited.

Use multivariant return to make it easier to use only of the fields insted of a struct. Use Map with index instead of MapOverlap. 

Using a SkePU reduce call to see if the sum of the costs has changed between the iterations. I assume this should be faster than a sequential comparison.

Save previous reduce result cumulative cost and compare (2 generations)

Change to Map, get rid of struct.
Reduce call on bool result vector to decide if another iteration is needed.
Find articles that run the Rodinia BFS benchmark, and see what type of inputs they use.

You talked about having nodes as the input matrix but I did not understand it.
Or I understand that since we only access one element of the node vector we do not need it as random access.
How do I specify that.
