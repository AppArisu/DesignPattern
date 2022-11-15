#pragma once
/*
    Bridge �i�u���b�W�A �˂����j �́A �\���I�p�^�[���̈�ł��B ����ȃN���X�▧�ڂɊ֘A�����N���X�̏W�܂���A
    ���ە����Ǝ��������Ƃ����A ��̊K�w�ɕ������A ���ꂼ�ꂪ�Ɨ����ĊJ���ł���悤�ɂ��܂��B
*/

// �����͂��ׂĂ̎����N���X�̃C���^�t�F�[�X���`���܂��B�����͒��ۂ̃C���^�t�F�[�X�ƈ�v����K�v�͂���܂���B
// ���ہA2�̃C���^�t�F�[�X�͊��S�ɈقȂ�ꍇ������܂��B�ʏ�A�����C���^�t�F�[�X�̓v���~�e�B�u����݂̂�񋟂��܂����A
// ���ۂ͂����̃v���~�e�B�u�Ɋ�Â��Ă�荂���x���̑�����`���܂��B
class Implementation
{
public:
    virtual ~Implementation() {}
    virtual std::string OperationImplementation() const = 0;
};

// �e��ێ����͓���̃v���b�g�t�H�[���ɑΉ����Ă���A���̃v���b�g�t�H�[����API���g�p���Ď����C���^�[�t�F�[�X���������܂��B
class ConcreteImplementationA : public Implementation
{
public:
    std::string OperationImplementation() const override
    {
        return "ConcreteImplementationA�F����̓v���b�g�t�H�[��A�ł̌��ʂł�\n";
    }
};

class ConcreteImplementationB : public Implementation
{
public:
    std::string OperationImplementation() const override
    {
        return "ConcreteImplementationB�F����̓v���b�g�t�H�[��B�ł̌��ʂł�\n";
    }
};

// ���ۂ́A2�̃N���X�K�w�́u����v�����̃C���^�t�F�[�X���`���܂��B
// ���ۂ́A�����K�w�̃I�u�W�F�N�g�ւ̎Q�Ƃ��ێ����A���ׂĂ̎��ۂ̍�Ƃ����̃I�u�W�F�N�g�ɈϔC���܂��B
class Abstraction
{
protected:
    Implementation* implementation_;

public:
    Abstraction(Implementation* implementation) :implementation_(implementation) {}

    virtual ~Abstraction() {}

    virtual std::string Operation() const
    {
        return "Abstraction�F���̊����F" +
            this->implementation_->OperationImplementation();
    }
};

// Implementation�N���X��ύX�����ɁAAbstraction���g�����邱�Ƃ��ł��܂�
class ExtendedAbstraction : public Abstraction
{
public:
    ExtendedAbstraction(Implementation* implementation) :Abstraction(implementation) {}

    std::string Operation()const override
    {
        return "ExtendedAbstraction�F�g�����ꂽ����F" +
            this->implementation_->OperationImplementation();
    }
};

// Abstraction�I�u�W�F�N�g�������Implementation�I�u�W�F�N�g�Ƀ����N����鏉�����t�F�[�Y�������A
// �N���C�A���g�R�[�h��Abstraction�N���X�ɂ݈̂ˑ�����K�v������܂��B
// ���̂悤�ɂ��āA�N���C�A���g�R�[�h�͒��ۉ��Ǝ����̔C�ӂ̑g�ݍ��킹���T�|�[�g�ł��܂��B
void ClientCode(const Abstraction& abstraction)
{
    std::cout << abstraction.Operation();
}

// �N���C�A���g�R�[�h�́A���O�ɐݒ肳�ꂽ���ۉ��Ǝ����̔C�ӂ̑g�ݍ��킹�œ���ł���K�v������܂��B
void Bridge_Start()
{
    Implementation* implementation = new ConcreteImplementationA;
    Abstraction* abstraction = new Abstraction(implementation);
    ClientCode(*abstraction);
    std::cout << std::endl;
    delete implementation;
    delete abstraction;

    implementation = new ConcreteImplementationB;
    abstraction = new ExtendedAbstraction(implementation);
    ClientCode(*abstraction);

    delete implementation;
    delete abstraction;
};