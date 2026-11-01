
#include "sorts.h"
#include <utility>

bool heapSort(const std::vector<std::string>& data,
    std::vector<std::string>& result)
{
    result = data;

    if (result.size() < 2)
        return true;

    auto siftDown = [&result](size_t root, size_t heapSize)
        {
            while (root < heapSize / 2)
            {
                size_t largest = root;
                size_t left = 2 * root + 1;
                size_t right = 2 * root + 2;

                if (left < heapSize && result[left] > result[largest])
                    largest = left;

                if (right < heapSize && result[right] > result[largest])
                    largest = right;

                if (largest == root)
                    break;

                std::swap(result[root], result[largest]);

                root = largest;
            }
        };

    for (size_t i = result.size() / 2; i > 0; --i)
    {
        siftDown(i - 1, result.size());
    }

    for (size_t i = result.size(); i > 1; --i)
    {
        std::swap(result[0], result[i - 1]);

        siftDown(0, i - 1);
    }

    return true;
}
