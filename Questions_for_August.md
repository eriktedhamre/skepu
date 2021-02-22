There should probably be a simple example on how Element index retrieval works. In the SkePU userguide.


setDefaultSize, there is an explanation, for MapPairsReduce but not one for MapReduce.

Under listing 1.3 the paragraph should finish above the listing

Multiple return types for reduce??

did a combined max,min and sum operation, then simply divided the sum. One reduce call but feel cheap.

MapOverlap-using index in it? How would you solve the rolling average exercise?

Rolling average implementation sometime gets floating point errors which results in very large or small values.



Bodytrack
Applying filter on images. Would have to create a particlefilter class as well as a trackingmovements for SkePU. Do not forsee any SkePu-related problems, more so difficulty in understanding the math and physics behind.



Faceanimate
Was harder for me to analyze I don't feel like I got a grip of the parallelization process.



Freqmine
The three functions below were said to be the Hotspot according to the READ.ME

first_transform_FPTree_into_FPArray: Transforms a Frequent Pattern Tree data-structure into a Frequent Pattern Array. 

FPArray_scan2_DB: I assume this function scans the old tree and modifies the new one based on the scan....

FPArray_conditional_pattern_base

There are a few OpenMP directives in the code that could probably be converted to SkePU calls.

Vips
Just looks like a bash script to me unsure how to parallelize.
Also has a 70 Page manual, I have not read.

Something I would appreciate is a dedicated documentation.
This is probably obvious but just putting it out there.

You have to specify the SkePU data structures in their shortened form when using them as parameters for user functions.




We have to loop over all nodes.

for all nodes
    for all edges_from_that_node

How do we solve the cost matrix

What if we do individual nodes that send back cost matrices.

for each node check if the node has been visited
if the node has been visited 


1.
//Need someway to know we have stopped if we have a node with no edges or an island.
Might have to use some special Edge struct:
struct Edge{
    int u;
    int v;
    int cost;
}
Cases when looping over edges(u,v): 
    cost[u] == -1:
        return
    cost[u] != -1:
        Add cost[v] as cost[u] + 1

For each edge check if source is reached
    if so add cost + 1
    else do nothing
    if 


Looping over nodes and neighbours in reverse is probably too slow.
Each nodes looks through all their neighbours and looks for a discovered node.
Could probably work.


//Implementation looks promising
// I'm unsure of the complexity of this implementation
https://canyilu.github.io/teaching/appd-fall-2016/tp3/tp3.pdf


