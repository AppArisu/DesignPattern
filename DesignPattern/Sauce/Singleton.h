#pragma once
#include<mutex>
/*
    Singleton （シングルトン） は、 生成に関するデザインパターンの一つで、 クラスが一つのインスタンスのみを持つことを保証するとともに、
    このインスタンスへの大域アクセス・ポイントを提供します。
*/

class Singleton
{
private:
    static Singleton* pinstance_;
    static std::mutex mutex_;

protected:
    Singleton(const std::string value) :value_(value) {}
    ~Singleton() {}
    std::string value_;

public:
    Singleton(Singleton& other) = delete;

    void operator=(const Singleton&) = delete;

    static Singleton* GetInstance(const std::string& value);

    void SomeBusinessLogic()
    {
    }

    std::string value() const 
    {
        return value_;
    }
};

Singleton* Singleton::pinstance_{ nullptr };
std::mutex Singleton::mutex_;

Singleton* Singleton::GetInstance(const std::string& value)
{
    std::lock_guard<std::mutex> lock(mutex_);
    if (pinstance_ == nullptr)
    {
        pinstance_ = new Singleton(value);
    }
    return pinstance_;
}

void ThreadFoo() 
{
    // 次のコードは遅い初期化をエミュレートします
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    Singleton* singleton = Singleton::GetInstance("FOO");
    std::cout << singleton->value() << "\n";
}

void ThreadBar() 
{
    // 次のコードは遅い初期化をエミュレートします
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    Singleton* singleton = Singleton::GetInstance("BAR");
    std::cout << singleton->value() << "\n";
}

void Singleton_Start()
{
    std::cout << "同じ値が表示された場合は、シングルトンが再利用されています(yay!)\n" <<
        "異なる値が表示された場合は、2つのシングルトンが作成されています(booo!)\n\n" <<
        "結果:\n";
    std::thread t1(ThreadFoo);
    std::thread t2(ThreadBar);
    t1.join();
    t2.join();
}