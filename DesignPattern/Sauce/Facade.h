#pragma once
#include<iostream>
#include<string>
/*
    Facade �i�t�@�T�[�h�j �́A �\���Ɋւ���f�U�C���p�^�[���̈�ŁA ���C�u�����[�A �t���[�����[�N�A ���̑��̃N���X�̕��G�ȑg�ݍ��킹�ɑ΂��A
    �ȑf�����ꂽ�C���^�[�t�F�[�X��񋟂��܂��B
*/

class SubSystem1
{
public:
    std::string Operation1() const { return "SubSystem�FRedy!\n"; }
    std::string OperationN() const { return "SubSystem�FGO!\n"; }
};

class SubSystem2
{
public:
    std::string Operation1() const { return "SubSystem�FGet Redy!\n"; }
    std::string OperationZ() const { return "SubSystem�FFire!\n"; }
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
        std::string result = "Facade���T�u�V�X�e�����������F\n";
        result += this->subsystem1_->Operation1();
        result += this->subsystem2_->Operation1();
        result += "�t�@�T�[�h�̓T�u�V�X�e���ɃA�N�V���������s����悤�ɖ��߂���F\n";
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