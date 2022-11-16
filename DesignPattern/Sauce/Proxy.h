#pragma once
/*
    Proxy �i�v���L�V�[�A �㗝�j �́A �\���Ɋւ���f�U�C���p�^�[���̈�ŁA ���̃I�u�W�F�N�g�̑㗝�A ��p��񋟂��܂��B
    �v���L�V�[�́A ���̃I�u�W�F�N�g�ւ̃A�N�Z�X�𐧌䂵�A ���̃I�u�W�F�N�g�փ��N�G�X�g���s���O����ɕʂ̉������s���悤�ɂ��邱�Ƃ��ł��܂��B
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
        std::cout << "RealSubject�F���N�G�X�g�̏���\n";
    }
};

class Proxy :public SubJect
{
private:
    RealSubJect* real_subject_;

    bool CheckAccess() const
    {
        std::cout << "Proxy�F���ۂ̃��N�G�X�g�𔭍s����O�̃A�N�Z�X�̃`�F�b�N\n";
        return true;
    }
    void LogAccess() const
    {
        std::cout << "Proxy�F�v�������̃��M���O\n";
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
    std::cout << "Client: ���ۂ̃T�u�W�F�N�g���g�p�����N���C�A���g�R�[�h�̎��s:\n";
    RealSubJect* real_subject = new RealSubJect;
    ClientCode(*real_subject);
    std::cout << "\n";
    std::cout << "Client: �v���L�V���g�p���������N���C�A���g�R�[�h�̎��s:\n";
    Proxy* proxy = new Proxy(real_subject);
    ClientCode(*proxy);

    delete real_subject;
    delete proxy;
}