#pragma once
/*
    Bridge （ブリッジ、 架け橋） は、 構造的パターンの一つです。 巨大なクラスや密接に関連したクラスの集まりを、
    抽象部分と実装部分という、 二つの階層に分離し、 それぞれが独立して開発できるようにします。
*/

// 実装はすべての実装クラスのインタフェースを定義します。実装は抽象のインタフェースと一致する必要はありません。
// 実際、2つのインタフェースは完全に異なる場合があります。通常、実装インタフェースはプリミティブ操作のみを提供しますが、
// 抽象はこれらのプリミティブに基づいてより高レベルの操作を定義します。
class Implementation
{
public:
    virtual ~Implementation() {}
    virtual std::string OperationImplementation() const = 0;
};

// 各具象実装は特定のプラットフォームに対応しており、そのプラットフォームのAPIを使用して実装インターフェースを実装します。
class ConcreteImplementationA : public Implementation
{
public:
    std::string OperationImplementation() const override
    {
        return "ConcreteImplementationA：これはプラットフォームAでの結果です\n";
    }
};

class ConcreteImplementationB : public Implementation
{
public:
    std::string OperationImplementation() const override
    {
        return "ConcreteImplementationB：これはプラットフォームBでの結果です\n";
    }
};

// 抽象は、2つのクラス階層の「制御」部分のインタフェースを定義します。
// 抽象は、実装階層のオブジェクトへの参照を維持し、すべての実際の作業をこのオブジェクトに委任します。
class Abstraction
{
protected:
    Implementation* implementation_;

public:
    Abstraction(Implementation* implementation) :implementation_(implementation) {}

    virtual ~Abstraction() {}

    virtual std::string Operation() const
    {
        return "Abstraction：次の基準操作：" +
            this->implementation_->OperationImplementation();
    }
};

// Implementationクラスを変更せずに、Abstractionを拡張することができます
class ExtendedAbstraction : public Abstraction
{
public:
    ExtendedAbstraction(Implementation* implementation) :Abstraction(implementation) {}

    std::string Operation()const override
    {
        return "ExtendedAbstraction：拡張された操作：" +
            this->implementation_->OperationImplementation();
    }
};

// Abstractionオブジェクトが特定のImplementationオブジェクトにリンクされる初期化フェーズを除き、
// クライアントコードはAbstractionクラスにのみ依存する必要があります。
// このようにして、クライアントコードは抽象化と実装の任意の組み合わせをサポートできます。
void ClientCode(const Abstraction& abstraction)
{
    std::cout << abstraction.Operation();
}

// クライアントコードは、事前に設定された抽象化と実装の任意の組み合わせで動作できる必要があります。
void Bridge_Start()
{
    Implementation* implementation = new ConcreteImplementationA;
    Abstraction* abstraction = new Abstraction(implementation);
    ClientCode(*abstraction);
    std::cout << std::endl;
    delete implementation;
    delete abstraction;

    implementation = new ConcreteImplementationB;
    abstraction = new ExtendedAbstraction(implementation);
    ClientCode(*abstraction);

    delete implementation;
    delete abstraction;
};