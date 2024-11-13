#include <string>
#include <iostream>
#include <algorithm>
#include <iterator>


class Text {
public:
    virtual void render(const std::string& data) const
    {
        std::cout << data;
    }
};


class DecoratedText : public Text
{
public:
    explicit DecoratedText(Text* text) : text_(text)
    {}
    Text* text_;
};

class ItalicText : public DecoratedText
{
public:
    explicit ItalicText(Text* text) : DecoratedText(text) {}
    void render(const std::string& data)  const override
    {
        std::cout << "<i>";
        text_->render(data);
        std::cout << "</i>";
    }
};

class BoldText : public DecoratedText
{
public:
    explicit BoldText(Text* text) : DecoratedText(text) {}
    void render(const std::string& data) const override
    {
        std::cout << "<b>";
        text_->render(data);
        std::cout << "</b>";
    }
};

class Paragraph : public DecoratedText
{
public:
    explicit Paragraph(Text* text) : DecoratedText(text) {}
    void render(const std::string& data) const override
    {
        std::cout << "<p>";
        text_->render(data);
        std::cout << "</p>";
    }
};

class Reversed : public DecoratedText
{
public:
    explicit Reversed(Text* text) : DecoratedText(text) {}
    void render(const std::string& data) const override
    {       
        std::string data_new = data;
        std::reverse(std::begin(data_new), std::end(data_new));
        text_->render(data_new);
    }
};

    class Link : public DecoratedText
{
public:
    explicit Link(Text* text) : DecoratedText(text) {}
    void render(const std::string& address, const std::string& data) const
    {
        std::cout << "<a href = " << address << ">";
        text_->render(data);
        std::cout << "</a>";
    }
};


int main()
{
    ItalicText* text_block = new ItalicText(new BoldText(new Text()));
    text_block->render("Hello world");
    std::cout << std::endl;

    Paragraph* text_block2 = new Paragraph(new Text());
    text_block2->render("Hello world");//<p>Hello world</p>
    std::cout << std::endl;

    Reversed* text_block3 = new Reversed(new Text());
    text_block3->render("Hello world"); //dlrow olleH
    std::cout << std::endl;

    Link* text_block4 = new Link(new Text());
    text_block4->render("netology.ru", "Hello world"); //<a href = netology.ru>Hello world</a>
   
}




