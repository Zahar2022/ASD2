

#include <iostream>
#include <vector>
#include <random>
#include <fstream>у
#include <string>
#include <chrono>



bool createFileWithRandomNumbers(const std::string& fileName, const int numbersCount, const int maxNumberValue) {
    std::ofstream file(fileName);
    if (!file.is_open()) {
        std::cout << "Couldn't open the file for writing" << std::endl;
        return false;
    } 

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, maxNumberValue);
    for (int i = 0; i < numbersCount; i++) {
        file << dis(gen) << std::endl;
    }
    file.close();

    if (!file) {
        std::cout << "Error of writing in file" << std::endl;
        return false;
    }

    return true;
};



bool isFileContainsSortedArray(const std::string& fileName) {
    std::ifstream file(fileName);
    if (!file.is_open()) {
        std::cout << "Couldn't open the file for reading" << std::endl;
        return false;
    }

    int currentNumber, secondNumber;
    file >> currentNumber;
    while (file >> secondNumber && !file.eof()) {
        if (secondNumber < currentNumber) {
            file.close();
            return false;
        }
        currentNumber = secondNumber;
    }
    file.close();
    return true;

};


void Splitting(const std::string& fileName1, const std::string& fileName3, const std::string& fileName4) {
    std::ofstream F[2] = { std::ofstream(fileName3), std::ofstream(fileName4) };
    std::ifstream A(fileName1);
    if (!A.is_open()) {
        std::cout << "Couldn't open the file for reading" << std::endl;
    }

    int n = 0, p = 1, x;
    while (A >> x && !A.eof()) {
        int i = 0;
        while (!A.eof() && i < p) {
            F[n] << x;
            i++;
        }
        n = 1 - n;
    }
    A.close();
    F[0].close();
    F[1].close();
}


void Merging(int p, const std::string& fileName1, const std::string& fileName2, const std::string& fileName3, const std::string& fileName4) {
    int x[2];
    std::ifstream S[2] = { std::ifstream(fileName3), std::ifstream(fileName4) };
    std::ofstream F[2] = { std::ofstream(fileName1), std::ofstream(fileName2) };
    int i, j, n = 0;
    while (!S[0].eof() && !S[1].eof()) {
        i = 0, j = 0;
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


void DirectMergingSort(const std::string& inputFile) {
    int p = 1;
    std::string F[2] = { "F0.txt", "F1.txt" };
    std::string S[2] = { "S0.txt", "S1.txt" };

    std::ifstream input(inputFile);
    if (!input.is_open()) {
        std::cout << "Couldn't open the file for reading" << std::endl;
    }

    std::ofstream F0(F[0]);
    std::ofstream F1(F[1]);
    if (!F0.is_open() || !F1.is_open()) {
        std::cout << "Couldn't open the files for writing" << std::endl;
    }

    Splitting(inputFile, F[0], F[1]);

    input.close();
    F0.close();
    F1.close();

    if (!F1.eof()) {
        while (true) {
            std::ifstream checkFile(F[1]);
            if (!checkFile.is_open() || checkFile.peek() == std::ifstream::traits_type::eof()) {
                break;
            }
            checkFile.close();

            std::ifstream F0Read(F[0]);
            std::ifstream F1Read(F[1]);

            std::ofstream S0(S[0]);
            std::ofstream S1(S[1]);

            Merging(p, S[0], S[1], F[0], F[1]);

            F0Read.close();
            F1Read.close();
            S0.close();
            S1.close();

            p *= 2;

            std::ifstream S0Reading(S[0]);
            std::ifstream S1Reading(S[1]);

            std::ofstream F0Writing(F[0]);
            std::ofstream F1Writing(F[1]);

            Merging(p, F[0], F[1], S[0], S[1]);

            S0Reading.close();
            S1Reading.close();
            F0Writing.close();
            F1Writing.close();


            p *= 2;
        }
    }
}



int createAndSortFile(const std::string& fileName,  const int numbersCount, const int maxNumberValue)
{
    if (!createFileWithRandomNumbers(fileName, numbersCount, maxNumberValue)) {
        return -1;
    }

    DirectMergingSort(fileName);

    if (!isFileContainsSortedArray(fileName)) {
        return -2;
    }

    return 1;
}

int main()
{
    std::string fileName = "file.txt";
    const int numbersCount = 20;
    const int maxNumberValue = 100;

    for (int i = 0; i < 10; i++) {
        switch (createAndSortFile(fileName, numbersCount, maxNumberValue)) {
        case 1:
            std::cout << "Test passed" << std::endl;
            break;

        case -1:
            std::cout << "Test failed: can't create file" << std::endl;
            break;

        case -2:
            std::cout << "Test failed: file isn't sorted" << std::endl;
            break;
        }
    }

    return 0;
}
// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
