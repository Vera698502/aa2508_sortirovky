#include "sorts.h"
#include <string>
#include <vector>
#include <algorithm>


bool radixSort(const std::vector<std::string>& data, std::vector<std::string>& result) {
    if (data.empty())
        return false;

    result = data;
    int n = (int)result.size();

    size_t maxLen = 0;
    for (const std::string& s : result)
        maxLen = std::max(maxLen, s.size());

    std::vector<std::string> output(n);

    for (int pos = (int)maxLen - 1; pos >= 0; pos--) {
        int count[257] = { 0 };

        for (const std::string& s : result) {
            int d = (pos < (int)s.size()) ? (unsigned char)s[pos] + 1 : 0;
            count[d]++;
        }

        for (int d = 1; d < 257; d++)
            count[d] += count[d - 1];

        for (int i = n - 1; i >= 0; i--) {
            int d = (pos < (int)result[i].size()) ? (unsigned char)result[i][pos] + 1 : 0;
            output[--count[d]] = result[i];
        }

        result.swap(output);
    }
    return true;
}
