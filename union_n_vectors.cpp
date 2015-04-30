// Union of N vectors via std::set_union (without using std::set)
// http://stackoverflow.com/q/29968206/3093378 (question)
// http://stackoverflow.com/a/29969050/3093378 (my answer)

#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

int main()
{
    std::vector<std::vector<int>> v{{1, 1, 2}, {1, 1, 1}, {1, 5, 6, 7}};
    std::vector<int> result, tmp;
    for (auto && elem : v)
    {
        std::set_union(elem.begin(), elem.end(),
                       result.begin(), result.end(),
                       std::back_inserter(tmp));
        result = std::move(tmp);
    }
    result.erase(std::unique(result.begin(), result.end()), result.end());
    for (auto && elem : result)
        std::cout << elem << " ";
}