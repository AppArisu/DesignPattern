#pragma once
/*
    Command （コマンド、 命令） は、 振る舞いに関するデザインパターンの一つで、 リクエストを、 それに関するすべての情報を含む独立したオブジェクトに転換します。
    この転換により、 リクエストをメソッドの引数として渡したり、 リクエストの実行を遅らせたり、 待ち行列に入れたり、 取り消し操作を行なうことが可能になります。
*/

// コマンドインタフェースは、コマンドを実行するためのメソッドを宣言します。
class Command
{
public:
    virtual ~Command() {}
    virtual void Execute()const = 0;
};

// コマンドの中には、単純な操作を単独で実行できるものがあります。
class SimpleCommand :public Command
{
private:
    std::string pay_load_;

public:
    explicit SimpleCommand(std::string pay_load) :pay_load_(pay_load) {}
    
    void Execute()const override
    {
        std::cout << "シンプルコマンド：印刷の様な簡単な事も出来ます（" << this->pay_load_ << "）\n";
    }
};

// Receiverクラスには、いくつかの重要なビジネス・ロジックが含まれています。
// 彼らはどうやって要求の実行に関連するすべての種類の操作を実行します。
// 実際には、どのクラスもReceiverとして機能します。
class Receiver
{
public:
    void DoSomething(const std::string& a)
    {
        std::cout << "受信者：作業中（" << a << "）\n";
    }
    void DoSomethingElse(const std::string& b)
    {
        std::cout << "受信者：作業中（" << b << "）\n";
    }
};

// ただし、コマンドによっては、より複雑な操作を「レシーバ」と呼ばれる他のオブジェクトに委任することができます。
class ComplexCommand :public Command
{
private:
    Receiver* receiver_;

    // 受信者のメソッドを起動するために必要なコンテキストデータ。
    std::string a_;
    std::string b_;

    // 複合コマンドは、コンストラクタを介して任意のコンテキストデータとともに
    // 1つまたは複数のレシーバオブジェクトを受け入れることができる。
public:
    ComplexCommand(Receiver* receiver, std::string a, std::string b) 
        :receiver_(receiver), a_(a), b_(b) {}

    // コマンドは、受信者の任意のメソッドに委任できます。
    void Execute() const override
    {
        std::cout << "ComplexCommand：複雑な処理はレシーバオブジェクトで行うべきです\n";
        this->receiver_->DoSomething(this->a_);
        this->receiver_->DoSomethingElse(this->b_);
    }
};

// 起動側は1つ以上のコマンドに関連付けられています。起動側はコマンドに要求を送信します。
class Invoker
{
private:
    Command* on_start_;
    Command* on_finish_;

public:
    ~Invoker()
    {
        delete on_start_;
        delete on_finish_;
    }

    void SetOnStart(Command* command)
    {
        this->on_start_ = command;
    }
    void SetOnFinish(Command* command)
    {
        this->on_finish_ = command;
    }

    // Invokerは具象コマンドやレシーバクラスに依存しない。
    // Invokerは、コマンドを実行することによって、リクエストを受信者に間接的に渡します。
    void DoSomethingImportant()
    {
        std::cout << "Invoker：私が始める前に何かをして欲しい人はいますか？\n";
        if (this->on_start_)
        {
            this->on_start_->Execute();
        }
        std::cout << "Invoker： …本当に重要なことをして…\n";
        std::cout << "Invoker： 私が終わった後に何かをして欲しい人はいますか？\n";
        if (this->on_finish_)
        {
            this->on_finish_->Execute();
        }
    }
};

// クライアント・コードは、任意のコマンドを使用して起動側をパラメーター化できます。
void Command_Start()
{
    Invoker* invoker = new Invoker;
    invoker->SetOnStart(new SimpleCommand("挨拶して！"));
    Receiver* receiver = new Receiver;
    invoker->SetOnFinish(new ComplexCommand(receiver, "電子メールを送信します", "レポートの保存"));
    invoker->DoSomethingImportant();

    delete invoker;
    delete receiver;
}