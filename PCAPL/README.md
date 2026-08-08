# Programming and Computer Architecture in Programming Languages (PCAPL)

## Overview
The PCAPL directory focuses on parallel programming and OpenMP (Open Multi-Processing) concepts in C, demonstrating how to leverage multi-threaded processing for performance optimization and parallel algorithm implementations.

## Subdirectories

### Lab 1: OpenMP Fundamentals
Basics of parallel programming with OpenMP
- **q1**: Thread counting and parallel region identification
- **q2**: Dynamic thread configuration and thread communication
- **q3**: Parallel matrix initialization with work distribution
- **q4**: Parallel array addition with thread tracking
- **q5**: Parallel matrix addition with serial/parallel performance comparison
- **q6**: Serial vs parallel array summation with timing analysis

### Lab 2: Intermediate Parallel Operations
Advanced parallel matrix and vector operations
- **q1**: Serial vs parallel matrix addition with performance metrics
- **q2**: Matrix transformation with max/min operations per row
- **q3**: Binary complement and bit manipulation with parallel processing
- **q4**: Matrix-vector multiplication (Ax = b)
- **q5**: Parallel sections with array element squaring operations
- **q6**: Vector operations (addition, subtraction, multiplication) using parallel sections

### Lab 3: Advanced Parallel Concepts
Complex scheduling, synchronization, and algorithm optimization
- **q1**: Variable scope exploration (shared, private, firstprivate, lastprivate, reduction)
- **q2**: Synchronization mechanisms (master, atomic, critical sections)
- **q3**: Prime number detection with different scheduling strategies (static, dynamic, guided)
- **q4**: Parallel merge sort implementation with serial/parallel comparison

## Key Technologies
- **OpenMP** - Parallel programming API for C
- **Compiler Support**: GCC with `-fopenmp` flag
- **Concepts**: Thread management, work distribution, synchronization, scheduling strategies

## Purpose
This directory is part of Semester 5 coursework focusing on understanding parallel computing concepts through practical OpenMP implementations, comparing serial and parallel performance, and mastering thread synchronization and load balancing techniques.

