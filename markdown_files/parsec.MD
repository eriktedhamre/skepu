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
