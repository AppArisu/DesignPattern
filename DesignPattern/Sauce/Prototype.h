#pragma once
#include<unordered_map>
/*
    Prototype �i�v���g�^�C�v�A ���^�j �́A �����I�u�W�F�N�g�̃R�s�[�����̃N���X�Ɉˑ����邱�ƂȂ��\�Ƃ���A �����Ɋւ���f�U�C���p�^�[���̈�ł��B
*/

enum Type
{
    PROTOTYPE_1 = 0,
    PROTOTYPE_2
};

class Prototype
{
protected:
    std::string prototype_name_;
    float prototype_field_;

public:
    Prototype() {}
    Prototype(std::string prototype_name) :prototype_name_(prototype_name) {}

    virtual ~Prototype() {}
    virtual Prototype* Clone()const = 0;
    virtual void Method(float prototype_field)
    {
        this->prototype_field_ = prototype_field;
        std::cout << "�t�B�[���h���g�p����" << prototype_name_ << "����̃R�[�����\�b�h�F" << prototype_field << std::endl;
    }
};

class ConcretePrototype1 : public Prototype
{
private:
    float concrete_prototype_field1_;

public:
    ConcretePrototype1(std::string prototype_name, float concrete_prototype_field)
        : Prototype(prototype_name), concrete_prototype_field1_(concrete_prototype_field) {}

    Prototype* Clone() const override
    {
        return new ConcretePrototype1(*this);
    }
};

class ConcretePrototype2 : public Prototype
{
private:
    float concrete_prototype_field2_;

public:
    ConcretePrototype2(std::string prototype_name, float concrete_prototype_field)
        : Prototype(prototype_name), concrete_prototype_field2_(concrete_prototype_field) {}

    Prototype* Clone() const override
    {
        return new ConcretePrototype2(*this);
    }
};

class PrototypeFactory
{
private:
    std::unordered_map<Type, Prototype*, std::hash<int>> prototypes_;

public:
    PrototypeFactory()
    {
        prototypes_[Type::PROTOTYPE_1] = new ConcretePrototype1("PROTOTYPE_1 ", 50.f);
        prototypes_[Type::PROTOTYPE_2] = new ConcretePrototype2("PROTOTYPE_2 ", 60.f);
    }
    ~PrototypeFactory() 
    {
        delete prototypes_[Type::PROTOTYPE_1];
        delete prototypes_[Type::PROTOTYPE_2];
    }

    Prototype* CreatePrototype(Type type) 
    {
        return prototypes_[type]->Clone();
    }
};

void ClientCode(PrototypeFactory& prototype_factory) 
{
    std::cout << "Prototype 1���쐬���܂�\n";

    Prototype* prototype = prototype_factory.CreatePrototype(Type::PROTOTYPE_1);
    prototype->Method(90);
    delete prototype;

    std::cout << "\n";

    std::cout << "Prototype 2���쐬���܂�\n";

    prototype = prototype_factory.CreatePrototype(Type::PROTOTYPE_2);
    prototype->Method(10);

    delete prototype;
}

void Prototype_Start()
{
    PrototypeFactory* prototype_factory = new PrototypeFactory();
    ClientCode(*prototype_factory);
    delete prototype_factory;
}