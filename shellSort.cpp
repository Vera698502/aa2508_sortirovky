#include "sorts.h"
#include <string>
#include <vector>
#include <utility>

bool shellSort(const std::vector<std::string>& data, std::vector<std::string>& result) {
    if (data.empty())
        return false;

    result = data;
    int n = (int)result.size();

    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            for (int j = i; j >= gap && result[j - gap] > result[j]; j -= gap) {
                std::swap(result[j], result[j - gap]);
            }
        }
    }
    return true;
}