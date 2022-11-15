#pragma once
/*
    Visitor �i�r�W�^�[�A �K��ҁj �́A �U�镑���Ɋւ���f�U�C���p�^�[���̈�ŁA �A���S���Y�������̓���ΏۂƂȂ�I�u�W�F�N�g����؂藣���܂��B
*/
#include<array>

// Visitor�C���^�t�F�[�X�́A�R���|�[�l���g�E�N���X�ɑΉ������A�̖K�⃁�\�b�h��錾���܂��B
// �K�⃁�\�b�h�̃V�O�l�`���ɂ��A�K��҂͎��̂��Ƃ��\�ɂȂ�܂��B
// ��������R���|�[�l���g�̐��m�ȃN���X�����ʂ��܂��B
class ConcreteComponentA;
class ConcreteComponentB;

class Visitor 
{
public:
    virtual void VisitConcreteComponentA(const ConcreteComponentA* element) const = 0;
    virtual void VisitConcreteComponentB(const ConcreteComponentB* element) const = 0;
};

// Component�C���^�t�F�[�X�́A��{�r�W�^�[�C���^�t�F�[�X�������Ƃ��Ď��uaccept�v���\�b�h��錾���܂��B
class Component 
{
public:
    virtual ~Component() {}
    virtual void Accept(Visitor* visitor) const = 0;
};

// �e��ۃR���|�[�l���g�́A�R���|�[�l���g�̃N���X�ɑΉ�����r�W�^�[�̃��\�b�h���Ăяo���悤��`Accept`���\�b�h����������K�v������܂��B
class ConcreteComponentA : public Component 
{
    // ���݂̃N���X���ƈ�v����`visitConcreteComponentA`���Ăяo���Ă��邱�Ƃɒ��ӂ��Ă��������B
    // ����ɂ��A�K��҂͑���Ώۂ̃R���|�[�l���g�̃N���X��m�邱�Ƃ��ł��܂��B
public:
    void Accept(Visitor* visitor) const override 
    {
        visitor->VisitConcreteComponentA(this);
    }

    // Concrete�R���|�[�l���g�ɂ́A��{�N���X�܂��̓C���^�t�F�[�X�ɑ��݂��Ȃ����\�b�h������ꍇ������܂��B
    // �r�W�^�[�̓R���|�[�l���g�̋�ۃN���X��F�����Ă��邽�߁A�����̃��\�b�h���g�p�ł��܂��B
    std::string ExclusiveMethodOfConcreteComponentA() const 
    {
        return "A";
    }
};

class ConcreteComponentB : public Component 
{
    // ����visitConcreteComponentB��ConcreteComponentB
public:
    void Accept(Visitor* visitor) const override 
    {
        visitor->VisitConcreteComponentB(this);
    }
    std::string SpecialMethodOfConcreteComponentB() const 
    {
        return "B";
    }
};

// Concrete Visitor�͓����A���S���Y���̂������̃o�[�W�������������Ă���A���ׂĂ̋�ۃR���|�[�l���g�E�N���X�œ��삵�܂��B
// Visitor�p�^�[���̍ő�̗��_�́AComposite Tree�Ȃǂ̕��G�ȃI�u�W�F�N�g�\���Ŏg�p����ꍇ�ɓ����܂��B
// ���̏ꍇ�A�\���̗l�X�ȃI�u�W�F�N�g�ɑ΂���visitor�̃��\�b�h�����s����Ƃ��ɁA�A���S���Y���̒��ԏ�Ԃ��i�[���Ă����ƕ֗��ł��B
class ConcreteVisitor1 : public Visitor 
{
public:
    void VisitConcreteComponentA(const ConcreteComponentA* element) const override 
    {
        std::cout << element->ExclusiveMethodOfConcreteComponentA() << " + ConcreteVisitor1\n";
    }

    void VisitConcreteComponentB(const ConcreteComponentB* element) const override 
    {
        std::cout << element->SpecialMethodOfConcreteComponentB() << " + ConcreteVisitor1\n";
    }
};

class ConcreteVisitor2 : public Visitor 
{
public:
    void VisitConcreteComponentA(const ConcreteComponentA* element) const override 
    {
        std::cout << element->ExclusiveMethodOfConcreteComponentA() << " + ConcreteVisitor2\n";
    }
    void VisitConcreteComponentB(const ConcreteComponentB* element) const override 
    {
        std::cout << element->SpecialMethodOfConcreteComponentB() << " + ConcreteVisitor2\n";
    }
};

// �N���C�A���g�E�R�[�h�́A��̓I�ȃN���X��F�����邱�ƂȂ��A�C�ӂ̗v�f�Z�b�g�ɑ΂��ăr�W�^�[��������s�ł��܂��B
// accept����́A�r�W�^�[�E�I�u�W�F�N�g���̓K�؂ȑ���ւ̌ďo�����w�����܂��B
void ClientCode(std::array<const Component*, 2> components, Visitor* visitor) 
{
    // ...
    for (const Component* comp : components) 
    {
        comp->Accept(visitor);
    }
    // ...
}

void Visitor_Start() {
    std::array<const Component*, 2> components = { new ConcreteComponentA, new ConcreteComponentB };
    std::cout << "�N���C�A���g�R�[�h�́A��{��Visitor�C���^�t�F�[�X����Ă��ׂĂ̖K��҂ƘA�g���܂�:\n";
    ConcreteVisitor1* visitor1 = new ConcreteVisitor1;
    ClientCode(components, visitor1);
    std::cout << "\n";
    std::cout << "����ɂ��A�����N���C�A���g�R�[�h�����܂��܂ȃ^�C�v�̃r�W�^�[�������ł��܂��B:\n";
    ConcreteVisitor2* visitor2 = new ConcreteVisitor2;
    ClientCode(components, visitor2);

    for (const Component* comp : components) {
        delete comp;
    }
    delete visitor1;
    delete visitor2;
}