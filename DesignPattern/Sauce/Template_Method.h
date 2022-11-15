#pragma once
/*
    Template Method �i�e���v���[�g�E���\�b�h�A ���^�@�j �́A �U�镑���Ɋւ���f�U�C���p�^�[���̈�ŁA �X�[�p�[�N���X���ŃA���S���Y���̍��i���`���Ă����A
    �T�u�N���X�͍\����ς��邱�ƂȂ��A���S���Y���̓���̃X�e�b�v���㏑�����܂��B
*/


// ���ۃN���X�́A(�ʏ��)���ۃv���~�e�B�u����ւ̌Ăяo���ō\�������A���炩�̃A���S���Y���̃X�P���g�����܂ރe���v���[�g���\�b�h���`���܂��B
// ��ۃT�u�N���X�͂����̑������������K�v������܂����A�e���v���[�g�E���\�b�h���̂͂��̂܂܂ɂ��Ă����܂��B
class AbstractClass {
    // �e���v���[�g�@�̓A���S���Y���̍��i���`����B
public:
    void TemplateMethod() const 
    {
        this->BaseOperation1();
        this->RequiredOperations1();
        this->BaseOperation2();
        this->Hook1();
        this->RequiredOperation2();
        this->BaseOperation3();
        this->Hook2();
    }

    // �����̑���͂��łɎ�������Ă��܂�
protected:
    void BaseOperation1() const 
    {
        std::cout << "AbstractClass �̐���: ���͑啔���̎d�������Ă���\n";
    }
    void BaseOperation2() const 
    {
        std::cout << "AbstractClass �̐���: �������A���̓T�u�N���X�ɂ������̑�����I�[�o�[���C�h�����܂���\n";
    }
    void BaseOperation3() const 
    {
        std::cout << "AbstractClass �̐���: �������A�Ƃɂ������͎d���̑啔�������Ă���\n";
    }

    // �����̑���̓T�u�N���X�Ŏ�������K�v������܂��B
    virtual void RequiredOperations1() const = 0;
    virtual void RequiredOperation2() const = 0;

    // �����́u�t�b�N�v�ł��B�T�u�N���X�͂������I�[�o�[���C�h�ł��܂����A
    // �t�b�N�ɂ͂��łɃf�t�H���g(��������)�̎��������邽�߁A�K�{�ł͂���܂���B
    // �t�b�N�́A�A���S���Y���̂������̏d�v�ȏꏊ�ɒǉ��̊g���|�C���g��񋟂��܂��B
    virtual void Hook1() const {}
    virtual void Hook2() const {}
};

// ��ۃN���X�́A��{�N���X�̂��ׂĂ̒��ۑ������������K�v������܂��B
// �܂��A�ꕔ�̑�����f�t�H���g�̎����ŏ㏑�����邱�Ƃ��ł��܂��B
class ConcreteClass1 : public AbstractClass 
{
protected:
    void RequiredOperations1() const override 
    {
        std::cout << "ConcreteClass1 �̐���: �������ꂽ����1\n";
    }
    void RequiredOperation2() const override 
    {
        std::cout << "ConcreteClass1 �̐���: �������ꂽ����2\n";
    }
};

// �ʏ�A��ۃN���X�͊�{�N���X�̑���̈ꕔ�݂̂��I�[�o�[���C�h���܂��B
class ConcreteClass2 : public AbstractClass
{
protected:
    void RequiredOperations1() const override
    {
        std::cout << "ConcreteClass2 �̐���:�������ꂽ����1\n";
    }
    void RequiredOperation2() const override
    {
        std::cout << "ConcreteClass2 �̐���: �������ꂽ����2\n";
    }
    void Hook1() const override
    {
        std::cout << "ConcreteClass2 �̐���: �D��t�b�N1\n";
    }
};

// �N���C�A���g�E�R�[�h�́A�A���S���Y�������s���邽�߂Ƀe���v���[�g�E���\�b�h���R�[�����܂��B
// �N���C�A���g�E�R�[�h�́A��{�N���X�̃C���^�t�F�[�X����ăI�u�W�F�N�g�ƘA�g�������A�A�g����I�u�W�F�N�g�̋�ۃN���X��F������K�v�͂���܂���B
void ClientCode(AbstractClass* class_) {
    // ...
    class_->TemplateMethod();
    // ...
}

void TemplateMethod_Start() 
{
    std::cout << "�����N���C�A���g�R�[�h���قȂ�T�u�N���X�œ���ł���:\n";
    ConcreteClass1* concreteClass1 = new ConcreteClass1;
    ClientCode(concreteClass1);
    std::cout << "\n";
    std::cout << "�����N���C�A���g�R�[�h���قȂ�T�u�N���X�œ���ł���:\n";
    ConcreteClass2* concreteClass2 = new ConcreteClass2;
    ClientCode(concreteClass2);
    delete concreteClass1;
    delete concreteClass2;
}