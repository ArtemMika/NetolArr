#include <iostream>
#include <string>
#include <fstream>

class LogCommand 
{
public:
    virtual ~LogCommand() = default;
    virtual void print(const std::string& message) = 0;
};

class ConsoleLogCommand : public LogCommand 
{
public:
    void print(const std::string& message) override
    {
        std::cout << message << "\n";
    }
};

class FileLogCommand : public LogCommand 
{
public:
    explicit FileLogCommand(const std::string& path) : path_(path) {}

    void print(const std::string& message) override 
    {
        std::ofstream file(path_, std::ios::app);
        if (file.is_open()) 
        {
            file << message << "\n";
            file.close();
        }
        else
        {
            std::cerr << "Error: cannot open log file at " << path_ << "\n";
        }
    }

private:
    std::string path_;
};

void print(LogCommand& command, const std::string& message) 
{
    command.print(message);
}

int main() 
{
    ConsoleLogCommand console_cmd;
    FileLogCommand file_cmd("app.log");

    print(console_cmd, "Это сообщение в консоль");
    print(file_cmd, "Это сообщение в файл app.log");

    return 0;
}