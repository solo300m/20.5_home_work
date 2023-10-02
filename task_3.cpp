#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

int takeFish(string type)
{
    int count = 0;
    string pathIn = "fish.txt";
    string pathOut = "basket.txt";
    vector<string> fish;
    ifstream fileIn(pathIn);
    if (fileIn.is_open())
    {
        string tmp;
        while (!fileIn.eof())
        {
            fileIn >> tmp;
            if (tmp == type)
            {
                fish.push_back(tmp);
                count++;
            }
        }
        fileIn.close();
    }
    else
    {
        cout << "Файл не был найден!";
    }
    if (!fish.empty())
    {
        ofstream fileOut(pathOut, std::ios::app);
        if (fileOut.is_open())
        {
            for (string s : fish)
            {
                fileOut << s << endl;
            }
            fileOut.close();
        }
        else
        {
            cout << "Не возможно записать информацию...";
        }
    }
    else
    {
        cout << "Ни чего не поймано!";
    }
    return count;
}

int main()
{
    char fish;
    int count;
    cout << "Выберите рыбу, которую хотите поймать" << endl;
    cout << "a - sunfish" << endl;
    cout << "b - shad" << endl;
    cout << "c - carp" << endl;
    cout << "d - bass" << endl;
    cout << "f - bullhead" << endl;
    cout << "e - walleye" << endl;
    cout << "k - catfish" << endl;
    cout << "Ввод ->";
    cin >> fish;
    switch (fish)
    {
    case 'a':
    {
        count = takeFish("sunfish");
        cout << "Поймано " << count << " sunfish!";
        break;
    }
    case 'b':
    {
        count = takeFish("shad");
        cout << "Поймано " << count << " shad!";
        break;
    }
    case 'c':
    {
        count = takeFish("carp");
        cout << "Поймано " << count << " carp!";
        break;
    }
    case 'd':
    {
        count = takeFish("bass");
        cout << "Поймано " << count << " bass!";
        break;
    }
    case 'f':
    {
        count = takeFish("bullhead");
        cout << "Поймано " << count << " bullhead!";
        break;
    }
    case 'e':
    {
        count = takeFish("walleye");
        cout << "Поймано " << count << " walleye!";
        break;
    }
    case 'k':
    {
        count = takeFish("catfish");
        cout << "Поймано " << count << " catfish!";
        break;
    }
    default:
        count = 0;
        cout << "Такой рыбы тут не водится!";
        break;
    }
}
