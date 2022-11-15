#pragma once
#include <iostream>
#include <string>
/*
    Adapter �i�A�_�v�^�[�A �K�����u�j �́A �\���Ɋւ���f�U�C���p�^�[���̈�ŁA ��݊��ȃC���^�[�t�F�[�X�̃I�u�W�F�N�g���m�̋������\�Ƃ��܂��B
*/

// �^�[�Q�b�g�́A�N���C�A���g�R�[�h�Ŏg�p�����h���C���ŗL�̃C���^�t�F�[�X���`���܂�
class Target
{
public:
    virtual ~Target() = default;

    virtual std::string Request() const
    {
        return "Target�F�f�t�H���g�̃^�[�Q�b�g�̓���";
    }
};

// Adaptee�ɂ͂������֗̕��ȓ��삪�܂܂�Ă��܂����A���̃C���^�[�t�F�C�X��
// �����̃N���C�A���g�R�[�h�ƌ݊���������܂���
// Adaptee�́A�N���C�A���g�R�[�h��������g�p�ł���悤�ɂ���O�ɁA�������̓K�����K�v�ł�
class Adaptee
{
public:
    std::string SpecificRequest() const
    {
        return "eetpadA eht fo roivaheb laicepS";
    }
};

// �A�_�v�^�́AAdaptee�̃C���^�t�F�[�X��Target�̃C���^�t�F�[�X�ƌ݊����̂�����̂ɂ��܂�
class Adapter : public Target
{
private:
    Adaptee* adaptee_;

public:
    Adapter(Adaptee* adaptee) :adaptee_(adaptee) {}

    std::string Request() const override
    {
        std::string to_reverse = this->adaptee_->SpecificRequest();
        std::reverse(to_reverse.begin(), to_reverse.end());
        return "Adapter�F(�|��ς�)" + to_reverse;
    }
};

//class Adapter : public Target, public Adaptee 
//{
//public:
//    Adapter() {}
//    std::string Request() const override 
//    {
//        std::string to_reverse = SpecificRequest();
//        std::reverse(to_reverse.begin(), to_reverse.end());
//        return "Adapter: (�|��ς�) " + to_reverse;
//    }
//};

// �N���C�A���g�R�[�h�́ATarget�C���^�t�F�[�X�ɏ]�����ׂẴN���X���T�|�[�g���܂�
void Target_Start(const Target* target)
{
    std::cout << target->Request();
}

void Adapter_Start()
{
    std::cout << "Client: �^�[�Q�b�g�I�u�W�F�N�g�ł͖��Ȃ���Ƃł��܂�:\n";
    Target* target = new Target;
    Target_Start(target);
    std::cout << "\n\n";
    Adaptee* adaptee = new Adaptee;
    std::cout << "Client: Adaptee�N���X�ɂ͊�ȃC���^�[�t�F�[�X������܂��B�˂��A���͂���𗝉����Ă��Ȃ�:\n";
    std::cout << "Adaptee: " << adaptee->SpecificRequest();
    std::cout << "\n\n";
    std::cout << "Client: �������A�A�_�v�^����đ��삷�邱�Ƃ͂ł��܂��B:\n";
    Adapter* adapter = new Adapter(adaptee);
    Target_Start(adapter);
    std::cout << "\n";

    delete target;
    delete adaptee;
    delete adapter;
};
