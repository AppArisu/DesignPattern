#pragma once
/*
    State （ステート、 状態） は、 振る舞いに関するデザインパターンの一つで、 オブジェクトの内部状態が変化した時に、 その挙動を変化させます。
    それは、 あたかもそのオブジェクトのクラスが変わったかのように見えます。
*/
#include <typeinfo>

// ベースStateクラスは、すべてのConcrete Stateが実装する必要があるメソッドを宣言し、Stateに関連付けられたContextオブジェクトへのバックリファレンスも提供します。
// このバックリファレンスは、Contextを別のStateに移行するためにStatesで使用できます。
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

// Contextは、クライアントに関係するインタフェースを定義します。また、Contextの現在の状態を表すStateサブクラスのインスタンスへの参照も維持します。
class Context 
{
    // Stateコンテキストの現在の状態への参照
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

    // Contextを使用すると、実行時にStateオブジェクトを変更できます
    void TransitionTo(State* state) 
    {
        std::cout << "Context: Transition to " << typeid(*state).name() << ".\n";
        if (this->state_ != nullptr)
            delete this->state_;
        this->state_ = state;
        this->state_->set_context(this);
    }

    // Contextは、その動作の一部を現在のStateオブジェクトに委任します
    void Request1() 
    {
        this->state_->Handle1();
    }
    void Request2() 
    {
        this->state_->Handle2();
    }
};

// 具象状態は、コンテキストの状態に関連付けられたさまざまな動作を実装します
class ConcreteStateA :public State
{
public:
    void Handle1() override;

    void Handle2() override
    {
        std::cout << "ConcreteStateAが要求2を処理\n";
    }
};

class ConcreteStateB : public State 
{
public:
    void Handle1() override 
    {
        std::cout << "ConcreteStateBが要求1を処理\n";
    }
    void Handle2() override 
    {
        std::cout << "ConcreteStateBが要求2を処理\n";
        std::cout << "ConcreteStateBは状況を変えようとしている\n";
        this->context_->TransitionTo(new ConcreteStateA);
    }
};

void ConcreteStateA::Handle1() 
{
    {
        std::cout << "ConcreteStateAが要求1を処理\n";
        std::cout << "ConcreteStateAは状況を変えようとしている\n";

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