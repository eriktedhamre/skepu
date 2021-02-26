How should I think about the domains for the remaining benchmarks.
Rodinia clearly states what domain of computing the benchmarks are in.
Should I take this into account when choosing further benchmarks.

For example having done BFS it is considered part of the Graph traversal Dwarf.
In the Graph Algorithm domain.
There are three more in the Graph traversal domain in Rodinia benchmark.
Should these be avoided then.

In that case I should try and get a feel for the already implemented benchmarks so that I do not choose new benchmarks that are to similar to the already implemented ones.

Dense Linear Algebra and Structured Grid are two of the larger groups.
A benchmark from the Sparse Linear Algebra dwarf might be interesting as a way to show of SkePUs new SLA if that is implemented in time.


BFS could be suitable for the CUDA vs SkePU comparison is however not very hard.
Might be more interesting to compare to a parallel Pthreads-implementation.