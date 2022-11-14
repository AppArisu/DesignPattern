#pragma once
#include<algorithm>
/*
    Strategy （ストラテジー、 戦略） は、 振る舞いに関するデザインパターンの一つで、 アルゴリズムのファミリーを定義し、
    それぞれのアルゴリズムを別個のクラスとし、 それらのオブジェクトを交換可能にします。
*/

// Strategyインターフェイスは、一部のアルゴリズムのサポートされているすべてのバージョンに共通する操作を宣言します。
// Contextはこのインターフェースを使用して、Concrete Strategiesで定義されたアルゴリズムを呼び出します。
class Strategy
{
public:
    virtual ~Strategy() = default;
    virtual std::string doAlgorithm(std::string_view data) const = 0;
};

// コンテキストは、クライアントに関係するインタフェースを定義します。
class Contexts
{
    // 戦略Contextは、いずれかの戦略オブジェクトへの参照を保持します。
    // Contextは、戦略の具象クラスを認識しません。Contextは、戦略インタフェースを介してすべての戦略で機能する必要があります。
private:
    std::unique_ptr<Strategy> strategy_;

    // 通常、Contextはコンストラクターを介してストラテジーを受け入れますが、実行時にそれを変更するためのセッターも提供します。
public:
    explicit Contexts(std::unique_ptr<Strategy>&& strategy = {}) : strategy_(std::move(strategy))
    {
    }

    // 通常、Contextでは実行時にStrategyオブジェクトを置き換えることができます。
    void set_strategy(std::unique_ptr<Strategy>&& strategy)
    {
        strategy_ = std::move(strategy);
    }

    // Contextは、アルゴリズムの+複数バージョンを単独で実装するのではなく、一部の作業をStrategyオブジェクトに委任します。
    void doSomeBusinessLogic() const
    {
        if (strategy_) 
        {
            std::cout << "Context: 戦略を使用したデータのソート(方法は不明)\n";
            std::string result = strategy_->doAlgorithm("aecbd");
            std::cout << result << "\n";
        }
        else 
        {
            std::cout << "Context: 戦略が設定されていない\n";
        }
    }
};

// 具象戦略では、基本戦略インタフェースに従ってアルゴリズムが実装されます。インタフェースにより、これらはコンテキスト内で交換可能になります。
class ConcreteStrategyA : public Strategy
{
public:
    std::string doAlgorithm(std::string_view data) const override
    {
        std::string result(data);
        std::sort(std::begin(result), std::end(result));

        return result;
    }
};
class ConcreteStrategyB : public Strategy
{
    std::string doAlgorithm(std::string_view data) const override
    {
        std::string result(data);
        std::sort(std::begin(result), std::end(result), std::greater<>());

        return result;
    }
};

// クライアント・コードは具体的な戦略を選択してコンテキストに渡します。クライアントは正しい選択を行うために、戦略間の違いを認識する必要があります。
void Strategy_Start()
{
    Contexts context(std::make_unique<ConcreteStrategyA>());
    std::cout << "Client: 戦略は通常のソートに設定されています\n";
    context.doSomeBusinessLogic();
    std::cout << "\n";
    std::cout << "Client: 戦略は逆ソートに設定されています\n";
    context.set_strategy(std::make_unique<ConcreteStrategyB>());
    context.doSomeBusinessLogic();
}