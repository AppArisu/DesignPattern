#pragma once
#include<unordered_map>
/*
    Flyweight �i�t���C�E�F�C�g�A �t���C���j �́A �\���Ɋւ���f�U�C���p�^�[���̈�ŁA �����̃I�u�W�F�N�g�Ԃŋ��ʂ��镔�����e���Ŏ�����ɋ��L���邱�Ƃɂ���āA
    ���p�\�� RAM �ɂ�葽���̃I�u�W�F�N�g�����߂���悤�ɂ��܂��B
*/

struct SharedState
{
    std::string brand_;
    std::string model_;
    std::string color_;

    SharedState(const std::string& brand, const std::string& model, const std::string& color)
        : brand_(brand), model_(model), color_(color)
    {
    }

    friend std::ostream& operator<<(std::ostream& os, const SharedState& ss)
    {
        return os << "[ " << ss.brand_ << " , " << ss.model_ << " , " << ss.color_ << " ]";
    }
};

struct UniqueState
{
    std::string owner_;
    std::string plates_;

    UniqueState(const std::string& owner, const std::string& plates)
        : owner_(owner), plates_(plates)
    {
    }

    friend std::ostream& operator<<(std::ostream& os, const UniqueState& us)
    {
        return os << "[ " << us.owner_ << " , " << us.plates_ << " ]";
    }
};

class Flyweight
{
private:
    SharedState* shared_state_;

public:
    Flyweight(const SharedState* shared_state) :shared_state_(new SharedState(*shared_state_))
    {
    }
    Flyweight(const Flyweight& other) :shared_state_(new SharedState(*other.shared_state_))
    {
    }
    ~Flyweight()
    {
        delete shared_state_;
    }
    SharedState* shared_state()const
    {
        return shared_state_;
    }
    void Operation(const UniqueState& unique_state) const
    {
        std::cout << "Flyweight: Displaying shared (" << *shared_state_ << ") and unique (" << unique_state << ") state.\n";
    }
};

class FlyweightFactory
{
private:
    std::unordered_map<std::string, Flyweight> flyweights_;

    std::string GetKey(const SharedState& ss)const
    {
        return ss.brand_ + "_" + ss.model_ + "_" + ss.color_;
    }

public:
    FlyweightFactory(std::initializer_list<SharedState>share_states)
    {
        for (const SharedState& ss : share_states)
        {
            this->flyweights_.insert(std::make_pair<std::string, Flyweight>(this->GetKey(ss), Flyweight(&ss)));
        }
    }

    Flyweight GetFlyweight(const SharedState& shared_state)
    {
        std::string key = this->GetKey(shared_state);
        if (this->flyweights_.find(key) == this->flyweights_.end())
        {
            std::cout << "FlyweightFactory�F�t���C�E�F�C�g��������܂���B�V�����t���C�E�F�C�g���쐬���Ă��܂�\n";
            this->flyweights_.insert(std::make_pair(key, Flyweight(&shared_state)));
        }
        else
        {
            std::cout << "FlyweightFactory�F�����̃t���C�E�F�C�g���ė��p����\n";
        }
        return this->flyweights_.at(key);
    }

    void ListFlyweight()const
    {
        size_t count = this->flyweights_.size();
        std::cout << "\nFlyweightFactory�F����" << count << "�̃t���C�E�F�C�g�������Ă��܂�\n";
        for (std::pair<std::string, Flyweight>pair : this->flyweights_)
        {
            std::cout << pair.first << "\n";
        }
    }
};

void AddCarToPoliceDataBase(
    FlyweightFactory& ff, const std::string& plates, const std::string& owner,
    const std::string& brand, const std::string& model, const std::string& color)
{
    std::cout << "\nClient�F�Ԃ��f�[�^�x�[�X�ɒǉ�����\n";
    const Flyweight& flyweight = ff.GetFlyweight({ brand,model,color });
    flyweight.Operation({ owner,plates });
}

void Flyweight_Start()
{
    FlyweightFactory* factory = new FlyweightFactory(
        {
            {"Chevrolet", "Camaro2018", "pink"},
            {"Mercedes Benz", "C300", "black"},
            {"Mercedes Benz", "C500", "red"},
            {"BMW", "M5", "red"},
            {"BMW", "X6", "white"}
        });
    factory->ListFlyweight();

    AddCarToPoliceDataBase(*factory,
        "CL234IR",
        "James Doe",
        "BMW",
        "M5",
        "red");

    AddCarToPoliceDataBase(*factory,
        "CL234IR",
        "James Doe",
        "BMW",
        "X1",
        "red");
    factory->ListFlyweight();
    delete factory;
}