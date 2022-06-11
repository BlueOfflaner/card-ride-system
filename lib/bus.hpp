#ifndef _Bus_H_
#define _Bus_H_

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <queue>
#include "people.hpp"
using namespace std;

class Bus
{
public:
    Bus();
    Bus(int id, std::string type, std::string driverName,
        int startTime, int endTime, int maxCnt) 
        : id(id), type(type), driverName(driverName), startTime(startTime),
        endTime(endTime), maxCnt(maxCnt)
        {};
    ~Bus() {};

    void show();
    void runInfo(); //运行信息
    void check(People &p); //乘客上车,检查人员并调用人的ride方法
    void cal();
    bool isFull();
    std::string print();
    void clear();
    void uncheck(People &p);

    std::vector <int> station;
    int startTime;
    int endTime;
    int id;
    std::vector <People> passenger;
    queue <string> Info;
private:
    
    std::string type;
    std::string driverName;
    std::string realStime;
    std::string realEtime;
    int maxCnt;
    int realCnt;
    bool full = false;
    double timeRate;
    double passRate; //实际乘车人数与核载人数比
};

#endif