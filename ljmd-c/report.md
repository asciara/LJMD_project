### Collaborative project on MD code optimization (Group 4) 

##### Team members: Alberto Cazzaniga, Celia Laurent, Antonio Sciarappa, Miguel Castellano.

#### 1. Introduction

For this project, we're given a simplified code to run molecular dynamics simulations in C and the goal is to implement a python interface along with a series of optimizations including parallelization schemes for MPI and OpenMP in a collaborative way, using continuous integration. 

#### 2. Work

The work developed during the project can be split in two parts: The realization of a Python interface in charge of calling the time-critical functions from C and the implementation of a bunch of optimizations to speed up the code plus the addition of both an MPI and OpenMP parallelization schemes aimed at providing a certain sense of scalability. 

For the first part, we wrote a python script that acted as an interface to the C code by implementing the same C functions in Python and calling only the time-critical functions from C by making use of ctypes and shared library handles.

For the second part, distributed memory parallelization was added by means of MPI directives into the code while shared memory multi-threading was enabled in a peculiar, more performant but also more memory consuming way using OpenMP pragmas. As for the optimizations, we implemented the in-lining of frequently called functions, re-formulation of expensive mathematical operations, vectorization and others.



