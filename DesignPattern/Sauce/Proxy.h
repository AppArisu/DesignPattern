#pragma once
/*
    Proxy （プロキシー、 代理） は、 構造に関するデザインパターンの一つで、 他のオブジェクトの代理、 代用を提供します。
    プロキシーは、 元のオブジェクトへのアクセスを制御し、 元のオブジェクトへリクエストが行く前か後に別の何かを行うようにすることができます。
*/

class SubJect
{
public:
    virtual void Request01() const = 0;
};

class RealSubJect :public SubJect
{
public:
    void Request01() const override
    {
        std::cout << "RealSubject：リクエストの処理\n";
    }
};

class Proxy :public SubJect
{
private:
    RealSubJect* real_subject_;

    bool CheckAccess() const
    {
        std::cout << "Proxy：実際のリクエストを発行する前のアクセスのチェック\n";
        return true;
    }
    void LogAccess() const
    {
        std::cout << "Proxy：要求時刻のロギング\n";
    }

public:
    Proxy(RealSubJect* real_subject) :real_subject_(new RealSubJect(*real_subject)) {}

    ~Proxy()
    {
        delete real_subject_;
    }

    void Request01() const override
    {
        if (this->CheckAccess())
        {
            this->real_subject_->Request01();
            this->LogAccess();
        }
    }
};

void ClientCode(const SubJect& subject)
{
    subject.Request01();
}

void Proxy_Start()
{
    std::cout << "Client: 実際のサブジェクトを使用したクライアントコードの実行:\n";
    RealSubJect* real_subject = new RealSubJect;
    ClientCode(*real_subject);
    std::cout << "\n";
    std::cout << "Client: プロキシを使用した同じクライアントコードの実行:\n";
    Proxy* proxy = new Proxy(real_subject);
    ClientCode(*proxy);

    delete real_subject;
    delete proxy;
}