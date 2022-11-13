// 振る舞い
#include"Behavior.h"

// 生成
#include"Generation.h"

// 構築
#include"Structure.h"

enum Behavior
{
    Chain_of_Responsibility_ = 1,
    Command_,
    Iterator_,
    Mediator_,
    Memento_,
    Observer_,
    State_,
    Strtegy_,
    Template_Method_,
    Visitor_
};

enum Generation
{
    Abstract_Factory_ = 1,
    Builder_,
    Factory_Method_,
    Prototype_,
    Singleton_
};

enum Structure
{
    Adapter_ = 1,
    Bridge_,
    Composite_,
    Decorator_,
    Facade_,
    Flyweight_,
    Proxy_
};

int main()
{
    int stateChanger = 0;

    std::cout << "振る舞いに関するのデザインパターンの例を選ぶ：\n" <<
        "１：Chain of Responsibility\n２：Command\n３：Iterator\n４：Mediator\n５：Memento" << std::endl;
    std::cout << "番号：";
    std::cin >> stateChanger;
    std::cout << std::endl;

    switch (stateChanger)
    {
    case Behavior::Chain_of_Responsibility_:
        CofR_Start();
        break;
    case Behavior::Command_:
        Command_Start();
        break;
    case Behavior::Iterator_:
        Iterator_Start();
        break;
    case Behavior::Mediator_:
        Mediator_Start();
        break;
    case Behavior::Memento_:
        std::srand(static_cast<unsigned int>(std::time(NULL)));
        Memento_Start();
        break;
    case Behavior::Observer_:
        break;
    case Behavior::State_:
        break;
    case Behavior::Strtegy_:
        break;
    case Behavior::Template_Method_:
        break;
    case Behavior::Visitor_:
        break;
    default:
        std::cout << "何もせず終了します" << std::endl;
        break;
    };

    return 0;
}