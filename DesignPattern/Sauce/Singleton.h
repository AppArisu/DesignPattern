#pragma once
#include<mutex>
/*
    Singleton �i�V���O���g���j �́A �����Ɋւ���f�U�C���p�^�[���̈�ŁA �N���X����̃C���X�^���X�݂̂������Ƃ�ۏ؂���ƂƂ��ɁA
    ���̃C���X�^���X�ւ̑��A�N�Z�X�E�|�C���g��񋟂��܂��B
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
    // ���̃R�[�h�͒x�����������G�~�����[�g���܂�
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    Singleton* singleton = Singleton::GetInstance("FOO");
    std::cout << singleton->value() << "\n";
}

void ThreadBar() 
{
    // ���̃R�[�h�͒x�����������G�~�����[�g���܂�
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    Singleton* singleton = Singleton::GetInstance("BAR");
    std::cout << singleton->value() << "\n";
}

void Singleton_Start()
{
    std::cout << "�����l���\�����ꂽ�ꍇ�́A�V���O���g�����ė��p����Ă��܂�(yay!)\n" <<
        "�قȂ�l���\�����ꂽ�ꍇ�́A2�̃V���O���g�����쐬����Ă��܂�(booo!)\n\n" <<
        "����:\n";
    std::thread t1(ThreadFoo);
    std::thread t2(ThreadBar);
    t1.join();
    t2.join();
}