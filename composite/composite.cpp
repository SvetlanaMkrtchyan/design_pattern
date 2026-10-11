#include <iostream>
#include <string>
#include <vector>

class Component {
    protected:
        std::string name;
    public:
        Component(const std::string& name) : name(name) {}  
        virtual void operation() {
            std::cout << "Component: " << name << std::endl;
        }       
};

class Leaf : public Component {
    public:
        Leaf(const std::string& name) : Component(name) {}
        void operation() override {
            std::cout << "Leaf: " << name << std::endl;
        }
};

class Composite : public Component {
    private:
        std::vector<Component*> children;
    public:
        Composite(const std::string& name) : Component(name) {}
        void add(Component* component) {
            children.push_back(component);
        }
        void operation() override {
            std::cout << "Composite: " << name << std::endl;
            for (auto child : children) {
                child->operation();
            }
        }
};

int main() {
    Composite* root = new Composite("Root");
    Leaf* leaf1 = new Leaf("Leaf 1");
    Leaf* leaf2 = new Leaf("Leaf 2");
    Composite* composite1 = new Composite("Composite 1");
    Leaf* leaf3 = new Leaf("Leaf 3");

    composite1->add(leaf3);
    root->add(leaf1);
    root->add(leaf2);
    root->add(composite1);

    root->operation();

    delete leaf1;
    delete leaf2;
    delete leaf3;
    delete composite1;
    delete root;

    return 0;
}