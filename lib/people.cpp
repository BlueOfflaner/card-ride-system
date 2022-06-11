#ifndef _People_C_
#define _People_C_

#include "people.hpp"
#include "card.hpp"
#include <iostream>
#include <sstream>

void People::login()
{
    Card* tmp = _card;
    if(tmp != nullptr)
    {
        std::cout << "一人仅限持有一张公交卡" << "\n";
        return;
    } 
    tmp = nullptr;
    int opt;
    std::cout << "请选择要申请的一卡通类型";
    std::cin >> opt;
    if(opt == 1) tmp = new TeacherCard(id,1,name,workplace,0,114514,id);
    else if(opt == 2) tmp = new StudentCard(id,2,name,0,workplace,0,114514,id);
    else if(opt == 3) tmp = new LimitedCard(id,3,name,0,workplace,0,114514,id);
    else
    {
        std::cout << "输入错误,请重新输入" << "\n";
        login();
    }
    _card = tmp;
}

void People::logout()
{
    Card* c = _card;
    c = nullptr;
}

bool People::ride()
{
    if(_card == nullptr) return false;
    if((*_card).use())
    {
        cnt++;
        onBus = true;
        return true;
    }
    return false;
}

void People::unride()
{
    if(onBus) onBus = false;
}

std::string People::print()
{
    std::stringstream ss;
    ss << id << " " << name << " " << sex << " " << carrer << " " << workplace << " " << cnt << std::endl;
    return ss.str();
}

std::string People::getName()
{
    return name;
}

int People::getId()
{
    return id;
}

bool People::pay()
{
    if(_card == nullptr)
    {
        std::cout << "您还没有公交卡,请先办理新卡" << std::endl;
        return false;
    }
    else
    {
        std::cout << "请输入要充值的额度:";
        int x; std::cin >> x;
        return (*_card).recharge(x) ? true : false;
    }
    return true;
}

#endif