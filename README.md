# Survival Inventory System in C

An educational C project designed to demonstrate fundamental data structures, search algorithms, sorting algorithms, and performance analysis through a survival-themed inventory management simulation.

## Features

* Dynamic inventory management using arrays
* Linked list implementation and manipulation
* Item insertion, removal, traversal, and search operations
* Linear search and binary search implementations
* Bubble Sort and Selection Sort algorithms
* Performance benchmarking and comparison counting
* Array versus linked list performance analysis
* Survival scenario simulation with inventory-based escape conditions

## Technical Concepts Demonstrated

### Data Structures

* Dynamic Array (Linear List)
* Singly Linked List

### Search Algorithms

* Linear Search
* Iterative Binary Search
* Recursive Binary Search

### Sorting Algorithms

* Bubble Sort (Alphabetical Order)
* Selection Sort (Priority Descending)

### Performance Analysis

* Comparison counting
* Execution time measurement using `clock()`
* Array versus linked list search benchmarking

## Project Structure

```text
survival-inventory-system-c/
├── src/
│   └── main.c
├── .gitignore
├── Makefile
└── README.md
```

## Requirements

* GCC or Clang
* Make

## Build

```bash
make
```

## Clean Build Files

```bash
make clean
```

## Run

```bash
./freefire
```

## Alternative Compilation

```bash
gcc -O2 -Wall -Wextra -o freefire src/main.c
./freefire
```

## Interactive Menu

```text
1) Display inventory (array)
2) Add item
3) Remove item
4) Sort by name (Bubble Sort)
5) Sort by priority (Selection Sort)
6) Linear search by name
7) Iterative binary search
8) Recursive binary search
9) Display linked list
10) Insert into linked list
11) Remove from linked list
12) Benchmark array vs linked list search
13) Attempt island escape
0) Exit
```

## Search and Sorting

### Linear Search

Performs sequential traversal of the inventory array.

### Binary Search

Available in both iterative and recursive implementations.

Requirement:

* Data must be sorted by name before performing binary search.

### Bubble Sort

Sorts items alphabetically while counting comparisons.

### Selection Sort

Sorts items by descending priority.

## Array vs Linked List Comparison

The benchmark module compares:

* Search position
* Number of comparisons
* Execution time

This demonstrates practical differences between contiguous memory structures and linked structures.

## Educational Notes

### Arrays

Advantages:

* O(1) indexed access
* Cache-friendly memory layout

Disadvantages:

* Insertions and removals may require shifting elements

### Linked Lists

Advantages:

* Efficient local insertions and removals

Disadvantages:

* O(n) sequential access
* Lower cache locality

### Binary Search

Binary search requires:

* Sorted data
* Random-access structure

For this reason, it is applied only to the array implementation.

## Learning Objectives

This project was developed to practice:

* Data structures in C
* Algorithm analysis
* Search and sorting algorithms
* Performance measurement
* Memory organization
* Problem solving using C

## License

MIT License
