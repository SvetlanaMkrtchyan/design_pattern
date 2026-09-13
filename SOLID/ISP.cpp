#include <iostream>

class iwork {
    public:
        virtual ~iwork() = default;
        virtual void work() const = 0;
};

class ieat {
    public:
        virtual ~ieat() = default;
        virtual void eat() const = 0;
};

class isleep {
    public:
        virtual ~isleep() = default;
        virtual void sleep() const = 0;
};

class human : public iwork, public ieat, public isleep {
    public:
        void work() const override {
            std::cout << "Human is working." << std::endl;
        }

        void eat() const override {
            std::cout << "Human is eating." << std::endl;
        }

        void sleep() const override {
            std::cout << "Human is sleeping." << std::endl;
        }
};

class robot : public iwork {
    public:
        void work() const override {
            std::cout << "Robot is working." << std::endl;
        }
};

int main () {
    human humanobj;
    robot robotobj;

    humanobj.work();
    humanobj.eat(); 
    humanobj.sleep();

    robotobj.work();    
    
    return 0;
}