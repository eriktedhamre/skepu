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