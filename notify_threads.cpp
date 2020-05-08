// Notifying suspended threads, EMC++ Item 39 pg. 270

#include <chrono>
#include <future>
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

std::promise<void> p;
std::mutex m;

void react(int i) {
    using namespace std::literals;
    std::unique_lock<std::mutex> lk(m);

    std::cout << "Thread " << i << " sleeping for 1s... " << std::flush;
    std::this_thread::sleep_for(1s);
    std::cout << "Thread " << i << " reacting!" << std::endl;
}

void detect() {
    auto sf = p.get_future().share(); // get a shared_future
    std::vector<std::thread> vt;
    for (int i = 0; i < 10; ++i) {
        vt.emplace_back([&sf, i] {
            sf.wait();
            react(i);
        });
    }

    p.set_value(); // notify all threads

    for (auto& t : vt) {
        t.join(); // join all threads
    }
}

int main() { detect(); }
