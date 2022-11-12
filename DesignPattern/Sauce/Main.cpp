// 振る舞い
#include"Behavior.h"

// 生成
#include"Generation.h"

// 構築
#include"Structure.h"

enum Behavior
{
    Chain_of_Responsibility = 1,
    Command,
    Iterator,
    Mediator,
    Memento,
    Observer,
    State,
    Strtegy,
    Template_Method,
    Visitor
};

enum Generation
{
    Abstract_Factory = 1,
    Builder,
    Factory_Method,
    Prototype,
    Singleton
};

enum Structure
{
    Adapter = 1,
    Bridge,
    Composite,
    Decorator,
    Facade,
    Flyweight,
    Proxy
};

int main()
{
    int stateChanger = 0;

    std::cout << "振る舞いに関するのデザインパターンの例を選ぶ：";
    std::cin >> stateChanger;

    switch (stateChanger)
    {
    case Behavior::Chain_of_Responsibility:
        CofR_Start();
        break;
    case Behavior::Command:
        break;
    case Behavior::Iterator:
        break;
    case Behavior::Mediator:
        break;
    case Behavior::Memento:
        break;
    case Behavior::Observer:
        break;
    case Behavior::State:
        break;
    case Behavior::Strtegy:
        break;
    case Behavior::Template_Method:
        break;
    case Behavior::Visitor:
        break;
    default:
        std::cout << "何もせず終了します" << std::endl;
        break;
    };

    return 0;
}