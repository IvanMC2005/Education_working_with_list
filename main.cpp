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
    cout << "Введите название файла ";
    cin >> filename;
    ifstream fl;
    fl.open(filename);
    if (!fl.is_open())
    {
        cout << "Не удалось открыть файл";
        return -1;
    }
    fl.close();
    train = readfile(filename);
    int menu;
    do
    {
        do
        {
            cout << "1 - Удалить элемент в начале списка \n 2 - Просмотр списка \n 3 - Вывести номера поездов и время их отправления в определенный город в заданном временном интервале.\n 4 - Получить информацию о наличии билетов на поезд с определенным номером.\n 5 - Добавить новый элеменет в список.\n6 - Выход из меню\n";
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
                    cout << "Введите нижнюю границу временного промежутка ";
                    cin >> lowdegree;
                    cin.clear();
                    char ch;
                    //while((ch=getch()) != '/n');
                    fflush(stdin);
                }
                while(cin.fail());
                cout << endl;
                cout << "Введите верхнюю границу временного промежутка ";
                cin >> upperdegree;
                cout << endl;
                cout << "Введите называние станции ";
                cin >> namestation;
                cout << endl;
                findtrains(train, lowdegree, upperdegree, namestation);
                break;
            }
            case 4:
            {
                int number;
                cout << "Введите номер искомого поезда";
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
        cout << "Файл сохранён";
    else
        cout << "Файл не сохранён";
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
                cout << "Поезд под номером " << temp->data.number << " отправляется в указанный город в указанном промежутке времени\n";
            }
        }
        temp = temp->next;
    }
}

void fillstruct(datatype & type)
{
    cout << "Введите номер поезда ";
    cin >> type.number;
    cout << endl;
    cout << "Введите время в пути поезда ";
    cin >> type.road_time;
    cout << endl;
    cout << "Введите время отправления поезда ";
    cin >> type.start_time;
    cout << endl;
    cout << "Введите название станции ";
    cin >> type.staton;
    cout << endl;
    cout << "Есть ли бидеты на этот поезд ";
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
            cout << "На поезд с данным номером есть билеты";
            flag = 1;
        }
        temp = temp->next;
    }
    if (flag == 0)
    {
        cout << "На указанный поезд нет билетов или не удалось найти этот поезд";
    }
}


void showtrains(node * beginer)
{
    cout << "Номер станции  ";
    cout << "Название станции  ";
    cout << "Время отправления  ";
    cout << "Время в пути  ";
    cout << "Наличие билетов";
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
        cout << "Не удалось открыть файл";
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
