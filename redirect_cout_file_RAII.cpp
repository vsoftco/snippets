// Redirecting std::cout to a file with RAII

#include <iostream>
#include <fstream>
#include <streambuf>

class RAIIcout_redirect
{
    std::streambuf* _oldbuf;
public:
    RAIIcout_redirect(std::ofstream& os): _oldbuf(std::cout.rdbuf())
    {
        std::cout.rdbuf(os.rdbuf());
    }
    ~RAIIcout_redirect()
    {
        std::cout.rdbuf(_oldbuf);
    }
};

void f()
{
    std::cout << "Say something\n";
}

int main()
{
    std::cout << "Writing to file..." << std::endl;
    std::ofstream ofile("output.txt", std::fstream::app); // output file

    // local scope, at exit cout is redirected back automatically
    {
        RAIIcout_redirect tmp(ofile);
        f(); // call f
    } // now redirect back because of ~RAIIcout_redirect()

    std::cout << "Done writing to file" << std::endl;
}