////////////////////////////////////////////////////////////////////////////////////////////////////////////////

I think perhaps I should avoid more Parsec benchmarks for now can see with August, mostly since I feel they are probably hard to SkePUify in a reasonable time.

Currently I am looking at Rodinia mostly because they have GPU implementations and I can use the four programs from the Parsec paper.
But it seems like arbitrary reasoning to me, which I think should be avoided.

BFS(Graph Traversal, Graph Algorithms)LOC≈300: implemented

Discarded:

Structured Grid:
Particle Filter(Probably similar to Parsec Bodytracking, both use a Particle filter)

Dense Linear Algebra:
Streamcluster(Probably similar to Parsec Streamcluster, which I can use)

Graph traversal:
MUMerGPU
B+Tree

Under consideration:

Dynamic programming
My naive picture of Dynamic Programming using CPU requires
non-side effect free modification of the dynamic programming table.
This I assume is solved in the GPU version.
Needleman-Wunsch LOC≈ 450
PathFinder LOC≈ 250
                                          
Finite State Machine
Huffman LOC≈2000

Dense Linear Algebra
Should be suitable for SkePU.
LU Decomposition LOC≈ 350
kMeans LOC≈2000 most of it is in the getopt.c file, unsure if this needs to be translated
Gaussian Elimination LOC≈470
k-Nearest Neighbors LOC≈300

N-Body
LavaMD2 LOC≈ 800

Sorting
Hybrid sort LOC≈2000 A lot of large helper files.

Spectral Method
GPUDWT LOC≈3500 Has a separate folder named dwt_cuda responsible for 2000

Structured Grid
Leukocyte LOC≈ 4000+, also uses AVI-lib might not need to be translated
Heart wall LOC≈2500 Assuming AVI-lib does not need to be translated
HotSpot LOC≈ 350
HotSpot3D LOC≈ 300, this implementation might use HotSpot don't know seems like few lines otherwise

SRAD_v1 LOC≈1000 SRAD_v2 LOC≈500 SRAD_v1 processes a real image while SRAD_v2 randomizes the inputs.
SRAD_v1 puts more computation on the GPU, e.g. initializations and reductions. 
Some of SRAD_v2 kernels takes more advantage of GPU's scratchpad memory.

Myocyte LOC≈4000+

Unstructured Grid
This should be problematic for SkePU.
CFD Solver LOC≈2400 (They are however split into 2, one version for Double and the other for float I assume)
Back Propogation LOC≈ 350 lines CUDA and a lot of c code





