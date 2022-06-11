#ifndef _Card_C_
#define _Card_C_

#include "card.hpp"
#include <sstream>

std::string Card::getUsername()
{
    return username;
}
bool Card::balanceCheck()
{
    if(balance < 2) return false;
    balance -= 2; cnt++;
    if(balance <= 5) std::cout << username << "余额即将耗尽,请尽快充值" << "\n";//提醒充值
    return true;
}

bool Card::recharge(int x)
{
    if(x < 0)
    {
        return false;
    }
    balance += x;
    return true;
}

void Card::show()
{
    std::cout << "持卡人:" << username << "\n";
    std::cout << "余额: " << balance << "\n";
    std::cout << "已乘坐:" << cnt << "次\n";
}

// void LimitedCard::show()
// {
//     std::cout << "持卡人:" << username << "\n";
//     std::cout << "余额: " << balance << "\n";
//     std::cout << "已乘坐:" << cnt << "次\n";
// }
bool Card::use()
{
    return balanceCheck() ? true : false;
}

// bool LimitedCard::isOutLimit() 
// {
//     if(cnt > 20) return true;
//     if(cnt == 20) std::cout << username << "的公交卡免费使用次数已耗尽" << std::endl;
//     return false;
// }

bool StudentCard::use()
{
    std::cout << "姓名:" << username << " 余额:" << balance << std::endl;
    if(balanceCheck())
    {
        return true;
    }
    return false;
    //return balanceCheck() ? true : false;
}

bool TeacherCard::use()
{
    cnt++;
    std::cout << "姓名:" << username << " 余额:" << balance << std::endl;
    return true;
}

bool LimitedCard::use()
{
    std::cout << "姓名:" << username << " 余额:" << balance << " 已乘坐:" << cnt << std::endl;
    if(cnt < 20) {cnt++;}
    else 
    {
        if(cnt == 21) std::cout << "将从本次乘车开始收费" << std::endl;
        if(!balanceCheck()) return false;
    }
    if(cnt == 20) std::cout << username << "的公交卡免费使用次数已耗尽" << std::endl;
    return true;
}

std::string Card::print()
{
    std::stringstream ss;
    ss << id << " " << type << " " << username << " " << workplace << " " << balance << " " << cnt << " " << endDate << " " << uid << std::endl;
    return ss.str();
}

int Card::getUid()
{
    return uid;
}
#endif