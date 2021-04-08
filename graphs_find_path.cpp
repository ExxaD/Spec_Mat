#include <iostream>             // Стандартная библиотека ввода/вывода
#include <cstdlib>              // Библиотека стандартных функций 
#include <vector>               // Библиотека для работы с векторами
#include "Windows.h"            // Библиотека Windows
#include <algorithm>            // Библиотека алгоритма (в частности сортировка)
#include <set>
#include <queue>
#include <stack>

using namespace std;            // Используем пространство имён std

// Векторы, в которых мы будем хранить графы
// Любой ввод графа будет заполнять векторы данными
vector<int> graph[100]; 
int **mtrxI, **mtrxS;              // Переменные для двумерных матриц (инцедентности и смежности)
// Булевские флажки, для проверки наличия графа в памяти и сортировки векторов
bool mtrxIInput = false, mtrxSInput = false, spisokInput = false, vectSorted = false;
// Переменные для хранения кол-ва вершин, ребёр, работы с отдельной вершиной / ребром
int vertices, edges = 0, vertice, edge; 

void inputSpisokSmezhn()                        // Ввод графа через список смежности
{
    do 
    {
        cout << "\nВведите количество вершин графа: ";
        cin >> vertices;
        if (vertices < 1)                       // Проверка правильности ввода
        {
            cout << "Ошибка. Проверьте ввод!";
        }
    } while (vertices < 1);
    cout << "\nВведите список смежности, номера вершин разделяйте пробелом:\n";
    cout << "(Для перехода на следующую строку введите 0 и нажмите ENTER)\n";
    for (int i = 1; i <= vertices; i++)         // Для каждой вершины
    {
        cout << i << ": ";
        do
        {
            cin >> vertice; 
            if (vertice == 0)       // Если конец строки - ломаем цикл и переход к след. вершине
            {
                break;
            }
            else                                // Иначе добавляем пару к текущей вершине
            {
                graph[i].push_back(vertice);
            }
        } while (true);                         // Бесконечный цикл - пока не получим 0
    }
    if (!vectSorted)
    {
        for (int i = 1; i <= vertices; i++)
        {
            sort(graph[i].begin(), graph[i].end());
        }
    }
    cout << "\n";
    spisokInput = true;                         // Отмечаем флажком, что получили данные
}

void inputMatricaSmezhn()                       // Ввод графа через матрицу смежности
{
    do 
    {
        cout << "\nВведите количество вершин графа: ";
        cin >> vertices;
        if (vertices < 1)                       // Проверка правильности ввода
        {
            cout << "Ошибка. Проверьте ввод!";
        }
    } while (vertices < 1);
    mtrxS = new int*[vertices];                 // Выделяем память для матрицы строки
    cout << "\nПоочерёдно вводите данные для каждой вершины матрицы\n";
    cout << "Введите строку для вершины || Элементы разделяйте между собой пробелом\n";
    for (int i = 1; i <= vertices; i++)         // Для каждой вершины
    {
        mtrxS[i-1] = new int [vertices];        // Выделяем память для всех пар (для каждой строки)
        cout << "[X" << i <<"] = ";             // Для лучшей визуализации
        for (int j = 1; j <= vertices; j++)     // Все пары для каждой вершины
        {
            cin >> edge;
            if (edge != 0)                      // Если пара не 0, тогда записываем в матрицу и в вектор
            {
                graph[i].push_back(j);
                mtrxS[i-1][j-1] = edge;
            }
            else                                // Иначе пишем 0 только в матрицу
            {
                mtrxS[i-1][j-1] = 0;
            }
        }
    }
    if (!vectSorted)
    {
        for (int i = 1; i <= vertices; i++)
        {
            sort(graph[i].begin(), graph[i].end());
        }
    }
    cout << "\n";
    mtrxSInput = true;                          // Помечаем флажком получение данных
}

void inputMatricaIncedent()                     // Ввод через матрицу идентичности
{
    do
    {
        cout << "\nВведите количество вершин: ";
        cin >> vertices;
        cout << "Введите количество рёбер: ";
        cin >> edges;
        if (vertices < 1 || edges < 1)
        {
            cout << "Ошибка! Проверьте ввод.";
        }
    } while (vertices < 1 || edges < 1);
    cout << "\nПоочерёдно вводите элементы матрицы в соответствии с комментарием:\n";

    mtrxI = new int*[edges];            // Выделяем память для матрицы - для ребёр, которые будут строками
    // Переменные для хранения найденных пересечений и их номеров
    int firstOccurence[2], secondOccurence[2];
    bool edgeOverflow = false;          // Для проверка переполнения ребра значениями
    cout << "Введите строку (или столбец) для ребра || Элементы разделяйте между собой пробелом\n";
    for (int i = 1; i <= edges; i++)                    // Для всех рёбер
    {
        mtrxI[i-1] = new int [vertices];                // Выделяем память для всех строк
        firstOccurence[0] = 0; secondOccurence[0] = 0;  // Обнуляем значения пересечений
        do {
            cout << "[E" << i << "] = ";                    // Для лучшей визуализации
            for (int j = 1; j <= vertices; j++)             // По всей строке
            {
                cin >> edge;
                mtrxI[i-1][j-1] = edge;                     // Вписываем значение в матрицу
                if (edge != 0)                              // Если на пересечении не 0, тогда
                {
                    // Записываем в переменную для первой встречи с пересечением
                    if (firstOccurence[0] == 0)
                    {
                        firstOccurence[0] = edge;
                        firstOccurence[1] = j;
                    }
                    else if (secondOccurence[0] == 0)       // Или во вторую если она ещё не занята
                    {
                        secondOccurence[0] = edge;
                        secondOccurence[1] = j;
                    }
                    else    // Если у нас больше 2 значений - ребро переполнено - отмечаем
                    {
                        edgeOverflow = true;
                    }
                }
            }
            // Проверка правильности ввода ребра:
            // Если все нули - повторный ввод ребра
            // Если пересечение одно и оно не 2 (не петля) - повторный ввод
            // Если есть оба значения и хотя бы одно из них не равно 1 или -1
            // - повторный ввод            
            // Если больше двух пересечений - повторный ввод
            if  (edgeOverflow || (firstOccurence[0] == 0) 
                    || ((secondOccurence[0] == 0) && (firstOccurence[0] != 2))
                    || ((secondOccurence[0] != 0) 
                        && (!((firstOccurence[0] == 1) || (firstOccurence[0] == -1))
                        || !((secondOccurence[0] == 1) || (secondOccurence[0] == -1)))))
            {
                cout << "\nНеверные данные для ребра. ";
                cout << "Проверьте свой ввод и повторите попытку!\n\n";
                firstOccurence[0] = 0; secondOccurence[0] = 0; edgeOverflow = false;
            }
        } while (edgeOverflow || (firstOccurence[0] == 0) 
                    || ((secondOccurence[0] == 0) && (firstOccurence[0] != 2))
                    || ((secondOccurence[0] != 0) 
                        && (!((firstOccurence[0] == 1) || (firstOccurence[0] == -1))
                        || !((secondOccurence[0] == 1) || (secondOccurence[0] == -1)))));

        if (secondOccurence[0] == 0)            // Если у нас одно пересечение
        {                                       // Значит это петля, заносим в граф
            graph[firstOccurence[1]].push_back(firstOccurence[1]);
        }
        else
        {
            if (firstOccurence[0] == -1)        // Если граф ориентирован из 1 пересечения во 2   
            {                                   // Запишем в граф для 1 - 2
                graph[firstOccurence[1]].push_back(secondOccurence[1]);
            }
            else if (secondOccurence[0] == -1)  // Если граф ориентирован из 2 в 1 
            {                                   // Запишем в граф 2 - 1
                graph[secondOccurence[1]].push_back(firstOccurence[1]);
            }
            else                // Иначе - ребро неориентированный, записываем и 1 - 2 и 2 - 1
            {
            graph[firstOccurence[1]].push_back(secondOccurence[1]); 
            graph[secondOccurence[1]].push_back(firstOccurence[1]);
            }
        }
    }
    cout << "\n";
    if (!vectSorted)
    {
        for (int i = 1; i <= vertices; i++)
        {
            sort(graph[i].begin(), graph[i].end());
        }
    }
    mtrxIInput = true;  // Помечаем флажком получение данных
}

void createMatricaSmezhn()
{
    mtrxS = new int*[vertices];         // Выделяем память для матрицы - строки
    for (int i = 0; i < vertices; i++)  // Для каждой вершины
    {
        mtrxS[i] = new int[vertices];   // Выделяем память для каждой строки
        for (int j = 0; j < vertices; j++)  // Для всех пар
        {
            mtrxS[i][j] = 0;                // Заполняем матрицу нулями
        }
    }
    for (int i = 0; i < vertices; i++)      // Для всех вершин
    {
        for (int currentEdge : graph[i+1])  // Все значения из векторов
        {
            if (currentEdge == i + 1)       // Если вершина начала = вершине конца
            {                               // Значит это петля
                mtrxS[i][i] = 2;            // И в матрицу заносим 2
            }
            else                            // Иначе записываем 1
            {                               
                mtrxS[i][currentEdge-1] = 1;  
                if (mtrxS[currentEdge-1][i] == 0)
                {
                    edges++;
                } 
            }
        }
    }
    mtrxSInput = true;      // Помечаем флажком, что мы сформировали матрицу смежности
}

void outputMatricaSmezhn()                  // Вывод через матрицу смежности
{                                           // Если на вводе мы не получили такую же матрицу 
    if (mtrxSInput == false)                // и ещё её не формировали
    {                                       // Тогда формируем сами из векторов (списка смежности)
        createMatricaSmezhn();
    }
    cout << "\n     ";
    for (int i = 1; i <= vertices; i++)         
    {
        cout << "X" << i << "   ";              // Для лучшей визуализации
    }
    cout << "\n\n";
    for (int i = 0; i < vertices; i++)          // Для каждой вершины
    {
        cout << "X" << i + 1 << "   ";          // Для лучшей визуализации
        for (int j = 0; j < vertices; j++)      // Для всех пар
        {
            printf ("%-5d", mtrxS[i][j]);       // Вывод матрицы
        }
        printf ("\n\n");
    }
}

void outputMatricaIncedent()            // Вывод матрицы идентичности
{
    if (mtrxIInput == false)            // Если матрица не получена и не сформирована 
    {                                   // Тогда формируем сами из векторов (списка смежности)
        mtrxI = new int *[vertices*4];  // Выделяем память для строк (макс. возможное кол-во рёбер)
        bool orientedEdge = true;       // Принимаем изначально ребро за ориентированное
        edges = 0;                      // Счётчик рёбер
        for (int i = 0; i < vertices; i++)      // Для всех вершин
        {
            for (int edge : graph[i+1])         // Все пары для каждой вершины
            {
                mtrxI[edges] = new int [vertices];  // Выделяем память под строку (ребро)
                for (int j = 0; j < vertices; j++)  
                {
                    mtrxI[edges][j] = 0;            // Зануляем строку
                }

                if (i != edge - 1)      // Если вершина нач. не равна вершине конца
                {
                    // Здесь мы проверяем ориентированность ребра:
                    // Мы получили пару 1 - 2. Теперь проверяем во 2 вершине наличие 1
                    for (short tempGraph : graph[edge]) 
                    {
                        if (tempGraph == i + 1)     // Если находим
                        {
                            orientedEdge = false;   // значит ребро неориентированно   
                        }                           // иначе остаётся ориентированным
                    }
                    if (orientedEdge)               // Если ребро ориентированно
                    {                               // Записываем в матрицу и прибавляем
                        mtrxI[edges][i] = -1;       // счётчик рёбер
                        mtrxI[edges][edge - 1] = 1;
                        edges++;
                    }
                    // Если ребро неориентированно, значит значения ребра в списке смежности
                    // находится дважды.
                    // Если мы запишем 1 в 2, дойдём до 2 вершины, и встретим 1
                    // то записав его второй раз допустим ошибку
                    // Чтобы избежать ошибки используем хитрость
                    // Если это ребро (не петля) значит значение одной вершины больше, 
                    // другой вершины меньше. Поставим проверку если знач 1 вершины
                    // меньше значения 2, тогда записываем, иначе нет
                    // Пример: 1 < 2 - записываем, а уже 2 < 1 - нет
                    // Таким образом неориент. ребро будет записано как следует - 1 раз
                    else if (edge - 1 < i)
                    {
                        mtrxI[edges][i] = 1;
                        mtrxI[edges][edge - 1] = 1;
                        edges++;                        // Прибавляем счётчик рёбер
                    }
                }
                else    // Иначе если это петля, записываем 2
                {
                    mtrxI[edges][i] = 2;
                    edges++;                // Прибавляем счётчик рёбер
                }
                orientedEdge = true;        // Возвращаем исходное значение ориентированности   
            }                               // для следующего ребра
        }
        mtrxIInput = true;      // Помечаем, что сформировали матрицу инцедентности
    }

    cout << "\n     ";
    for (int i = 1; i <= vertices; i++)     // Для лучшей визуализации
    {
        cout << "X" << i << "   ";
    }
    cout << "\n\n";
    for (int i = 0; i < edges; i++)         // Для всех ребёр
    {
        cout << "E" << i + 1 << "   ";
        for (int j = 0; j < vertices; j++)  // Все пары вершин
        {
            printf ("%-5d", mtrxI[i][j]);   // Выводим значения
        }
        cout << "\n\n";
    }
}

void outputSpisokSmezhn()               // Вывод через список смежности 
{
    cout << "Вывод графа через список смежности...\n\n";
    string output;                      // Для формирования каждой строки вывода
    for (int i = 1; i <= vertices; i++) // Для всех вершин
    {
        output = to_string(i) + ": ";        // Очищаем для каждой строки
        for (int j : graph[i])              // Все пары для каждой вершины
        {
            output.append(to_string(j) + ", "); // Записываем к строке - результату
        }
        output.append("0");                       
        cout << output << "\n";                 // Выводим строку - результат
    }
    cout << "\n";
}

void clearMemory()                          // Очищение памяти
{
    for (int i = 1; i <= vertices; i++)     // Т.к. при любом вводе мы заносим данные в вектора
    {                                       // то в обязательном порядке их чистим
        graph[i].clear();
    }
    if (mtrxSInput)                     // Если выделена память для матрицы смежности
    {                                   // освобождаем её
        for (int i = 0; i < vertices; i++)
        {
            delete mtrxS[i];
        }
        delete []mtrxS;
    }
    if (mtrxIInput)                     // Если выделена память для матрицы инцедентности
    {                                   // Освобождаем её
        for (int i = 0; i < edges; i++)
        {
            delete mtrxI[i];
        }
        delete []mtrxI;
    }
    spisokInput = false;                // Отмечаем для всех флажков, что данные очищены
    mtrxSInput = false;
    mtrxIInput = false;
}

void dfs(int vertex, set<int> &used)
{
    cout << vertex << " ";
    used.insert(vertex);
    for (int neighbour : graph[vertex])
    {
        if (used.find(neighbour) == used.end())
        {
            dfs(neighbour, used);
        }
    }

}

void deepSearch()
{
    if (!(spisokInput || mtrxSInput || mtrxIInput))
    {
        cout << "\nОшибка. Нет графа в памяти!\n\n";
        return;
    }
    set<int> used;
    int vertex;
    do
    {
        cout << "\nВведите номер вершины, из которой будем начинать обход: ";
        cin >> vertex;
        if (vertex < 1 || vertex > vertices)
        {
            cout << "Ошибка, проверьте ввод!\n\n";
        }
    } while (vertex < 1 || vertex > vertices);
    cout << "\nНачинаем обход в глубину. Выводим пройденные вершины:\n\n";
    dfs(vertex, used);
    cout << "\n\nОбход завершён.\n\n";
}

void breadthSearch()
{
   if (!(spisokInput || mtrxSInput || mtrxIInput))
    {
        cout << "\nОшибка. Нет графа в памяти!\n\n";
        return;
    }
    int distances[vertices+1];
    for (int i = 1; i < vertices + 1; i++)
    {
        distances[i] = -1;
    }
    int vertex;
    do
    {
        cout << "\nВведите номер вершины, из которой будем начинать обход: ";
        cin >> vertex;
        if (vertex < 1 || vertex > vertices)
        {
            cout << "Ошибка, проверьте ввод!\n\n";
        }
    } while (vertex < 1 || vertex > vertices);
    distances[vertex] = 0;
    queue<int> q;
    q.push(vertex);

    cout << "\nВершины, в порядке их обхода:\n\n";

    int cur_v;
    while (!q.empty())
    {
        cur_v = q.front();
        cout << cur_v << " ";
        q.pop();
        for (int neigh_v : graph[cur_v])
        {
            if (distances[neigh_v] == -1)
            {
                distances[neigh_v] = distances[cur_v] + 1;
                q.push(neigh_v);
            }
        }
    }
    cout << "\n\nОбход завершён!\n\n";
}

void findPathFord()
{
    if (mtrxSInput == false)
    {
        createMatricaSmezhn();
    }

    int start_vertex, end_vertex; 
    do
    {
        cout << "\nВведите начальную вершину: ";
        cin >> start_vertex;
        if (start_vertex < 1 || start_vertex > vertices)
        {
            cout << "Ошибка, проверьте ввод!\n\n";
        }
    } while (start_vertex < 1 || start_vertex > vertices);

    do
    {
        cout << "\nВведите конечную вершину: ";
        cin >> end_vertex;
        if (end_vertex < 1 || end_vertex > vertices)
        {
            cout << "Ошибка, проверьте ввод!\n\n";
        }
    } while (end_vertex < 1 || end_vertex > vertices);

    int distances[vertices + 1];
    for (int i = 1; i < vertices + 1; i++)
    {
        distances[i] = 99999;
    }
    distances[start_vertex] = 0;

    bool negativeLoop = false;
    for (int i = 0; i < vertices; i++)
    {
        for (int cur_v = 1; cur_v < vertices + 1; cur_v++)
        {
            for (int neigh_v : graph[cur_v])
            {
                if (distances[neigh_v] - distances[cur_v] > mtrxS[cur_v - 1][neigh_v - 1])
                {
                    distances[neigh_v] = distances[cur_v] + mtrxS[cur_v - 1][neigh_v - 1];
                    if (i == vertices - 1)
                    {
                        negativeLoop = true;
                    } 
                }
            }
        }
    }
    if (negativeLoop)
    {
        cout << "\nНайти путь невозможно. Граф содержит отрицательный цикл!\n\n";
        return;
    } 

    int curr_vertex = end_vertex, curr_dist = distances[end_vertex];
    stack<int> path;
    path.push(end_vertex);
    while (curr_vertex != start_vertex)
    {
        for (int i = 0; i < vertices; i++)
        {
            if ((mtrxS[i][curr_vertex - 1] != 0) 
                && (curr_dist - mtrxS[i][curr_vertex - 1] == distances[i + 1]))
            {
                curr_dist -= mtrxS[i][curr_vertex-1];
                curr_vertex = i + 1;
                path.push(curr_vertex);
                break;
            }
        }
    }

    if (distances[end_vertex] == 99999)
    {
        cout << "Невозможно попасть из вершины " << start_vertex << " в вершину " << end_vertex;
        cout << "!\n\n";
        return;
    }
    cout << "\nМинимальный путь = " << distances[end_vertex];
    cout << "\nПуть: ";
    while (!path.empty())
    {
        cout << path.top();
        if (path.size() != 1)
        {
            cout << " -> ";
        }
        path.pop();
    }
    cout << "\n\n";
}

void findPathBelman()
{
    if (!mtrxSInput)
    {
        mtrxS = new int*[vertices];         // Выделяем память для матрицы - строки
        for (int i = 0; i < vertices; i++)  // Для каждой вершины
        {
            mtrxS[i] = new int[vertices];   // Выделяем память для каждой строки
            for (int j = 0; j < vertices; j++)  // Для всех пар
            {
                if (i != j)
                {
                    mtrxS[i][j] = 99999;   
                }
                else
                {
                    mtrxS[i][j] = 0;
                }           
            }
        }
        for (int i = 0; i < vertices; i++)      // Для всех вершин
        {
            for (int currentEdge : graph[i+1])  // Все значения из векторов
            {
                if (currentEdge == i + 1)       // Если вершина начала = вершине конца
                {                               // Значит это петля
                    mtrxS[i][i] = 2;            // И в матрицу заносим 2
                }
                else                            // Иначе записываем 1
                {                               
                    mtrxS[i][currentEdge-1] = 1;  
                }
            }
        }
        mtrxSInput = true;
    }
    else
    {
        for (int i = 0; i < vertices; i++)
        {
            for (int j = 0; j < vertices; j++)
            {
                if ((mtrxS[i][j] == 0) && (i != j))
                {
                    mtrxS[i][j] = 99999;
                }
            }
        }
    }

    int start_vertex, end_vertex; 
    do
    {
        cout << "\nВведите начальную вершину: ";
        cin >> start_vertex;
        if (start_vertex < 1 || start_vertex > vertices)
        {
            cout << "Ошибка, проверьте ввод!\n\n";
        }
    } while (start_vertex < 1 || start_vertex > vertices);

    do
    {
        cout << "\nВведите конечную вершину: ";
        cin >> end_vertex;
        if (end_vertex < 1 || end_vertex > vertices)
        {
            cout << "Ошибка, проверьте ввод!\n\n";
        }
    } while (end_vertex < 1 || end_vertex > vertices);

    int **path;
    path = new int *[vertices];
    path[0] = new int [vertices];
    for (int i = 0; i < vertices; i++)
    {
        path[0][i] = mtrxS[i][end_vertex - 1];
    }
    bool pathIdent = false;
    int j = 1, min, current;
    while (!pathIdent)
    {
        path[j] = new int [vertices];
        pathIdent = true;
        for (int k = 0; k < vertices; k++)
        {
            min = 99999;
            for (int i = 0; i < vertices; i++)
            {
                current = path[j-1][i] + mtrxS[k][i];
                if (current < min)
                {
                    min = current;
                } 
            }
            path[j][k] = min;
            if (path[j][k] != path[j-1][k])
            {
                pathIdent = false;
            }
        }
        j++;
    }
    j--;

    if (path[j-1][start_vertex-1] == 99999)
    {
        cout << "Невозможно попасть из вершины " << start_vertex << " в вершину " << end_vertex;
        cout << "!\n\n";
        return;
    } 
    cout << "\nМинимальный путь = " << path[j-1][start_vertex-1];
    cout << "\nПуть: ";
    while (start_vertex != end_vertex)
    {
        for (int i = 1; i < vertices + 1; i++)
        {
            if (i == start_vertex)
            {
                continue;
            }
            if (path[j-1][start_vertex-1] - path[j-1][i-1] == mtrxS[start_vertex-1][i-1])
            {
                cout << start_vertex << " -> ";
                start_vertex = i;
                break;
            }
        }
    }
    cout << end_vertex << "\n\n";

    for (int i = 0; i < vertices; i++)
    {
        for (int j = 0; j < vertices; j++)
        {
            if ((mtrxS[i][j] == 99999) && (i != j))
            {
                mtrxS[i][j] = 0;
            }
        }
    }
    
    for (int i = 0; i < j; i++)
    {
        delete path[i];
    }
    delete []path;
}

int main() 
{
    SetConsoleCP(1251); SetConsoleOutputCP(1251);   // Для вывода русской кирилицы в консоль
    short choice;                                   // Выбор пользователя в меню
    do 
    {
        cout << "Меню:\n";
        cout << "1. Ввод графа\n";
        cout << "2. Вывод графа\n";
        cout << "3. Обход графа в глубину\n";
        cout << "4. Обход графа в ширину\n";
        cout << "5. Нахождение минимального пути : Форд - Беллман\n";
        cout << "6. Нахождение минимального пути : Беллман - Калаб\n";
        cout << "7. Завершение программы\n\n";
        cout << "Введите цифру вашего выбора: ";
        cin >> choice;                              // Ввод выбора
        switch (choice)                             // В зависимости от выбора
        {
            case 1:                                 // Открываем меню ввода
                short inputChoice;
                do
                {
                    cout << "\nМеню ввода:\n";
                    cout << "1. Матрица смежности\n";
                    cout << "2. Матрица инцедентности\n";
                    cout << "3. Список смежности\n";
                    cout << "4. Вернуться обратно в главное меню\n\n";
                    cout << "Введите ваш выбор: ";
                    cin >> inputChoice;             // Выбор пользователя
                    if ((inputChoice < 1) || (inputChoice > 4))
                    {
                        cout << "\nНеверный выбор, проверьте ваш ввод!\n";
                    }
                    // Пока не введутся корректные значения - просим их
                } while ((inputChoice < 1) || (inputChoice > 4));
                // Если память уже занята, тогда очищаем её для нового графа
                if ((inputChoice != 4) && (spisokInput || mtrxSInput || mtrxIInput))
                {
                    clearMemory();
                }
                switch (inputChoice)    // В зависимости от выбора вводим тем или иным способами
                {
                    case 1:
                        inputMatricaSmezhn();
                        break;
                    case 2:
                        inputMatricaIncedent();
                        break;
                    case 3:
                        inputSpisokSmezhn();
                        break;
                    case 4:
                        cout << "\n";
                        break;
                }
                break;
            case 2:
                short outputChoice;         
                do
                {
                    do
                    {
                        cout << "\nМеню вывода:\n";
                        cout << "1. Матрица смежности\n";
                        cout << "2. Матрица инцедентности\n";
                        cout << "3. Список смежности\n";
                        cout << "4. Вернуться в главное меню\n\n";
                        cout << "Введите ваш выбор: ";
                        cin >> outputChoice;        // Выбор пользователя
                        // Пока не получим корректные данные - просим их
                        if ((outputChoice < 1) || (outputChoice > 4))
                        {
                            cout << "\nНеверный выбор, проверьте свой ввод!\n";
                        }
                    } while ((outputChoice < 1) || (outputChoice > 4));
                    if ((spisokInput || mtrxSInput || mtrxIInput) || (outputChoice == 4)) 
                    // Если данные графа есть в памяти или пользователь выходит
                    {
                        switch (outputChoice)   // В зависимости от выбора выводим определённым 
                        {                       // способом
                            case 1:
                            {
                                outputMatricaSmezhn();
                                break;
                            }
                            case 2:
                                outputMatricaIncedent();
                                break;
                            case 3:
                                outputSpisokSmezhn();
                                break;
                            case 4:
                                cout << "\n";
                                break;
                        }
                    }
                    else
                    {       // Если нет данных графа в памяти, выводи сообщение об ошибке
                        cout << "\nОшибка! Вы не ввели данные графа для их вывода!\n\n";
                    }
                }
                while (outputChoice != 4);   // Пока пользователь не вернётся в главное меню
                break;
            case 3:
                deepSearch();
                break;
            case 4: 
                breadthSearch();
                break;
            case 5:
                findPathFord();
                break;
            case 6:
                findPathBelman();
                break;
            case 7:
                cout << "\nПока!\n\n";  
                // Если перед выходом память занята (в частности динамическая) - очищаем её
                if (spisokInput || mtrxIInput || mtrxSInput)
                {
                    clearMemory();
                }
                break;
            default:       // Сообщаем о неверном вводе 
                cout << "\nНеверный выбор, проверьте свой ввод!\n\n";
        }
    }  
    while (choice != 7);    // Пока пользователь не выберет выход

    system("pause");        // Не закрывать сразу консоль
    return 0;               // Код 0 - успешное выполнение программы
}