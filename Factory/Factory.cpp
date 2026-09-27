#include <iostream>
#include <string>
#include <memory>

class notification {
    public:
        virtual void notify(const std::string& message) = 0;
        virtual ~notification() = default;
};

class email_notification : public notification {
    public:
        void notify(const std::string& message) override {
            std::cout << "EMAIL: " << message << std::endl;
        }
};

class sms_notification : public notification {
    public:
        void notify(const std::string& message) override {
            std::cout << "SMS: " << message << std::endl;
        }
};

class notification_factory {
    public:
        static notification* create_notification(const std::string& type) {
            if (type == "email") {
                return new email_notification();
            } else if (type == "sms") {
                return new sms_notification();
            } else {
                return nullptr;
            }
        }
};

int main() {
    notification* email = notification_factory::create_notification("email");
    if (email) {
        email->notify("This is an email notification.");
        delete email;
    }

    notification* sms = notification_factory::create_notification("sms");
    if (sms) {
        sms->notify("This is an SMS notification.");
        delete sms;
    }

    return 0;
}