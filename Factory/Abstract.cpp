#include <iostream>
#include <memory>
#include <string>

class Notification {
    public:
        virtual void send(const std::string& message) const = 0;
        virtual ~Notification() = default;
};

class Formatter {
    public:
        virtual std::string format(const std::string& message) const = 0;
        virtual ~Formatter() = default;
};

class EmailNotification : public Notification {
    public:
        void send(const std::string& message) const override {
            std::cout << "[Email] Sending: " << message << "\n";
        }
};

class HtmlFormatter : public Formatter {
    public:
        std::string format(const std::string& message) const override {
            return "<p>" + message + "</p>";
        }
};

class SmsNotification : public Notification {
    public:
        void send(const std::string& message) const override {
            std::cout << "[SMS] Sending: " << message << "\n";
        }
};

class PlainFormatter : public Formatter {
    public:
        std::string format(const std::string& message) const override {
            return message;
        }
};

class NotificationFactory {
    public:
        virtual std::unique_ptr<Notification> createNotification() const = 0;
        virtual std::unique_ptr<Formatter> createFormatter() const = 0;
        virtual ~NotificationFactory() = default;
};

class EmailFactory : public NotificationFactory {
    public:
        std::unique_ptr<Notification> createNotification() const override {
            return std::make_unique<EmailNotification>();
        }
        std::unique_ptr<Formatter> createFormatter() const override {
            return std::make_unique<HtmlFormatter>();
        }
};

class SmsFactory : public NotificationFactory {
    public:
        std::unique_ptr<Notification> createNotification() const override {
            return std::make_unique<SmsNotification>();
        }
        std::unique_ptr<Formatter> createFormatter() const override {
            return std::make_unique<PlainFormatter>();
        }
};

void notifyUser(const NotificationFactory& factory, const std::string& text) {
    auto formatter = factory.createFormatter();
    auto notification = factory.createNotification();

    std::string formatted = formatter->format(text);
    notification->send(formatted);
}

int main() {
    EmailFactory emailFactory;
    SmsFactory smsFactory;

    notifyUser(emailFactory, "Hello, you're invited to Svetlana's birthday party!");
    notifyUser(smsFactory, "Hello, you're invited to Svetlana's birthday party!");

    return 0;
}