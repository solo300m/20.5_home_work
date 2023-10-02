#include <fstream>
#include <iostream>
#include <ctime>
#include <vector>

using namespace std;

bool saveArr(string path, vector<vector<int>> *arr, int wight, int height)
{
    ofstream file(path);
    if (file.is_open())
    {
        for (int i = 0; i < wight; i++)
        {
            vector<int> tmp = arr->at(i);
            for (int j = 0; j < height; j++)
            {
                file << tmp.at(j);
            }
            file << endl;
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
int main()
{
    int wight;
    int height;
    string path = "C:\\develop\\Tasks_20_5\\pic.txt";
    srand(time(0));
    cout << "Ввести ширину: ";
    cin >> wight;
    cout << "Ввести высоту: ";
    cin >> height;
    // int arr[wight][height];
    vector<vector<int>> arr;

    for (int i = 0; i < wight; i++)
    {
        vector<int> tmp;
        for (int j = 0; j < height; j++)
        {
            int sing = rand() % 2;
            tmp.push_back(sing);
        }
        arr.push_back(tmp);
    }
    if (saveArr(path, &arr, wight, height))
    {
        cout << "Картинка сохранена в файле "
             << "\"" << path << "\"" << endl;
    }
    else
    {
        cout << "Что то пошло не так. Картинка не сохранена в файле..." << endl;
    }
}
