#include <iostream>
#include <string>
#include <map>
#include <stdexcept>

class HttpRequest {
    private:
        std::string method;
        std::string url;
        std::map<std::string, std::string> headers;
        std::string body;
        int timeoutMs = 3000; 
    public:
        HttpRequest(std::string method, std::string url, std::map<std::string, std::string> headers, std::string body, int timeoutMs)
            : method(std::move(method)), url(std::move(url)), 
            headers(std::move(headers)), body(std::move(body)), timeoutMs(timeoutMs) {}

        void display() const {
            std::cout << "Method: " << method << "\n"
                    << "URL: " << url << "\n"
                    << "Timeout: " << timeoutMs << " ms\n"
                    << "Body: " << (body.empty() ? "(none)" : body) << "\n"
                    << "Headers count: " << headers.size() << "\n";
        }
};

class HttpRequestBuilder {
    private:
        std::string method_ = "GET";
        std::string url_;
        std::map<std::string, std::string> headers_;
        std::string body_;
        int timeoutMs_ = 3000;
    public:
        explicit HttpRequestBuilder(std::string url) : url_(std::move(url)) {}

        HttpRequestBuilder& method(const std::string& m) {
            method_ = m;
            return *this;
        }

        HttpRequestBuilder& header(const std::string& key, const std::string& value) {
            headers_[key] = value;
            return *this;
        }

        HttpRequestBuilder& body(const std::string& b) {
            body_ = b;
            return *this;
        }

        HttpRequestBuilder& timeout(int ms) {
            timeoutMs_ = ms;
            return *this;
        }

        HttpRequest build() const {
            if (url_.empty()) {
                throw std::logic_error("URL cannot be empty!");
            }
            return HttpRequest(method_, url_, headers_, body_, timeoutMs_);
        }
};

int main() {
    HttpRequestBuilder builder("http://example.com/lana");
    HttpRequest request = builder.method("POST")
                                 .header("Content-Type", "application/json")
                                 .body("{\"key\":\"value\"}")
                                 .timeout(5000)
                                 .build();

    request.display();
    return 0;
}