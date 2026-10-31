#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>
#include <algorithm>
#include "sorts.h"

using namespace std;

#define RUN(x) { Run(#x, x, data); }

void Run(string method_name, bool(*p)(const vector<string>&, vector<string>&), const vector<string>& data)
{
    vector<string> result;

    auto startPrep = chrono::system_clock::now();
    result = data;
    auto stopPrep = chrono::system_clock::now();
    auto timePrep = chrono::duration_cast<chrono::microseconds>(stopPrep - startPrep).count();

    auto startSort = chrono::system_clock::now();
    bool ok = p(data, result);
    auto stopSort = chrono::system_clock::now();
    auto timeSort = chrono::duration_cast<chrono::microseconds>(stopSort - startSort).count();

    bool isSorted = std::is_sorted(result.begin(), result.end());

    cout << method_name << ";" << data.size() << ";" << timePrep << ";" << timeSort << ";"
        << (ok && isSorted ? "OK" : "FAILED") << endl;
}

vector<string> LoadData(const string& filename) {
    vector<string> data;
    ifstream file(filename);
    string line;
    while (getline(file, line)) data.push_back(line);
    return data;
}

int main() {
    setlocale(LC_ALL, "Russian");
    cout << "Method;Size;PrepTime_mcs;SortTime_mcs;Status" << endl;

    vector<string> bestData = LoadData("best.txt");
    vector<string> worstData = LoadData("worst.txt");
    vector<string> avgData = LoadData("average.txt");
    vector<string> dupData = LoadData("duplicates.txt");

    cout << "Best_";
    vector<string> data = bestData;
    RUN(shellSort); RUN(heapSort); RUN(quickSortbyBorschevskaya); RUN(mergeSort); RUN(radixSort);

    cout << "Worst_";
    data = worstData;
    RUN(shellSort); RUN(heapSort); RUN(quickSortbyBorschevskaya); RUN(mergeSort); RUN(radixSort);

    cout << "Average_";
    data = avgData;
    RUN(shellSort); RUN(heapSort); RUN(quickSortbyBorschevskaya); RUN(mergeSort); RUN(radixSort);

    cout << "Duplicates_";
    data = dupData;
    RUN(shellSort); RUN(heapSort); RUN(quickSortbyBorschevskaya); RUN(mergeSort); RUN(radixSort);

    return 0;
}