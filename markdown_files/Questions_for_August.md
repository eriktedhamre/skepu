1.How should I think about the domains for the remaining benchmarks.
Rodinia clearly states what domain of computing the benchmarks are in.
Should I take this into account when choosing further benchmarks.

Even though two programs are mathematically similar so that they fit into the same dwarf their program could potentially be very different or is this generally not the case for HPC?

For example having done BFS it is considered part of the Graph traversal Dwarf.
In the Graph Algorithm domain.
There are three more in the Graph traversal domain in Rodinia benchmark.
Should these be avoided then.

In that case I should try and get a feel for the already implemented benchmarks so that I do not choose new benchmarks that are to similar to the already implemented ones.

2.Dense Linear Algebra and Structured Grid are two of the larger groups.
A benchmark from the Sparse Linear Algebra dwarf might be interesting as a way to show of SkePUs new SLA if that is implemented in time.


3.BFS could be suitable for the CUDA vs SkePU comparison is however not very hard.
Might be more interesting to compare to a parallel Pthreads-implementation.


Currently wrtiting some theory on readability, there is a few concepts that are also part of the same type of static code analysis.
Readability
There is quite a few articles that want to re-use some models and theories from linguistics, is this of interest.
Complexity
Code can be hard to write but easy to understand and the reverse
Understandability
I assume this is what is at the core most valuable

Theory can have some text about definitions of readability. But a usable definition should be selected in the method chapther and used for the survey.

//////////////////////////////////////////////////////////////////////////////////////////////////////////////

Decide the experimental setup:
I would like to if possible to run atleast suitable benchmarks on Tetralith.

Otherwise I suppose Excess will have to do. I should probably verify that the hardware is not expected to skew the results. 

Make sure the hardware and required software is available.

Should probably check if I can run things properly on tetralith, in the near future.

What input sizes to use. Sparse vs Dense?
As it stands right now, I'm thinking at least one small and one large per benchmark.
Where I suppose the small one should have a run-time equivalent to the small instance for the Parsec benchmarks.
For large I don't know what is feasible. Perhaps 10 or 30 minutes.
But perhaps to once again lean on Parsec to find an input size that has about the same runtime as either simlarge or Native input.
Although this might not be interesting. What is interesting is if SkePU deviates from the expected time curve for larger inputs.

Iteration number.
Should probably check in with the article linked by kessler where it was argued that ?ANOVA? was measured instead and a confidence interval was used instead of an actual measurement.
Number of measurements.

Which backends to use? Experimental(MPI, MPI + CUDA) For each backend, what configuration:

CPU on Excess for baseline.
I assume, I use the available cores there are.
CUDA on Excess for GPU.
Same here use what is available.
I think the statistics article Christoph linked prefered it if all available hardware of a system was used.
This is not as relevant for Tetralith, I would think.

OpenMP on Excess or Tetralith?
Number of cores? 1, 8, 16, 32?
Starting to approach a lot of measurements.
What is most important?

MPI on Tetralith
MPI + CUDA on Tetralith
Again, number of cores?

And so on.

Try to define Memory and Time Complexity.
Both sequential and parallel time complexity.
Look at TDDC78 course material for parallel time complexity.
Important to separate Parallel Work and Parallel Cost.


Done with Complexity and reading the articles. Found a loose and ok definition: https://ieeexplore-ieee-org.e.bibl.liu.se/document/1456082
Pretty old but more in-line with what we are after. Complexity is the the resources requiered for a system to interact with another system. 

Referenced in Improvements to a Complexity Metric: CB Measure as:
"Psychological complexity affects the  performance of programmers trying to comprehend or  modify a class/module whereas algorithmic or computational complexity   characterizes the run-time performance of an algorithm [5]."
I think I'm just going to sort of stick with this. Measure the psychological difficulty from the survey and consider computational complexity either as a separate question of the survey or only on Big-O-notation.

In the end what is interesting is
