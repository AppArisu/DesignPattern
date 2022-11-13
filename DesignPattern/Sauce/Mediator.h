#pragma once
/*
    Mediator �i���f�B�G�[�^�[�A ����ҁj �́A �U�镑���Ɋւ���f�U�C���p�^�[���̈�ŁA �I�u�W�F�N�g�Ԃ̍��ׂƂ����ˑ������팸���܂��B
    �p�^�[���́A �I�u�W�F�N�g�Ԃ̒��ڂ̒ʐM�𐧌����A ���f�B�G�[�^�[�E�I�u�W�F�N�g����Ă݂̂̋�����Ƃ��������܂��B
*/

// Mediator�C���^�[�t�F�[�X�́A�R���|�[�l���g���g�p���郁�\�b�h��錾����
// ����҂́A�����̃C�x���g�ɑΉ������s�𑼂̃R���|�[�l���g�ɓn���B
class BaseComponent;
class Mediator 
{
public:
    virtual void Notify(BaseComponent* sender, std::string event) const = 0;
};

//��{�R���|�[�l���g�́A���f�B�G�[�^�̃R���|�[�l���g�I�u�W�F�N�g���̃C���X�^���X�B
class BaseComponent 
{
protected:
    Mediator* mediator_;

public:
    BaseComponent(Mediator* mediator = nullptr) : mediator_(mediator) {}

    void set_mediator(Mediator* mediator) 
    {
        this->mediator_ = mediator;
    }
};

// Concrete Components�͂��܂��܂ȋ@�\���������܂��B
// Concrete Components�͑��̃R���|�[�l���g�Ɉˑ����܂���B
// �܂��AConcrete Mediator�N���X�ɂ��ˑ����܂���
class Component1 : public BaseComponent 
{
public:
    void DoA() 
    {
        std::cout << "�R���|�[�l���g1��A�����s���܂�\n";
        this->mediator_->Notify(this, "A");
    }
    void DoB() 
    {
        std::cout << "�R���|�[�l���g1��B�����s���܂�\n";
        this->mediator_->Notify(this, "B");
    }
};

class Component2 : public BaseComponent 
{
public:
    void DoC() 
    {
        std::cout << "�R���|�[�l���g2��C�����s���܂�\n";
        this->mediator_->Notify(this, "C");
    }
    void DoD() 
    {
        std::cout << "�R���|�[�l���g2��D�����s���܂�\n";
        this->mediator_->Notify(this, "D");
    }
};

// ��̓I�Ȓ���҂́A�������̃R���|�[�l���g�𒲐����邱�Ƃɂ���ċ��͓I�ȍs�����������܂��B
class ConcreteMediator : public Mediator 
{
private:
    Component1* component1_;
    Component2* component2_;

public:
    ConcreteMediator(Component1* c1, Component2* c2) : component1_(c1), component2_(c2) 
    {
        this->component1_->set_mediator(this);
        this->component2_->set_mediator(this);
    }
    void Notify(BaseComponent* sender, std::string event) const override 
    {
        if (event == "A") 
        {
            std::cout << "���f�B�G�[�^�[��A�ɔ������A���̑�����g���K�[���܂��F\n";
            this->component2_->DoC();
        }
        if (event == "D") 
        {
            std::cout << "���f�B�G�[�^�[��D�ɔ������A���̑�����g���K�[���܂��F\n";
            this->component1_->DoB();
            this->component2_->DoC();
        }
    }
};

// �N���C�A���g�R�[�h
void Mediator_Start()
{
    Component1* c1 = new Component1;
    Component2* c2 = new Component2;
    ConcreteMediator* mediator = new ConcreteMediator(c1, c2);
    std::cout << "�N���C�A���g������A���g���K�[���܂�\n";
    c1->DoA();
    std::cout << "\n";
    std::cout << "�N���C�A���g������D���g���K�[���܂��B\n";
    c2->DoD();

    delete c1;
    delete c2;
    delete mediator;
}