#pragma once
#include<algorithm>
#include<list>
/*
    Composite （コンポジット、 混成） は、 構造に関するデザインパターンの一つで、 オブジェクトからツリー （木） 構造を組み立て、
    そのツリー構造がまるで独立したオブジェクトであるかのように扱えるようにします。
*/

// 基本Componentクラスは、コンポジションの単純なオブジェクトと複雑なオブジェクトの両方に対する共通操作を宣言します
class Component
{
protected:
    Component* parent_;

    // 必要に応じて、ベース・コンポーネントは、ツリー構造でコンポーネントの親を設定してアクセスするためのインタフェースを宣言できます。
    // また、これらのメソッドのデフォルト実装も提供できます。
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
        return "分岐（" + result + "）";
    }
};

void ClientCode1(Component* component)
{
    std::cout << "結果：" << component->Operation();
}

void ClientCode2(Component* component1, Component* component2)
{
    if (component1->IsComposite()){ component1->Add(component2); }
    std::cout << "結果：" << component1->Operation();
}

void Composite_Start()
{
    Component* simple = new Leaf;
    std::cout << "Client: 単純なコンポーネントがあります：\n";
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
    std::cout << "Client: これで合成ツリーができました：\n";
    ClientCode1(tree);
    std::cout << "\n\n";

    std::cout << "Client: ツリーを管理する場合でも、コンポーネントクラスをチェックする必要はありません：\n";
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