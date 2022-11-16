#pragma once
#include<iostream>
#include<string>
/*
    Factory Method�i�t�@�N�g���[�E���\�b�h�j�́A�����Ɋւ���f�U�C���p�^�[���̈�ŁA�X�[�p�[�N���X�ŃI�u�W�F�N�g���쐬���邽�߂̃C���^�[�t�F�[�X�����܂��Ă��܂��B
    �������A �T�u�N���X�ł͍쐬�����I�u�W�F�N�g�̌^��ύX���邱�Ƃ��ł��܂��B
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
        return "{ConcreteProduct1���̐���}";
    }
};
class ConcreteProduct2 :public Product
{
public:
    std::string Operation()const override
    {
        return "{ConcreteProduct2���̐���}";
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
        std::string result = "Creator�F�����쐬�҂̃R�[�h��" + product->Operation();
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
    std::cout << "Client�F�N���G�[�^�̃N���X�͒m��܂��񂪁A����ł����삵�܂�\n"
        << creator.SomeOperation() << std::endl;
}

void FactoryMethod_Start()
{
    std::cout << "App: �uConcreteCreator1�v�ƂƂ��ɔ���\n";
    Creator* creator = new ConcreteCreator1();
    ClientCode(*creator);
    std::cout << std::endl;
    std::cout << "App: �uConcreteCreator2�v�ƂƂ��ɔ���\n";
    Creator* creator2 = new ConcreteCreator2();
    ClientCode(*creator2);

    delete creator;
    delete creator2;
}
