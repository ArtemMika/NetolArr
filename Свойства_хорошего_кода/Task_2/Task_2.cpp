#include <fstream>
#include <string>
#include <stdexcept>

class PrintableAsHTML
{
public:
    virtual ~PrintableAsHTML() = default;
    virtual std::string printAsHTML() const = 0;
};

class PrintableAsText 
{
public:
    virtual ~PrintableAsText() = default;
    virtual std::string printAsText() const = 0;
};

class PrintableAsJSON 
{
public:
    virtual ~PrintableAsJSON() = default;
    virtual std::string printAsJSON() const = 0;
};

class TextData : public PrintableAsText
{
public:
    explicit TextData(std::string data) : data_(std::move(data)) {}

    std::string printAsText() const override 
    {
        return data_;
    }

private:
    std::string data_;
};

class HTMLData : public PrintableAsHTML 
{
public:
    explicit HTMLData(std::string data) : data_(std::move(data)) {}

    std::string printAsHTML() const override 
    {
        return "<html>" + data_ + "</html>";
    }

private:
    std::string data_;
};

class JSONData : public PrintableAsJSON 
{
public:
    explicit JSONData(std::string data) : data_(std::move(data)) {}

    std::string printAsJSON() const override
    {
        return "{ \"data\": \"" + data_ + "\" }";
    }

private:
    std::string data_;
};

void saveToAsHTML(std::ofstream& file, const PrintableAsHTML& printable) 
{
    file << printable.printAsHTML();
}

void saveToAsJSON(std::ofstream& file, const PrintableAsJSON& printable) 
{
    file << printable.printAsJSON();
}

void saveToAsText(std::ofstream& file, const PrintableAsText& printable) 
{
    file << printable.printAsText();
}

int main() 
{
    std::ofstream html_file("output.html");
    std::ofstream json_file("output.json");
    std::ofstream text_file("output.txt");

    HTMLData html_data("Hello, World!");
    JSONData json_data("Hello, World!");
    TextData text_data("Hello, World!");

    saveToAsHTML(html_file, html_data);
    saveToAsJSON(json_file, json_data);
    saveToAsText(text_file, text_data);

    return 0;
}