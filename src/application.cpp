#include <iostream>
#include <vector>
#include <cstring>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <windows.h>
#include "card.cpp"
#include "people.cpp"
#include "bus.cpp"

using namespace std;

vector<Bus> busList;
vector<Bus> runningBus;
vector<StudentCard> SCardList;
vector<TeacherCard> TCardList;
vector<LimitedCard> LCardList;
vector<People> peopleList;

int STATION_SIZE;
int Rand(int limit)
{
    return rand()%limit+1;
}

void readBus(string filename)
{
    STATION_SIZE = Rand(7);
    cout << "Reading buslist...\n";
    ifstream file(filename);
    if(!file.good())
    {
        cout << "读取失败" << endl;
        system("pause");
        exit(0);
    }
    string line;
    while(getline(file,line))
    {
        stringstream ss(line);
        int id,maxCnt;
        string type;
        string driverName;
        int startTime;
        int endTime;
        ss >> id >> type >> driverName >> startTime >> endTime >> maxCnt;
        Bus b(id,type,driverName,startTime,endTime,maxCnt);
        for(int i = 1; i <= STATION_SIZE; i++)
        {
            if(rand()%2) b.station.push_back(i);
        }
        busList.push_back(b);
    }
}

void readCard(string filename)
{
    int Date = Rand(2147483640);
    cout << "Reading cardlist...\n";
    ifstream file(filename);
    if(!file.good())
    {
        cout << "读取失败" << endl;
        system("pause");
        exit(0);
    }
    string line;
    while(getline(file,line))
    {
        stringstream ss(line);
        int id,type,uid;
        std::string username;
        std::string workplace;
        int balance;
        int cnt;
        int endDate;
        ss >> id >> type >> username >> workplace >> balance >> cnt >> endDate >> uid;
        if(endDate > Date) continue;
        if(type == 1) TCardList.push_back(TeacherCard(id,type,username,workplace,cnt,endDate,uid));
        else if(type == 2) SCardList.push_back(StudentCard(id,type,username,balance,workplace,cnt,endDate,uid));
        else LCardList.push_back(LimitedCard(id,type,username,balance,workplace,cnt,endDate,uid));
    }
}
void readPeople(string filename)
{
    cout << "Reading peoplelist...\n";
    ifstream file(filename);
    if(!file.good())
    {
        cout << "读取失败" << endl;
        system("pause");
        exit(0);
    }
    string line;
    while(getline(file,line))
    {
        stringstream ss(line);
        int id,cnt;
        string name;
        string sex;
        string carrer;
        string workplace;
        ss >> id >> name >> sex >> carrer >> workplace >> cnt;
        People p(id,name,sex,carrer,workplace,cnt);
        for(auto &i : TCardList)
        {
            if(i.getUid() == p.getId()) 
            {
                p._card = &i;
                break;
            }
        }
        for(auto &i : SCardList)
        {
            if(i.getUid() == p.getId()) 
            {
                p._card = &i;
                break;
            }
        }
        for(auto &i : LCardList)
        {
            if(i.getUid() == p.getId()) 
            {
                p._card = &i;
                break;
            }
        }
        peopleList.push_back(p);
    }
}
void read(string busFile, string cardFile, string peopleFile)
{
    readBus(busFile);
    readCard(cardFile);
    readPeople(peopleFile);
}

void saveBus(string filename)
{
    cout << "Saving busList...\n";
    ofstream file(filename);
    if(!file.good())
    {
        cout << "读取失败" << endl;
        exit(0);
    }
    for(auto &i : busList)
    {
        file << i.print();
    }
}
void saveCard(string filename)
{
    cout << "Saving cardList...\n";
    ofstream file(filename);
    if(!file.good())
    {
        cout << "读取失败" << endl;
        exit(0);
    }
    for(auto &i : TCardList)
    {
        file << i.print();
    }
    for(auto &i : SCardList)
    {
        file << i.print();
    }
    for(auto &i : LCardList)
    {
        file << i.print();
    }
}
void savePeople(string filename)
{
    cout << "Saving peopleList...\n";
    ofstream file(filename);
    if(!file.good())
    {
        cout << "读取失败" << endl;
        exit(0);
    }
    for(auto &i : peopleList)
    {
        file << i.print();
    }
}
void save(string busFile, string cardFile, string peopleFile)
{
    saveBus(busFile);
    saveCard(cardFile);
    savePeople(peopleFile);
}

void cardManagement()
{
    cout << "请输入您的用户id:";
    int id; cin >> id;
    People* p = nullptr;
    for(auto &i : peopleList)
    {
        if(id == i.getId())
        {
            p = &i;
            break;
        }
    }
    cout << "1.申请新卡\n2.注销卡\n3.充值\n";
    int opt; cin >> opt;
    if(opt == 1)
    {
        p->login();
    }
    else if(opt == 2)
    {
        p->logout();
        for(int i = 0; i < TCardList.size(); i++)
        {
            if(TCardList[i].getUid() == p->getId())
            {
                swap(*(begin(TCardList)+i),*(end(TCardList)-1));
                TCardList.pop_back();
            }
        }
        for(int i = 0; i < SCardList.size(); i++)
        {
            if(SCardList[i].getUid() == p->getId())
            {
                swap(*(begin(SCardList)+i),*(end(SCardList)-1));
                SCardList.pop_back();
            }
        }
        for(int i = 0; i < LCardList.size(); i++)
        {
            if(LCardList[i].getUid() == p->getId())
            {
                swap(*(begin(LCardList)+i),*(end(LCardList)-1));
                LCardList.pop_back();
            }
        }
    }
    else 
    {
        if(!p->pay()) cout << "充值失败" << endl;
        else cout << "充值成功" << endl;
    }
}

void start()
{
    for(auto &i : peopleList) i.onBus = false;
    for(int clk = 6; clk <= 20; clk++)
    {
        for(auto &i : busList)
        {
            if(i.startTime == clk)
            {
                runningBus.push_back(i);
            }
            if(i.endTime == clk)
            {
                for(int pos = 0; pos < runningBus.size(); pos++)
                {
                    if(runningBus[pos].id == i.id)
                    {
                        for(auto &k : busList)
                        {
                            if(runningBus[pos].id == k.id)
                            {
                                k = runningBus[pos];
                            }
                        }
                        runningBus.erase((begin(runningBus)+pos));
                        break;
                    }
                }
                i.clear();
            }
        }
        for(int i = 1; i <= STATION_SIZE; i++)
        {
            for(auto &bus : runningBus)
            {
                for(int j : bus.station)
                {
                    if(i == j)
                    {
                        //乘客下车
                        for(auto &p : bus.passenger)
                        {
                            if(p.offplace == j)
                            {
                                if(p.onBus == true) 
                                    bus.uncheck(p);
                            }
                        }
                        //乘客上车
                        for(auto &p : peopleList)
                        {
                            if(p.onBus == false)
                            {
                                if(Rand(10) < 5)
                                {
                                    p.onplace = j;
                                    p.offplace = bus.station[Rand(bus.station.size())-1];
                                    bus.check(p);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

int main(int argc, char* argv[])
{
    srand(time(0));
    SetConsoleOutputCP(65001);
    string busFile = "E:\\WorkSpace\\card-ride-system\\src\\bus.txt";
    string cardFile = "E:\\WorkSpace\\card-ride-system\\src\\card.txt";
    string peopleFile = "E:\\WorkSpace\\card-ride-system\\src\\people.txt";
    busFile = argv[1], cardFile = argv[2], peopleFile = argv[3];
    read(busFile,cardFile,peopleFile);
    cout << "1.公交卡管理\n2.运行模拟\n3.查询车辆信息\nelse.退出\n";
    int opt;
    while(cin >> opt)
    {
        switch(opt)
        {
            case 1:
            {
                cardManagement();
                break;
            }
            case 2:
            {
                start();
                ofstream file("E:\\WorkSpace\\card-ride-system\\src\\runInfo.txt",ios::trunc);
                file.close();
                for(auto &i : busList)
                {
                    i.runInfo();
                }
                break;
            }
            case 3:
            {
                for(auto &i : busList)
                {
                    i.show();
                }
                break;
            }
            default:
            {
                save(busFile,cardFile,peopleFile);
                exit(0);
            }
        }
        save(busFile,cardFile,peopleFile);
        cout << "1.公交卡管理\n2.运行模拟\n3.查询车辆信息\nelse.退出\n";
    }

    save(busFile,cardFile,peopleFile);
    system("pause");
    return 0;
}