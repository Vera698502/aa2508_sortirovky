#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>
#include <algorithm>
#include "sorts.h"

using namespace std;

vector<string> shellSortWrap(const vector<string>& data) {
    vector<string> result;
    shellSort(data, result);
    return result;
}

vector<string> heapSortWrap(const vector<string>& data) {
    vector<string> result;
    heapSort(data, result);
    return result;
}

vector<string> quickSortWrap(const vector<string>& data) {
    vector<string> result;
    quickSort(data, result);
    return result;
}

vector<string> mergeSortWrap(const vector<string>& data) {
    vector<string> result;
    mergeSort(data, result);
    return result;
}

vector<string> radixSortWrap(const vector<string>& data) {
    vector<string> result;
    radixSort(data, result);
    return result;
}

void Run(string method_name, vector<string>(*p)(const vector<string>&), vector<string> data, ofstream& out)
{
    auto startPrep = chrono::system_clock::now();
    vector<string> dataForSort = data;
    auto stopPrep = chrono::system_clock::now();
    auto timePrep = chrono::duration_cast<chrono::microseconds>(stopPrep - startPrep).count();

    auto startSort = chrono::system_clock::now();
    vector<string> result;
    bool ok = false;

    try {
        result = p(dataForSort); 
        ok = true;
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

    cout << "   [Отсортировано: ";
    int limit = min((int)result.size(), 10);
    for (int i = 0; i < limit; ++i) cout << result[i] << " ";
    if (result.size() > 10) cout << "...";
    cout << "]" << endl;
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
    if (!out.is_open()) { cout << "Error!" << endl; return 1; }

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

    cout << "Best_";
    Run("shellSort", shellSortWrap, bestData, out);
    Run("heapSort", heapSortWrap, bestData, out);
    Run("quickSort", quickSortWrap, bestData, out);
    Run("mergeSort", mergeSortWrap, bestData, out);
    Run("radixSort", radixSortWrap, bestData, out);

    cout << "Worst_";
    Run("shellSort", shellSortWrap, worstData, out);
    Run("heapSort", heapSortWrap, worstData, out);
    Run("quickSort", quickSortWrap, worstData, out);
    Run("mergeSort", mergeSortWrap, worstData, out);
    Run("radixSort", radixSortWrap, worstData, out);

    cout << "Average_";
    Run("shellSort", shellSortWrap, avgData, out);
    Run("heapSort", heapSortWrap, avgData, out);
    Run("quickSort", quickSortWrap, avgData, out);
    Run("mergeSort", mergeSortWrap, avgData, out);
    Run("radixSort", radixSortWrap, avgData, out);

    cout << "Duplicates_";
    Run("shellSort", shellSortWrap, dupData, out);
    Run("heapSort", heapSortWrap, dupData, out);
    Run("quickSort", quickSortWrap, dupData, out);
    Run("mergeSort", mergeSortWrap, dupData, out);
    Run("radixSort", radixSortWrap, dupData, out);

    if (!shellData.empty()) {
        cout << "\n DATA: Best_shellSort.txt \n";
        Run("shellSort (Anya)", shellSortWrap, shellData, out);
        Run("heapSort (Anya)", heapSortWrap, shellData, out);
        Run("quickSort (Anya)", quickSortWrap, shellData, out);
        Run("mergeSort (Anya)", mergeSortWrap, shellData, out);
        Run("radixSort (Anya)", radixSortWrap, shellData, out);
    }

    if (!heapData.empty()) {
        cout << "\nDATA: Heap_best.txt\n";
        Run("shellSort (Altynai)", shellSortWrap, heapData, out);
        Run("heapSort (Altynai)", heapSortWrap, heapData, out);
        Run("quickSort (Altynai)", quickSortWrap, heapData, out);
        Run("mergeSort (Altynai)", mergeSortWrap, heapData, out);
        Run("radixSort (Altynai)", radixSortWrap, heapData, out);
    }

    if (!mergeData.empty()) {
        cout << "\n DATA: merge_test.txt \n";
        Run("shellSort (Polina)", shellSortWrap, mergeData, out);
        Run("heapSort (Polina)", heapSortWrap, mergeData, out);
        Run("quickSort (Polina)", quickSortWrap, mergeData, out);
        Run("mergeSort (Polina)", mergeSortWrap, mergeData, out);
        Run("radixSort (Polina)", radixSortWrap, mergeData, out);
    }

    if (!quickData.empty()) {
        cout << "\nDATA: quick_test.txt\n";
        Run("shellSort (Katya)", shellSortWrap, quickData, out);
        Run("heapSort (Katya)", heapSortWrap, quickData, out);
        Run("quickSort (Katya)", quickSortWrap, quickData, out);
        Run("mergeSort (Katya)", mergeSortWrap, quickData, out);
        Run("radixSort (Katya)", radixSortWrap, quickData, out);
    }

    if (!currencyData.empty()) {
        cout << "\nDATA: currency.txt\n";
        Run("shellSort (David)", shellSortWrap, currencyData, out);
        Run("heapSort (David)", heapSortWrap, currencyData, out);
        Run("quickSort (David)", quickSortWrap, currencyData, out);
        Run("mergeSort", mergeSortWrap, currencyData, out);
        Run("radixSort", radixSortWrap, currencyData, out);
    }

    out.close();
    cout << "\nResults saved to file results.csv!" << endl;
    return 0;
}