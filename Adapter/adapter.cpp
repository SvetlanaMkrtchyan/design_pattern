#include <iostream>
#include <string>

class oldKitchen {
    public:
        std::string menu(int menu_number) const {
            switch (menu_number) {
                case 1:
                    return "Peperoni Pizza";
                case 2:
                    return "Chicken Burger";
                case 3:
                    return "Caesar Salad";
                default:
                    return "Menu item not found";
            }
        }
};

class interfaceKitchen {
    public:
        virtual ~interfaceKitchen() = default;
        virtual std::string getMenu(int menu_number) const = 0;
};

class kitchenAdapter : public interfaceKitchen {
    private:
        const oldKitchen& old_kitchen;
    public:
        kitchenAdapter(const oldKitchen& old_kitchen) : old_kitchen(old_kitchen) {}

        std::string getMenu(int menu_number) const override {
            return old_kitchen.menu(menu_number);
        }
};

int main () {
    oldKitchen old_kitchen;
    kitchenAdapter adapter(old_kitchen);

    std::cout << "Menu item 1: " << adapter.getMenu(1) << std::endl;
    std::cout << "Menu item 2: " << adapter.getMenu(2) << std::endl;
    std::cout << "Menu item 3: " << adapter.getMenu(3) << std::endl;
    std::cout << "Menu item 4: " << adapter.getMenu(4) << std::endl;

    return 0;
}