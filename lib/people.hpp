#ifndef _People_H_
#define _People_H_

#include <iostream>
#include <string>
#include <vector>
#include "card.hpp"

class People
{
public:
    People();
    People(int id, std::string name, std::string sex,
        std::string carrer, std::string workplace, int cnt) 
        : id(id), name(name), sex(sex), carrer(carrer), 
        workplace(workplace), cnt(cnt)
        {};
    ~People() {};

    void login(); //申请新卡
    void logout(); //注销
    bool ride(); //乘车
    void unride();
    std::string print();
    std::string getName();
    bool pay();
    int getId();

    Card* _card = nullptr;
    bool onBus = false;
    int onplace;
    int offplace;
protected:
    int id;
    std::string name;
    std::string sex;
    std::string carrer;
    std::string workplace;
    int cnt;
};

class Student : public People
{
    using People::People;
};

class Teacher : public People
{
    using People::People;
};

#endif