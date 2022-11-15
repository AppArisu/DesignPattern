#pragma once
#include <iostream>
#include <string>
/*
    Adapter （アダプター、 適合装置） は、 構造に関するデザインパターンの一つで、 非互換なインターフェースのオブジェクト同士の協働を可能とします。
*/

// ターゲットは、クライアントコードで使用されるドメイン固有のインタフェースを定義します
class Target
{
public:
    virtual ~Target() = default;

    virtual std::string Request() const
    {
        return "Target：デフォルトのターゲットの動作";
    }
};

// Adapteeにはいくつかの便利な動作が含まれていますが、そのインターフェイスは
// 既存のクライアントコードと互換性がありません
// Adapteeは、クライアントコードがそれを使用できるようにする前に、いくつかの適合が必要です
class Adaptee
{
public:
    std::string SpecificRequest() const
    {
        return "eetpadA eht fo roivaheb laicepS";
    }
};

// アダプタは、AdapteeのインタフェースをTargetのインタフェースと互換性のあるものにします
class Adapter : public Target
{
private:
    Adaptee* adaptee_;

public:
    Adapter(Adaptee* adaptee) :adaptee_(adaptee) {}

    std::string Request() const override
    {
        std::string to_reverse = this->adaptee_->SpecificRequest();
        std::reverse(to_reverse.begin(), to_reverse.end());
        return "Adapter：(翻訳済み)" + to_reverse;
    }
};

//class Adapter : public Target, public Adaptee 
//{
//public:
//    Adapter() {}
//    std::string Request() const override 
//    {
//        std::string to_reverse = SpecificRequest();
//        std::reverse(to_reverse.begin(), to_reverse.end());
//        return "Adapter: (翻訳済み) " + to_reverse;
//    }
//};

// クライアントコードは、Targetインタフェースに従うすべてのクラスをサポートします
void Target_Start(const Target* target)
{
    std::cout << target->Request();
}

void Adapter_Start()
{
    std::cout << "Client: ターゲットオブジェクトでは問題なく作業できます:\n";
    Target* target = new Target;
    Target_Start(target);
    std::cout << "\n\n";
    Adaptee* adaptee = new Adaptee;
    std::cout << "Client: Adapteeクラスには奇妙なインターフェースがあります。ねえ、私はそれを理解していない:\n";
    std::cout << "Adaptee: " << adaptee->SpecificRequest();
    std::cout << "\n\n";
    std::cout << "Client: しかし、アダプタを介して操作することはできます。:\n";
    Adapter* adapter = new Adapter(adaptee);
    Target_Start(adapter);
    std::cout << "\n";

    delete target;
    delete adaptee;
    delete adapter;
};
