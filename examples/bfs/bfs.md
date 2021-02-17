Implementation based on algorithm given in HiPC'07
paper "Accelerating Large Graph Algorithms on the GPU Using CUDA".

Uses Compact adjacency list notation.
One large array containing all the individual adjacency list.
With each node containing its starting position in the array as well as its number of edges.

Is a preprocess required like the minmax implementation.