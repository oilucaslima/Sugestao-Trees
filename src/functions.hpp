#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP
#include "structs.hpp"

void updateWord(string word, map <string,int> &wordHash, unordered_map <string,int> &allStopWords);

vector<pair <string,int>> returnHeap(map <string,int> wordHash, int j);

void cleanLine(string &line);

void makeHeap(vector<pair <string,int>> &heapWord);

void toCreateTree(map<string,int> wordHash, string nomeFile, ofstream &output);

string toLowercase(string str);

unordered_map <string,int> returnAllStopWord();

void returnHash();

bool TreeEmpty(Tree **t);

map<int,vector<pair <string,int>>> return_AllHeaps(map <string,int> wordHash);

Tree* binaryTree(vector<pair <string,int>> heapWord, bool deleteWord, string word);

void InsertTree(Tree **originalTree, Data record);

Data takeDados(vector<pair <string,int>> heapWord, int i);

int getIndex(AVL **originalAVL);

int getMaxIndex(int tamLeft, int tamRight);

void spinSimple_Left(AVL **originalAVL);

void spinDouble_Left(AVL **originalAVL);

void spinSimple_Right(AVL **originalAVL);

void spinDouble_Right(AVL **originalAVL);

void insertTree_AVL(AVL **originalAVL, Data record);

AVL* AVL_Tree(vector<pair <string,int>> heapWord, bool deleteWord, string word);

void saveOutput(ofstream &output, HistoryAllText vetor);

void saveWidthBinary(ofstream &file, Tree *root);

void saveWidthAVL(ofstream &file, AVL *root);

Huffman HuffmanTree(priority_queue<Huffman, vector<Huffman>, pair_maior> queueWords);

priority_queue<Huffman, vector<Huffman>, pair_maior> returnQueue(vector<pair <string,int>> heapWord);

priority_queue<Huffman, vector<Huffman>, pair_maior> returnQueueMore(vector<pair <string,int>> heapWord, string word);

void saveWidthHuffman(ofstream &output, Huffman root);

void decoderHuffman(Huffman *tree, string &code);

#endif
