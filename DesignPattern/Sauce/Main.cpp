#include<iostream>
// �\�z
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

    std::cout << "�U�镑���Ɋւ���̃f�U�C���p�^�[���̗��I�ԁF\n" <<
        "�P�FAdapter\n�Q�FBridge\n�R�FComposite\n�S�FDecorator\n�T�FFacade\n" <<
        "�U�FFlyweight\n�V�FProxy" << std::endl;
    std::cout << "�ԍ��F";
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
        std::cout << "���������I�����܂�" << std::endl;
        break;
    };

    return 0;
}