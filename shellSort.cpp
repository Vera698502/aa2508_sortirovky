#include "sorts.h"
#include <string>
#include <vector>

bool shellSort(const std::vector<std::string>& data, std::vector<std::string>& result) {
    if (data.empty())
        return false;

    result = data;
    int n = (int)result.size(); 

    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            std::string temp = result[i];
            int j;
            for (j = i; j >= gap && result[j - gap] > temp; j -= gap) {
                result[j] = result[j - gap];
            }
            result[j] = temp;
        }
    }
    return true;
}