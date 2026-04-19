#include <iostream>
#include "Generator.h"

using namespace std;



int main()
{
    setlocale(LC_ALL, "rus");

    int count;
    cout << "Введите количество вершин: ";
    cin >> count;
    graph g(count);

    int choice;
    do {
        cout << "1. Построить граф" << endl;
        cout << "2. Вывести информацию о графе" << endl;
        cout << "3. Вычислить эксцентриситеты вершин" << endl;
        cout << "4. Сгенерировать весовую матрицу" << endl;
        cout << "5. Применить метод Шимбелла" << endl;
        cout << "6. Найти маршрут между вершинами" << endl;
        cout << "0. Выход" << endl;
        cout << "========================================" << endl;
        cout << "Ваш выбор: ";
        cin >> choice;

        switch (choice) {
        case 2:
            g.print();
            break;

        case 3:
            g.eccentricities();
            break;

        case 4: {
            int minW, maxW;
            cout << "Введите минимальный вес: ";
            cin >> minW;
            cout << "Введите максимальный вес: ";
            cin >> maxW;
            g.genWeightMatrix(minW, maxW);
            break;
        }

        case 5:
            g.shimbel();
            break;

        case 6:
            g.findRoutes();
            break;

        case 0:
            cout << "Выход из программы..." << endl;
            break;

        default:
            cout << "Неверный выбор! Попробуйте снова." << endl;
            break;
        }

    } while (choice != 0);

    return 0;
}