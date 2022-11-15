#pragma once
/*
    Visitor （ビジター、 訪問者） は、 振る舞いに関するデザインパターンの一つで、 アルゴリズムをその動作対象となるオブジェクトから切り離します。
*/
#include<array>

// Visitorインタフェースは、コンポーネント・クラスに対応する一連の訪問メソッドを宣言します。
// 訪問メソッドのシグネチャにより、訪問者は次のことが可能になります。
// 処理するコンポーネントの正確なクラスを識別します。
class ConcreteComponentA;
class ConcreteComponentB;

class Visitor 
{
public:
    virtual void VisitConcreteComponentA(const ConcreteComponentA* element) const = 0;
    virtual void VisitConcreteComponentB(const ConcreteComponentB* element) const = 0;
};

// Componentインタフェースは、基本ビジターインタフェースを引数として取る「accept」メソッドを宣言します。
class Component 
{
public:
    virtual ~Component() {}
    virtual void Accept(Visitor* visitor) const = 0;
};

// 各具象コンポーネントは、コンポーネントのクラスに対応するビジターのメソッドを呼び出すように`Accept`メソッドを実装する必要があります。
class ConcreteComponentA : public Component 
{
    // 現在のクラス名と一致する`visitConcreteComponentA`を呼び出していることに注意してください。
    // これにより、訪問者は操作対象のコンポーネントのクラスを知ることができます。
public:
    void Accept(Visitor* visitor) const override 
    {
        visitor->VisitConcreteComponentA(this);
    }

    // Concreteコンポーネントには、基本クラスまたはインタフェースに存在しないメソッドがある場合があります。
    // ビジターはコンポーネントの具象クラスを認識しているため、これらのメソッドを使用できます。
    std::string ExclusiveMethodOfConcreteComponentA() const 
    {
        return "A";
    }
};

class ConcreteComponentB : public Component 
{
    // 同じvisitConcreteComponentB→ConcreteComponentB
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

// Concrete Visitorは同じアルゴリズムのいくつかのバージョンを実装しており、すべての具象コンポーネント・クラスで動作します。
// Visitorパターンの最大の利点は、Composite Treeなどの複雑なオブジェクト構造で使用する場合に得られます。
// この場合、構造の様々なオブジェクトに対してvisitorのメソッドを実行するときに、アルゴリズムの中間状態を格納しておくと便利です。
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

// クライアント・コードは、具体的なクラスを認識することなく、任意の要素セットに対してビジター操作を実行できます。
// accept操作は、ビジター・オブジェクト内の適切な操作への呼出しを指示します。
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
    std::cout << "クライアントコードは、基本のVisitorインタフェースを介してすべての訪問者と連携します:\n";
    ConcreteVisitor1* visitor1 = new ConcreteVisitor1;
    ClientCode(components, visitor1);
    std::cout << "\n";
    std::cout << "これにより、同じクライアントコードをさまざまなタイプのビジターを処理できます。:\n";
    ConcreteVisitor2* visitor2 = new ConcreteVisitor2;
    ClientCode(components, visitor2);

    for (const Component* comp : components) {
        delete comp;
    }
    delete visitor1;
    delete visitor2;
}