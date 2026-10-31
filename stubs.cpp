#include "sorts.h"

bool shellSort(const std::vector<std::string>& data, std::vector<std::string>& result) {
    if (data.empty()) return false;
    result = data; 
    return true;
}

bool heapSort(const std::vector<std::string>& data, std::vector<std::string>& result) {
    if (data.empty()) return false;
    result = data;
    return true;
}
/*
bool quickSort(const std::vector<std::string>& data, std::vector<std::string>& result) {
    if (data.empty()) return false;
    result = data;
    return true;
}
*/

bool radixSort(const std::vector<std::string>& data, std::vector<std::string>& result) {
    if (data.empty()) return false;
    result = data;
    return true;
}