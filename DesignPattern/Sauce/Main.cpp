// êUÇÈïëÇ¢
#include"Behavior.h"

// ê∂ê¨
#include"Generation.h"

// ç\íz
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

    std::cout << "êUÇÈïëÇ¢Ç…ä÷Ç∑ÇÈÇÃÉfÉUÉCÉìÉpÉ^Å[ÉìÇÃó·ÇëIÇ‘ÅF\n" <<
        "ÇPÅFChain of Responsibility\nÇQÅFCommand\nÇRÅFIterator\nÇSÅFMediator\nÇTÅFMemento\n" <<
        "ÇUÅFObserver\nÇVÅFState\nÇWÅFStrtegy\nÇXÅFTemplate_Method\nÇPÇOÅFVisitor" << std::endl;
    std::cout << "î‘çÜÅF";
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
        Observer_Start();
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
        std::cout << "âΩÇ‡ÇπÇ∏èIóπÇµÇ‹Ç∑" << std::endl;
        break;
    };

    return 0;
}