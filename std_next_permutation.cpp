// Some application of std::next_permutation: sums without repeating an index
// Question: http://stackoverflow.com/q/30098903/3093378
// My answer: http://stackoverflow.com/a/30100330/3093378

#include <algorithm>
#include <iostream>
#include <string>

int main() {
    const std::size_t N = 3; // number of arrays
    std::vector<std::vector<int>> arrays{{37, 9, 7}, {42, 50, 2}, {57, 92, 52}};
    std::vector<int> result; // here we store the results

    std::vector<std::size_t> perm(N);
    // fill in the vector with 0 ... N-1, which we'll later permute
    std::iota(perm.begin(), perm.end(), 0);
    do {
        int sum = 0;
        for (std::size_t i = 0; i < perm.size(); ++i)
            sum += arrays[i][perm[i]];
        result.push_back(sum);
    } while (std::next_permutation(perm.begin(), perm.end()));

    // display the result
    std::cout << "The possible sums are: " << std::endl;
    for (auto elem : result)
        std::cout << elem << " ";
}
