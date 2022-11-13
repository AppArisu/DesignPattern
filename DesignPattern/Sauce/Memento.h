#pragma once
/*
    Memento （メメント、 形見） は、 振る舞いに関するデザインパターンの一つで、
    オブジェクトの以前の状態を保存し復元することを、 実装の詳細を明かさずに行います。
*/
#include<time.h>

// Mementoインターフェースは、作成日や名前など、mementoのメタデータを取得する方法を提供します。
// ただし、Originatorの状態は公開されません
class Memento
{
public:
    virtual ~Memento() {}
    virtual std::string GetName() const = 0;
    virtual std::string date() const = 0;
    virtual std::string state() const = 0;
};

// 具象メメントには、Originatorの状態を格納するためのインフラストラクチャが含まれています。
class ConcreteMemento :public Memento
{
private:
    std::string state_;
    std::string date_;

public:
    ConcreteMemento(std::string state) :state_(state)
    {
        this->state_ = state;
        std::time_t now = std::time(0);
        char buf[100];
        ctime_s(buf, sizeof(buf), &now);
        this->date_ = buf;
    }

    // Originatorは、状態を復元するときにこのメソッドを使用します。
    std::string state() const override 
    {
        return this->state_;
    }

    // 残りのメソッドは、メタデータを表示するために管理人によって使用されます
    std::string GetName() const override
    {
        return this->date_ + "/" + this->state_.substr(0, 9) + "...";
    }
    std::string date() const override
    {
        return this->date_;
    }
};

// Originatorは、時間の経過とともに変化する可能性のあるいくつかの重要な状態を保持します。
// また、メメント内に状態を保存する方法と、その状態から状態を復元する別の方法も定義します。
class Originator
{
private:
    // 文字列単純にするために、作成者の状態は1つの変数に格納されます。
    std::string state_;

    std::string GenerateRandomString(int length = 10)
    {
        const char alphanum[] =
            "0123456789"
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            "abcdefghijklmnopqrstuvwxyz";
        int stringLength = sizeof(alphanum) - 1;

        std::string random_string;
        for (int i = 0; i < length; i++)
        {
            random_string += alphanum[std::rand() % stringLength];
        }
        return random_string;
    }

public:
    Originator(std::string state) :state_(state)
    {
        std::cout << "Originator：初期状態は次のとおりです：" << this->state_ << "\n";
    }

    // Originatorのビジネス・ロジックは、その内部状態に影響を与える可能性があります。
    // したがって、クライアントは、save()メソッドを介してビジネス・ロジックのメソッドを起動する前に、
    // 状態をバックアップする必要があります。
    void DoSomething()
    {
        std::cout << "Originator：私は重要なことをしています\n";
        this->state_ = this->GenerateRandomString(30);
        std::cout << "Originator：私の州は次のように変わりました：" << this->state_ << "\n";
    }

    // 現在の状態をメモリに保存します。
    Memento* Save()
    {
        return new ConcreteMemento(this->state_);
    }

    // メメントオブジェクトからOriginatorの状態を復元します。
    void Restore(Memento* memento)
    {
        this->state_ = memento->state();
        std::cout << "Originator：状態が次のように変化しました：" << this->state_ << "\n";
    }
};

// 
class Caretaker
{
private:
    std::vector<Memento*>mementos_;
    Originator* originator_;

public:
    Caretaker(Originator* originator) : originator_(originator) {}

    ~Caretaker() 
    {
        for (auto m : mementos_) delete m;
    }

    void Backup() 
    {
        std::cout << "\nCaretaker: 作成者の状態を保存しています...\n";
        this->mementos_.push_back(this->originator_->Save());
    }

    void Undo() 
    {
        if (!this->mementos_.size()) 
        {
            return;
        }
        Memento* memento = this->mementos_.back();
        this->mementos_.pop_back();
        std::cout << "Caretaker: 状態を次の状態に復元しています： " << memento->GetName() << "\n";
        try 
        {
            this->originator_->Restore(memento);
        }
        catch (...) 
        {
            this->Undo();
        }
    }
    void ShowHistory() const 
    {
        std::cout << "Caretaker:以下は記念品のリストです：\n";
        for (Memento* memento : this->mementos_) 
        {
            std::cout << memento->GetName() << "\n";
        }
    }
};

void Memento_Start()
{
    Originator* originator = new Originator("Super-duper-super-puper-super.");
    Caretaker* caretaker = new Caretaker(originator);
    caretaker->Backup();
    originator->DoSomething();
    caretaker->Backup();
    originator->DoSomething();
    caretaker->Backup();
    originator->DoSomething();
    std::cout << "\n";
    caretaker->ShowHistory();
    std::cout << "\nClient: さあ、ロールバックしよう！\n\n";
    caretaker->Undo();
    std::cout << "\nClient: もう一度！\n\n";
    caretaker->Undo();

    delete originator;
    delete caretaker;
}
