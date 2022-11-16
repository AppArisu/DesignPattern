#pragma once
#include<iostream>
#include<string>
/*
    Factory Method（ファクトリー・メソッド）は、生成に関するデザインパターンの一つで、スーパークラスでオブジェクトを作成するためのインターフェースが決まっています。
    しかし、 サブクラスでは作成されるオブジェクトの型を変更することができます。
*/

class Product
{
public:
    virtual ~Product() {}
    virtual std::string Operation()const = 0;
};

class ConcreteProduct1 :public Product
{
public:
    std::string Operation()const override
    {
        return "{ConcreteProduct1号の成果}";
    }
};
class ConcreteProduct2 :public Product
{
public:
    std::string Operation()const override
    {
        return "{ConcreteProduct2号の成果}";
    }
};

class Creator
{
public:
    virtual ~Creator() {}
    virtual Product* FactoryMethod()const = 0;

    std::string SomeOperation()const
    {
        Product* product = this->FactoryMethod();
        std::string result = "Creator：同じ作成者のコードが" + product->Operation();
        delete product;
        return result;
    }
};

class ConcreteCreator1 :public Creator
{
public:
    Product* FactoryMethod()const override
    {
        return new ConcreteProduct1();
    }
};
class ConcreteCreator2 :public Creator
{
public:
    Product* FactoryMethod()const override
    {
        return new ConcreteProduct2();
    }
};

void ClientCode(const Creator& creator)
{
    std::cout << "Client：クリエータのクラスは知りませんが、それでも動作します\n"
        << creator.SomeOperation() << std::endl;
}

void FactoryMethod_Start()
{
    std::cout << "App: 「ConcreteCreator1」とともに発売\n";
    Creator* creator = new ConcreteCreator1();
    ClientCode(*creator);
    std::cout << std::endl;
    std::cout << "App: 「ConcreteCreator2」とともに発売\n";
    Creator* creator2 = new ConcreteCreator2();
    ClientCode(*creator2);

    delete creator;
    delete creator2;
}
