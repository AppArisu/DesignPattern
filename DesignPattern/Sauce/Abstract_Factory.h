#pragma once
#include<iostream>
#include<string>
/*
     Abstract Factory （抽象ファクトリー、 抽象工場） は、 生成に関するデザインパターンの一つで、 関連したオブジェクトの集りを、
     具象クラスを指定することなく生成することを可能とします。
*/

class AbstractProductA
{
public:
    virtual ~AbstractProductA() {}
    virtual std::string UsefulFunctionA()const = 0;
};

class ConcreteProductA1 : public AbstractProductA
{
public:
    std::string UsefulFunctionA() const override
    {
        return "積A1の結果";
    }
};

class ConcreteProductA2 : public AbstractProductA
{
public:
    std::string UsefulFunctionA() const override
    {
        return "積A2の結果";
    }
};

class AbstractProductB
{
public:
    virtual ~AbstractProductB() {}
    virtual std::string UsefulFunctionB()const = 0;
    virtual std::string AnotherUsefulFunctionB(const AbstractProductA& collaborator)const = 0;
};

class ConcreteProductB1 : public AbstractProductB
{
public:
    std::string UsefulFunctionB() const override
    {
        return "積B1の結果";
    }

    std::string AnotherUsefulFunctionB(const AbstractProductA& collaborator)const override
    {
        const std::string result = collaborator.UsefulFunctionA();
        return "B1がとコラボレーションした結果（" + result + "）";
    }
};

class ConcreteProductB2 : public AbstractProductB
{
public:
    std::string UsefulFunctionB() const override
    {
        return "積B2の結果";
    }

    std::string AnotherUsefulFunctionB(const AbstractProductA& collaborator)const override
    {
        const std::string result = collaborator.UsefulFunctionA();
        return "B2がとコラボレーションした結果（" + result + "）";
    }
};

class AbstractFactory
{
public:
    virtual AbstractProductA* CreateProductA() const = 0;
    virtual AbstractProductB* CreateProductB() const = 0;
};

class ConcreteFactory1 :public AbstractFactory
{
public:
    AbstractProductA* CreateProductA()const override
    {
        return new ConcreteProductA1();
    }
    AbstractProductB* CreateProductB()const override
    {
        return new ConcreteProductB1();
    }
};

class ConcreteFactory2 :public AbstractFactory
{
public:
    AbstractProductA* CreateProductA()const override
    {
        return new ConcreteProductA2();
    }
    AbstractProductB* CreateProductB()const override
    {
        return new ConcreteProductB2();
    }
};

void ClientCode(const AbstractFactory& factory)
{
    const AbstractProductA* product_a = factory.CreateProductA();
    const AbstractProductB* product_b = factory.CreateProductB();
    std::cout << product_b->UsefulFunctionB() << "\n";
    std::cout << product_b->AnotherUsefulFunctionB(*product_a) << "\n";
    delete product_a;
    delete product_b;
}

void AbstractFactory_Start()
{
    std::cout << "Client: 最初のファクトリタイプを使用したクライアントコードのテスト\n";
    ConcreteFactory1* f1 = new ConcreteFactory1();
    ClientCode(*f1);
    delete f1;
    std::cout << std::endl;
    std::cout << "Client: 2番目のファクトリタイプで同じクライアントコードをテストする:\n";
    ConcreteFactory2* f2 = new ConcreteFactory2();
    ClientCode(*f2);
    delete f2;
}