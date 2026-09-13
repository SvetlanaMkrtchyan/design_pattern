#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

class SingletonOnce {
    public:
        static SingletonOnce& getInstance() {
            std::call_once(s_flag, []() {
                s_instance = new SingletonOnce();
            });
            return *s_instance;
        }

        SingletonOnce(const SingletonOnce&) = delete;
        SingletonOnce& operator=(const SingletonOnce&) = delete;

        void printAddress() const {
            std::cout << "Thread " << std::this_thread::get_id() 
                    << "| Singleton address: " << this << "\n";
        }

    private:
        SingletonOnce() {
            std::cout << " SingletonOnce Instance created! \n";
        }
        static SingletonOnce* s_instance;
        static std::once_flag s_flag; 
};

SingletonOnce* SingletonOnce::s_instance = nullptr;
std::once_flag SingletonOnce::s_flag;

int main() {
    const int numThreads = 5;
    std::vector<std::thread> threads;

    for (int i = 0; i < numThreads; ++i) {
        threads.emplace_back([]() {
            SingletonOnce& instance = SingletonOnce::getInstance();
            instance.printAddress();
        });
    }

    for (auto& thread : threads) {
        thread.join();
    }

    return 0;
}