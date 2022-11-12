#pragma once
#include <iostream>
#include <vector>
#include <string>
/*
    Chain of Responsibility （責任の連鎖） は、 振る舞いに関するデザインパターンの一つで、 ハンドラーの連鎖に沿ってリクエストを渡すことができます。
    各ハンドラーは、 リクエストを受け取ると、 リクエストを処理するか、 連鎖内の次のハンドラーに渡すかを決めます。
*/

// Handlerインターフェースは、ハンドラーのチェーンを構築するためのメソッドを宣言します。
// また、要求を実行するためのメソッドも宣言します。
class Handler
{
public:
    virtual Handler* SetNext(Handler* handler) = 0;
    virtual std::string Handle(std::string requires) = 0;
};

// デフォルトの連鎖動作は、ベース・ハンドラー・クラスの中に実装することができます。
class AbstractHandler :public Handler
{
private:
    Handler* next_handler_;

public:
    AbstractHandler() :next_handler_(nullptr) {}

    Handler* SetNext(Handler* handler) override 
    {
        // ここからハンドラを返すと、次のような便利な方法でハンドラをリンクできます。
        this->next_handler_ = handler;
        return handler;
    }

    std::string Handle(std::string requires) override
    {
        if (this->next_handler_)
        {
            return this->next_handler_->Handle(requires);
        }
        return {};
    }
};

// すべてのConcrete Handlerは、要求を処理するか、チェーン内の次のハンドラーに要求を渡します。
class MonkeyHandler : public AbstractHandler {
 public:
  std::string Handle(std::string request) override {
    if (request == "バナナ") {
        return "サル:" + request + "を食べます.\n";
    } else {
      return AbstractHandler::Handle(request);
    }
  }
};
class SquirrelHandler : public AbstractHandler {
 public:
  std::string Handle(std::string request) override {
    if (request == "ナッツ") {
        return "リス:" + request + "を食べます.\n";
    } else {
      return AbstractHandler::Handle(request);
    }
  }
};
class DogHandler : public AbstractHandler {
 public:
  std::string Handle(std::string request) override {
    if (request == "ミートボール") {
        return "イヌ:" + request + "を食べます.\n";
    } else {
      return AbstractHandler::Handle(request);
    }
  }
};

// クライアント・コードは通常、単一のハンドラを操作するのに適しています。
// ほとんどの場合、クライアント・コードはハンドラがチェーンの一部であることさえ認識しません。
void ClientCode(Handler& handler)
{
    std::vector<std::string> food = { "ナッツ", "バナナ", "コーヒー一杯" };
    for (const std::string& f : food) {
        std::cout << "クライアント: " << f << "が欲しい人？\n";
        const std::string result = handler.Handle(f);
        if (!result.empty()) {
            std::cout << "  " << result;
        }
        else {
            std::cout << "  " << f << " 手つかずのままだった.\n";
        }
    }
}

void CofR_Start()
{
    MonkeyHandler* monkey = new MonkeyHandler;
    SquirrelHandler* squirrel = new SquirrelHandler;
    DogHandler* dog = new DogHandler;
    monkey->SetNext(squirrel)->SetNext(dog);
    //squirrel->SetNext(monkey)->SetNext(dog);

    std::cout << "クライアント: サル > リス > イヌ\n\n";
    ClientCode(*monkey);
    std::cout << "\n";
    std::cout << "サブチェイン: リス > イヌ\n\n";
    ClientCode(*squirrel);

    delete monkey;
    delete squirrel;
    delete dog;
}