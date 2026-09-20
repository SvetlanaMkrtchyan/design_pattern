#include <iostream>
#include <stdexcept>
#include <string>

class Burger {
    private:
        std::string bun;
        std::string patty;
        std::string cheese;
        std::string toppings;
    public:
        Burger(const std::string& bun, const std::string& patty, const std::string& cheese, const std::string& toppings)
            : bun(bun), patty(patty), cheese(cheese), toppings(toppings) {}

        void display() const {
            std::cout << "Burger with " << bun << " bun, " << patty << " patty, " << cheese << " cheese, and " << toppings << " toppings." << std::endl;
        }
};

class BurgerBuilder {
    private:
        std::string bun;
        std::string patty;
        std::string cheese;
        std::string toppings;
    public:
        BurgerBuilder& setBun(const std::string& bun) {
            this->bun = bun;
            return *this;
        }

        BurgerBuilder& setPatty(const std::string& patty) {
            this->patty = patty;
            return *this;
        }

        BurgerBuilder& setCheese(const std::string& cheese) {
            this->cheese = cheese;
            return *this;
        }

        BurgerBuilder& setToppings(const std::string& toppings) {
            this->toppings = toppings;
            return *this;
        }

        Burger build() const {
            if (bun.empty() || patty.empty()) {
                throw std::logic_error("Burger must have at least a bun and a patty!");
            }
            return Burger(bun, patty, cheese, toppings);
        }
};

int main() {
    BurgerBuilder builder;
    Burger myBurger = builder.setBun("sesame")
                              .setPatty("beef")
                              .setCheese("cheddar")
                              .setToppings("lettuce, tomato, onion")
                              .build();

    myBurger.display();

    return 0;
}