#include <iostream>

class Config {
    public:
        static Config& getInstance() {
            static Config instance; 
            return instance;
        }

        Config(const Config&) = delete;           
        Config& operator=(const Config&) = delete; 
        Config(Config&&) = delete;                 
        Config& operator=(Config&&) = delete;     

        void print() const {
            std::cout << "Meyers Singleton is working!\n";
        }

    private:
        Config() = default;  
        ~Config() = default; 
};

int main() {
    Config& config = Config::getInstance();
    config.print();

    return 0;
}