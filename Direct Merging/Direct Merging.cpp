

#include <iostream>
#include <vector>
#include <random>
#include <fstream>
#include <string>
#include <chrono>



bool createFileWithRandomNumbers(std::string& fileName, const int numbersCount, const int maxNumberValue) {
    std::ofstream file(fileName);
    if (!file.is_open()) {
        std::cout << "Couldn't open the file for writing" << std::endl;
        return false;
    } 

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, maxNumberValue);
    for (int i = 0; i < numbersCount; i++) {
        file << dis(gen) << " ";
    }
    file.close();

    if (!file) {
        std::cout << "Error of writing in file" << std::endl;
        return false;
    }

    return true;
};


bool IsEndOfCycle(std::string& file2) {
    std::ifstream f2(file2);
    int sym;
    bool IsCycleEnded = !(f2 >> sym);
    if (!(f2 >> sym)) {
        f2.close();
        return false;
    }
     f2.close();
    return true;
}


bool isFileContainsSortedArray(const std::string& fileName) {
    std::string sym;
    std::ifstream file;
    file.open(fileName);
    if (!file.is_open()) {
        std::cout << "Couldn't open the file for reading" << std::endl;
        return false;
    }

    int currentNumber = 0, previousNumber = -100000000;
    while (!file.eof()) {
        sym = " ";
        file >> sym;
        if (sym != " ") {
            currentNumber = stoi(sym);
            if (currentNumber < previousNumber) {
                return false;
            }
            previousNumber = currentNumber;
        }
    }
    return true;
};


void Splitting(std::string& filename, std::string& fileSplit1, std::string& fileSplit2)
{
    std::ofstream fileSplit[2];
    fileSplit[0].open(fileSplit1);
    fileSplit[1].open(fileSplit2);
    std::ifstream file(filename);

    int n = 0, x, i;
    file >> x;
    while (!file.eof())
    {
        i = 0;
        while (!file.eof() && i < 1)
        {
            fileSplit[n] << x << " ";
            file >> x;
            i++;
        }
        n = 1 - n;
    }
    file.close();
    fileSplit[0].close();
    fileSplit[1].close();
}


void Merging(const int p, std::string& fileName1, std::string& fileName2, std::string& fileName3, std::string& fileName4) {
    int x[2];
  //  std::ifstream S[2] = { std::ifstream(fileName1), std::ifstream(fileName2) };
   // std::ofstream F[2] = { std::ofstream(fileName3), std::ofstream(fileName4) };
    std::ifstream S[2];
    std::ofstream F[2];
    S[0].open(fileName1);
    S[1].open(fileName2);
    F[0].open(fileName3);
    F[1].open(fileName4);

    int n = 0;
    S[0] >> x[0];
    S[1] >> x[1];
    while (!S[0].eof() && !S[1].eof()) {
        int i = 0, j = 0;
        while (!S[0].eof() && !S[1].eof() && i < p && j < p) {
            if (x[0] < x[1]) {
                F[n] << x[0] << " ";
                S[0] >> x[0];
                i++;
            }
            else {
                F[n] << x[1] << " ";
                S[1] >> x[1];
                j++;
            }
        }
        while (!S[0].eof() && i < p) {
            F[n] << x[0] << " ";
            S[0] >> x[0];
            i++;
        }
        while (!S[1].eof() && j < p) {
            F[n] << x[1] << " ";
            S[1] >> x[1];
            j++;
        }
        n = 1 - n;
    }

    while (!S[0].eof()) {
        F[n] << x[0] << " ";
        S[0] >> x[0];
    }

    while (!S[1].eof()) {
        F[n] << x[1] << " ";
        S[1] >> x[1];
    }
    
    S[0].close();
    S[1].close();
    F[0].close();
    F[1].close();
}


void DirectMergingSort(std::string& inputFile) {
    int p = 1;
    std::string F[2] = { "F0.txt", "F1.txt" };
    std::string S[2] = { "S0.txt", "S1.txt" };
 

    Splitting(inputFile, F[0], F[1]);


    while (IsEndOfCycle(F[1])) {

        Merging(p, F[0], F[1], S[0], S[1]);

            p *= 2;

           Merging(p, S[0], S[1], F[0], F[1]);

            p *= 2;
    }
}



int createAndSortFile(std::string& fileName,  const int numbersCount, const int maxNumberValue)
{
    if (!createFileWithRandomNumbers(fileName, numbersCount, maxNumberValue)) {
        return -1;
    }

    DirectMergingSort(fileName);

    if (!isFileContainsSortedArray("F0.txt")) {
        return -2;
    }

    return 1;
}


int main()
{
    std::string fileName = "file.txt";
    const int numbersCount = 20;
    const int maxNumberValue = 10;

    createAndSortFile(fileName, numbersCount, maxNumberValue);

  
    return 0;

}

