#include <iostream>
#include "Generator.h"

using namespace std;



int main()
{
    setlocale(LC_ALL, "rus");

    graph g;

    int choice;
    do {
        cout << "1. Построить граф" << endl;
        cout << "2. Вывести информацию о графе" << endl;
        cout << "3. Вычислить эксцентриситеты, центры и диаметральные вершины графа" << endl;
        cout << "4. Сгенерировать весовую матрицу" << endl;
        cout << "5. Применить метод Шимбелла" << endl;
        cout << "6. Найти маршрут между вершинами" << endl;
        cout << "========================================" << endl;
        cout << "Ваш выбор: ";
        cin >> choice;

        switch (choice) {
        case 1:
            int count;
            cout << "Введите количество вершин: ";
            cin >> count;
            g.generateGraph(count);
            g.print();
            break;

        case 2:
            g.print();
            break;

        case 3:
            g.eccentricities();
            break;

        case 4: {
            int count;
            cout << "Введите количество ребер: ";
            cin >> count;
            g.genWeightMatrix(count);
            g.printWM();
            break;
        }

        case 5:
            g.shimbel();
            break;

        case 6:
            g.findRoutes();
            break;
        default:
            cout << "Неверный выбор! Попробуйте снова." << endl;
            break;
        }
        cout << endl;
    } while (choice != 0);

    return 0;
}