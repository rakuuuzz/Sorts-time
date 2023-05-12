#include <iostream>
#include <vector>
#include <ctime>
#include <random>

using namespace std;

class Sort
{
    public:
        virtual void Func(vector<int>& num) const = 0;
        virtual vector<int> Print(vector<int> num) const = 0;
};

class EasySort
{
public:
    virtual void Func(vector<int>& num) const = 0;
    virtual vector<int> Print(vector<int> num) const = 0;
};

class BubbleSort : public Sort
{
public:
    void Func(vector<int>& num) const override
    {
    clock_t int_start = clock();
       for (size_t i = 0; i + 1 < num.size(); ++i)
       {
           for (size_t j = 0; j + 1 < num.size() - i; ++j)
           {
               if (num[j + 1] < num[j])
               {
                   swap(num[j], num[j + 1]);
               }
           }
       }
       //Print(num);
    clock_t int_finish = clock();
    cout << "Time: " << (double)(int_finish - int_start) / CLOCKS_PER_SEC << endl;
    }
    vector<int> Print(vector<int> num) const override
    {
        for (size_t i = 0; i < num.size(); i++) {
            cout << num[i];
        }
        cout << endl << ",";
        return num;
    }
};

class ShakeSort : public Sort
{
public:
    void Func(vector<int>& num) const override
    {
        clock_t int_start = clock();
        int left = 0, right = num.size()-1;
    
        try
        {
            if (num.empty())
            {
                throw runtime_error("Array empty");
            }
            while (left <= right) {
                for (int i = right; i > left; --i) {
                    if (num[i - 1] > num[i]) {
                        swap(num[i - 1], num[i]);
                    }
                }
                ++left;
                for (int i = left; i < right; ++i) {
                    if (num[i] > num[i + 1]) {
                        swap(num[i], num[i + 1]);
                    }
                }
                --right;
            }
            //Print(num);
        clock_t int_finish= clock();
        cout << "Time: " << (double)(int_finish - int_start) / CLOCKS_PER_SEC << endl;
        }
        catch (exception& er1)
        {
            cout << "Error!" << endl;
        }
    };
    vector<int> Print(vector<int> num) const override
    {
        for (size_t i = 0; i < num.size(); i++) {
            cout << num[i] << ",";
        }
        cout << endl;
        return num;
    }
};

class ComboSort : public Sort
{
public:

    void Func(vector<int>& num) const override
    {
        clock_t int_start = clock();
        const double factor = 1.247;
        int step = num.size() - 1;
        while (step >= 1)
        {
            for (int i = 0; i + step < num.size(); ++i)
            {
                if (num[i] > num[i + step])
                {
                    swap(num[i], num[i + step]);
                }
            }
            step /= factor;
        }
        for (size_t i = 0; i + 1 < num.size(); ++i)
        {
            for (size_t j = 0; j + 1 < num.size(); ++j)
            {
                if (num[j + 1] < num[j])
                {
                    swap(num[j], num[j + 1]);
                }
            }
        }
        //Print(num);
        clock_t int_finish = clock();
        cout << "Time: " << (double)(int_finish - int_start) / CLOCKS_PER_SEC << endl;
    }
    vector<int> Print(vector<int> num) const override
    {
        for (size_t i = 0; i < num.size(); i++) {
            cout << num[i] << ",";
        }
        cout << endl;
        return num;
    }
};

class FastSort
{
public:
    vector<int> Func(vector<int>& num,int left,int right)
    {
        int l = left;
        int r = right;
        int mid = num[(l+r) / 2];
        do
        {
            while(num[l] < mid)
            {
                ++l;
            }
            while (num[r] > mid)
            {
                --r;
            }
            if (r >= l)
            {
                swap(num[l], num[r]);
                ++l;
                --r;
            }
        } while (l <= r);
        if (r > left) { Func(num,left,r); }
        if (l < right) { Func(num,l,right ); }
        return num;
    }
    vector<int> Print(vector<int>& num)
    {
        for (size_t i = 0; i < num.size(); i++) {
            cout << num[i] << ",";
        }
        cout << endl;
        return num;
    }
};

class InserSort : public EasySort
{
public:
    void Func(vector<int>& num) const override
    {
        clock_t int_start = clock();
        for (size_t i = 1; i < num.size(); ++i)
        {
            int x = num[i];
            size_t j = i;
            while (j > 0 && num[j - 1] > x)
            {
                swap(num[j],num[j - 1]);
                j--;
            }
            num[j] = x;
        }
        clock_t int_finish = clock();
        cout << "Time: " << (double)(int_finish - int_start) / CLOCKS_PER_SEC << endl;
        //Print(num);
    }
    vector<int> Print(vector<int> num) const override
    {
        for (size_t i = 0; i < num.size(); i++) {
            cout << num[i]<< ",";
        }
        cout << endl;
        return num;
    }
};

class ChoosenSort : public EasySort
{
public:
    void Func(vector<int>& num) const override
    {
        clock_t int_start = clock();
        for (auto i = num.begin(); i != num.end(); ++i)
        {
            auto j = std::min_element(i, num.end());
            swap(*i, *j);
        }
        clock_t int_finish = clock();
        cout << "Time: " << (double)(int_finish - int_start) / CLOCKS_PER_SEC << endl;
    }
    vector<int> Print(vector<int> num) const override
    {
        for (size_t i = 0; i < num.size(); i++) {
            cout << num[i] << ",";
        }
        cout << endl;
        return num;
    }
};

class MergeSort
{
public:
    void Func(vector<int>& num, vector<int>& buff,int l,int r)
    {
        if (l < r)
        {
            int m = (l + r) / 2;
            Func(num, buff, l, m);
            Func(num, buff, m + 1, r);

            int k = l;
            for (int i = l, j = m + 1; i <= m || j <= r;)
            {
                if (j > r || (i <= m && num[i] < num[j]))
                {
                    buff[k] = num[i];
                    ++i;
                }
                else
                {
                    buff[k] = num[j];
                    ++j;
                }
                ++k;
            }
            for (int i = l; i <= r; ++i)
            {
                num[i] = buff[i];
            }
        }
    }
    void Merge(vector<int>& num)
    {
        if (!num.empty())
        {
            vector<int> buff(num.size());
            Func(num, buff, 0, num.size() - 1);
        }
    }
};

class HeapdSort
{
public:
    void Func(vector<int>& num)
    {
        clock_t int_start = clock();
        for (auto i = num.end(); i != num.begin(); --i)
        {
            pop_heap(num.begin(), i);
        }
        clock_t int_finish = clock();
        cout << "Time: " << (double)(int_finish - int_start) / CLOCKS_PER_SEC << endl;
    }
};
int main()
{
    setlocale(LC_ALL, "Russian");
    vector<int> num1;
    vector<int> num;
    for (int i = 0;i<10000;i++)
    {
        num.push_back(rand());
    }
    int choose=0;
    clock_t int_start = 0; clock_t int_finish = 0;
    ShakeSort Shake;
    BubbleSort Bubble;
    ComboSort Combo;
    FastSort Fast;
    InserSort Insert;
    ChoosenSort Choosen;
    MergeSort Merge;
    HeapdSort Heap;

    cout << "1.Пузырьковая сортировка" << "\t" << "2.Сортировка перемешиванием" << "\t" << "3.Сортировка расчёской" << endl;
    cout << "4.Быстрая соритровка" <<"\t" << "5.Сортировка вставками" << "\t" << "6.Сортировка выбором" << endl;
    cout << "7.Сортировка слиянием" << "\t" << "8.Пирамидальная сортировка" << endl;
    try
    {
        while (true) {
            cin >> choose;
            switch (choose)
            {
            case(1):
                cout << "Пузырьковая сортировка: ";
                Shake.Func(num);
                num.clear();
                for (int i = 0; i < 10000; i++)
                {
                    num.push_back(rand());
                }
                continue;
            case(2):
                cout << "Сортировка перемешиванием: ";
                Bubble.Func(num);
                num.clear();
                for (int i = 0; i < 10000; i++)
                {
                    num.push_back(rand());
                }
                continue;
            case(3):
                cout << "Сортировка расчёской: ";
                Combo.Func(num);
                num.clear();
                for (int i = 0; i < 10000; i++)
                {
                    num.push_back(rand());
                }
                continue;
            case(4):
                cout << "Быстрая соритовка: ";
                int_start = clock();
                Fast.Func(num,0,num.size()-1);
                int_finish = clock();
                cout << "Time: " << (double)(int_finish - int_start) / CLOCKS_PER_SEC << endl;
                num.clear();
                for (int i = 0; i < 10000; i++)
                {
                    num.push_back(rand());
                }
                continue;
            case(5):
                cout << "Сортировка вставками: ";
                Insert.Func(num);
                num.clear();
                for (int i = 0; i < 10000; i++)
                {
                    num.push_back(rand());
                }
                continue;
            case(6):
                cout << "Сортировка выбором: ";
                Choosen.Func(num);
                num.clear();
                for (int i = 0; i < 10000; i++)
                {
                    num.push_back(rand());
                }
                continue;
            case(7):
                cout << "Сортировка слиянием: ";
                int_start = clock();
                Merge.Merge(num);
                int_finish = clock();
                cout << "Time: " << (double)(int_finish - int_start) / CLOCKS_PER_SEC << endl;
                num.clear();
                for (int i = 0; i < 10000; i++)
                {
                    num.push_back(rand());
                }
                continue;
            case(8):
                cout << "Пирамидальная сортировка: ";
                Heap.Func(num);
                num.clear();
                for (int i = 0; i < 10000; i++)
                {
                    num.push_back(rand());
                }
                continue;
            default:
                throw exception("No avaliable option");
            }
        }
    }
    catch(exception& er2)
    {
        cout << er2.what() << endl;
        system("pause");
    }
}

