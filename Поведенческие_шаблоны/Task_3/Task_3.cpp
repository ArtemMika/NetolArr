#include <string>
#include <stdexcept>
#include <fstream>
#include <iostream>

enum class Type 
{
    Warning,
    Error,
    FatalError,
    Unknown
};

class LogMessage 
{
public:
    LogMessage(Type type, const std::string& message)
        : type_(type), message_(message) {
    }

    Type type() const { return type_; }
    const std::string& message() const { return message_; }

private:
    Type type_;
    std::string message_;
};

class LogHandler 
{
public:
    virtual ~LogHandler() = default;

    void setNext(LogHandler* next) 
    {
        next_ = next;
    }

    void handle(const LogMessage& msg) 
    {
        if (canHandle(msg))
        {
            process(msg);
        }
        else if (next_) 
        {
            next_->handle(msg);
        }
        else
        {
            throw std::runtime_error("No handler available for this message type");
        }
    }

protected:
    virtual bool canHandle(const LogMessage& msg) const = 0;
    virtual void process(const LogMessage& msg) = 0;

    LogHandler* next_ = nullptr;
};

class FatalErrorHandler : public LogHandler
{
protected:
    bool canHandle(const LogMessage& msg) const override 
    {
        return msg.type() == Type::FatalError;
    }

    void process(const LogMessage& msg) override 
    {
        throw std::runtime_error(msg.message());
    }
};

class ErrorHandler : public LogHandler
{
public:
    explicit ErrorHandler(const std::string& path) : path_(path) {}

protected:
    bool canHandle(const LogMessage& msg) const override 
    {
        return msg.type() == Type::Error;
    }

    void process(const LogMessage& msg) override 
    {
        std::ofstream file(path_, std::ios::app);
        if (file.is_open()) {
            file << "[ERROR] " << msg.message() << "\n";
        }
    }

private:
    std::string path_;
};

class WarningHandler : public LogHandler 
{
protected:
    bool canHandle(const LogMessage& msg) const override 
    {
        return msg.type() == Type::Warning;
    }

    void process(const LogMessage& msg) override 
    {
        std::cout << "[WARNING] " << msg.message() << "\n";
    }
};

class UnknownHandler : public LogHandler
{
protected:
    bool canHandle(const LogMessage& msg) const override 
    {
        return msg.type() == Type::Unknown;
    }

    void process(const LogMessage& msg) override
    {
        throw std::runtime_error("Unknown message: " + msg.message());
    }
};

int main()
{
    FatalErrorHandler fatalHandler;
    ErrorHandler errorHandler("errors.log");
    WarningHandler warningHandler;
    UnknownHandler unknownHandler;

    // фатальная ошибка → ошибка → предупреждение → неизвестное
    fatalHandler.setNext(&errorHandler);
    errorHandler.setNext(&warningHandler);
    warningHandler.setNext(&unknownHandler);

    fatalHandler.handle(LogMessage(Type::Warning, "Low disk space"));

    fatalHandler.handle(LogMessage(Type::Error, "Database connection failed"));

    // Фатальная ошибка — обработает FatalErrorHandler 
    try 
    {
        fatalHandler.handle(LogMessage(Type::FatalError, "Out of memory"));
    }
    catch (const std::runtime_error& e)
    {
        std::cout << "Caught fatal error: " << e.what() << "\n";
    }

    // Неизвестное сообщение — обработает UnknownHandler
    try 
    {
        fatalHandler.handle(LogMessage(Type::Unknown, "Something weird happened"));
    }
    catch (const std::runtime_error& e)
    {
        std::cout << "Caught unknown: " << e.what() << "\n";
    }

    return 0;
}