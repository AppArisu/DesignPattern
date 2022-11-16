#include<iostream>
// 生成
#include"Generation.h"

enum Generation
{
    Abstract_Factory_ = 1,
    Builder_,
    Factory_Method_,
    Prototype_,
    Singleton_
};

int main()
{
    int stateChanger = 0;

    std::cout << "生成に関するのデザインパターンの例を選ぶ：\n" <<
        "１：Abstract Factory\n２：Builder\n３：Factory Method\n４：Prototype\n５：Singleton" << std::endl;
    std::cout << "番号：";
    std::cin >> stateChanger;
    std::cout << std::endl;

    switch (stateChanger)
    {
    case Generation::Abstract_Factory_:
        AbstractFactory_Start();
        break;
    case Generation::Builder_:
        break;
    case Generation::Factory_Method_:
        break;
    case Generation::Prototype_:
        break;
    case Generation::Singleton_:
        break;
    default:
        std::cout << "何もせず終了します" << std::endl;
        break;
    };

    return 0;
}