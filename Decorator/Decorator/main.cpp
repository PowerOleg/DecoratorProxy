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
    explicit DecoratedText(std::shared_ptr<Text> text) : text_ptr{ text } {}

    std::shared_ptr<Text> text_ptr;
};

class ItalicText : public DecoratedText
{
public:
    explicit ItalicText(std::shared_ptr<Text> text_ptr) : DecoratedText(text_ptr) {}

    void render(const std::string& data)  const override
    {
        std::cout << "<i>";
        text_ptr->render(data);
        std::cout << "</i>";
    }
};

class BoldText : public DecoratedText
{
public:
    explicit BoldText(std::shared_ptr<Text> text_ptr) : DecoratedText(text_ptr) {}

    void render(const std::string& data) const override
    {
        std::cout << "<b>";
        text_ptr->render(data);
        std::cout << "</b>";
    }
};

class Paragraph : public DecoratedText
{
public:
    explicit Paragraph(std::shared_ptr<Text> text_ptr) : DecoratedText(text_ptr) {}

    void render(const std::string& data) const override
    {
        std::cout << "<p>";
        text_ptr->render(data);
        std::cout << "</p>";
    }
};

class Reversed : public DecoratedText
{
public:
    explicit Reversed(std::shared_ptr<Text> text_ptr) : DecoratedText(text_ptr) {}

    void render(const std::string& data) const override
    {       
        std::string data_new = data;
        std::reverse(std::begin(data_new), std::end(data_new));
        text_ptr->render(data_new);
    }
};

    class Link : public DecoratedText
{
public:
    explicit Link(std::shared_ptr<Text> text_ptr) : DecoratedText(text_ptr) {}
    void render(const std::string& address, const std::string& data) const
    {
        std::cout << "<a href = " << address << ">";
        text_ptr->render(data);
        std::cout << "</a>";
    }
};


int main()
{
    Text text;
    auto text_ptr = std::make_shared<Text>(text);

    auto text_block = std::make_shared<ItalicText>(ItalicText(std::make_shared<BoldText>(BoldText(text_ptr))));
    text_block->render("Hello world");
    std::cout << std::endl;

    //Paragraph* text_block2 = new Paragraph(new Text());
    auto text_block2 = std::make_shared<Paragraph>(text_ptr);
    text_block2->render("Hello world");//<p>Hello world</p>
    std::cout << std::endl;
    
    //Reversed* text_block3 = new Reversed(new Text());
    auto text_block3 = std::make_shared<Reversed>(text_ptr);
    text_block3->render("Hello world"); //dlrow olleH
    std::cout << std::endl;

    //Link* text_block4 = new Link(new Text());
    auto text_block4 = std::make_shared<Link>(text_ptr);
    text_block4->render("netology.ru", "Hello world"); //<a href = netology.ru>Hello world</a>
}




