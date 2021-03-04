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


Decide the experimental setup.
Make sure the hardware and required software is available.
What input sizes to use.
Iteration number.
Number of measurements.
Which backends to use? Experimental(MPI, MPI + CUDA) For each backend, what configuration.
And so on.

Try to define Memory and Time Complexity.
Both sequential and parallel time complexity.
Look at TDDC78 course material for parallel time complexity.
Important to separate Parallel Work and Parallel Cost.
