#pragma once



#include <iostream>
#include <algorithm>
#include <vector>
#include "C:\\Gittyup Files\Repos\OOPLabs\BoolVector\BoolVector.h"
#include "fstream"

class Huffman
{
public:
    class Node
    {

    public:
        Node();

        ~Node();

        std::string stringifySymbols() const;
        void printHorizontal(Node* root, int marginLeft = 0, int levelSpacing = 4) const;
        int getFrequency() const;
        void setFrequency(int frequencyValue);
        BoolVector getSymbols() const;
        void setSymbols(const BoolVector& symbolsValue);
        Node* getLeft() const;
        Node* getRight() const;
        void setLeft(Node* leftValue);
        void setRight(Node* rightValue);



    private:
        BoolVector symbols = BoolVector(256, false);
        int frequency;
        Node* left = nullptr;
        Node* right = nullptr;

    };

public:
    Huffman() = default;
    ~Huffman();

    Node* getRoot() const;
    void print();
    void clear();
    void build(const std::string& fileName);
    double encode(const std::string& fileName, const std::string& encodedFileName);
    bool decode(const std::string& encodedText, std::string& decodedText);
    std::string encode(Node* node, const char symbol);
    char decode(Huffman::Node* node, std::ifstream& fileToRead);
    void clearNode(Node* node);

private:
    Node* m_root = nullptr;
};