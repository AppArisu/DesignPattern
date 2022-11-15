#pragma once
#include <iostream>
#include <string>
/*
    Decorator （デコレーター、 装飾器） は、 構造に関するデザインパターンの一つで、 ある振る舞いを含む特別なラッパー・オブジェクトの中にオブジェクトを配置することで、
    それらのオブジェクトに新しい振る舞いを付け加えます。
*/

class Component1 
{
public:
    virtual ~Component1() {}
    virtual std::string Operation() const = 0;
};

class ConcreteComponen1 : public Component1 
{
public:
    std::string Operation() const override 
    {
        return "ConcreteComponent1";
    }
};

class Decorator :public Component1
{
protected:
    Component1* component_;
public:
    Decorator(Component1* component) :component_(component) {}

    std::string Operation() const override { return this->component_->Operation(); }
};

class ConcreteDecoartorA :public Decorator
{
public:
    ConcreteDecoartorA(Component1* component) :Decorator(component) {}

    std::string Operation()const override
    {
        return "ConcreteDecoartorA（" + Decorator::Operation() + "）";
    }
};

class ConcreteDecoartorB :public Decorator
{
public:
    ConcreteDecoartorB(Component1* component) :Decorator(component) {}

    std::string Operation()const override
    {
        return "ConcreteDecoartorB（" + Decorator::Operation() + "）";
    }
};

void ClientCode(Component1* component) {
    // ...
    std::cout << "結果: " << component->Operation();
    // ...
}

void Decorator_Start()
{
    Component1* simple = new ConcreteComponen1;
    std::cout << "Client: 単純なコンポーネントがあります：\n";
    ClientCode(simple);
    std::cout << "\n\n";

    Component1* decorator1 = new ConcreteDecoartorA(simple);
    Component1* decorator2 = new ConcreteDecoartorB(decorator1);
    std::cout << "Client: 装飾されたコンポーネントがあります：\n";
    ClientCode(decorator2);
    std::cout << "\n";

    delete simple;
    delete decorator1;
    delete decorator2;
}