#include "Generator.h"

int Distribution(int max)
{
    static bool seeded = false;
    if (!seeded) {
        srand(time(NULL));
        seeded = true;
    }

    int N = 100;
    int M = 30;
    int m = 3;

    int x = 0;
    int r = 0;
    int p = 0;

    while (r < m)
    {
        p = (M * 100) / N;

        if ((rand() % 100) < p)
        {
            r++;
            M--;
        }
        else
        {
            x++;
        }

        N--;
    }

    x = x + m;
    if (x > max) x %= 10;

    return x;
}

void graph::generateGraph(int n)
{
    vertices = n;
    degrees.resize(vertices);
    adj.resize(vertices);
    edges.clear();

    if (vertices == 1) {
        degrees[0] = 0;
        return;
    }

    for (int i = 0; i < vertices; i++) {
        degrees[i] = Distribution(vertices - 1);
        if (degrees[i] > vertices - 1) degrees[i] = vertices - 1;
        if (degrees[i] < 1) degrees[i] = 1;
    }

    int sum = 0;
    for (int d : degrees) sum += d;
    int targetSum = 2 * (vertices - 1);
    int diff = targetSum - sum;

    if (diff > 0) {
        for (int i = 0; i < diff; i++) {
            degrees[i % vertices]++;
            if (degrees[i % vertices] > vertices - 1)
                degrees[i % vertices] = vertices - 1;
        }
    }
    else if (diff < 0) {
        for (int i = 0; i < -diff; i++) {
            if (degrees[i % vertices] > 1)
                degrees[i % vertices]--;
        }
    }

    vector<int> deg = degrees;
    set<pair<int, int>> usedEdges;

    for (int step = 0; step < vertices - 1; step++) {
        int leaf = -1;
        for (int j = 0; j < vertices; j++) {
            if (deg[j] == 1) {
                leaf = j;
                break;
            }
        }
        if (leaf == -1) {
            int minDeg = 1000;
            for (int j = 0; j < vertices; j++) {
                if (deg[j] > 0 && deg[j] < minDeg) {
                    minDeg = deg[j];
                    leaf = j;
                }
            }
        }

        int parent = -1;
        for (int j = 0; j < vertices; j++) {
            if (deg[j] > 0 && j != leaf) {
                parent = j;
                break;
            }
        }

        pair<int, int> newEdge = { min(leaf, parent), max(leaf, parent) };
        if (usedEdges.find(newEdge) != usedEdges.end()) {
            for (int j = 0; j < vertices; j++) {
                if (deg[j] > 0 && j != leaf) {
                    pair<int, int> testEdge = { min(leaf, j), max(leaf, j) };
                    if (usedEdges.find(testEdge) == usedEdges.end()) {
                        parent = j;
                        newEdge = testEdge;
                        break;
                    }
                }
            }
        }

        usedEdges.insert(newEdge);
        edges.push_back({ leaf, parent });

        deg[leaf]--;
        deg[parent]--;
    }

    for (const auto& e : edges) {
        adj[e.first].push_back(e.second);
        adj[e.second].push_back(e.first);
    }
    for (int i = 0; i < vertices; i++) {
        sort(adj[i].begin(), adj[i].end());
    }
}

void graph::print()
{
    cout << "\n=== ИНФОРМАЦИЯ О ГРАФЕ ===" << endl;
    cout << "Количество вершин: " << vertices << endl;
    cout << "Количество ребер: " << edges.size() << endl;

    cout << "\nСтепени вершин:" << endl;
    for (int i = 0; i < vertices; i++) {
        cout << "Вершина " << i << ": степень = " << degrees[i] << endl;
    }

    cout << "\nСписок ребер:" << endl;
    for (const auto& e : edges) {
        cout << "(" << e.first << ", " << e.second << ")" << endl;
    }

    cout << "\nСписок смежности:" << endl;
    for (int i = 0; i < vertices; i++) {
        cout << "Вершина " << i << ": ";
        for (int j : adj[i]) cout << j << " ";
        cout << endl;
    }
}

void graph::eccentricities()
{
    vector<int> eccentricity(vertices, 0);
    int minEcc = vertices;
    int maxEcc = 0;

    for (int i = 0; i < vertices; i++) {
        vector<int> dist(vertices, -1);
        queue<int> q;

        dist[i] = 0;
        q.push(i);

        while (!q.empty()) {
            int v = q.front();
            q.pop();

            for (int u : adj[v]) {
                if (dist[u] == -1) {
                    dist[u] = dist[v] + 1;
                    q.push(u);
                }
            }
        }

        eccentricity[i] = 0;
        for (int j = 0; j < vertices; j++) {
            if (dist[j] > eccentricity[i]) {
                eccentricity[i] = dist[j];
            }
        }

        if (eccentricity[i] < minEcc) {
            minEcc = eccentricity[i];
        }
        if (eccentricity[i] > maxEcc) {
            maxEcc = eccentricity[i];
        }

        cout << "Вершина " << i << ": эксцентриситет = " << eccentricity[i] << endl;
    }

    cout << "Центры: ";
    for (int i = 0; i < vertices; i++) {
        if (eccentricity[i] == minEcc) {
            cout << i << " ";
        }
    }
    cout << endl;

    cout << "Диаметральные вершины: ";
    for (int i = 0; i < vertices; i++) {
        if (eccentricity[i] == maxEcc) {
            cout << i << " ";
        }
    }
    cout << endl;
}

void graph::genWeightMatrix(int numEdges)
{
    weightMatrix.assign(vertices, vector<int>(vertices, 0));

    int edgesAdded = 0;
    int maxPossibleEdges = vertices * (vertices - 1) / 2;


    set<pair<int, int>> addedEdges;

    while (edgesAdded < numEdges) {
        int u = rand() % vertices;
        int v = rand() % vertices;

        if (u != v) {
            pair<int, int> edge = { min(u, v), max(u, v) };
            if (addedEdges.find(edge) == addedEdges.end()) {
                int weight = Distribution(100);
                if (weight < 1) weight = 1;

                weightMatrix[u][v] = weight;
                weightMatrix[v][u] = weight;
                addedEdges.insert(edge);
                edgesAdded++;
            }
        }
    }

    cout << "Весовая матрица сгенерирована (" << numEdges << " ребер)" << endl;
}

void graph::printWM()
{
    cout << "\n=== ВЕСОВАЯ МАТРИЦА ===" << endl;
    cout << "    ";
    for (int i = 0; i < vertices; i++) {
        cout << i;
    }
    cout << endl;

    cout << "    ";
    for (int i = 0; i < vertices; i++) {
        cout << "____";
    }
    cout << endl;

    for (int i = 0; i < vertices; i++) {
        cout << i << " |";
        for (int j = 0; j < vertices; j++) {
            if (weightMatrix[i][j] == 0 && i != j) {
                cout << "0" << " ";
            }
            else if (i == j) {
                cout << "0" << " ";
            }
            else {
                cout << weightMatrix[i][j] << " ";
            }
        }
        cout << endl;
    }
}

void graph::shimbel()
{

    vector<vector<int>> dist = weightMatrix;

    const int INF = 1000000;
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            if (i != j && dist[i][j] == 0) {
                dist[i][j] = INF;
            }
        }
    }

    for (int k = 0; k < vertices; k++) {
        for (int i = 0; i < vertices; i++) {
            for (int j = 0; j < vertices; j++) {
                if (dist[i][k] != INF && dist[k][j] != INF) {
                    if (dist[i][k] + dist[k][j] < dist[i][j]) {
                        dist[i][j] = dist[i][k] + dist[k][j];
                    }
                }
            }
        }
    }

    cout << "Матрица кратчайших расстояний:" << endl;

    cout << "    ";
    for (int i = 0; i < vertices; i++) {
        cout << i;
    }
    cout << endl;

    cout << "    ";
    for (int i = 0; i < vertices; i++) {
        cout << "_____";
    }
    cout << endl;

    for (int i = 0; i < vertices; i++) {
        cout << i << " |";
        for (int j = 0; j < vertices; j++) {
            if (dist[i][j] == INF) {
                cout << "INF";
            }
            else {
                cout << dist[i][j] << " ";
            }
        }
        cout << endl;
    }
}

void graph::findRoutes()
{
    int start, end;
    cout << "Введите начальную и конечную вершины: ";
    cin >> start >> end;

    if (start < 0 || start >= vertices || end < 0 || end >= vertices) {
        cout << "Неверные вершины" << endl;
        return;
    }

    vector<int> dist(vertices, -1);
    queue<int> q;
    dist[start] = 0;
    q.push(start);

    while (!q.empty()) {
        int v = q.front(); q.pop();
        for (int u : adj[v])
            if (dist[u] == -1) { dist[u] = dist[v] + 1; q.push(u); }
    }

    if (dist[end] == -1) {
        cout << "Маршрут НЕ СУЩЕСТВУЕТ" << endl;
        return;
    }

    cout << "Кратчайший путь: " << dist[end] << endl;
}