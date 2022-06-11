#ifndef _Card_H_
#define _Card_H_

#include <iostream>
#include <vector>
#include <string>

class Card
{
public:
    Card();
    Card(int id, int type, std::string username, int balance,
        std::string workplace, int cnt, int endDate, int uid) 
        : id(id), username(username), workplace(workplace),
        balance(balance), cnt(cnt), endDate(endDate), type(type), uid(uid)
        {};
    ~Card() {};

    virtual bool use();
    bool balanceCheck();
    bool recharge(int x=0);
    void show();
    std::string getUsername();
    std::string print();
    int getUid();

protected:
    int id;
    int type;
    std::string username;
    std::string workplace;
    int balance;
    int cnt;
    int endDate;
    int uid;
};


class StudentCard : public Card
{
public:
    StudentCard(int id, int type, std::string username, int balance, std::string workplace, int cnt, int endDate, int uid) 
        : Card(id, type, username, balance, workplace, cnt, endDate, uid) {};
    bool use();
};

class TeacherCard : public Card
{
public:
    TeacherCard(int id, int type, std::string username, std::string workplace, int cnt, int endDate, int uid) 
        : Card(id, type, username, 0, workplace, cnt, endDate, uid) {};
    bool use();
};

class LimitedCard : public Card
{
public:
    LimitedCard(int id, int type, std::string username, int balance, std::string workplace, int cnt, int endDate,int uid) 
        : Card(id, type, username, balance, workplace, cnt, endDate, uid) {};
    bool isOutLimit();
    bool use();
    // void show();
};

#endif