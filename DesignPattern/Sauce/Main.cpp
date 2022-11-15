#include<iostream>
// ç\íz
#include"Structure.h"

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
        "ÇPÅFAdapter\nÇQÅFBridge\nÇRÅFComposite\nÇSÅFDecorator\nÇTÅFFacade\n" <<
        "ÇUÅFFlyweight\nÇVÅFProxy" << std::endl;
    std::cout << "î‘çÜÅF";
    std::cin >> stateChanger;
    std::cout << std::endl;

    switch (stateChanger)
    {
    case Structure::Adapter_:
        break;
    case Structure::Bridge_:
        break;
    case Structure::Composite_:
        break;
    case Structure::Decorator_:
        break;
    case Structure::Facade_:
        break;
    case Structure::Flyweight_:
        break;
    case Structure::Proxy_:
        break;
    default:
        std::cout << "âΩÇ‡ÇπÇ∏èIóπÇµÇ‹Ç∑" << std::endl;
        break;
    };

    return 0;
}