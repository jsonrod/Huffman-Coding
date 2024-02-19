// Jason Rodriguez - U16884123
// This program implements a binary tree as a max-heap using a priority queue to compress, decompress, serialize a given string according to
// the frequency of each character occurances. 
// I collaborated with Brendan Berlin on this project on a partial amount of some of the functions.

#include "HuffmanTree.hpp"
#include "HeapQueue.hpp"
#include <map>
#include <stack>
#include <iostream>

HuffmanTree::HuffmanTree() : _root(nullptr) {}

// Destructor uses post order delete helper function to free all memory allocated on the heap.
HuffmanTree::~HuffmanTree() {
  postorderDelete(_root);
  _root = nullptr;
}

// Deallocates space for all nodes in tree in post order traversal.
void HuffmanTree::postorderDelete(HuffmanNode* node) {
  if (node->left != nullptr) {
    postorderDelete(node->left);
  }
  if (node->right != nullptr) {
    postorderDelete(node->right);
  }
  delete node;
}

std::string HuffmanTree::compress(const std::string inputStr) {
  
  // Map is created to contain a list of each character from the input string along with their frequencies (# of occurances)  
  std::map<char, int> map;
  for (const char &c : inputStr) {
    if (map.find(c) == map.end()) {
      map.insert({c, 1});
    }
    else {
      map[c]++;
    }
  }

  
  HeapQueue<HuffmanNode*, HuffmanNode::Compare> priorityQueue;

  // Create tree nodes and insert in heap queue sorted by frequency   
  for (auto it = map.begin(); it != map.end(); ++it) {
    HuffmanNode *newNode = new HuffmanNode(it->first, it->second);
    priorityQueue.insert(newNode);
  }

  // Create tree by popping the two first nodes containing the smallest frequencies at a time and assign each to a parent
  // containing the sum of their frequencies. This process repeats itself until one node is left in the tree.
  while (priorityQueue.size() != 1) {
    HuffmanNode *left = priorityQueue.min();
    priorityQueue.removeMin();
    HuffmanNode *right = priorityQueue.min();
    priorityQueue.removeMin();

    int newFrequency = left->getFrequency() + right->getFrequency();
    HuffmanNode *newNode = new HuffmanNode('\0', newFrequency);

    newNode->left = left;
    left->parent = newNode;
    newNode->right = right;
    right->parent = newNode;
    priorityQueue.insert(newNode);
  }
  // Last node in queue is assigned as the root of the tree.
  _root = priorityQueue.min();
  priorityQueue.removeMin();

  // New map is created to contain a list of each character and their corresponding binary values from tree traversals.
  std::map<char, std::string> codes;
  createCodes(_root, "", codes);
  
  // Create binary string from map using the original input string.
  std::string result = "";
  for (const char &c : inputStr) {
    if (codes.find(c) != codes.end()) {
      result += codes[c];
    }
  }

  return result;

}

// Helper function that creates the binary representation for each character in tree dependent upon traversal routes.
void HuffmanTree::createCodes(HuffmanNode* node, std::string code, std::map<char, std::string> &codes) {
  if (node->isLeaf()) {
    codes.insert({node->getCharacter(), code});
  }
  if (node->left != nullptr) {
    createCodes(node->left, code + "0", codes);
  }
  if (node->right != nullptr) {
    createCodes(node->right, code + "1", codes);
  }
}

// serializeTree function uses serialize helper function to traverse in post order.
std::string HuffmanTree::serializeTree() const {
  std::string result = serialize(_root, "");
  return result;
}

// The isLeaf and isBranch conditions follow the traversal calls in a post order fashion
std::string HuffmanTree::serialize(HuffmanNode *node, std::string result) const {
  
  if (node->left != nullptr) {
    result = serialize(node->left, result);
  }
  if (node->right != nullptr) {
    result = serialize(node->right, result);
  }
  if (node->isLeaf()) {
    result += "L";
    result += node->getCharacter();
  }
  if (node->isBranch()) {
    result += "B";
  }
  return result;
}

std::string HuffmanTree::decompress(const std::string inputCode, const std::string serializedTree) {
  // Create temporary stack to assist with building the tree with huffman nodes from serialized string
  std::stack<HuffmanNode *> nodeStack;
  for (auto it = serializedTree.begin(); it != serializedTree.end(); ++it) {
    // If a leaf is encountered, the character to the right of it will be inserted into a node and added onto the stack
    if (*it == 'L') {
      ++it;
      HuffmanNode *newNode = new HuffmanNode(*it, 0);
      nodeStack.push(newNode);
    }
    // If a branch is encountered, the right child takes precedence on the top value of the stack and then the left.
    // This is done because the serialized strings come in a post order fashion.
    else if (*it == 'B') {
      HuffmanNode *right = nodeStack.top();
      nodeStack.pop();
      HuffmanNode *left = nodeStack.top();
      nodeStack.pop();
      HuffmanNode *branch = new HuffmanNode('\0', 0, nullptr, left, right);
      right->parent = branch;
      left->parent = branch;
      nodeStack.push(branch);
    }
  }
  // Root points to the last remaining node on the stack and empties the stack.
  _root = nodeStack.top();
  nodeStack.pop();

  // Create original string by following the path of the given binary string until each character is approached. 
  std::string outStr = "";
  HuffmanNode *cur = _root;
  for (const char &c : inputCode) {
    if (c == '0') {
      cur = cur->left;
    }
    else if (c == '1') {
      cur = cur->right;
    }
    if (cur->isLeaf()) {
      outStr += cur->getCharacter();
      cur = _root;
    }
  }
  return outStr;
}

// Main functions for user
void help() {
	std::cout << "List of operation codes:" << std::endl;
	std::cout <<"\t'h' for help" << std::endl;
	std::cout <<"\t'c' for compression and serialization of data" << std::endl;;
	std::cout <<"\t'q' for quit" << std::endl;
}

void input(HuffmanTree &t) {
  // Accept input
  std::string str;
  std::cout << "Enter the message for compression and serialization: ";
  getline(std::cin, str);

  // Compression
  std::cout << std::endl;
  std::cout << "Compressed form: ";
  std::cout << t.compress(str) << std::endl;

  // Serialization
  std::cout << std::endl;
  std::cout << "Serialization of tree form: ";
  std::cout << t.serializeTree() << std::endl;

  // Decompression
  std::cout << std::endl;
  std::cout << "Decompressing back to original form: ";
  std::cout << t.decompress(t.compress(str), t.serializeTree()) << std::endl;

}
