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

    vector<string> bestShellData = LoadData("best_shell.txt");
    vector<string> bestHeapData = LoadData("best_heap.txt");
    vector<string> bestQuickData = LoadData("best_quick.txt");
    vector<string> bestMergeData = LoadData("best_merge.txt");
    vector<string> bestRadixData = LoadData("best_radix.txt");

    vector<string> avgShellData = LoadData("average_shell.txt");
    vector<string> avgHeapData = LoadData("average_heap.txt");
    vector<string> avgQuickData = LoadData("average_quick.txt");
    vector<string> avgMergeData = LoadData("average_merge.txt");
    vector<string> avgRadixData = LoadData("average_radix.txt");

    vector<string> worstShellData = LoadData("worst_shell.txt");
    vector<string> worstHeapData = LoadData("worst_heap.txt");
    vector<string> worstQuickData = LoadData("worst_quick.txt");
    vector<string> worstMergeData = LoadData("worst_merge.txt");
    vector<string> worstRadixData = LoadData("worst_radix.txt");

    vector<string> data;

    cout << "Basic_Best_"; data = bestData;
    RUN(shellSort); RUN(heapSort); RUN(quickSort); RUN(mergeSort); RUN(radixSort);

    cout << "Basic_Worst_"; data = worstData;
    RUN(shellSort); RUN(heapSort); RUN(quickSort); RUN(mergeSort); RUN(radixSort);

    cout << "Basic_Average_"; data = avgData;
    RUN(shellSort); RUN(heapSort); RUN(quickSort); RUN(mergeSort); RUN(radixSort);

    cout << "Basic_Duplicates_"; data = dupData;
    RUN(shellSort); RUN(heapSort); RUN(quickSort); RUN(mergeSort); RUN(radixSort);

    cout << "\nBEST CASES " << endl;

    if (!bestShellData.empty()) { cout << "\nDATA: best_shell.txt\n"; data = bestShellData; RUN(shellSort); RUN(heapSort); RUN(quickSort); RUN(mergeSort); RUN(radixSort); }
    if (!bestHeapData.empty()) { cout << "\nDATA: best_heap.txt\n";  data = bestHeapData;  RUN(shellSort); RUN(heapSort); RUN(quickSort); RUN(mergeSort); RUN(radixSort); }
    if (!bestQuickData.empty()) { cout << "\nDATA: best_quick.txt\n"; data = bestQuickData; RUN(shellSort); RUN(heapSort); RUN(quickSort); RUN(mergeSort); RUN(radixSort); }
    if (!bestMergeData.empty()) { cout << "\nDATA: best_merge.txt\n"; data = bestMergeData; RUN(shellSort); RUN(heapSort); RUN(quickSort); RUN(mergeSort); RUN(radixSort); }
    if (!bestRadixData.empty()) { cout << "\nDATA: best_radix.txt\n"; data = bestRadixData; RUN(shellSort); RUN(heapSort); RUN(quickSort); RUN(mergeSort); RUN(radixSort); }

    cout << "\nAVERAGE CASES" << endl;

    if (!avgShellData.empty()) { cout << "\nDATA: average_shell.txt\n"; data = avgShellData; RUN(shellSort); RUN(heapSort); RUN(quickSort); RUN(mergeSort); RUN(radixSort); }
    if (!avgHeapData.empty()) { cout << "\nDATA: average_heap.txt\n";  data = avgHeapData;  RUN(shellSort); RUN(heapSort); RUN(quickSort); RUN(mergeSort); RUN(radixSort); }
    if (!avgQuickData.empty()) { cout << "\nDATA: average_quick.txt\n"; data = avgQuickData; RUN(shellSort); RUN(heapSort); RUN(quickSort); RUN(mergeSort); RUN(radixSort); }
    if (!avgMergeData.empty()) { cout << "\nDATA: average_merge.txt\n"; data = avgMergeData; RUN(shellSort); RUN(heapSort); RUN(quickSort); RUN(mergeSort); RUN(radixSort); }
    if (!avgRadixData.empty()) { cout << "\nDATA: average_radix.txt\n"; data = avgRadixData; RUN(shellSort); RUN(heapSort); RUN(quickSort); RUN(mergeSort); RUN(radixSort); }

    cout << "\n WORST CASES " << endl;

    if (!worstShellData.empty()) { cout << "\nDATA: worst_shell.txt\n"; data = worstShellData; RUN(shellSort); RUN(heapSort); RUN(quickSort); RUN(mergeSort); RUN(radixSort); }
    if (!worstHeapData.empty()) { cout << "\nDATA: worst_heap.txt\n";  data = worstHeapData;  RUN(shellSort); RUN(heapSort); RUN(quickSort); RUN(mergeSort); RUN(radixSort); }
    if (!worstQuickData.empty()) { cout << "\nDATA: worst_quick.txt\n"; data = worstQuickData; RUN(shellSort); RUN(heapSort); RUN(quickSort); RUN(mergeSort); RUN(radixSort); }
    if (!worstMergeData.empty()) { cout << "\nDATA: worst_merge.txt\n"; data = worstMergeData; RUN(shellSort); RUN(heapSort); RUN(quickSort); RUN(mergeSort); RUN(radixSort); }
    if (!worstRadixData.empty()) { cout << "\nDATA: worst_radix.txt\n"; data = worstRadixData; RUN(shellSort); RUN(heapSort); RUN(quickSort); RUN(mergeSort); RUN(radixSort); }

    cout << "\n\n";
    cout << "STABILITY & ROBUSTNESS TESTS\n";
    cout << "\n";

    vector<string> emptyData = LoadData("empty.txt");
    if (emptyData.empty()) {
        cout << "\n[TEST] Empty File\n";
        Run("shellSort (Empty)", shellSort, emptyData, out);
        Run("heapSort (Empty)", heapSort, emptyData, out);
        Run("quickSort (Empty)", quickSort, emptyData, out);
        Run("mergeSort (Empty)", mergeSort, emptyData, out);
        Run("radixSort (Empty)", radixSort, emptyData, out);
    }

    vector<string> stabilityData = LoadData("stability_test.txt");
    if (!stabilityData.empty()) {
        cout << "\n[TEST] Stability (Checking relative order)\n";

        vector<string> qResult = stabilityData;
        quickSort(stabilityData, qResult);
        cout << "QuickSort result: ";
        for (int i = 0; i < 8; ++i) cout << qResult[i] << " "; 
        cout << "...\n";

        vector<string> mResult = stabilityData;
        mergeSort(stabilityData, mResult);
        cout << "MergeSort result: ";
        for (int i = 0; i < 8; ++i) cout << mResult[i] << " "; 
        cout << "...\n";

        Run("shellSort (Stability)", shellSort, stabilityData, out);
        Run("heapSort (Stability)", heapSort, stabilityData, out);
        Run("quickSort (Stability)", quickSort, stabilityData, out);
        Run("mergeSort (Stability)", mergeSort, stabilityData, out);
        Run("radixSort (Stability)", radixSort, stabilityData, out);
    }

    vector<string> allSameData = LoadData("all_same.txt");
    if (!allSameData.empty()) {
        cout << "\n[TEST] All Identical Elements (Size = " << allSameData.size() << ")\n";

        Run("shellSort (AllSame)", shellSort, allSameData, out);
        Run("heapSort (AllSame)", heapSort, allSameData, out);
        Run("quickSort (AllSame)", quickSort, allSameData, out);
        Run("mergeSort (AllSame)", mergeSort, allSameData, out);
        Run("radixSort (AllSame)", radixSort, allSameData, out);
    }

    cout << "\n\n";
    cout << " STARTING SIZE TESTS (100 - 50000) \n";
    cout << "\n";

    vector<string> fullData = LoadData("random_words_10000.txt");

    if (!fullData.empty()) {
        vector<int> sizes = { 100, 500, 1000, 2500, 5000, 7500, 10000, 15000, 20000, 25000, 30000, 35000, 40000, 45000, 50000 };

        for (int size : sizes) {
            if (size > fullData.size()) continue;

            vector<string> currentData(fullData.begin(), fullData.begin() + size);

            cout << "\n SIZE: " << size << " " << endl;

            Run("shellSort (Size_" + to_string(size) + ")", shellSort, currentData, out);
            Run("heapSort (Size_" + to_string(size) + ")", heapSort, currentData, out);
            Run("quickSort (Size_" + to_string(size) + ")", quickSort, currentData, out);
            Run("mergeSort (Size_" + to_string(size) + ")", mergeSort, currentData, out);
            Run("radixSort (Size_" + to_string(size) + ")", radixSort, currentData, out);
        }
    }
    else {
        cout << "ERROR: File random_words_10000.txt not found or is empty!" << endl;
    }

    out.close();
    cout << "\nResults saved to file results.csv!" << endl;

    return 0;
}