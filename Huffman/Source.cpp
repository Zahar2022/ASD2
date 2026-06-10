


#include <iostream>
#include <fstream>
#include "Huffman.h"

void createTestFile(const std::string& filename, const std::string& content) {
    std::ofstream file(filename);
    file << content;
    file.close();
    std::cout << "Created file: " << filename << std::endl;
    std::cout << "Content: " << content << std::endl;
}


int main() {
    setlocale(LC_ALL, "Russian");
    Huffman huffman;

    std::string inputFile = "input.txt";
    std::string encodedFile = "encoded.txt";
    std::string decodedFile = "decoded.txt";

    createTestFile(inputFile, "tomsk university");
    std::cout << std::endl;

    huffman.build(inputFile);
    huffman.print();

    double code = huffman.encode(inputFile, encodedFile);
    std::cout << "Compression coefficient: " << code << std::endl;

    if (huffman.decode(encodedFile, decodedFile)) {
        std::cout << "Decoding completed successfully" << std::endl;
        std::ifstream resultFile(decodedFile);
        std::string result;
        char ch;
        while (resultFile.get(ch)) {
            result += ch;
        }
        resultFile.close();

        std::cout << "Result: " << result << "\"" << std::endl;

        if (result == "tomsk university") {
            std::cout << "\n Test completed successfully" << std::endl;
        }
        else {
            std::cout << "\n Test failed" << std::endl;
        }
    }
    else {
        std::cout << "Decoding error" << std::endl;
    }

    return 0;
}