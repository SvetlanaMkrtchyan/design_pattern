#include <iostream>
#include <memory>

class Bird {
    public:
        virtual ~Bird() = default;
        virtual void eat() const {
            std::cout << "Bird is eating." << std::endl;
        }
};

class FlyingBird : public Bird {
    public:
        virtual void fly() const {
            std::cout << "Flying bird is flying." << std::endl;
        }
};

class penguin : public Bird {
    public:
        void swim() const {
            std::cout << "Penguin is swimming." << std::endl;
        }
};

class mockingbird : public FlyingBird {
    public:
        void sing() const {
            std::cout << "Mockingbird is singing." << std::endl;
        }
};

int main() {
    auto bird = std::make_unique<Bird>();
    bird->eat();

    auto flyingBird = std::make_unique<FlyingBird>();
    flyingBird->eat();
    flyingBird->fly();

    auto penguinBird = std::make_unique<penguin>();
    penguinBird->eat();
    penguinBird->swim();

    auto mockingbirdBird = std::make_unique<mockingbird>();
    mockingbirdBird->eat();
    mockingbirdBird->fly();
    mockingbirdBird->sing();

    return 0;
}