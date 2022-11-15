#include<iostream>
// 構築
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

    std::cout << "構築に関するのデザインパターンの例を選ぶ：\n" <<
        "１：Adapter\n２：Bridge\n３：Composite\n４：Decorator\n５：Facade\n" <<
        "６：Flyweight\n７：Proxy" << std::endl;
    std::cout << "番号：";
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
        std::cout << "何もせず終了します" << std::endl;
        break;
    };

    return 0;
}