#include <iostream>
#include <stdexcept>
#include <thread>

class Dualton {
    private:
        Dualton(size_t id) : m_id(id) {
            std::cout << " Dualton Instance " << m_id << " is created\n";
        }
        ~Dualton() = default;

        size_t m_id;

    public:
        static Dualton& getInstance(size_t index) {
            if (index == 0) {
                static Dualton instance0(0); 
                return instance0;
            } 
            else if (index == 1) {
                static Dualton instance1(1); 
                return instance1;
            } 
            else {
                throw std::out_of_range("ERRORRRRRRRRR");
            }
        }

        Dualton(const Dualton&) = delete;
        Dualton& operator=(const Dualton&) = delete;
        Dualton(Dualton&&) = delete;
        Dualton& operator=(Dualton&&) = delete;

        void printInfo() const {
            std::cout << "Instance ID: " << m_id << " | Address: " << this << "\n";
        }
};

int main() {
    Dualton& obj1_a = Dualton::getInstance(0);
    Dualton& obj1_b = Dualton::getInstance(0); 
    Dualton& obj2 = Dualton::getInstance(1);

    obj1_a.printInfo();
    obj1_b.printInfo(); 
    obj2.printInfo();  

    return 0;
}