#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>

class SortingStrategy {
public:
    virtual ~SortingStrategy() = default;
    virtual void sort(std::vector<int>& data) = 0;
};

