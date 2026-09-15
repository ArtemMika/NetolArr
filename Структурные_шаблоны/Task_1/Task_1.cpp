#include <iostream>
#include <string>
#include <algorithm>

class TextComponent 
{
public:
    virtual ~TextComponent() = default;
    virtual void render(const std::string& text) const = 0;
};

class Text : public TextComponent
{
public:
    void render(const std::string& text) const override 
    {
        std::cout << text;
    }
};

class Paragraph : public TextComponent
{
public:
    explicit Paragraph(TextComponent* component) : component_(component) {}

    void render(const std::string& text) const override 
    {
        std::cout << "<p>";
        component_->render(text);
        std::cout << "</p>";
    }

private:
    TextComponent* component_;
};

class Reversed : public TextComponent
{
public:
    explicit Reversed(TextComponent* component) : component_(component) {}

    void render(const std::string& text) const override 
    {
        std::string reversed = text;
        std::reverse(reversed.begin(), reversed.end());
        component_->render(reversed);
    }

private:
    TextComponent* component_;
};

class Link 
{
public:
    explicit Link(TextComponent* component) : component_(component) {}

    void render(const std::string& url, const std::string& text) const
    {
        std::cout << "<a href=" << url << ">";
        component_->render(text);
        std::cout << "</a>";
    }

private:
    TextComponent* component_;
};

int main() 
{
    // Paragraph
    auto text_block = new Paragraph(new Text());
    text_block->render("Hello world");
    std::cout << "\n";

    // Reversed
    auto reversed_block = new Reversed(new Text());
    reversed_block->render("Hello world");
    std::cout << "\n";

    // Link
    auto link_block = new Link(new Text());
    link_block->render("netology.ru", "Hello world");
    std::cout << "\n";

    // Комбинированный пример: ссылка с обратным текстом
    auto link_reversed = new Link(new Reversed(new Text()));
    link_reversed->render("netology.ru", "Hello world");
    std::cout << "\n";

    delete text_block;
    delete reversed_block;
    delete link_block;
    delete link_reversed;

    return 0;
}