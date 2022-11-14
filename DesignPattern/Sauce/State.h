#pragma once
/*
    State �i�X�e�[�g�A ��ԁj �́A �U�镑���Ɋւ���f�U�C���p�^�[���̈�ŁA �I�u�W�F�N�g�̓�����Ԃ��ω��������ɁA ���̋�����ω������܂��B
    ����́A �����������̃I�u�W�F�N�g�̃N���X���ς�������̂悤�Ɍ����܂��B
*/
#include <typeinfo>

// �x�[�XState�N���X�́A���ׂĂ�Concrete State����������K�v�����郁�\�b�h��錾���AState�Ɋ֘A�t����ꂽContext�I�u�W�F�N�g�ւ̃o�b�N���t�@�����X���񋟂��܂��B
// ���̃o�b�N���t�@�����X�́AContext��ʂ�State�Ɉڍs���邽�߂�States�Ŏg�p�ł��܂��B
class Context;

class State {
protected:
    Context* context_;

public:
    virtual ~State() {}

    void set_context(Context* context) 
    {
        this->context_ = context;
    }

    virtual void Handle1() = 0;
    virtual void Handle2() = 0;
};

// Context�́A�N���C�A���g�Ɋ֌W����C���^�t�F�[�X���`���܂��B�܂��AContext�̌��݂̏�Ԃ�\��State�T�u�N���X�̃C���X�^���X�ւ̎Q�Ƃ��ێ����܂��B
class Context 
{
    // State�R���e�L�X�g�̌��݂̏�Ԃւ̎Q��
private:
    State* state_;

public:
    Context(State* state) : state_(nullptr) 
    {
        this->TransitionTo(state);
    }
    ~Context() 
    {
        delete state_;
    }

    // Context���g�p����ƁA���s����State�I�u�W�F�N�g��ύX�ł��܂�
    void TransitionTo(State* state) 
    {
        std::cout << "Context: Transition to " << typeid(*state).name() << ".\n";
        if (this->state_ != nullptr)
            delete this->state_;
        this->state_ = state;
        this->state_->set_context(this);
    }

    // Context�́A���̓���̈ꕔ�����݂�State�I�u�W�F�N�g�ɈϔC���܂�
    void Request1() 
    {
        this->state_->Handle1();
    }
    void Request2() 
    {
        this->state_->Handle2();
    }
};

// ��ۏ�Ԃ́A�R���e�L�X�g�̏�ԂɊ֘A�t����ꂽ���܂��܂ȓ�����������܂�
class ConcreteStateA :public State
{
public:
    void Handle1() override;

    void Handle2() override
    {
        std::cout << "ConcreteStateA���v��2������\n";
    }
};

class ConcreteStateB : public State 
{
public:
    void Handle1() override 
    {
        std::cout << "ConcreteStateB���v��1������\n";
    }
    void Handle2() override 
    {
        std::cout << "ConcreteStateB���v��2������\n";
        std::cout << "ConcreteStateB�͏󋵂�ς��悤�Ƃ��Ă���\n";
        this->context_->TransitionTo(new ConcreteStateA);
    }
};

void ConcreteStateA::Handle1() 
{
    {
        std::cout << "ConcreteStateA���v��1������\n";
        std::cout << "ConcreteStateA�͏󋵂�ς��悤�Ƃ��Ă���\n";

        this->context_->TransitionTo(new ConcreteStateB);
    }
}

void State_Start() 
{
    Context* context = new Context(new ConcreteStateA);
    context->Request1();
    context->Request2();
    delete context;
}