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