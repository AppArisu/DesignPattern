#pragma once
/*
    Memento �i�������g�A �`���j �́A �U�镑���Ɋւ���f�U�C���p�^�[���̈�ŁA
    �I�u�W�F�N�g�̈ȑO�̏�Ԃ�ۑ����������邱�Ƃ��A �����̏ڍׂ𖾂������ɍs���܂��B
*/
#include<time.h>

// Memento�C���^�[�t�F�[�X�́A�쐬���▼�O�ȂǁAmemento�̃��^�f�[�^���擾������@��񋟂��܂��B
// �������AOriginator�̏�Ԃ͌��J����܂���
class Memento
{
public:
    virtual ~Memento() {}
    virtual std::string GetName() const = 0;
    virtual std::string date() const = 0;
    virtual std::string state() const = 0;
};

// ��ۃ������g�ɂ́AOriginator�̏�Ԃ��i�[���邽�߂̃C���t���X�g���N�`�����܂܂�Ă��܂��B
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

    // Originator�́A��Ԃ𕜌�����Ƃ��ɂ��̃��\�b�h���g�p���܂��B
    std::string state() const override 
    {
        return this->state_;
    }

    // �c��̃��\�b�h�́A���^�f�[�^��\�����邽�߂ɊǗ��l�ɂ���Ďg�p����܂�
    std::string GetName() const override
    {
        return this->date_ + "/" + this->state_.substr(0, 9) + "...";
    }
    std::string date() const override
    {
        return this->date_;
    }
};

// Originator�́A���Ԃ̌o�߂ƂƂ��ɕω�����\���̂��邢�����̏d�v�ȏ�Ԃ�ێ����܂��B
// �܂��A�������g���ɏ�Ԃ�ۑ�������@�ƁA���̏�Ԃ����Ԃ𕜌�����ʂ̕��@����`���܂��B
class Originator
{
private:
    // ������P���ɂ��邽�߂ɁA�쐬�҂̏�Ԃ�1�̕ϐ��Ɋi�[����܂��B
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
        std::cout << "Originator�F������Ԃ͎��̂Ƃ���ł��F" << this->state_ << "\n";
    }

    // Originator�̃r�W�l�X�E���W�b�N�́A���̓�����Ԃɉe����^����\��������܂��B
    // ���������āA�N���C�A���g�́Asave()���\�b�h����ăr�W�l�X�E���W�b�N�̃��\�b�h���N������O�ɁA
    // ��Ԃ��o�b�N�A�b�v����K�v������܂��B
    void DoSomething()
    {
        std::cout << "Originator�F���͏d�v�Ȃ��Ƃ����Ă��܂�\n";
        this->state_ = this->GenerateRandomString(30);
        std::cout << "Originator�F���̏B�͎��̂悤�ɕς��܂����F" << this->state_ << "\n";
    }

    // ���݂̏�Ԃ��������ɕۑ����܂��B
    Memento* Save()
    {
        return new ConcreteMemento(this->state_);
    }

    // �������g�I�u�W�F�N�g����Originator�̏�Ԃ𕜌����܂��B
    void Restore(Memento* memento)
    {
        this->state_ = memento->state();
        std::cout << "Originator�F��Ԃ����̂悤�ɕω����܂����F" << this->state_ << "\n";
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
        std::cout << "\nCaretaker: �쐬�҂̏�Ԃ�ۑ����Ă��܂�...\n";
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
        std::cout << "Caretaker: ��Ԃ����̏�Ԃɕ������Ă��܂��F " << memento->GetName() << "\n";
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
        std::cout << "Caretaker:�ȉ��͋L�O�i�̃��X�g�ł��F\n";
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
    std::cout << "\nClient: �����A���[���o�b�N���悤�I\n\n";
    caretaker->Undo();
    std::cout << "\nClient: ������x�I\n\n";
    caretaker->Undo();

    delete originator;
    delete caretaker;
}
