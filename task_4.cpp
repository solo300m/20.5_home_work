#include <fstream>
#include <iostream>
using namespace std;
void init(int &r5000, int &r1000, int &r500, int &r200, int &r100)
{
    int number;
    ifstream f("bankomat.bin", ios::binary);
    if (!f.eof())
    {
        int idx = 1;
        while (!f.eof())
        {
            f.read((char *)&number, sizeof(number));
            switch (idx)
            {
            case 1:
                r5000 = number;
                break;
            case 2:
                r1000 = number;
                break;
            case 3:
                r500 = number;
                break;
            case 4:
                r200 = number;
                break;
            case 5:
                r100 = number;
                break;
            default:
                break;
            }
            idx++;
            number = 0;
        }
    }
}
bool saveBankomat(int &r5000, int &r1000, int &r500, int &r200, int &r100)
{
    ofstream file("bankomat.bin", std::ios::binary);
    int number;
    if (file.is_open())
    {
        number = r5000;
        file.write((char *)&number, sizeof(number));
        file.close();
    }
    else
    {
        return false;
    }
    ofstream file2("bankomat.bin", std::ios::binary | ios::app);
    if (file2.is_open())
    {
        number = r1000;
        file2.write((char *)&number, sizeof(number));
        number = r500;
        file2.write((char *)&number, sizeof(number));
        number = r200;
        file2.write((char *)&number, sizeof(number));
        number = r100;
        file2.write((char *)&number, sizeof(number));
        number = 0;
        file2.close();
    }
    else
    {
        return false;
    }
    return true;
}
void addFin(int &r5000, int &r1000, int &r500, int &r200, int &r100, int LIMIT)
{
    int countAll = 0;
    char contin = 'y';
    while (contin != 'Q')
    {
        int nom;
        int count;
        countAll = r5000 + r1000 + r500 + r200 + r100;
        if (countAll == LIMIT)
        {
            cout << "Банкомат заполнен. Добавление купюр невозможно!" << endl;
            break;
        }
        cout << "В банкомате сейчас " << countAll << " купюр" << endl;
        cout << "Для пополнения введите номинал (5000, 1000, 500, 200, 100) и количество вносимых купюр" << endl;
        cout << "Номинал-> ";
        cin >> nom;
        cout << "Количество-> ";
        cin >> count;
        if ((countAll + count) <= LIMIT)
        {
            switch (nom)
            {
            case 5000:
                r5000 += count;
                break;
            case 1000:
                r1000 += count;
                break;
            case 500:
                r500 += count;
                break;
            case 200:
                r200 += count;
                break;
            case 100:
                r100 += count;
                break;
            default:
                break;
            }
        }
        else
        {
            cout << "Слишком много купюр.";
        }
        cout << "\nПродолжить внесение денег в банкомат? Если да, нажмите любую клавишу. Нет - 'Q'." << endl;
        cin >> contin;
    }
    if (saveBankomat(r5000, r1000, r500, r200, r100))
    {
        cout << "Данные после пополнения успешно сохранены!" << endl;
    }
    else
    {
        cout << "Пополнение! Что то пошло не так. Данные не сохранены!..." << endl;
    }
}

void takeFin(int &r5000, int &r1000, int &r500, int &r200, int &r100)
{
    int getSum;
    int currentSum;
    currentSum = 5000 * r5000 + 1000 * r1000 + 500 * r500 + 200 * r200 + 100 * r100;
    if (currentSum == 0)
    {
        cout << "Операция снятия денег временно закрыта, в связи с отсутствием денег в банкомате." << endl;
        return;
    }
    cout << "Введите сумму, кратную 100" << endl;
    cout << "Снять-> ";
    cin >> getSum;

    if (getSum > currentSum)
    {
        cout << "В банкомате нет такой суммы." << endl;
    }
    else
    {
        if (getSum % 100 != 0)
        {
            cout << "Банкомат может выдать сумму " << (getSum - (getSum % 100)) << " или " << (getSum - (getSum % 100)) + 100 << endl;
        }
        else
        {
            int check[5] = {0, 0, 0, 0, 0};
            int delta = getSum;
            if (r5000 != 0 && delta / 5000 != 0)
            {
                if (delta / 5000 <= r5000)
                {
                    r5000 -= delta / 5000;
                    check[0] = delta / 5000;
                    delta = delta % 5000;
                }
                else
                {
                    delta = delta - r5000 * 5000;
                    check[0] = r5000;
                    r5000 = 0;
                }
            }
            if (r1000 != 0 && delta / 1000 != 0)
            {
                if (delta / 1000 <= r1000)
                {
                    r1000 -= delta / 1000;
                    check[1] = delta / 1000;
                    delta = delta % 1000;
                }
                else
                {
                    delta = delta - r1000 * 1000;
                    check[1] = r1000;
                    r1000 = 0;
                }
            }
            if (r500 != 0 && delta / 500 != 0)
            {
                if (delta / 500 <= r500)
                {
                    r500 -= delta / 500;
                    check[2] = delta / 500;
                    delta = delta % 500;
                }
                else
                {
                    delta = delta - r500 * 500;
                    check[2] = r500;
                    r500 = 0;
                }
            }
            if (r200 != 0 && delta / 200 != 0)
            {
                if (delta / 200 <= r200)
                {
                    r200 -= delta / 200;
                    check[3] = delta / 200;
                    delta = delta % 200;
                }
                else
                {
                    delta = delta - r200 * 200;
                    check[3] = r200;
                    r200 = 0;
                }
            }
            if (r100 != 0 && delta / 100 != 0)
            {
                if (delta / 100 <= r100)
                {
                    r100 -= delta / 100;
                    check[4] = delta / 100;
                    delta = delta % 100;
                }
                else
                {
                    delta = delta - r100 * 100;
                    check[4] = r100;
                    r100 = 0;
                }
            }
            int checkSum = 0;
            for (int i = 0; i < 5; i++)
            {
                switch (i)
                {
                case 0:
                    checkSum += (check[i] * 5000);
                    break;
                case 1:
                    checkSum += (check[i] * 1000);
                    break;
                case 2:
                    checkSum += (check[i] * 500);
                    break;
                case 3:
                    checkSum += (check[i] * 200);
                    break;
                case 4:
                    checkSum += (check[i] * 100);
                    break;
                default:
                    break;
                }
            }
            if (checkSum == 0)
            {
                cout << "Банкомат не сможет выдать запрошенную сумму." << endl;
            }
            else if (checkSum == getSum)
            {
                cout << " Деньги в сумме " << getSum << " получены." << endl;
                for (int i = 0; i < 5; i++)
                {
                    if (check[i] != 0)
                    {
                        switch (i)
                        {
                        case 0:
                            cout << "5000 - " << check[i] << " сумма - " << (check[i] * 5000) << endl;
                            break;
                        case 1:
                            cout << "1000 - " << check[i] << " сумма - " << (check[i] * 1000) << endl;
                            break;
                        case 2:
                            cout << "500 - " << check[i] << " сумма - " << (check[i] * 500) << endl;
                            break;
                        case 3:
                            cout << "200 - " << check[i] << " сумма - " << (check[i] * 200) << endl;
                            break;
                        case 4:
                            cout << "100 - " << check[i] << " сумма - " << (check[i] * 100) << endl;
                            break;
                        default:
                            break;
                        }
                    }
                }
            }
        }
    }
    if (saveBankomat(r5000, r1000, r500, r200, r100))
    {
        cout << "Данные после выдачи успешно сохранены!" << endl;
    }
    else
    {
        cout << "Выдача! Что то пошло не так. Данные не сохранены!..." << endl;
    }
}

void displyStatus(int &r5000, int &r1000, int &r500, int &r200, int &r100)
{
    cout << "5000 " << r5000 << " сумма - " << (r5000 * 5000) << endl;
    cout << "1000 " << r1000 << " сумма - " << (r1000 * 1000) << endl;
    cout << "500 " << r500 << " сумма - " << (r500 * 500) << endl;
    cout << "200 " << r200 << " сумма - " << (r200 * 200) << endl;
    cout << "100 " << r100 << " сумма - " << (r100 * 100) << endl;
    cout << "Общий остаток средств - " << (5000 * r5000 + 1000 * r1000 + 500 * r500 + 200 * r200 + 100 * r100) << endl;
}

int main()
{
    const int LIMIT = 1000;
    int k5000 = 0;
    int &r5000 = k5000;
    int k1000 = 0;
    int &r1000 = k1000;
    int k500 = 0;
    int &r500 = k500;
    int k200 = 0;
    int &r200 = k200;
    int k100 = 0;
    int &r100 = k100;
    int countAll = 0;
    init(r5000, r1000, r500, r200, r100);
    char typeOper;
    while (true)
    {
        cout << "Введите тип операции. '+' - операция пополнения, '-' - операция снятия. Для отмены нажмите '*'" << endl;
        cout << "Для получения информации об остатках нажмите - '=': ";
        cin >> typeOper;
        if (typeOper == '+' || typeOper == '-')
        {
            if (typeOper == '+')
            {
                addFin(r5000, r1000, r500, r200, r100, LIMIT);
            }
            else
            {
                takeFin(r5000, r1000, r500, r200, r100);
            }
        }
        else if (typeOper == '*')
        {
            break;
        }
        else if (typeOper == '=')
        {
            displyStatus(r5000, r1000, r500, r200, r100);
        }
        else
        {
            cout << "Вы ввели не правильную операцию. Попробуйте еще раз!";
        }
    }
}
