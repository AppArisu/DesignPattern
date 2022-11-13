#pragma once
/*
    Observer �i�I�u�U�[�o�[�A �ώ@�ҁj �́A �U�镑���Ɋւ���f�U�C���p�^�[���̈�ŁA �T�u�X�N���v�V���� �i�ʒm�\�����݁j �̎d�g�݂��`���邱�Ƃɂ��A
    �ώ@�ΏۃI�u�W�F�N�g�ɉ����C�x���g�������������A ���̃C�x���g�̊ώ@�҂ł��镡���̃I�u�W�F�N�g�֒ʒm���s���܂��B
*/
#include<list>

// �I�u�U�[�o�̃f�U�C���p�^�[��
// �Ӑ}:�Ď����Ă���I�u�W�F�N�g�ɔ��������C�x���g�ɂ��ĕ����̃I�u�W�F�N�g��
// �ʒm����T�u�X�N���v�V�������J�j�Y�����`�ł��܂��B
// ���̃p�^�[���ɂ́A�����悤�ȈӖ��������܂��܂ȗp�ꂪ�֘A�t�����Ă��邱�Ƃɒ��ӂ��Ă��������B
// Subject��Publisher�Ƃ��Ă΂�AObserver��Subscriber�ƌĂ΂�邱�Ƃ������A���̋t���܂����l�ł��B
// �܂��A�����uobserve�v�A�ulisten�v�A�܂��́utrack�v�͒ʏ퓯�����Ƃ��Ӗ����܂��B


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

// Subject�͂������̏d�v�ȏ�Ԃ����L���A��Ԃ��ω������Ƃ��ɃI�u�U�[�o�ɒʒm���܂��B
class Subject :public ISubject
{
public:
    virtual ~Subject()
    {
        std::cout << "���悤�Ȃ�A����Subject������\n";
    }

    // �T�u�X�N���v�V�����̊Ǘ����@�B
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
        std::cout << "T���̃��X�g�ɂ� " << list_observer_.size() << " �l�̃I�u�U�[�o�[�����܂�\n";
    }

    // �ʏ�A�T�u�X�N���v�V�����E���W�b�N�́A�T�u�W�F�N�g�����ۂɎ��s�ł��邱�Ƃ̂ق�̈ꕔ�ł��B
    // �T�u�W�F�N�g�͒ʏ�A���̂悤�ȏd�v�ȃr�W�l�X�E���W�b�N��ێ����Ă��܂��B
    // �����d�v�Ȃ��Ƃ��N���낤�Ƃ��Ă���Ƃ�(�܂��͂��̌�)�ɒʒm���\�b�h���g���K�[���܂��B
    void SomeBusinessLogic() {
        this->message_ = "���b�Z�[�W���b�Z�[�W�̕ύX";
        Notify();
        std::cout << "���͏d�v�Ȃ��Ƃ����悤�Ƃ��Ă���\n";
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
        std::cout << "����ɂ��́A���̓I�u�U�[�o�[�ł� \"" << ++Observer::static_number_ << "\".\n";
        this->number_ = Observer::static_number_;
    }
    virtual ~Observer()
    {
        std::cout << "���悤�Ȃ�A����Observer������ \"" << this->number_ << "\".\n";
    }

    void Update(const std::string& message_from_subject) override
    {
        message_from_subject_ = message_from_subject;
        PrintInfo();
    }
    void RemoveMeFromTheList()
    {
        subject_.Detach(this);
        std::cout << "Observer \"" << number_ << "\" ���X�g����폜���܂�.\n";
    }
    void PrintInfo()
    {
        std::cout << "Observer \"" << this->number_ << "\": �V�������b�Z�[�W���g�p�\�ł� --> " << this->message_from_subject_ << "\n";
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

    subject->CreateMessage("�����͏����ł���! :p");
    observer4 = new Observer(*subject);

    observer2->RemoveMeFromTheList();
    observer5 = new Observer(*subject);

    subject->CreateMessage("���̐V�����Ԃ͑f���炵���ł�! ;)");
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