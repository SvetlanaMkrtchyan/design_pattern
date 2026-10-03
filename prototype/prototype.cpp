#include <iostream>
#include <string>
#include <memory>

class Shape {
    public: 
        virtual void draw() const = 0;
        virtual std::unique_ptr<Shape> clone() const = 0; 
        virtual ~Shape() = default;
};

class Circle : public Shape {
    private:
        double r;
        std::string color;

    public:
        Circle(double r, std::string color) : r(r), color(std::move(color)) {}

        std::unique_ptr<Shape> clone() const override {
            return std::make_unique<Circle>(*this);
        }

        void draw() const override {
            std::cout << "Drawing a Circle | Radius: " << r << ", Color: " << color << "]\n";
        }
};

class Square : public Shape {
    private:
        double side;

    public:
        explicit Square(double side) : side(side) {}

        std::unique_ptr<Shape> clone() const override {
            return std::make_unique<Square>(*this);
        }

        void draw() const override {
            std::cout << "Drawing a Square | Side: " << side << "]\n";
        }
};

int main() {
    std::unique_ptr<Shape> redCirclePrototype = std::make_unique<Circle>(10.0, "Pink");
    std::unique_ptr<Shape> bigSquarePrototype = std::make_unique<Square>(50.0);

    std::unique_ptr<Shape> circle1 = redCirclePrototype->clone();
    std::unique_ptr<Shape> square1 = bigSquarePrototype->clone();

    circle1->draw();
    square1->draw();

    return 0;
}