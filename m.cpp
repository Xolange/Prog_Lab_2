#include <iostream>
#include <random>
#include <functional>
#include <string>
#include <chrono>
#include <vector>
#include <cmath>
#include <iomanip>


using namespace std;

const int N = 100;

void bubbleSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i) {
        bool swapped = false;
        for (int j = 0; j < n - i - 1; ++j)
            if (arr[j] > arr[j + 1]) { swap(arr[j], arr[j + 1]); swapped = true; }
        if (!swapped) break;
    }
}

void shakerSort(vector<int>& arr) {
    int left = 0, right = arr.size() - 1, lastSwap;
    while (left < right) {
        lastSwap = left;
        for (int i = left; i < right; ++i)
            if (arr[i] > arr[i + 1]) { swap(arr[i], arr[i + 1]); lastSwap = i; }
        right = lastSwap;
        lastSwap = right;
        for (int i = right; i > left; --i)
            if (arr[i] < arr[i - 1]) { swap(arr[i], arr[i - 1]); lastSwap = i; }
        left = lastSwap;
    }
}

void insertionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 1; i < n; ++i) {
        int key = arr[i], j = i - 1;
        while (j >= 0 && arr[j] > key) { arr[j + 1] = arr[j]; --j; }
        arr[j + 1] = key;
    }
}

void selectionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i) {
        int minIndex = i;
        for (int j = i + 1; j < n; ++j)
            if (arr[j] < arr[minIndex]) minIndex = j;
        if (minIndex != i) swap(arr[i], arr[minIndex]);
    }
}

int partition(vector<int>& arr, int l1, int high) {
    int pivot = arr[high], i = l1 - 1;
    for (int j = l1; j <= high - 1; ++j)
        if (arr[j] < pivot) { ++i; swap(arr[i], arr[j]); }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSort(vector<int>& arr, int l1w, int high) {
    if (l1w < high) {
        int pi = partition(arr, l1w, high);
        quickSort(arr, l1w, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void quickSortWrapper(vector<int>& arr) {
    quickSort(arr, 0, arr.size() - 1);
}

int measure(const string& name,
                  vector<int> arr,                    
                  function<void(vector<int>&)> func)
{
    auto t1 = chrono::steady_clock::now();
    func(arr);
    auto t2 = chrono::steady_clock::now();
    auto us = chrono::duration_cast<chrono::microseconds>(t2 - t1).count();
    cout << name << ": " << us << " мкс\n";
    return us;
}

int measure1(const string& name,
                  vector<int> arr,                    
                  function<void(vector<int>&, int a, int b)> func, int a, int b)
{
    auto t1 = chrono::steady_clock::now();
    func(arr,a,b);
    auto t2 = chrono::steady_clock::now();
    auto us = chrono::duration_cast<chrono::microseconds>(t2 - t1).count();
    cout << name << ": " << us << " мкс\n";
    return us;
}

int measure2(const string& name,
                  vector<int> arr,                    
                  function<void(vector<int>&, int a)> func, int a)
{
    auto t1 = chrono::steady_clock::now();
    for (int i = 0; i < 20; i++){func(arr,a);}
    auto t2 = chrono::steady_clock::now();
    auto us = chrono::duration_cast<chrono::microseconds>(t2 - t1).count();
    cout << name << ": " << float(us/20.0) << " мкс\n";
    return us;
}

int measure3(const string& name,
                  vector<int> arr,                    
                  function<void(vector<int>&, int a, int b)> func, int a, int b)
{
    auto t1 = chrono::steady_clock::now();
    for (int i = 0; i < 100000; i++){func(arr,a,b);}
    auto t2 = chrono::steady_clock::now();
    auto us = chrono::duration_cast<chrono::microseconds>(t2 - t1).count();
    cout << name << ": " << std::setprecision(10) << us/100000.0 << " мкс\n";
    return us;
}

void mnmx(vector<int> arr){
    int mx = INT_MIN;
    int mn = INT_MAX;
    for (auto x : arr){
        if (x > mx) mx = x;
        if (x < mn) mn = x;
    }

}
vector<int> srt_minmax(vector<int> arr){
    int mx = arr[arr.size()-1];
    int mn = arr[0];
    return {mn,mx};
}

void void_srt_minmax(vector<int> arr){
    srt_minmax(arr);
}


vector<int> findavg(const vector<int>& arr) {

    vector<int> res = srt_minmax(arr);
    int mn = res[0];
    int mx = res[1];
    int avg = round((mn + mx) / 2.0);

    vector<int> indx;
    for (int i = 0; i < (int)arr.size(); ++i)
        if (arr[i] == avg) indx.push_back(i);
    return indx;
}

int lin_a_b(const vector<int>& arr, int a, int b) {

    int cnt = 0;
    for (auto x : arr) {
        if (x < a || x > b) {
            cnt++;
        }
    }
    return cnt;
}

int bin_a_b(const vector<int>& arr, int a, int b) {
    int n = arr.size();
    
    int l = 0, r = n - 1;
    int li = n; 
    while (l <= r) {
        int mid = l + (r - l) / 2;
        if (arr[mid] >= a) {
            li = mid;
            r = mid - 1; 
        } else {
            l = mid + 1;
        }
    }
    
    l = 0; r = n - 1;
    int ri = n; 
    while (l <= r) {
        int mid = l + (r - l) / 2;
        if (arr[mid] > b) {
            ri = mid;
            r = mid - 1; 
        } else {
            l = mid + 1;
        }
    }
    
    return li + (n - ri);
}
bool bin_num_in_func(const vector<int>& arr, int a) {

    int l = 0;
    int r = arr.size() - 1;
    while (l <= r) {
        int mid = l + (r - l) / 2;
        if (arr[mid] == a) return true;
        else if (arr[mid] < a) l = mid + 1;
        else r = mid - 1;
    }
    return false;
}

bool lin_num_in_func(const vector<int>& arr, int a){
    for (auto x: arr){if (x == a) return true;}
    return false;
}

void changeElem(vector<int>& arr, int a, int b){

    int c = arr[b];
    arr[b] = arr[a];
    arr[a] = c;

}

void inidvidTask(vector<int>& arr, int a){

    int cnt = 0;

    for(int i = 0; i < arr.size(); i+=2){
        int& el = arr[i];
        el += a;
    }

    for(int i = 1; i < arr.size(); i+=2){
        int& el = arr[i];
        el /= 2;
    }

    for(int i = 0; i < arr.size(); i++){
        int& el = arr[i];
        if(el % 3 != 0 and el % 5 != 0 and el % 7 != 0) cnt++;

    }

    cout << "Количество элементов, которые не делятся на 3, 5, 7, 9: " << cnt << endl; 
}

int main() {
    mt19937 gen(random_device{}());
    uniform_int_distribution<> d(-99, 99);

    vector<int> rand_arr(N);
    for (auto& x : rand_arr) x = d(gen);

    for(auto x: rand_arr) cout << x << ' ';
    cout << "\n";

    vector<int> srt_arr = rand_arr;
    quickSort(srt_arr,0,srt_arr.size()-1);

    int a,b;

    cout << "1 - Замер времени сортировок \n" << "2 - Поиск минимума и максимума \n" << "3 - Среднее значение min/max и поиск совпадений\n"
    << "4 - Подсчёт элементов меньше a и больше b\n" << "5 - Наличие введённого числа\n" << "6 - Обмен элементов\n" << "7 - Индивидуальное задание\n"
    << "0 - Выйти\n";

    cout << "Введите номер пункта: ";
    int n; cin >> n; cout << "\n";
    while (n != 0){
        switch(n){
        case 1: 
            measure("Bubble sort",    rand_arr, bubbleSort);
            measure("Shaker sort",    rand_arr, shakerSort);
            measure("Insertion sort", rand_arr, insertionSort);
            measure("Selection sort", rand_arr, selectionSort);
            measure("Quick sort",     rand_arr, quickSortWrapper);
            break;

        case 2:
            measure("min/max в неотсорт.", rand_arr, mnmx);
            measure("min/max в сорт.", srt_arr, void_srt_minmax);
            break;

        case 3:{
            vector<int> avgs = findavg(srt_arr);
            cout << "Индексы: ";
            for (auto x : avgs) cout << x << " ";
            cout << endl << "Количество: ";
            cout << avgs.size() << endl;
            measure("поиск avgs в неотсорт.", rand_arr, findavg);
            measure("поиск avgs в сорт.", srt_arr, findavg);
            break;}


        case 4:
            cout << "Введите a и b: ";
            cin >> a >> b;

            measure1("подсчёт меньше а и больше б / линейно", srt_arr, lin_a_b, a, b);
            measure1("подсчёт меньше а и больше б / бинпоиск", srt_arr, bin_a_b, a, b);
            break;


        case 5:
            cout << "Введите искомый элемент: ";
            cin >> a;

            measure2("проверка наличия числа / линейно", srt_arr, lin_num_in_func, a);
            measure2("проверка наличия числа / бинпоиск", srt_arr, bin_num_in_func, a);
            break;

        case 6:
            cout << "Введите индексы для обмена: ";
            cin >> a >> b;

            measure3("обмен двух элементов", srt_arr, changeElem, a, b);
            break;
        
        case 7:
            cout << "Введите значение для индивидуального задания: ";
            cin >> a;
            inidvidTask(srt_arr, a);
            break;
        
        default:
            cout << "Введён некорретный номер.\n";
            break;
        }

        cout << "Введите номер пункта: ";
        cin >> n; cout << "\n";
    }
    
}