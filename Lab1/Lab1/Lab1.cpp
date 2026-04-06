#include <iostream>
#include "Generator.h"

using namespace std;

int main()
{
    setlocale(LC_ALL, "rus");

    int count;

    cout << "Введите количество вершин: ";
    cin >> count;

    graph t(count);
    t.print();
    t.eccentricities();
}
