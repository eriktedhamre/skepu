
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
    cost[u] == -1 && cost[v] == -1:
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
