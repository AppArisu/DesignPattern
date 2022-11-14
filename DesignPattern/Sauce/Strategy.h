#pragma once
#include<algorithm>
/*
    Strategy �i�X�g���e�W�[�A �헪�j �́A �U�镑���Ɋւ���f�U�C���p�^�[���̈�ŁA �A���S���Y���̃t�@�~���[���`���A
    ���ꂼ��̃A���S���Y����ʌ̃N���X�Ƃ��A �����̃I�u�W�F�N�g�������\�ɂ��܂��B
*/

// Strategy�C���^�[�t�F�C�X�́A�ꕔ�̃A���S���Y���̃T�|�[�g����Ă��邷�ׂẴo�[�W�����ɋ��ʂ��鑀���錾���܂��B
// Context�͂��̃C���^�[�t�F�[�X���g�p���āAConcrete Strategies�Œ�`���ꂽ�A���S���Y�����Ăяo���܂��B
class Strategy
{
public:
    virtual ~Strategy() = default;
    virtual std::string doAlgorithm(std::string_view data) const = 0;
};

// �R���e�L�X�g�́A�N���C�A���g�Ɋ֌W����C���^�t�F�[�X���`���܂��B
class Contexts
{
    // �헪Context�́A�����ꂩ�̐헪�I�u�W�F�N�g�ւ̎Q�Ƃ�ێ����܂��B
    // Context�́A�헪�̋�ۃN���X��F�����܂���BContext�́A�헪�C���^�t�F�[�X����Ă��ׂĂ̐헪�ŋ@�\����K�v������܂��B
private:
    std::unique_ptr<Strategy> strategy_;

    // �ʏ�AContext�̓R���X�g���N�^�[����ăX�g���e�W�[���󂯓���܂����A���s���ɂ����ύX���邽�߂̃Z�b�^�[���񋟂��܂��B
public:
    explicit Contexts(std::unique_ptr<Strategy>&& strategy = {}) : strategy_(std::move(strategy))
    {
    }

    // �ʏ�AContext�ł͎��s����Strategy�I�u�W�F�N�g��u�������邱�Ƃ��ł��܂��B
    void set_strategy(std::unique_ptr<Strategy>&& strategy)
    {
        strategy_ = std::move(strategy);
    }

    // Context�́A�A���S���Y����+�����o�[�W������P�ƂŎ�������̂ł͂Ȃ��A�ꕔ�̍�Ƃ�Strategy�I�u�W�F�N�g�ɈϔC���܂��B
    void doSomeBusinessLogic() const
    {
        if (strategy_) 
        {
            std::cout << "Context: �헪���g�p�����f�[�^�̃\�[�g(���@�͕s��)\n";
            std::string result = strategy_->doAlgorithm("aecbd");
            std::cout << result << "\n";
        }
        else 
        {
            std::cout << "Context: �헪���ݒ肳��Ă��Ȃ�\n";
        }
    }
};

// ��ې헪�ł́A��{�헪�C���^�t�F�[�X�ɏ]���ăA���S���Y������������܂��B�C���^�t�F�[�X�ɂ��A�����̓R���e�L�X�g���Ō����\�ɂȂ�܂��B
class ConcreteStrategyA : public Strategy
{
public:
    std::string doAlgorithm(std::string_view data) const override
    {
        std::string result(data);
        std::sort(std::begin(result), std::end(result));

        return result;
    }
};
class ConcreteStrategyB : public Strategy
{
    std::string doAlgorithm(std::string_view data) const override
    {
        std::string result(data);
        std::sort(std::begin(result), std::end(result), std::greater<>());

        return result;
    }
};

// �N���C�A���g�E�R�[�h�͋�̓I�Ȑ헪��I�����ăR���e�L�X�g�ɓn���܂��B�N���C�A���g�͐������I�����s�����߂ɁA�헪�Ԃ̈Ⴂ��F������K�v������܂��B
void Strategy_Start()
{
    Contexts context(std::make_unique<ConcreteStrategyA>());
    std::cout << "Client: �헪�͒ʏ�̃\�[�g�ɐݒ肳��Ă��܂�\n";
    context.doSomeBusinessLogic();
    std::cout << "\n";
    std::cout << "Client: �헪�͋t�\�[�g�ɐݒ肳��Ă��܂�\n";
    context.set_strategy(std::make_unique<ConcreteStrategyB>());
    context.doSomeBusinessLogic();
}