#include <vector>
#include <string>
#include <utility>
#include "sorts.h"

using namespace std;

template <typename T>
void quickSortRec_Borschevs(vector<T>& arr, int low, int high)
{
    if (low >= high) return;
    int i = low;
    int j = high;
    T pivot = arr[low + (high - low) / 2];
    while (i <= j) {
        while (arr[i] < pivot) i++;
        while (arr[j] > pivot) j--;
        if (i <= j) {
            swap(arr[i], arr[j]);
            i++;
            j--;
        }
    }
    quickSortRec_Borschevs(arr, low, j);
    quickSortRec_Borschevs(arr, i, high);
}

bool quickSortbyBorschevs(const vector<string>& data, vector<string>& result)
{
    if (data.empty()) {
        result.clear();
        return true;
    }
    result = data;
    quickSortRec_Borschevs(result, 0, static_cast<int>(result.size()) - 1);
    return true;
}