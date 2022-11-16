#pragma once
#include<iostream>
#include<string>
/*
     Abstract Factory �i���ۃt�@�N�g���[�A ���ۍH��j �́A �����Ɋւ���f�U�C���p�^�[���̈�ŁA �֘A�����I�u�W�F�N�g�̏W����A
     ��ۃN���X���w�肷�邱�ƂȂ��������邱�Ƃ��\�Ƃ��܂��B
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
        return "��A1�̌���";
    }
};

class ConcreteProductA2 : public AbstractProductA
{
public:
    std::string UsefulFunctionA() const override
    {
        return "��A2�̌���";
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
        return "��B1�̌���";
    }

    std::string AnotherUsefulFunctionB(const AbstractProductA& collaborator)const override
    {
        const std::string result = collaborator.UsefulFunctionA();
        return "B1���ƃR���{���[�V�����������ʁi" + result + "�j";
    }
};

class ConcreteProductB2 : public AbstractProductB
{
public:
    std::string UsefulFunctionB() const override
    {
        return "��B2�̌���";
    }

    std::string AnotherUsefulFunctionB(const AbstractProductA& collaborator)const override
    {
        const std::string result = collaborator.UsefulFunctionA();
        return "B2���ƃR���{���[�V�����������ʁi" + result + "�j";
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
    std::cout << "Client: �ŏ��̃t�@�N�g���^�C�v���g�p�����N���C�A���g�R�[�h�̃e�X�g\n";
    ConcreteFactory1* f1 = new ConcreteFactory1();
    ClientCode(*f1);
    delete f1;
    std::cout << std::endl;
    std::cout << "Client: 2�Ԗڂ̃t�@�N�g���^�C�v�œ����N���C�A���g�R�[�h���e�X�g����:\n";
    ConcreteFactory2* f2 = new ConcreteFactory2();
    ClientCode(*f2);
    delete f2;
}