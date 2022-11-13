// �U�镑��
#include"Behavior.h"

// ����
#include"Generation.h"

// �\�z
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

    std::cout << "�U�镑���Ɋւ���̃f�U�C���p�^�[���̗��I�ԁF";
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
        break;
    case Behavior::Mediator_:
        break;
    case Behavior::Memento_:
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
        std::cout << "���������I�����܂�" << std::endl;
        break;
    };

    return 0;
}