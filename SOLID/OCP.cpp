#include <iostream>

class Discount {
    public:
        virtual ~Discount() = default;
        virtual double getDiscountRate(double price) const = 0;
};

class studentDiscount : public Discount {
    public:
        double getDiscountRate(double price) const override {
            return price * 0.25;
        }
};

class elderlyDiscount : public Discount {
    public:
        double getDiscountRate(double price) const override {
            return price * 0.3;
        }
};

class DiscountCalculator {
    public:
        static double calculate(double price, const Discount& discount) {
            double discountAmount = discount.getDiscountRate(price);
            return price - discountAmount;
        }
};

int main () {
    double price = 100.0;

    studentDiscount studdisc;
    elderlyDiscount elddisc;

    DiscountCalculator calculator;

    double studentPrice = calculator.calculate(price, studdisc);
    double elderlyPrice = calculator.calculate(price, elddisc);

    std::cout << "Price: " << price << std::endl;
    std::cout << "Price after Student Discount: " << studentPrice << std::endl;
    std::cout << "Price after Elderly Discount: " << elderlyPrice << std::endl;

    return 0;

}