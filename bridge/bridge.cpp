#include <iostream>
#include <memory>
#include <string>

class CookingMethod {
    public:
        virtual ~CookingMethod() = default;
        virtual void cook(const std::string& pizzaName) = 0;
};

class WoodOven : public CookingMethod {
    public:
        void cook(const std::string& pizzaName) override {
            std::cout << pizzaName << "cooked in the wooden oven\n";
        }
};

class ElectricOven : public CookingMethod {
    public:
        void cook(const std::string& pizzaName) override {
            std::cout << pizzaName << "cooked in the electric oven\n";
        }
};

class Pizza {
    protected:
        std::shared_ptr<CookingMethod> cookingMethod; 

    public:
        explicit Pizza(std::shared_ptr<CookingMethod> method) 
            : cookingMethod(std::move(method)) {}
        virtual ~Pizza() = default;

        virtual void prepare() = 0;
};

class PepperoniPizza : public Pizza {
    public:
        using Pizza::Pizza;

        void prepare() override {
            cookingMethod->cook("Pepperoni Pizza ");
        }
};

class MargheritaPizza : public Pizza {
    public:
        using Pizza::Pizza;

        void prepare() override {
            cookingMethod->cook("Margherita Pizza ");
        }
};

int main() {
    auto woodOven = std::make_shared<WoodOven>();
    auto electricOven = std::make_shared<ElectricOven>();

    PepperoniPizza pepperoni(woodOven);
    pepperoni.prepare();

    MargheritaPizza margherita(electricOven);
    margherita.prepare();

    return 0;
}