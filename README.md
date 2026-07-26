# Cache Manager

A custom cache management system implemented with a FIFO doubly linked list, hash table, and binary search tree to enable efficient insertion, retrieval, eviction, and range-based queries.

## Overview

This project implements a custom cache manager designed around multiple data structures, where each component addresses a different performance requirement.

## Data Structures

### FIFO Doubly Linked List
- Maintains the order of cached entries.
- Handles cache eviction by removing the oldest entry.
- Supports:
  - O(1) insertion
  - O(1) removal

### Hash Table
- Provides fast access to cached values.
- Uses key-based lookup.
- Supports:
  - Average O(1) lookup
  - Average O(1) insertion

### Binary Search Tree
- Maintains ordered cache keys.
- Enables efficient range queries.
- Supports:
  - Average O(log n) search
  - Average O(log n) insertion

## Design Decisions

Each data structure was selected to complement the limitations of the others:
- The linked list provides efficient ordering and eviction.
- The hash table provides fast direct access.
- The binary search tree enables ordered operations that hash tables cannot support.

## Technologies

- C++
- Data Structures & Algorithms
- Object-Oriented Programming

## Key Takeaways

Through this project, I strengthened my understanding of how data structures can be combined to build efficient systems and how engineering tradeoffs impact performance.