#pragma once
/*
    Command �i�R�}���h�A ���߁j �́A �U�镑���Ɋւ���f�U�C���p�^�[���̈�ŁA ���N�G�X�g���A ����Ɋւ��邷�ׂĂ̏����܂ޓƗ������I�u�W�F�N�g�ɓ]�����܂��B
    ���̓]���ɂ��A ���N�G�X�g�����\�b�h�̈����Ƃ��ēn������A ���N�G�X�g�̎��s��x�点����A �҂��s��ɓ��ꂽ��A ������������s�Ȃ����Ƃ��\�ɂȂ�܂��B
*/

// �R�}���h�C���^�t�F�[�X�́A�R�}���h�����s���邽�߂̃��\�b�h��錾���܂��B
class Command
{
public:
    virtual ~Command() {}
    virtual void Execute()const = 0;
};

// �R�}���h�̒��ɂ́A�P���ȑ����P�ƂŎ��s�ł�����̂�����܂��B
class SimpleCommand :public Command
{
private:
    std::string pay_load_;

public:
    explicit SimpleCommand(std::string pay_load) :pay_load_(pay_load) {}
    
    void Execute()const override
    {
        std::cout << "�V���v���R�}���h�F����̗l�ȊȒP�Ȏ����o���܂��i" << this->pay_load_ << "�j\n";
    }
};

// Receiver�N���X�ɂ́A�������̏d�v�ȃr�W�l�X�E���W�b�N���܂܂�Ă��܂��B
// �ނ�͂ǂ�����ėv���̎��s�Ɋ֘A���邷�ׂĂ̎�ނ̑�������s���܂��B
// ���ۂɂ́A�ǂ̃N���X��Receiver�Ƃ��ċ@�\���܂��B
class Receiver
{
public:
    void DoSomething(const std::string& a)
    {
        std::cout << "��M�ҁF��ƒ��i" << a << "�j\n";
    }
    void DoSomethingElse(const std::string& b)
    {
        std::cout << "��M�ҁF��ƒ��i" << b << "�j\n";
    }
};

// �������A�R�}���h�ɂ���ẮA��蕡�G�ȑ�����u���V�[�o�v�ƌĂ΂�鑼�̃I�u�W�F�N�g�ɈϔC���邱�Ƃ��ł��܂��B
class ComplexCommand :public Command
{
private:
    Receiver* receiver_;

    // ��M�҂̃��\�b�h���N�����邽�߂ɕK�v�ȃR���e�L�X�g�f�[�^�B
    std::string a_;
    std::string b_;

    // �����R�}���h�́A�R���X�g���N�^����ĔC�ӂ̃R���e�L�X�g�f�[�^�ƂƂ���
    // 1�܂��͕����̃��V�[�o�I�u�W�F�N�g���󂯓���邱�Ƃ��ł���B
public:
    ComplexCommand(Receiver* receiver, std::string a, std::string b) 
        :receiver_(receiver), a_(a), b_(b) {}

    // �R�}���h�́A��M�҂̔C�ӂ̃��\�b�h�ɈϔC�ł��܂��B
    void Execute() const override
    {
        std::cout << "ComplexCommand�F���G�ȏ����̓��V�[�o�I�u�W�F�N�g�ōs���ׂ��ł�\n";
        this->receiver_->DoSomething(this->a_);
        this->receiver_->DoSomethingElse(this->b_);
    }
};

// �N������1�ȏ�̃R�}���h�Ɋ֘A�t�����Ă��܂��B�N�����̓R�}���h�ɗv���𑗐M���܂��B
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

    // Invoker�͋�ۃR�}���h�⃌�V�[�o�N���X�Ɉˑ����Ȃ��B
    // Invoker�́A�R�}���h�����s���邱�Ƃɂ���āA���N�G�X�g����M�҂ɊԐړI�ɓn���܂��B
    void DoSomethingImportant()
    {
        std::cout << "Invoker�F�����n�߂�O�ɉ��������ė~�����l�͂��܂����H\n";
        if (this->on_start_)
        {
            this->on_start_->Execute();
        }
        std::cout << "Invoker�F �c�{���ɏd�v�Ȃ��Ƃ����āc\n";
        std::cout << "Invoker�F �����I�������ɉ��������ė~�����l�͂��܂����H\n";
        if (this->on_finish_)
        {
            this->on_finish_->Execute();
        }
    }
};

// �N���C�A���g�E�R�[�h�́A�C�ӂ̃R�}���h���g�p���ċN�������p�����[�^�[���ł��܂��B
void Command_Start()
{
    Invoker* invoker = new Invoker;
    invoker->SetOnStart(new SimpleCommand("���A���āI"));
    Receiver* receiver = new Receiver;
    invoker->SetOnFinish(new ComplexCommand(receiver, "�d�q���[���𑗐M���܂�", "���|�[�g�̕ۑ�"));
    invoker->DoSomethingImportant();

    delete invoker;
    delete receiver;
}