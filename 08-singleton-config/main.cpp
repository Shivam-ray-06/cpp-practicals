// Practical 08 - Singleton Design Pattern (application settings)
//
// Pattern chosen: SINGLETON.
// Use case: application-wide settings (for example, the app name, log level
// and a database URL) that every part of the program must read from the same
// place. Only one AppConfig object should ever exist.
//
// Trade-offs:
//   Benefit : one shared, consistent instance with a single global access point.
//   Cost    : hidden global state makes code harder to test (tests share settings)
//             and creates coupling between otherwise unrelated modules.

#include <iostream>
#include <map>
#include <stdexcept>
#include <string>

class AppConfig {
public:
    // Global access point. The static local is created once, on first use,
    // and is thread-safe in C++11 and later (Meyers' Singleton).
    static AppConfig& instance() {
        static AppConfig theOnlyInstance;
        return theOnlyInstance;
    }

    // Copying and assignment are forbidden, so no second instance can be made.
    AppConfig(const AppConfig&) = delete;
    AppConfig& operator=(const AppConfig&) = delete;

    void set(const std::string& key, const std::string& value) {
        settings_[key] = value;
    }

    std::string get(const std::string& key) const {
        auto it = settings_.find(key);
        if (it == settings_.end()) {
            throw std::out_of_range("Missing config key: " + key);
        }
        return it->second;
    }

    void display() const {
        std::cout << "Current settings (instance at " << this << "):\n";
        for (const auto& [key, value] : settings_) {
            std::cout << "  " << key << " = " << value << "\n";
        }
    }

private:
    // Private constructor: only instance() can create the object.
    AppConfig() {
        settings_["app.name"]  = "StudentPortal";
        settings_["log.level"] = "INFO";
        std::cout << "[AppConfig] created once\n";
    }

    std::map<std::string, std::string> settings_;
};

// Any module can use the same instance without passing it around.
void loggingModule() {
    AppConfig& cfg = AppConfig::instance();
    std::cout << "[logging] level = " << cfg.get("log.level") << "\n";
}

void databaseModule() {
    AppConfig& cfg = AppConfig::instance();
    std::cout << "[database] url = " << cfg.get("db.url") << "\n";
}

int main() {
    std::cout << "=== First access: configure the single instance ===\n";
    AppConfig::instance().set("db.url", "sqlite:///students.db");

    std::cout << "\n=== Modules read the same instance ===\n";
    loggingModule();
    databaseModule();

    std::cout << "\n=== Second call returns the SAME object ===\n";
    AppConfig& a = AppConfig::instance();
    AppConfig& b = AppConfig::instance();
    std::cout << "Same object? " << std::boolalpha << (&a == &b) << "\n";

    std::cout << "\n=== Change a setting once, see it everywhere ===\n";
    AppConfig::instance().set("log.level", "DEBUG");
    loggingModule();

    std::cout << "\n=== Full settings ===\n";
    AppConfig::instance().display();

    std::cout << "\n=== Missing key is handled safely ===\n";
    try {
        std::cout << AppConfig::instance().get("smtp.host") << "\n";
    } catch (const std::out_of_range& ex) {
        std::cout << "  caught: " << ex.what() << "\n";
    }

    // AppConfig c;            // compile error: constructor is private
    // AppConfig copy = a;     // compile error: copy constructor is deleted
    return 0;
}
