# Huffman Coding
README FILE

AUTHORS
=======
Jason Rodriguez, 
Brendan Berlin

DESCRIPTION
===========
This C++ project consists of files that constructs a Binary Tree data structure to integrate a Huffman Coding's algorithm which is a method for lossless data compression, commonly used in file compression algorithms such as ZIP.
The Huffman Coding algorithm uses the binary tree to assign variable-length codes to different characters within a message such that more frequent characters have shorter codes, reducing the overall size of the encoded message.
The program consists of a Node class, Huffman Binary Tree class, HeapQueue class, and Vector implementation of a Complete Tree.

FEATURES
========
- Huffman Coding Algorithm: Implements Huffman Coding to compress input data to variable-length binary codes based on character frequency. 
- Compression: Compresses input data using the generated Huffman codes, reducing the overall size of the data.
- Serialized Tree: The structure of the tree (consisted of serialized code) is also printed in a post-order traversal with 'L' representing a leaf node and 'B' representing a branch node.
- Decompression: Decompresses previously compressed data (binary code) along with the assistance of the tree's structure (serialized code) to reconstruct the original input data without any loss.

DEPENDENCIES
============
This project relies on a C++ compiler that supports the C++11 standard or later.

COMPILATION
===========
To compile the program, use the following command: ```g++ -Wall -std=c++17 main.cpp HuffmanTree.cpp HuffmanBase.cpp```

INPUT
=====
The program includes a simple user interface to execute the following functions:
- Enter 'h' to read the list of commands to that the program includes
- Enter 'c' to use the mentioned features, and enter input when instructed
- Enter 'q' to quit the program

CODE STRUCTURE
==============
- 'main.cpp': Contains the user interface for interacting with the program.
- 'HuffmanBase.hpp' and 'HuffmanBase.cpp': Contains the abstract base class prototypes with pure virtual functions for the Huffman binary tree, to be inherited in 'HuffmanTree.hpp'. The header file also contains the Huffman Node class which consists of a Compare class for the HeapQueue. Definitions for the methods declared within the HuffmanNode class for basic operations of each node in the binary tree are in the source file.
- 'HuffmanTree.hpp' and 'HuffmanTree.cpp': Implemented the Huffman Binary Tree class from the derivation of the abstract class HuffmanTreeBase and consists of the compression, seralization, and decompressiong operations.
- 'HeapQueue.hpp': Contains the implementation of a Heap Queue from a Vector-based complete tree.

ACKNOWLEDGEMENTS
================
The project was inspired by the Huffman Coding algorithm, a fundamental process in data compression.
