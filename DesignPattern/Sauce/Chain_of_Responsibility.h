#pragma once
#include <iostream>
#include <vector>
#include <string>
/*
    Chain of Responsibility �i�ӔC�̘A���j �́A �U�镑���Ɋւ���f�U�C���p�^�[���̈�ŁA �n���h���[�̘A���ɉ����ă��N�G�X�g��n�����Ƃ��ł��܂��B
    �e�n���h���[�́A ���N�G�X�g���󂯎��ƁA ���N�G�X�g���������邩�A �A�����̎��̃n���h���[�ɓn���������߂܂��B
*/

// Handler�C���^�[�t�F�[�X�́A�n���h���[�̃`�F�[�����\�z���邽�߂̃��\�b�h��錾���܂��B
// �܂��A�v�������s���邽�߂̃��\�b�h���錾���܂��B
class Handler
{
public:
    virtual Handler* SetNext(Handler* handler) = 0;
    virtual std::string Handle(std::string requires) = 0;
};

// �f�t�H���g�̘A������́A�x�[�X�E�n���h���[�E�N���X�̒��Ɏ������邱�Ƃ��ł��܂��B
class AbstractHandler :public Handler
{
private:
    Handler* next_handler_;

public:
    AbstractHandler() :next_handler_(nullptr) {}

    Handler* SetNext(Handler* handler) override 
    {
        // ��������n���h����Ԃ��ƁA���̂悤�ȕ֗��ȕ��@�Ńn���h���������N�ł��܂��B
        this->next_handler_ = handler;
        return handler;
    }

    std::string Handle(std::string requires) override
    {
        if (this->next_handler_)
        {
            return this->next_handler_->Handle(requires);
        }
        return {};
    }
};

// ���ׂĂ�Concrete Handler�́A�v�����������邩�A�`�F�[�����̎��̃n���h���[�ɗv����n���܂��B
class MonkeyHandler : public AbstractHandler {
 public:
  std::string Handle(std::string request) override {
    if (request == "�o�i�i") {
        return "�T��:" + request + "��H�ׂ܂�.\n";
    } else {
      return AbstractHandler::Handle(request);
    }
  }
};
class SquirrelHandler : public AbstractHandler {
 public:
  std::string Handle(std::string request) override {
    if (request == "�i�b�c") {
        return "���X:" + request + "��H�ׂ܂�.\n";
    } else {
      return AbstractHandler::Handle(request);
    }
  }
};
class DogHandler : public AbstractHandler {
 public:
  std::string Handle(std::string request) override {
    if (request == "�~�[�g�{�[��") {
        return "�C�k:" + request + "��H�ׂ܂�.\n";
    } else {
      return AbstractHandler::Handle(request);
    }
  }
};

// �N���C�A���g�E�R�[�h�͒ʏ�A�P��̃n���h���𑀍삷��̂ɓK���Ă��܂��B
// �قƂ�ǂ̏ꍇ�A�N���C�A���g�E�R�[�h�̓n���h�����`�F�[���̈ꕔ�ł��邱�Ƃ����F�����܂���B
void ClientCode(Handler& handler)
{
    std::vector<std::string> food = { "�i�b�c", "�o�i�i", "�R�[�q�[��t" };
    for (const std::string& f : food) {
        std::cout << "�N���C�A���g: " << f << "���~�����l�H\n";
        const std::string result = handler.Handle(f);
        if (!result.empty()) {
            std::cout << "  " << result;
        }
        else {
            std::cout << "  " << f << " ������̂܂܂�����.\n";
        }
    }
}

void CofR_Start()
{
    MonkeyHandler* monkey = new MonkeyHandler;
    SquirrelHandler* squirrel = new SquirrelHandler;
    DogHandler* dog = new DogHandler;
    monkey->SetNext(squirrel)->SetNext(dog);
    //squirrel->SetNext(monkey)->SetNext(dog);

    std::cout << "�N���C�A���g: �T�� > ���X > �C�k\n\n";
    ClientCode(*monkey);
    std::cout << "\n";
    std::cout << "�T�u�`�F�C��: ���X > �C�k\n\n";
    ClientCode(*squirrel);

    delete monkey;
    delete squirrel;
    delete dog;
}