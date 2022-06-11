#ifndef _Bus_C_
#define _Bus_C_

#include "bus.hpp"
#include <sstream>
#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>

void Bus::show()
{
    std::cout << "车牌号:" << id << "\n";
    std::cout << "型号: " << type << "\n";
    std::cout << "驾驶员:" << driverName << "\n";
    std::cout << "核载: " << maxCnt << "人\n";
    std::cout << "乘载: " << realCnt << "人\n";
    std::cout << "时段: " << startTime << "-" << endTime << "\n";
}

void Bus::check(People &p)
{
    if(!full)
    {
        if(p.ride())
        {
            realCnt++;
            if(realCnt >= maxCnt) full = true;
            passenger.push_back(p);
            std::string s = std::to_string(p.onplace) + "号车站" + p.getName() + "乘上本号巴士\n";
            //std::cout << id << s << std::endl;
            Info.push(s);
            //std::cout << RunInfo << std::endl;
        }
        else
        {
            std::cout << p.getName() << "无法乘车" << "\n";
        }
    }
    else 
    {
        std::cout << id << "号巴士人员已满" << "\n";
    }
}

void Bus::uncheck(People &p)
{
    p.unride();
    std::string s = std::to_string(p.offplace) + "号车站" + p.getName() + "下车\n";
    //cout << id << s;
    Info.push(s);
    for(int i = 0; i < passenger.size(); i++)
    {
        if(passenger[i].getId() == p.getId())
        {
            std::swap(*(begin(passenger)+i),*(end(passenger)-1));
            passenger.pop_back();
        }
    }
    realCnt--;
    if(realCnt < maxCnt) full = false;
}

bool Bus::isFull()
{
    return full;
}

void Bus::cal()
{
    passRate = realCnt / maxCnt;
}

std::string Bus::print()
{
    std::stringstream ss;
    ss << id << " " << type << " " << driverName << " " << startTime << " " << endTime << " " << maxCnt << std::endl;
    return ss.str();
}

void Bus::runInfo()
{
    string s;
    s += to_string(id) + "号公交车";
    //std::cout << id << "号公交车";
    for(int i = 0; i < station.size(); i++)
    {
        s += to_string(station[i]);
        //std::cout << station[i];
        if(i < station.size()-1) s += "->";//std::cout << "->";
    }
    //std::cout << std::endl;
    ofstream file("E:\\WorkSpace\\card-ride-system\\src\\runInfo.txt",ios::app | ios::out);
    stringstream sss(s);
    //cout << sss.str() << endl;
    file << sss.str() << endl;
    while(!Info.empty())
    {
        string u = Info.front();
        //cout << u << endl;
        stringstream ss(u);
        Info.pop();
        file << ss.str();
    }
    while(!Info.empty()) Info.pop();
}

void Bus::clear()
{
    string s = "车辆已到站\n";
    Info.push(s); 
    for(auto &i : passenger)
    {
        uncheck(i);
    }
    realCnt = 0;
    full = false;
    passenger.clear();
}

#endif