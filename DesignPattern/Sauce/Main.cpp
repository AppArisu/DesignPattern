#include<iostream>
// ����
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

    std::cout << "�����Ɋւ���̃f�U�C���p�^�[���̗��I�ԁF\n" <<
        "�P�FAbstract Factory\n�Q�FBuilder\n�R�FFactory Method\n�S�FPrototype\n�T�FSingleton" << std::endl;
    std::cout << "�ԍ��F";
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
        std::cout << "���������I�����܂�" << std::endl;
        break;
    };

    return 0;
}