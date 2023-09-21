#include "library.hpp"

using namespace std;

typedef struct Data{
    string word;
    int ocorrencia;   
}Data;

typedef struct Tree{
    Data infos;
    Tree *right, *left;
}Tree;

typedef struct AVL{
    Data infos;
    AVL *sonRight, *sonLeft;
    int index;
}AVL;

typedef struct Huffman{
    string nick;
    string code;
    int tam;
    int occurrences;
    Huffman *right, *left;
}Huffman;

typedef struct ResultWordResearch{
    Data wordResearch;
    Tree* treeBINARY;
    AVL* treeAVL;
    Huffman treeHuffman;
}ResultWordResearch;

typedef struct HistoryAllText{
    string nameFile;
    vector<ResultWordResearch> HistoryAllWord;
}HistoryAllText;

struct pair_maior{
  bool operator()(const Huffman &x, const Huffman & y) const {
    return x.occurrences > y.occurrences;
  }
};