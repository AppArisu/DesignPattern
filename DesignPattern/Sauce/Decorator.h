#pragma once
#include <iostream>
#include <string>
/*
    Decorator �i�f�R���[�^�[�A ������j �́A �\���Ɋւ���f�U�C���p�^�[���̈�ŁA ����U�镑�����܂ޓ��ʂȃ��b�p�[�E�I�u�W�F�N�g�̒��ɃI�u�W�F�N�g��z�u���邱�ƂŁA
    �����̃I�u�W�F�N�g�ɐV�����U�镑����t�������܂��B
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
        return "ConcreteDecoartorA�i" + Decorator::Operation() + "�j";
    }
};

class ConcreteDecoartorB :public Decorator
{
public:
    ConcreteDecoartorB(Component1* component) :Decorator(component) {}

    std::string Operation()const override
    {
        return "ConcreteDecoartorB�i" + Decorator::Operation() + "�j";
    }
};

void ClientCode(Component1* component) {
    // ...
    std::cout << "����: " << component->Operation();
    // ...
}

void Decorator_Start()
{
    Component1* simple = new ConcreteComponen1;
    std::cout << "Client: �P���ȃR���|�[�l���g������܂��F\n";
    ClientCode(simple);
    std::cout << "\n\n";

    Component1* decorator1 = new ConcreteDecoartorA(simple);
    Component1* decorator2 = new ConcreteDecoartorB(decorator1);
    std::cout << "Client: �������ꂽ�R���|�[�l���g������܂��F\n";
    ClientCode(decorator2);
    std::cout << "\n";

    delete simple;
    delete decorator1;
    delete decorator2;
}