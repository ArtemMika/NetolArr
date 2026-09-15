#include <string>
#include <vector>
#include <memory>
#include <fstream>
#include <iostream>
#include <algorithm>

class Observer 
{
public:
    virtual void onWarning(const std::string& message) {}
    virtual void onError(const std::string& message) {}
    virtual void onFatalError(const std::string& message) {}
    virtual ~Observer() = default;
};

class LoggerSubject 
{
public:
    void attach(std::shared_ptr<Observer> observer)
    {
        observers_.push_back(observer);
    }

    void warning(const std::string& message) const 
    {
        notifyAll([](auto& obs, const auto& msg) { obs->onWarning(msg); }, message);
    }

    void error(const std::string& message) const 
    {
        notifyAll([](auto& obs, const auto& msg) { obs->onError(msg); }, message);
    }

    void fatalError(const std::string& message) const 
    {
        notifyAll([](auto& obs, const auto& msg) { obs->onFatalError(msg); }, message);
    }

private:
    template<typename Func>
    void notifyAll(Func f, const std::string& message) const
    {

        for (const auto& weak_obs : observers_) 
        {
            if (auto obs = weak_obs.lock()) 
            {
                f(obs, message);
            }
        }
    }

    std::vector<std::weak_ptr<Observer>> observers_;
};

class ConsoleWarningObserver : public Observer 
{
public:
    void onWarning(const std::string& message) override 
    {
        std::cout << "[WARNING] " << message << "\n";
    }
};

class FileErrorObserver : public Observer
{
public:
    explicit FileErrorObserver(const std::string& path) : path_(path) {}

    void onError(const std::string& message) override 
    {
        std::ofstream file(path_, std::ios::app);
        if (file.is_open()) 
        {
            file << "[ERROR] " << message << "\n";
            file.close();
        }
        else 
        {
            std::cerr << "Error: cannot open error log file at " << path_ << "\n";
        }
    }

private:
    std::string path_;
};


class ConsoleAndFileFatalObserver : public Observer 
{
public:
    explicit ConsoleAndFileFatalObserver(const std::string& path) : path_(path) {}

    void onFatalError(const std::string& message) override 
    {
        std::cout << "[FATAL] " << message << "\n";

        std::ofstream file(path_, std::ios::app);
        if (file.is_open()) {
            file << "[FATAL] " << message << "\n";
            file.close();
        }
        else {
            std::cerr << "Error: cannot open fatal log file at " << path_ << "\n";
        }
    }

private:
    std::string path_;
};

int main() 
{
    LoggerSubject logger;

    auto console_warn = std::make_shared<ConsoleWarningObserver>();
    auto file_error = std::make_shared<FileErrorObserver>("errors.log");
    auto fatal_obs = std::make_shared<ConsoleAndFileFatalObserver>("fatal.log");

    logger.attach(console_warn);
    logger.attach(file_error);
    logger.attach(fatal_obs);

    logger.warning("Это предупреждение");
    logger.error("Это ошибка");
    logger.fatalError("Это фатальная ошибка");

    console_warn.reset();

    logger.warning("Ещё одно предупреждение (не появится в консоли)");

    return 0;
}