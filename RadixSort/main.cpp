#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include <fstream>
#include <string>


using namespace std;

string dataPath(const string& name) {
    string p = __FILE__;
    return p.substr(0, p.find_last_of("/\\") + 1) + name;
}

vector<int> readFromFile(const string& path) {
    ifstream in(path);
    if (!in.is_open()) {
        cout << "Не удалось открыть файл: " << path << endl;
        return {};
    }

    vector<int> a;
    int x;
    while (in >> x)
        a.push_back(x);
    return a;
}

void countNSortDigit(vector<int>& a, int exp) {
    vector <int> output(a.size());
    int count[10] = {0};
    
    for (int x: a)
        count[(x/exp)%10]++;
    
    for (int d =1; d<10; d++)
        count[d] += count[d-1];
    
    for (int i = (int)a.size() -1; i >= 0; i--)  {
        int d = (a[i] / exp) % 10;
        output[--count[d]] = a[i];
    }
    
    a = output;
}

void radixSort(vector<int>& a) {
    if (a.empty()) return;
    int maxVal = *max_element(a.begin(), a.end());
    
    for (int exp = 1; maxVal / exp > 0; exp*= 10)
        countNSortDigit(a, exp);
        
}





int main() {
    string path;
    cout << "Введите название файла: ";
    getline(cin, path);

    vector<int> a = readFromFile(dataPath(path));
    if (a.empty()) {
        cout << "Массив пустой или файл не прочитан" << endl;
        return 1;
    }
    
    
    auto start = std::chrono::steady_clock::now();
    radixSort(a);
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double, milli> radixTime = end - start;
    
    cout << "Radix sort: " << radixTime.count() << " мс" << endl;

    
    return EXIT_SUCCESS;
}
