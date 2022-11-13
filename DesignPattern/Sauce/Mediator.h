#pragma once
/*
    Mediator （メディエーター、 仲介者） は、 振る舞いに関するデザインパターンの一つで、 オブジェクト間の混沌とした依存性を削減します。
    パターンは、 オブジェクト間の直接の通信を制限し、 メディエーター・オブジェクトを介してのみの共同作業を強制します。
*/

// Mediatorインターフェースは、コンポーネントが使用するメソッドを宣言して
// 仲介者は、これらのイベントに対応し実行を他のコンポーネントに渡す。
class BaseComponent;
class Mediator 
{
public:
    virtual void Notify(BaseComponent* sender, std::string event) const = 0;
};

//基本コンポーネントは、メディエータのコンポーネントオブジェクト内のインスタンス。
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

// Concrete Componentsはさまざまな機能を実装します。
// Concrete Componentsは他のコンポーネントに依存しません。
// また、Concrete Mediatorクラスにも依存しません
class Component1 : public BaseComponent 
{
public:
    void DoA() 
    {
        std::cout << "コンポーネント1はAを実行します\n";
        this->mediator_->Notify(this, "A");
    }
    void DoB() 
    {
        std::cout << "コンポーネント1はBを実行します\n";
        this->mediator_->Notify(this, "B");
    }
};

class Component2 : public BaseComponent 
{
public:
    void DoC() 
    {
        std::cout << "コンポーネント2はCを実行します\n";
        this->mediator_->Notify(this, "C");
    }
    void DoD() 
    {
        std::cout << "コンポーネント2はDを実行します\n";
        this->mediator_->Notify(this, "D");
    }
};

// 具体的な仲介者は、いくつかのコンポーネントを調整することによって協力的な行動を実装します。
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
            std::cout << "メディエーターはAに反応し、次の操作をトリガーします：\n";
            this->component2_->DoC();
        }
        if (event == "D") 
        {
            std::cout << "メディエーターはDに反応し、次の操作をトリガーします：\n";
            this->component1_->DoB();
            this->component2_->DoC();
        }
    }
};

// クライアントコード
void Mediator_Start()
{
    Component1* c1 = new Component1;
    Component2* c2 = new Component2;
    ConcreteMediator* mediator = new ConcreteMediator(c1, c2);
    std::cout << "クライアントが操作Aをトリガーします\n";
    c1->DoA();
    std::cout << "\n";
    std::cout << "クライアントが操作Dをトリガーします。\n";
    c2->DoD();

    delete c1;
    delete c2;
    delete mediator;
}