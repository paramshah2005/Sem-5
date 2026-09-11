# Parallel Computer Architecture and Programming Lab (PCAPL)

## Overview
The PCAPL directory covers parallel and heterogeneous computing in C, progressing from shared-memory multithreading with **OpenMP**, to distributed-memory message passing with **MPI**, to GPU programming with **CUDA**. Each lab folder contains the lab handout PDF, an output/screenshot record of the runs, and the source solutions for that week's exercises.

## Subdirectories

### Lab 1: OpenMP Fundamentals
Basics of parallel programming with OpenMP.
- **q1**: Thread counting and parallel region identification
- **q2**: Dynamic thread configuration and thread communication
- **q3**: Parallel matrix initialization with work distribution
- **q4**: Parallel array addition with thread tracking
- **q5**: Parallel matrix addition with serial/parallel performance comparison
- **q6**: Serial vs parallel array summation with timing analysis

### Lab 2: Intermediate Parallel Operations
Advanced parallel matrix and vector operations with OpenMP.
- **q1**: Serial vs parallel matrix addition with performance metrics
- **q2**: Matrix transformation with max/min operations per row
- **q3**: Binary complement and bit manipulation with parallel processing
- **q4**: Matrix-vector multiplication (Ax = b)
- **q5**: Parallel sections with array element squaring operations
- **q6**: Vector operations (addition, subtraction, multiplication) using parallel sections

### Lab 3: Advanced Parallel Concepts (OpenMP)
Complex scheduling, synchronization, and algorithm optimization.
- **q1**: Variable scope exploration (shared, private, firstprivate, lastprivate, reduction)
- **q2**: Synchronization mechanisms (master, atomic, critical sections)
- **q3**: Prime number detection with different scheduling strategies (static, dynamic, guided) — variants `q3_1`, `q3_2`, `q3_3`
- **q4**: Parallel merge sort implementation with serial/parallel comparison

### Lab 4: Introduction to MPI
Point-to-point communication and process basics with MPI.
- **q1**: Each process computes `pow(x, rank)` to demonstrate per-rank computation
- **q2**: Each process toggles the case of one character of a string based on its rank
- **q3**: Rank-based factorial/Fibonacci computation across processes
- **q4**: Synchronous send/receive (`MPI_Ssend`/`MPI_Recv`) with `MPI_Barrier` to transmit and toggle a string between two processes
- **q5**: Master process broadcasts a number to worker processes via `MPI_Send`/`MPI_Recv`
- **q6**: Ring communication pattern — value passed and incremented around a ring of processes
- **q7**: Buffered send (`MPI_Bsend`) to distribute an array of values to worker processes

### Lab 5: MPI Collective Communication
Broadcast, scatter, and gather-based parallel algorithms.
- **q1**: Distributed factorial computation with result collection
- **q2**: `MPI_Scatter` to distribute array chunks and compute a global average
- **q3**: Parallel vowel counting in a string using `MPI_Scatter`
- **q4**: Parallel string comparison/merge across two input strings split among processes
- **q5**: Parallel selection sort of scattered chunks followed by a merge step

### Lab 6: MPI Collectives and Parallel Sorting
Prefix sums, searching, and matrix operations using MPI collectives.
- **q1**: Parallel prefix sum of factorials using `MPI_Scan` with custom error handling
- **q2**: Parallel search — count occurrences of a key in a 3×3 matrix distributed by row (`MPI_Scatter` + `MPI_Reduce`)
- **q3**: Parallel prefix-sum (cumulative sum) of a 4×4 matrix by column using `MPI_Scatter`, `MPI_Scan`, and `MPI_Gather`
- **q4**: Parallel Odd-Even Transposition Sort using `MPI_Sendrecv` between partner processes across phases

### Lab 7: Introduction to CUDA
Basics of GPU programming with CUDA — device properties, memory transfer, and kernel launches.
- **q1**: Query and print CUDA device properties (name, SM count, max threads/block, grid/thread dimensions, clock rate)
- **q2**: Parallel element-wise addition of two arrays on the GPU
- **q3**: Parallel computation of Euclidean distance between two vectors using `atomicAdd`
- **q4**: Parallel computation of `sin()` for an array of angles

### Lab 8: CUDA Programs and Synchronization
1D convolution, parallel sorting, and atomic operations in CUDA.
- **q1**: 1D convolution of an input array `N` with a mask array `M` to produce output array `P`
- **q2**: Parallel Odd-Even Transposition Sort using a CUDA kernel per sort phase
- **q3**: Parallel rank sort — each thread computes the final sorted position of its element
- **q4**: Count occurrences of a given word in a sentence using `atomicAdd`
- **q5**: Replace every vowel in a string with `*` using `atomicExch`

## Key Technologies
- **OpenMP** — shared-memory parallel programming API for C (Labs 1–3), compiled with `-fopenmp`
- **MPI** (Message Passing Interface) — distributed-memory, multi-process programming (Labs 4–6), compiled with `mpicc` and run with `mpirun`/`mpiexec`
- **CUDA** — NVIDIA GPU programming (Labs 7–8), compiled with `nvcc`
- **Concepts covered**: thread/process management, work distribution and scheduling, synchronization (critical/atomic sections, barriers), collective communication (broadcast, scatter, gather, reduce, scan), parallel sorting and searching algorithms, GPU memory management, and kernel-level atomic operations

## Purpose
This directory is part of Semester 5 coursework building a progression through parallel and heterogeneous computing: starting with shared-memory threads (OpenMP), moving to distributed-memory processes (MPI), and finishing with massively parallel GPU kernels (CUDA) — comparing serial and parallel performance and mastering synchronization/communication primitives at each level.
