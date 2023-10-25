# Lookup-optimization

This repository is a sandbox used to study ways to improve the performance of computation/memory intensive tasks, mostly related to data engineering tasks from other projects I am working on. In particular, I am interested in rewriting python code I have implemented elsewhere with C++/Fortran and optimizing code for parallelization.

## The Initial Problem

The first problem I am working on, and the current focus of this project, is fairly straightforward: searching a list of integers for occurences of certain subsequences *within individual integers in the list*. For example, given the subsequence 60235, a possible match from the list would be something like 134***60235***75. It's certainly an unusual challenge, but it was sadly born out of necessity.

There is a very obvious way to do this with python: convert everything to strings and use a nested loop to compare each test sequence with the entries in the master list. The problem is that these lists are *huge*. The master list has tens of millions of entries. And it's drawn from one column out of hundreds, so future tasks might require working with even more data. Not to mention there are over a thousand test sequences, which could rise to tens of thousands. The string approach quickly becomes prohibitively memory and computationally intensive.

So is there another way? One way is to do the search, but keep everything in integer form. The crude,straightforward approach is to break each integer from the parent list into pieces
matching the number of digits in the test sequence and check equality. In the above example it would look like this:<br><br>
[***13460***]23575 == 60235? X<br>
1[***34602***]3575 == 60235? X<br>
13[***46023***]575 == 60235? X<br>
134[***60235***]75 == 60235? ✓<br><br>
And having confirmed it is a match, we can save this as a potential match and break/continue to the next iteration of the loop (there can be multiple matches per test sequence).<br>

This approach is far from perfect, at least not without significant optimization. The most straightforward implementation involves several mathematical operations (modulus, log10, etc). Let's see how it performs on a small list of test sequences (25 test sequences, 63 million integer list):<br>
<code>test_loop.py</code><br>

<p align="center">
<img src="https://raw.githubusercontent.com/AWikramanayake/Lookup-optimization/master/misc_assets/Python%20loop%20performance.png" width="800"/>
</p>
<p align="center">

At first glance, it isn't promising. The integer mask method takes more than 10x as long! But there are some things to take into consideration. Since the list of test sequences is much smaller than in realistic use cases, the memory constraints from the string method aren't as apparent. There are also a LOT of possible ways to improve the integer mask method (more on that later), but most importantly, Python is a terrible choice of language for running it.

Let's try the same integer mask method with Fortran:<br>
<code>exec_fortran</code><br>

<p align="center">
<img src="https://raw.githubusercontent.com/AWikramanayake/Lookup-optimization/master/misc_assets/Fortran%20loop%20performace.png" width="800"/>
</p>
<p align="center">

And now the integer mask method is 10x ***faster*** than the python string method, instead of >10x slower. And there is still a lot of room for improvement. Next steps:<br>

- Improve the integer mask method (both by making the algorithm itself more efficient and by improving the code).
- Add parallelization. **C++**: add GPU parallelization with C++ CUDA. **Fortran**: rewrite the algorithm with pure subroutines so the <code>do concurrent</code> loop can be parallelized.
<br>

## Latest Updates:

### Improving integer log10 function (C++)

The log10 step in the integer mask algorithm is a glaring inefficiency. It is only used to get the number of digits in the test sequence, so the precision is not needed, and the cmath implementation is meant for reals. We can use the extremely cheap base-two logarithm to estimate the base-10 result. Let's compare the performance, with an additional step with a different integer data type:<br>
<code>Cpp_dev/log10comp.cpp</code>

<p align="center">
<img src="https://raw.githubusercontent.com/AWikramanayake/Lookup-optimization/master/misc_assets/cpp%20log10%20comp.png" width="800"/>
</p>
<p align="center">

This log10 substitute is a around 200x faster than just using the built in cmath log10 function! Using uint_fast64_t instead of unsigned ints improves most individual iterations, but it's balanced out by occasional iterations that are much slower. The choice of specific uint types can be left for later, when memory allocations become more important with CUDA implementation.




