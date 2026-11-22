#include <algorithm>
#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include <vector>

class OrderObserver {
    public:
        virtual ~OrderObserver() = default;
        virtual void onStatusChanged(int orderId, const std::string& status) = 0;
};

class BurgerOrder {
    public:
        explicit BurgerOrder(int id) : id_(id), status_("Received") {}

        void subscribe(const std::shared_ptr<OrderObserver>& observer) {
            observers_.push_back(observer);
        }

        void setStatus(const std::string& status) {
            status_ = status;
            std::cout << "\n[Order #" << id_ << "] " << status_ << "\n";
            notifyAll();
        }

    private:
        void notifyAll() {
            auto copy = observers_;
            for (auto& weak : copy) {
                if (auto observer = weak.lock()) {   
                    observer->onStatusChanged(id_, status_);
                }
            }

            observers_.erase(
                std::remove_if(observers_.begin(), observers_.end(),
                            [](const auto& w) { return w.expired(); }),
                observers_.end());
        }

        int id_;
        std::string status_;
        std::vector<std::weak_ptr<OrderObserver>> observers_;
};

class CustomerApp : public OrderObserver {
    public:
        void onStatusChanged(int orderId, const std::string& status) override {
            std::cout << "  Customer app: order #" << orderId << " is now \"" << status << "\"\n";
        }
};

class CourierScreen : public OrderObserver {
    public:
        void onStatusChanged(int orderId, const std::string& status) override {
            if (status == "Ready") {
                std::cout << "  Courier: order #" << orderId << " is ready, come pick it up!\n";
            } else {
                std::cout << "  Courier: order #" << orderId << " -> " << status << "\n";
            }
        }
};

class KitchenAnalytics : public OrderObserver {
    public:
        void onStatusChanged(int orderId, const std::string& status) override {
            std::cout << "  Analytics: saved \"" << status << "\" for order #" << orderId << "\n";
        }
};

int main() {
    BurgerOrder order(42);

    auto customer  = std::make_shared<CustomerApp>();
    auto courier   = std::make_shared<CourierScreen>();
    auto analytics = std::make_shared<KitchenAnalytics>();

    order.subscribe(customer);
    order.subscribe(courier);
    order.subscribe(analytics);

    order.setStatus("Preparing Burger");
    order.setStatus("Ready");

    customer.reset();  

    order.setStatus("Out for Delivery");   
    return 0;
}