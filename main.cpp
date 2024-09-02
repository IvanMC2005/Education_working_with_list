#include <iostream>
#include <locale.h>
#include <fstream>
#include <iomanip>
#include <ctime>
#include <cstdio>
#include <cconio>
using namespace std;

typedef struct
{
    int number;
    char staton[10];
    int start_time;
    int road_time;
    unsigned int tickets;
} datatype;

struct node
{
    datatype data;
    struct node * next;
};
void findtrains(node * temp, int lowdegree, int upperdegree, string townname);
void fillstruct(datatype & type);
void showtrains(node * beginer);
node * deleteobject(node * beginer);
void deletelist (node * beg);
int writefile(string filename, node * beg);
node * newnode(node * begintr, datatype type);
node * readfile(string filename);
void get_inf(node * temp, int number);
int main(int argc, char *argv[])
{
    setlocale(0, "rus");
    /*srand(time(NULL));
    ofstream file;
    file.open("myfile.odt");
    datatype datap;
    for (int i{0}; i < 100; i++)
    {
        datap.number = rand() % 100;
        datap.road_time = rand() % 1500;
        datap.tickets = rand() % 2;
        datap.start_time = rand() % 1440;
        file.write((char *)&datap, sizeof(datatype));
    }*/
    node * train;
    string filename;
    cout << "������� �������� ����� ";
    cin >> filename;
    ifstream fl;
    fl.open(filename);
    if (!fl.is_open())
    {
        cout << "�� ������� ������� ����";
        return -1;
    }
    fl.close();
    train = readfile(filename);
    int menu;
    do
    {
        do
        {
            cout << "1 - ������� ������� � ������ ������ \n 2 - �������� ������ \n 3 - ������� ������ ������� � ����� �� ����������� � ������������ ����� � �������� ��������� ���������.\n 4 - �������� ���������� � ������� ������� �� ����� � ������������ �������.\n 5 - �������� ����� �������� � ������.\n6 - ����� �� ����\n";
            cin >> menu;
            cin.clear();
            fflush(stdin);
        }
        while(cin.fail());
        switch(menu)
        {
            case 1: train = deleteobject(train);break;
            case 2:
            {
                showtrains(train);
                break;
            }
            case 3:
            {
                int lowdegree, upperdegree;
                char namestation[10];
                do
                {
                    cout << "������� ������ ������� ���������� ���������� ";
                    cin >> lowdegree;
                    cin.clear();
                    char ch;
                    //while((ch=getch()) != '/n');
                    fflush(stdin);
                }
                while(cin.fail());
                cout << endl;
                cout << "������� ������� ������� ���������� ���������� ";
                cin >> upperdegree;
                cout << endl;
                cout << "������� ��������� ������� ";
                cin >> namestation;
                cout << endl;
                findtrains(train, lowdegree, upperdegree, namestation);
                break;
            }
            case 4:
            {
                int number;
                cout << "������� ����� �������� ������";
                cin >> number;
                cout << endl;
                get_inf(train, number);
                break;
            }
            case 5:
            {
                datatype tire;
                fillstruct(tire);
                train = newnode(train,tire);
                break;
            }
        }
        cin.ignore();
        char ch;
        cin.get(ch);
        system("cls");
    }
    while(menu != 6);
    if (writefile(filename, train))
        cout << "���� �������";
    else
        cout << "���� �� �������";
    deletelist(train);
    return 0;
}

void findtrains(node * temp, int lowdegree, int upperdegree, string townname)
{
    int flag = 0;
    while(temp->next)
    {
        if ((temp->data.start_time > lowdegree) && (temp->data.start_time > lowdegree))
        {
            for (int i{0};townname[i]!='\0';i++)
            {

                if (temp->data.staton[i] != townname[i])
                {
                    flag = 1;
                    break;
                }
            }
            if (flag == 0)
            {
                cout << "����� ��� ������� " << temp->data.number << " ������������ � ��������� ����� � ��������� ���������� �������\n";
            }
        }
        temp = temp->next;
    }
}

void fillstruct(datatype & type)
{
    cout << "������� ����� ������ ";
    cin >> type.number;
    cout << endl;
    cout << "������� ����� � ���� ������ ";
    cin >> type.road_time;
    cout << endl;
    cout << "������� ����� ����������� ������ ";
    cin >> type.start_time;
    cout << endl;
    cout << "������� �������� ������� ";
    cin >> type.staton;
    cout << endl;
    cout << "���� �� ������ �� ���� ����� ";
    cin >> type.tickets;
    cout << endl;
}

void get_inf(node * temp, int number)
{
    char flag = 0;
    while(temp->next)
    {
        if (temp->data.number == number && temp->data.tickets == 1)
        {
            cout << "�� ����� � ������ ������� ���� ������";
            flag = 1;
        }
        temp = temp->next;
    }
    if (flag == 0)
    {
        cout << "�� ��������� ����� ��� ������� ��� �� ������� ����� ���� �����";
    }
}


void showtrains(node * beginer)
{
    cout << "����� �������  ";
    cout << "�������� �������  ";
    cout << "����� �����������  ";
    cout << "����� � ����  ";
    cout << "������� �������";
    cout << endl;
    while(beginer->next)
    {
        cout << left << setw(23) << beginer->data.number;
        cout << left << setw(10) << beginer->data.staton;
        cout << left << setw(19) << beginer->data.start_time;
        cout << left << setw(14) << beginer->data.road_time;
        cout << left << setw(10) << beginer->data.tickets;
        cout << endl;
        beginer = beginer->next;
    }
}
void deletelist (node * beg)
{
    node * temp;
    temp = beg;
    while(beg)
    {
        beg = beg->next;
        delete temp;
        temp = beg;
    }
}
node * deleteobject(node * beginer)
{
    node * cal;
    if (beginer)
    {
        cal = beginer;
        beginer = beginer->next;
        delete cal;
    }
    return beginer;
}

node * newnode(node * begintr, datatype type)
{
    node * temp = new node;
    temp->data = type;
    temp->next = begintr;
    return temp;
}

int writefile(string filename, node * beg)
{
    ofstream file;
    file.open(filename);
    if (!file.is_open())
    {
        cout << "�� ������� ������� ����";
        return 0;
    }
    while(beg)
    {
        if (file.write((char *)&beg->data, sizeof(datatype)))
            beg = beg->next;
        else
            return 0;
    }
    return 1;
}

node * readfile(string filename)
{
    ifstream file;
    file.open(filename);
    node * begintrain;
    node * curtrain;
    datatype data;
    if (!file.is_open())
    {
        return nullptr;
    }
    if (file.read((char *)&data, sizeof(datatype)))
    {
        begintrain = newnode(nullptr, data);
    }
    else
    {
        return nullptr;
    }
    curtrain = begintrain;
    while(file.read((char *)&data, sizeof(datatype)))
    {
        curtrain->next = newnode(nullptr, data);
        curtrain = curtrain->next;
    }
    file.close();
    return begintrain;
}
