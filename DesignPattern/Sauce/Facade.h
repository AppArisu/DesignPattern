#pragma once
#include<iostream>
#include<string>
/*
    Facade （ファサード） は、 構造に関するデザインパターンの一つで、 ライブラリー、 フレームワーク、 その他のクラスの複雑な組み合わせに対し、
    簡素化されたインターフェースを提供します。
*/

class SubSystem1
{
public:
    std::string Operation1() const { return "SubSystem：Redy!\n"; }
    std::string OperationN() const { return "SubSystem：GO!\n"; }
};

class SubSystem2
{
public:
    std::string Operation1() const { return "SubSystem：Get Redy!\n"; }
    std::string OperationZ() const { return "SubSystem：Fire!\n"; }
};

class Facade
{
protected:
    SubSystem1* subsystem1_;
    SubSystem2* subsystem2_;

public:
    Facade(
        SubSystem1* subsystem1 = nullptr,
        SubSystem2* subsystem2 = nullptr)
    {
        this->subsystem1_ = subsystem1;
        this->subsystem1_ = new SubSystem1;
        this->subsystem2_ = subsystem2;
        this->subsystem2_ = new SubSystem2;
    }

    ~Facade()
    {
        delete subsystem1_;
        delete subsystem2_;
    }

    std::string Operation() 
    {
        std::string result = "Facadeがサブシステムを初期化：\n";
        result += this->subsystem1_->Operation1();
        result += this->subsystem2_->Operation1();
        result += "ファサードはサブシステムにアクションを実行するように命令する：\n";
        result += this->subsystem1_->OperationN();
        result += this->subsystem2_->OperationZ();
        return result;
    }
};

void ClientCode(Facade* facade) 
{
    // ...
    std::cout << facade->Operation();
    // ...
}

void Facade_Start()
{
    SubSystem1* subsystem1 = new SubSystem1;
    SubSystem2* subsystem2 = new SubSystem2;
    Facade* facade = new Facade(subsystem1, subsystem2);
    ClientCode(facade);

    delete facade;
}