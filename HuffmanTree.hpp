#ifndef HUFFMANTREE_H
#define HUFFMANTREE_H

#include "HuffmanBase.hpp"
#include "HeapQueue.hpp"
#include <map>

class HuffmanTree : public HuffmanTreeBase {
private: 
  HuffmanNode* _root;
protected:
  void createCodes(HuffmanNode *node, std::string code, std::map<char, std::string> &codes);
  std::string serialize(HuffmanNode *node, std::string result) const;
  void postorderDelete(HuffmanNode* node);
public:
  HuffmanTree();
  ~HuffmanTree();
  std::string compress(const std::string inputStr);
  std::string serializeTree() const;
  std::string decompress(const std::string inputCode, const std::string serializedTree);
};

// Main functions for users
void help();
void input(HuffmanTree &t);

#endif