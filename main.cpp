#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>
#include <algorithm>
#include "sorts.h"

using namespace std;

#define RUN(x) { Run(#x, x, data, out); }

void Run(string method_name, bool(*p)(const vector<string>&, vector<string>&), const vector<string>& data, ofstream& out)
{
    vector<string> result;

    auto startPrep = chrono::system_clock::now();
    result = data;
    auto stopPrep = chrono::system_clock::now();
    auto timePrep = chrono::duration_cast<chrono::microseconds>(stopPrep - startPrep).count();

    auto startSort = chrono::system_clock::now();
    bool ok = false;

    try {
        ok = p(data, result);
    }
    catch (...) {
        cout << method_name << " crashed!" << endl;
        out << method_name << "," << data.size() << ",0,0,CRASHED\n";
        return;
    }

    auto stopSort = chrono::system_clock::now();
    auto timeSort = chrono::duration_cast<chrono::microseconds>(stopSort - startSort).count();

    bool isSorted = std::is_sorted(result.begin(), result.end());

    out << method_name << "," << data.size() << "," << timePrep << "," << timeSort << ","
        << (ok && isSorted ? "OK" : "FAILED") << "\n";

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

    ofstream out("results.csv");
    if (!out.is_open()) {
        cout << "Error: cannot create results.csv" << endl;
        return 1;
    }

    out << "Method,DatasetSize,PrepTime_mcs,SortTime_mcs,Status\n";
    cout << "Method;Size;PrepTime_mcs;SortTime_mcs;Status" << endl;

    vector<string> bestData = LoadData("best.txt");
    vector<string> worstData = LoadData("worst.txt");
    vector<string> avgData = LoadData("average.txt");
    vector<string> dupData = LoadData("duplicates.txt");

    vector<string> shellData = LoadData("Best_shellSort.txt");
    vector<string> heapData = LoadData("Heap_best.txt");
    vector<string> mergeData = LoadData("merge_test.txt");
    vector<string> quickData = LoadData("quick_test.txt");
    vector<string> currencyData = LoadData("currency.txt"); 

    vector<string> data;

    cout << "Best_"; data = bestData;
    RUN(shellSort); RUN(heapSort); RUN(quickSort); RUN(mergeSort); RUN(radixSort);

    cout << "Worst_"; data = worstData;
    RUN(shellSort); RUN(heapSort); RUN(quickSort); RUN(mergeSort); RUN(radixSort);

    cout << "Average_"; data = avgData;
    RUN(shellSort); RUN(heapSort); RUN(quickSort); RUN(mergeSort); RUN(radixSort);

    cout << "Duplicates_"; data = dupData;
    RUN(shellSort); RUN(heapSort); RUN(quickSort); RUN(mergeSort); RUN(radixSort);

    if (!shellData.empty()) {
        cout << "\n DATA: Best_shellSort.txt \n";
        data = shellData;
        Run("shellSort (Anya's Data)", shellSort, data, out);
        Run("heapSort (Anya's Data)", heapSort, data, out);
        Run("quickSort (Anya's Data)", quickSort, data, out);
        Run("mergeSort (Anya's Data)", mergeSort, data, out);
        Run("radixSort (Anya's Data)", radixSort, data, out);
    }

    if (!heapData.empty()) {
        cout << "\nDATA: Heap_best.txt\n";
        data = heapData;
        Run("shellSort (Altynai's Data)", shellSort, data, out);
        Run("heapSort (Altynai's Data)", heapSort, data, out);
        Run("quickSort (Altynai's Data)", quickSort, data, out);
        Run("mergeSort (Altynai's Data)", mergeSort, data, out);
        Run("radixSort (Altynai's Data)", radixSort, data, out);
    }

    if (!mergeData.empty()) {
        cout << "\n DATA: merge_test.txt \n";
        data = mergeData;
        Run("shellSort (Polina's Data)", shellSort, data, out);
        Run("heapSort (Polina's Data)", heapSort, data, out);
        Run("quickSort (Polina's Data)", quickSort, data, out);
        Run("mergeSort (Polina's Data)", mergeSort, data, out);
        Run("radixSort (Polina's Data)", radixSort, data, out);
    }

    if (!quickData.empty()) {
        cout << "\nDATA: quick_test.txt\n";
        data = quickData;
        Run("shellSort (Katya's Data)", shellSort, data, out);
        Run("heapSort (Katya's Data)", heapSort, data, out);
        Run("quickSort (Katya's Data)", quickSort, data, out);
        Run("mergeSort (Katya's Data)", mergeSort, data, out);
        Run("radixSort (Katya's Data)", radixSort, data, out);
    }

    if (!currencyData.empty()) {
        cout << "\nDATA: currency.txt\n";
        data = currencyData;
        Run("shellSort (David's Data)", shellSort, data, out);
        Run("heapSort (David's Data)", heapSort, data, out);
        Run("quickSort (David's Data)", quickSort, data, out);
        Run("mergeSort (David's Data)", mergeSort, data, out);
        Run("radixSort (David's Data)", radixSort, data, out);
    }

    out.close();
    cout << "\nResults saved to file results.csv!" << endl;

    return 0;
}