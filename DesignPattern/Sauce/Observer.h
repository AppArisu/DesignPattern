#pragma once
/*
    Observer （オブザーバー、 観察者） は、 振る舞いに関するデザインパターンの一つで、 サブスクリプション （通知申し込み） の仕組みを定義することにより、
    観察対象オブジェクトに何かイベントが発生した時、 そのイベントの観察者である複数のオブジェクトへ通知を行います。
*/
#include<list>

// オブザーバのデザインパターン
// 意図:監視しているオブジェクトに発生したイベントについて複数のオブジェクトに
// 通知するサブスクリプションメカニズムを定義できます。
// このパターンには、同じような意味を持つさまざまな用語が関連付けられていることに注意してください。
// SubjectはPublisherとも呼ばれ、ObserverはSubscriberと呼ばれることが多く、その逆もまた同様です。
// また、動詞「observe」、「listen」、または「track」は通常同じことを意味します。


class IObserver
{
public:
    virtual ~IObserver() {};
    virtual void Update(const std::string& message_from_subject) = 0;
};

class ISubject
{
public:
    virtual ~ISubject() {};
    virtual void Attach(IObserver* observer) = 0;
    virtual void Detach(IObserver* observer) = 0;
    virtual void Notify() = 0;
};

// Subjectはいくつかの重要な状態を所有し、状態が変化したときにオブザーバに通知します。
class Subject :public ISubject
{
public:
    virtual ~Subject()
    {
        std::cout << "さようなら、私はSubjectだった\n";
    }

    // サブスクリプションの管理方法。
    void Attach(IObserver* observer) override
    {
        list_observer_.push_back(observer);
    }
    void Detach(IObserver* observer) override
    {
        list_observer_.remove(observer);
    }
    void Notify() override
    {
        std::list<IObserver*>::iterator iterator = list_observer_.begin();
        HowManyObserver();
        while (iterator != list_observer_.end()) 
        {
            (*iterator)->Update(message_);
            ++iterator;
        }
    }

    void CreateMessage(std::string message = "Empty")
    {
        this->message_ = message;
        Notify();
    }

    void HowManyObserver()
    {
        std::cout << "Tそのリストには " << list_observer_.size() << " 人のオブザーバーがいます\n";
    }

    // 通常、サブスクリプション・ロジックは、サブジェクトが実際に実行できることのほんの一部です。
    // サブジェクトは通常、次のような重要なビジネス・ロジックを保持しています。
    // 何か重要なことが起ころうとしているとき(またはその後)に通知メソッドをトリガーします。
    void SomeBusinessLogic() {
        this->message_ = "メッセージメッセージの変更";
        Notify();
        std::cout << "私は重要なことをしようとしている\n";
    }

private:
    std::list<IObserver*> list_observer_;
    std::string message_;
};

class Observer : public IObserver
{
public:
    Observer(Subject& subject) : subject_(subject)
    {
        this->subject_.Attach(this);
        std::cout << "こんにちは、私はオブザーバーです \"" << ++Observer::static_number_ << "\".\n";
        this->number_ = Observer::static_number_;
    }
    virtual ~Observer()
    {
        std::cout << "さようなら、私はObserverだった \"" << this->number_ << "\".\n";
    }

    void Update(const std::string& message_from_subject) override
    {
        message_from_subject_ = message_from_subject;
        PrintInfo();
    }
    void RemoveMeFromTheList()
    {
        subject_.Detach(this);
        std::cout << "Observer \"" << number_ << "\" リストから削除します.\n";
    }
    void PrintInfo()
    {
        std::cout << "Observer \"" << this->number_ << "\": 新しいメッセージが使用可能です --> " << this->message_from_subject_ << "\n";
    }

private:
    std::string message_from_subject_;
    Subject& subject_;
    static int static_number_;
    int number_;
};

int Observer::static_number_ = 0;

void Observer_Start() {
    Subject* subject = new Subject;
    Observer* observer1 = new Observer(*subject);
    Observer* observer2 = new Observer(*subject);
    Observer* observer3 = new Observer(*subject);
    Observer* observer4;
    Observer* observer5;

    subject->CreateMessage("Hello World! :D");
    observer3->RemoveMeFromTheList();

    subject->CreateMessage("今日は暑いですね! :p");
    observer4 = new Observer(*subject);

    observer2->RemoveMeFromTheList();
    observer5 = new Observer(*subject);

    subject->CreateMessage("私の新しい車は素晴らしいです! ;)");
    observer5->RemoveMeFromTheList();

    observer4->RemoveMeFromTheList();
    observer1->RemoveMeFromTheList();

    delete observer5;
    delete observer4;
    delete observer3;
    delete observer2;
    delete observer1;
    delete subject;
}