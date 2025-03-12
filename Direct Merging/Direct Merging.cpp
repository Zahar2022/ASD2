

#include <iostream>
#include <vector>
#include <random>
#include <fstream>
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


void Splitting(const std::string& fileName1, const std::string& fileName2, const std::string& fileName3, const std::string& fileName4) {
    std::ofstream F[2] = { std::ofstream(fileName3), std::ofstream(fileName4) };
    std::ifstream A(fileName1);
    if (!A.is_open()) {
        std::cout << "Couldn't open the file for reading" << std::endl;
    }
    int n = 0, p = 1, x;
    while (!A.eof()) {
        int i = 0;
        while (!A.eof() && i < p) {
            A >> x;
            F[n] << x;
            i++;
        }
        n = 1 - n;
    }
    A.close();
    F[0].close();
    F[1].close();
}

void Merging(const std::string& fileName1, const std::string& fileName2, const std::string& fileName3, const std::string& fileName4){
    int x[2];
    std::ifstream S[2] = { std::ifstream(fileName3), std::ifstream(fileName4) };
    std::ofstream F[2] = { std::ofstream(fileName1), std::ofstream(fileName2) };
    int i, j, n = 0, p = 1;
    while (!S[0].eof() && !S[1].eof()) {
        i = 0, j = 0;
        while (!S[0] && !S[1].eof() && i < p && j < p) {
            if (x[0] < x[1]) {
                S[0] >> x[0];
                F[n] << x[0] << " ";
                i++;
            }
            else {
                S[1] >> x[1];
                F[n] << x[1] << " ";
                j++;
            }
            while (!S[0].eof() && i < p) {
                S[0] >> x[0];
                F[n] << x[0] << " ";
                i++;
            }
            while (!S[1].eof() && j < p) {
                S[1] >> x[1];
                F[n] << x[1] << " ";
                j++;
            }
            n = 1 - n;
        }
    }
    while (!S[0].eof()) {
        S[0] >> x[0];
        F[n] << x[0] << " ";
    }
    while (!S[1].eof()) {
        S[1] >> x[1];
        F[n] << x[1] << " ";
    }

    S[0].close();
    S[1].close();
    F[0].close();
    F[1].close();
}

void sortFile(std::string& fileName) {
    


}


int createAndSortFile(const std::string& fileName, const int numbersCount, const int maxNumberValue)
{
    if (!createFileWithRandomNumbers(fileName, numbersCount, maxNumberValue)) {
        return -1;
    }

    //sortFile(fileName); //Вызов вашей функции сортировки

    if (!isFileContainsSortedArray(fileName)) {
        return -2;
    }

    return 1;
}

int main()
{
    std::string fileName = "file.txt";
    const int numbersCount = 1000000;
    const int maxNumberValue = 100000;

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
