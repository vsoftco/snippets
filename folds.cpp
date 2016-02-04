// Compute the length of a list using left/right fold

#include <algorithm>
#include <iostream>
#include <list>

int main()
{
    auto lambda = [](auto x, auto ) {return x + 1;};

    std::list<int> li(10);

    // left fold, default
    auto llength = std::accumulate(li.begin(), li.end(), 0, lambda);
    // right fold
    auto rlength = std::accumulate(li.rbegin(), li.rend(), 0, lambda);

    std::cout << "Length (left fold): " << llength << std::endl;
    std::cout << "Length (right fold): " << rlength << std::endl;
}
