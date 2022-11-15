#pragma once
/*
    Template Method （テンプレート・メソッド、 鋳型法） は、 振る舞いに関するデザインパターンの一つで、 スーパークラス内でアルゴリズムの骨格を定義しておき、
    サブクラスは構造を変えることなくアルゴリズムの特定のステップを上書きします。
*/


// 抽象クラスは、(通常は)抽象プリミティブ操作への呼び出しで構成される、何らかのアルゴリズムのスケルトンを含むテンプレートメソッドを定義します。
// 具象サブクラスはこれらの操作を実装する必要がありますが、テンプレート・メソッド自体はそのままにしておきます。
class AbstractClass {
    // テンプレート法はアルゴリズムの骨格を定義する。
public:
    void TemplateMethod() const 
    {
        this->BaseOperation1();
        this->RequiredOperations1();
        this->BaseOperation2();
        this->Hook1();
        this->RequiredOperation2();
        this->BaseOperation3();
        this->Hook2();
    }

    // これらの操作はすでに実装されています
protected:
    void BaseOperation1() const 
    {
        std::cout << "AbstractClass の説明: 私は大部分の仕事をしている\n";
    }
    void BaseOperation2() const 
    {
        std::cout << "AbstractClass の説明: しかし、私はサブクラスにいくつかの操作をオーバーライドさせました\n";
    }
    void BaseOperation3() const 
    {
        std::cout << "AbstractClass の説明: しかし、とにかく私は仕事の大部分をしている\n";
    }

    // これらの操作はサブクラスで実装する必要があります。
    virtual void RequiredOperations1() const = 0;
    virtual void RequiredOperation2() const = 0;

    // これらは「フック」です。サブクラスはこれらをオーバーライドできますが、
    // フックにはすでにデフォルト(ただし空)の実装があるため、必須ではありません。
    // フックは、アルゴリズムのいくつかの重要な場所に追加の拡張ポイントを提供します。
    virtual void Hook1() const {}
    virtual void Hook2() const {}
};

// 具象クラスは、基本クラスのすべての抽象操作を実装する必要があります。
// また、一部の操作をデフォルトの実装で上書きすることもできます。
class ConcreteClass1 : public AbstractClass 
{
protected:
    void RequiredOperations1() const override 
    {
        std::cout << "ConcreteClass1 の説明: 実装された操作1\n";
    }
    void RequiredOperation2() const override 
    {
        std::cout << "ConcreteClass1 の説明: 実装された操作2\n";
    }
};

// 通常、具象クラスは基本クラスの操作の一部のみをオーバーライドします。
class ConcreteClass2 : public AbstractClass
{
protected:
    void RequiredOperations1() const override
    {
        std::cout << "ConcreteClass2 の説明:実装された操作1\n";
    }
    void RequiredOperation2() const override
    {
        std::cout << "ConcreteClass2 の説明: 実装された操作2\n";
    }
    void Hook1() const override
    {
        std::cout << "ConcreteClass2 の説明: 優先フック1\n";
    }
};

// クライアント・コードは、アルゴリズムを実行するためにテンプレート・メソッドをコールします。
// クライアント・コードは、基本クラスのインタフェースを介してオブジェクトと連携する限り、連携するオブジェクトの具象クラスを認識する必要はありません。
void ClientCode(AbstractClass* class_) {
    // ...
    class_->TemplateMethod();
    // ...
}

void TemplateMethod_Start() 
{
    std::cout << "同じクライアントコードが異なるサブクラスで動作できる:\n";
    ConcreteClass1* concreteClass1 = new ConcreteClass1;
    ClientCode(concreteClass1);
    std::cout << "\n";
    std::cout << "同じクライアントコードが異なるサブクラスで動作できる:\n";
    ConcreteClass2* concreteClass2 = new ConcreteClass2;
    ClientCode(concreteClass2);
    delete concreteClass1;
    delete concreteClass2;
}