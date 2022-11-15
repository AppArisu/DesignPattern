#pragma once
#include<algorithm>
#include<list>
/*
    Composite �i�R���|�W�b�g�A �����j �́A �\���Ɋւ���f�U�C���p�^�[���̈�ŁA �I�u�W�F�N�g����c���[ �i�؁j �\����g�ݗ��āA
    ���̃c���[�\�����܂�œƗ������I�u�W�F�N�g�ł��邩�̂悤�Ɉ�����悤�ɂ��܂��B
*/

// ��{Component�N���X�́A�R���|�W�V�����̒P���ȃI�u�W�F�N�g�ƕ��G�ȃI�u�W�F�N�g�̗����ɑ΂��鋤�ʑ����錾���܂�
class Component
{
protected:
    Component* parent_;

    // �K�v�ɉ����āA�x�[�X�E�R���|�[�l���g�́A�c���[�\���ŃR���|�[�l���g�̐e��ݒ肵�ăA�N�Z�X���邽�߂̃C���^�t�F�[�X��錾�ł��܂��B
    // �܂��A�����̃��\�b�h�̃f�t�H���g�������񋟂ł��܂��B
public:
    virtual ~Component() {}

    void SetParent(Component* parent) { this->parent_ = parent; }

    Component* GetParent() const { return this->parent_; }

    virtual void Add(Component* component) {}
    virtual void Remove(Component* component) {}

    virtual bool IsComposite() const { return false; }

    virtual std::string Operation() const = 0;
};

class Leaf : public Component
{
public:
    std::string Operation() const override { return "Leaf"; }
};

class Composite :public Component
{
protected:
    std::list< Component*>children_;

public:
    void Add(Component* component) override
    {
        this->children_.push_back(component);
        component->SetParent(this);
    }

    void Remove(Component* component) override
    {
        children_.remove(component);
        component->SetParent(nullptr);
    }

    bool IsComposite() const override { return true; }

    std::string Operation() const override
    {
        std::string result;
        for (const Component* c : children_)
        {
            if (c == children_.back())
            {
                result += c->Operation();
            }
            else
            {
                result += c->Operation() + "+";
            }
        }
        return "����i" + result + "�j";
    }
};

void ClientCode1(Component* component)
{
    std::cout << "���ʁF" << component->Operation();
}

void ClientCode2(Component* component1, Component* component2)
{
    if (component1->IsComposite()){ component1->Add(component2); }
    std::cout << "���ʁF" << component1->Operation();
}

void Composite_Start()
{
    Component* simple = new Leaf;
    std::cout << "Client: �P���ȃR���|�[�l���g������܂��F\n";
    ClientCode1(simple);
    std::cout << "\n\n";
    /**
     * ...as well as the complex composites.
     */

    Component* tree = new Composite;
    Component* branch1 = new Composite;

    Component* leaf_1 = new Leaf;
    Component* leaf_2 = new Leaf;
    Component* leaf_3 = new Leaf;
    branch1->Add(leaf_1);
    branch1->Add(leaf_2);
    Component* branch2 = new Composite;
    branch2->Add(leaf_3);
    tree->Add(branch1);
    tree->Add(branch2);
    std::cout << "Client: ����ō����c���[���ł��܂����F\n";
    ClientCode1(tree);
    std::cout << "\n\n";

    std::cout << "Client: �c���[���Ǘ�����ꍇ�ł��A�R���|�[�l���g�N���X���`�F�b�N����K�v�͂���܂���F\n";
    ClientCode2(tree, simple);
    std::cout << "\n";

    delete simple;
    delete tree;
    delete branch1;
    delete branch2;
    delete leaf_1;
    delete leaf_2;
    delete leaf_3;
}