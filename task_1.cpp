#include <fstream>
#include <iostream>
#include <vector>
#include <string>

using namespace std;
bool strVerify(string &str)
{
    int count = 0;
    while (count < str.length())
    {
        if (isalpha((char)str[count]))
        {
            if (!isupper((char)str[0]))
            {
                str[0] = toupper((char)str[0]);
            }
        }
        else
        {
            cout << "В имени и фамилии недопустимо использовать цыфры.";
            return false;
        }
        count++;
    }
    return true;
}
bool dblVerify(string data)
{
    string tmp = data;
    int count = 0;
    int punct = 0;
    while (count < tmp.length())
    {
        if (isalpha((char)tmp[count]))
        {
            cout << "В сумме выплаты необходимо использовать только цифры.";
            return false;
        }
        if ((char)tmp[count] == '.' && punct == 0)
        {
            punct++;
        }
        else if ((char)tmp[count] == '.' && punct >= 1)
        {
            cout << "Допущено применение знаков пунктуации, отличных от '.', либо знаков '.' больше одной";
            return false;
        }
        count++;
    }
    return true;
}
bool checkDayOfMonth(string &str)
{
    if (str.length() < 10)
    {
        return false;
    }
    for (int i = 0; i < str.length(); i++)
    {
        if (i == 0 || i == 1)
        {
            if (!isdigit(str[i]))
            {
                return false;
            }
        }
        else if (i == 2 && str[i] != '.')
        {
            return false;
        }
        else if (i == 3 || i == 4)
        {
            if (!isdigit(str[i]))
            {
                return false;
            }
        }
        else if (i == 5 && str[i] != '.')
        {
            return false;
        }
        else if ((i == 6 || i == 7) || (i == 8 || i == 9))
        {
            if (!isdigit(str[i]))
            {
                return false;
            }
        }
    }
    string tmp;
    tmp += str[0];
    tmp += str[1];

    string month;
    month += str[3];
    month += str[4];

    int day = stoi(tmp);
    int mon = stoi(month);
    if (mon > 12)
    {
        cout << "Месяц не может быть больше 12";
        return false;
    }
    else
    {
        if (day > 31)
        {
            cout << "Номер дня не может привышать 31 день." << endl;
            return false;
        }
        else if (day == 31 && (((mon == 1 || mon == 3) || (mon == 5 || mon == 7))) || ((mon == 8 || mon == 10) || mon == 12))
        {
            return true;
        }
        else if (day == 30 && ((mon == 4 || mon == 6) || (mon == 9 || mon == 11)))
        {
            return true;
        }
        else if (day == 28 && mon == 2)
        {
            return true;
        }
        else if (day == 29 && mon != 2)
        {
            return true;
        }
        else if ((day > 0 && day < 30) && mon != 2)
        {
            return true;
        }
        else if ((day > 0 && day < 28) && mon == 2)
        {
            return true;
        }
        else
        {

            return false;
        }
    }
}
bool datVerify(string &d)
{
    if (d[0] == '.')
    {
        cout << "Дата должна начинаться с номера дня месяца" << endl;
        return false;
    }
    if (d[1] == '.')
    {
        d.insert(0, "0");
    }
    if (d[4] == '.')
    {
        d.insert(3, "0");
    }

    if (!checkDayOfMonth(d))
    {
        cout << "С введенной датой что то не то... Проверьте пожалуйста!";
        return false;
    }

    int i = 0;
    while (i < d.length())
    {
        if (isdigit(d[i]) || (d[i] == '.' && d[i + 1] != '.'))
        {
            i++;
        }
        else
        {
            cout << "Формат введенного значения не соответствует заданному!";
            return false;
        }
    }
    return true;
}
void inputData(vector<string> *name, vector<string> *lastName, vector<double> *sayl, vector<string> *date)
{
    string n;
    string &ptrName = n;
    string lN;
    string &ptrLN = lN;
    string s;
    string d;
    string &ptr = d;
    do
    {
        cout << "Введите имя (начиная с большой буквы): ";
        cin >> n;
    } while (!strVerify(ptrName));

    do
    {
        cout << "\nВведите фамилию (начиная с большой буквы): ";
        cin >> lN;
    } while (!strVerify(ptrLN));
    do
    {
        cout << "\nВведите сумму выплаты: ";
        cin >> s;
    } while (!dblVerify(s));
    double sal = stod(s);
    do
    {
        cout << "Введите дату (формат ДД.ММ.ГГГГ): ";
        cin >> d;
    } while (!datVerify(ptr));
    name->push_back(n);
    lastName->push_back(lN);
    sayl->push_back(sal);
    date->push_back(d);
}

void displyData(vector<string> *name, vector<string> *lastName, vector<double> *sayl, vector<string> *date)
{
    cout << "Имя    "
         << "\t"
         << "Фамилия   "
         << "\t"
         << "Сумма выплаты"
         << "\t"
         << "Дата   " << endl;
    for (int i = 0; i < name->size(); i++)
    {
        cout << name->at(i)
             << "\t"
             << lastName->at(i)
             << "\t"
             << sayl->at(i)
             << "         \t"
             << date->at(i) << endl;
    }
}
bool saveInFile(string path, vector<string> *name, vector<string> *lastName, vector<double> *sayl, vector<string> *date)
{
    ofstream file(path, std::ios::app);
    if (file.is_open())
    {
        for (int i = 0; i < name->size(); i++)
        {
            file << name->at(i) << " " << lastName->at(i) << " " << sayl->at(i) << " " << date->at(i) << endl;
        }
        file.close();
        return true;
    }
    else
    {
        file.close();
        return false;
    }
}
void delInVector(vector<string> *name, vector<string> *lastName, vector<double> *sayl, vector<string> *date)
{
    name->clear();
    lastName->clear();
    sayl->clear();
    date->clear();
}
int main()
{
    vector<string> name;
    vector<string> lastName;
    vector<double> sayl;
    vector<string> date;
    string path = "C:\\develop\\Tasks_20_5\\sayl.txt";
    char newStr = 'y';
    while (newStr != 'Q')
    {
        inputData(&name, &lastName, &sayl, &date);
        cout << "Продолжить ввод данных? Если да нажмите любой символ на клавиатуре. Если нет - 'Q' ";
        cin >> newStr;
    }
    displyData(&name, &lastName, &sayl, &date);
    if (saveInFile(path, &name, &lastName, &sayl, &date))
    {
        delInVector(&name, &lastName, &sayl, &date);
    }
    else
    {
        cout << "Возникли проблемы с записью данных. Информация в файле не сохранена...";
    }
}
