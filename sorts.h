#pragma once
#include <vector>
#include <string>

bool shellSort(const std::vector<std::string>& data, std::vector<std::string>& result);
bool heapSort(const std::vector<std::string>& data, std::vector<std::string>& result);
bool quickSort(const std::vector<std::string>& data, std::vector<std::string>& result);
bool mergeSort(const std::vector<std::string>& data, std::vector<std::string>& result);
bool radixSort(const std::vector<std::string>& data, std::vector<std::string>& result);