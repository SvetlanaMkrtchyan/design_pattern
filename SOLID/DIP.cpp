#include <iostream>

class Weapon {
    public:
        virtual ~Weapon() = default;
        virtual void attack() const = 0; 
};

class Gun : public Weapon {
    public:
        void attack() const override {
            std::cout << "Gun is shooting." << std::endl;
        }
};

class Sword : public Weapon {
    public:
        void attack() const override {
            std::cout << "Sword is slashing." << std::endl;
        }
};

class Player {
    private:
        Weapon* weapon;
    public:
        Player(Weapon* w) : weapon(w) {}
        void hit() const {
            weapon->attack();
        }   
};

int main () {
    Gun gun;
    Sword sword;

    Player player1(&gun);   
    Player player2(&sword);
    player1.hit();
    player2.hit();
    
    return 0;
}