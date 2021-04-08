#include <iostream>             // ����������� ���������� �����/������
#include <cstdlib>              // ���������� ����������� ������� 
#include <vector>               // ���������� ��� ������ � ���������
#include "Windows.h"            // ���������� Windows
#include <algorithm>            // ���������� ��������� (� ��������� ����������)
#include <set>
#include <queue>
#include <stack>

using namespace std;            // ���������� ������������ ��� std

// �������, � ������� �� ����� ������� �����
// ����� ���� ����� ����� ��������� ������� �������
vector<int> graph[100]; 
int **mtrxI, **mtrxS;              // ���������� ��� ��������� ������ (������������� � ���������)
// ��������� ������, ��� �������� ������� ����� � ������ � ���������� ��������
bool mtrxIInput = false, mtrxSInput = false, spisokInput = false, vectSorted = false;
// ���������� ��� �������� ���-�� ������, ����, ������ � ��������� �������� / ������
int vertices, edges = 0, vertice, edge; 

void inputSpisokSmezhn()                        // ���� ����� ����� ������ ���������
{
    do 
    {
        cout << "\n������� ���������� ������ �����: ";
        cin >> vertices;
        if (vertices < 1)                       // �������� ������������ �����
        {
            cout << "������. ��������� ����!";
        }
    } while (vertices < 1);
    cout << "\n������� ������ ���������, ������ ������ ���������� ��������:\n";
    cout << "(��� �������� �� ��������� ������ ������� 0 � ������� ENTER)\n";
    for (int i = 1; i <= vertices; i++)         // ��� ������ �������
    {
        cout << i << ": ";
        do
        {
            cin >> vertice; 
            if (vertice == 0)       // ���� ����� ������ - ������ ���� � ������� � ����. �������
            {
                break;
            }
            else                                // ����� ��������� ���� � ������� �������
            {
                graph[i].push_back(vertice);
            }
        } while (true);                         // ����������� ���� - ���� �� ������� 0
    }
    if (!vectSorted)
    {
        for (int i = 1; i <= vertices; i++)
        {
            sort(graph[i].begin(), graph[i].end());
        }
    }
    cout << "\n";
    spisokInput = true;                         // �������� �������, ��� �������� ������
}

void inputMatricaSmezhn()                       // ���� ����� ����� ������� ���������
{
    do 
    {
        cout << "\n������� ���������� ������ �����: ";
        cin >> vertices;
        if (vertices < 1)                       // �������� ������������ �����
        {
            cout << "������. ��������� ����!";
        }
    } while (vertices < 1);
    mtrxS = new int*[vertices];                 // �������� ������ ��� ������� ������
    cout << "\n��������� ������� ������ ��� ������ ������� �������\n";
    cout << "������� ������ ��� ������� || �������� ���������� ����� ����� ��������\n";
    for (int i = 1; i <= vertices; i++)         // ��� ������ �������
    {
        mtrxS[i-1] = new int [vertices];        // �������� ������ ��� ���� ��� (��� ������ ������)
        cout << "[X" << i <<"] = ";             // ��� ������ ������������
        for (int j = 1; j <= vertices; j++)     // ��� ���� ��� ������ �������
        {
            cin >> edge;
            if (edge != 0)                      // ���� ���� �� 0, ����� ���������� � ������� � � ������
            {
                graph[i].push_back(j);
                mtrxS[i-1][j-1] = edge;
            }
            else                                // ����� ����� 0 ������ � �������
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
    mtrxSInput = true;                          // �������� ������� ��������� ������
}

void inputMatricaIncedent()                     // ���� ����� ������� ������������
{
    do
    {
        cout << "\n������� ���������� ������: ";
        cin >> vertices;
        cout << "������� ���������� ����: ";
        cin >> edges;
        if (vertices < 1 || edges < 1)
        {
            cout << "������! ��������� ����.";
        }
    } while (vertices < 1 || edges < 1);
    cout << "\n��������� ������� �������� ������� � ������������ � ������������:\n";

    mtrxI = new int*[edges];            // �������� ������ ��� ������� - ��� ����, ������� ����� ��������
    // ���������� ��� �������� ��������� ����������� � �� �������
    int firstOccurence[2], secondOccurence[2];
    bool edgeOverflow = false;          // ��� �������� ������������ ����� ����������
    cout << "������� ������ (��� �������) ��� ����� || �������� ���������� ����� ����� ��������\n";
    for (int i = 1; i <= edges; i++)                    // ��� ���� ����
    {
        mtrxI[i-1] = new int [vertices];                // �������� ������ ��� ���� �����
        firstOccurence[0] = 0; secondOccurence[0] = 0;  // �������� �������� �����������
        do {
            cout << "[E" << i << "] = ";                    // ��� ������ ������������
            for (int j = 1; j <= vertices; j++)             // �� ���� ������
            {
                cin >> edge;
                mtrxI[i-1][j-1] = edge;                     // ��������� �������� � �������
                if (edge != 0)                              // ���� �� ����������� �� 0, �����
                {
                    // ���������� � ���������� ��� ������ ������� � ������������
                    if (firstOccurence[0] == 0)
                    {
                        firstOccurence[0] = edge;
                        firstOccurence[1] = j;
                    }
                    else if (secondOccurence[0] == 0)       // ��� �� ������ ���� ��� ��� �� ������
                    {
                        secondOccurence[0] = edge;
                        secondOccurence[1] = j;
                    }
                    else    // ���� � ��� ������ 2 �������� - ����� ����������� - ��������
                    {
                        edgeOverflow = true;
                    }
                }
            }
            // �������� ������������ ����� �����:
            // ���� ��� ���� - ��������� ���� �����
            // ���� ����������� ���� � ��� �� 2 (�� �����) - ��������� ����
            // ���� ���� ��� �������� � ���� �� ���� �� ��� �� ����� 1 ��� -1
            // - ��������� ����            
            // ���� ������ ���� ����������� - ��������� ����
            if  (edgeOverflow || (firstOccurence[0] == 0) 
                    || ((secondOccurence[0] == 0) && (firstOccurence[0] != 2))
                    || ((secondOccurence[0] != 0) 
                        && (!((firstOccurence[0] == 1) || (firstOccurence[0] == -1))
                        || !((secondOccurence[0] == 1) || (secondOccurence[0] == -1)))))
            {
                cout << "\n�������� ������ ��� �����. ";
                cout << "��������� ���� ���� � ��������� �������!\n\n";
                firstOccurence[0] = 0; secondOccurence[0] = 0; edgeOverflow = false;
            }
        } while (edgeOverflow || (firstOccurence[0] == 0) 
                    || ((secondOccurence[0] == 0) && (firstOccurence[0] != 2))
                    || ((secondOccurence[0] != 0) 
                        && (!((firstOccurence[0] == 1) || (firstOccurence[0] == -1))
                        || !((secondOccurence[0] == 1) || (secondOccurence[0] == -1)))));

        if (secondOccurence[0] == 0)            // ���� � ��� ���� �����������
        {                                       // ������ ��� �����, ������� � ����
            graph[firstOccurence[1]].push_back(firstOccurence[1]);
        }
        else
        {
            if (firstOccurence[0] == -1)        // ���� ���� ������������ �� 1 ����������� �� 2   
            {                                   // ������� � ���� ��� 1 - 2
                graph[firstOccurence[1]].push_back(secondOccurence[1]);
            }
            else if (secondOccurence[0] == -1)  // ���� ���� ������������ �� 2 � 1 
            {                                   // ������� � ���� 2 - 1
                graph[secondOccurence[1]].push_back(firstOccurence[1]);
            }
            else                // ����� - ����� �����������������, ���������� � 1 - 2 � 2 - 1
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
    mtrxIInput = true;  // �������� ������� ��������� ������
}

void createMatricaSmezhn()
{
    mtrxS = new int*[vertices];         // �������� ������ ��� ������� - ������
    for (int i = 0; i < vertices; i++)  // ��� ������ �������
    {
        mtrxS[i] = new int[vertices];   // �������� ������ ��� ������ ������
        for (int j = 0; j < vertices; j++)  // ��� ���� ���
        {
            mtrxS[i][j] = 0;                // ��������� ������� ������
        }
    }
    for (int i = 0; i < vertices; i++)      // ��� ���� ������
    {
        for (int currentEdge : graph[i+1])  // ��� �������� �� ��������
        {
            if (currentEdge == i + 1)       // ���� ������� ������ = ������� �����
            {                               // ������ ��� �����
                mtrxS[i][i] = 2;            // � � ������� ������� 2
            }
            else                            // ����� ���������� 1
            {                               
                mtrxS[i][currentEdge-1] = 1;  
                if (mtrxS[currentEdge-1][i] == 0)
                {
                    edges++;
                } 
            }
        }
    }
    mtrxSInput = true;      // �������� �������, ��� �� ������������ ������� ���������
}

void outputMatricaSmezhn()                  // ����� ����� ������� ���������
{                                           // ���� �� ����� �� �� �������� ����� �� ������� 
    if (mtrxSInput == false)                // � ��� � �� �����������
    {                                       // ����� ��������� ���� �� �������� (������ ���������)
        createMatricaSmezhn();
    }
    cout << "\n     ";
    for (int i = 1; i <= vertices; i++)         
    {
        cout << "X" << i << "   ";              // ��� ������ ������������
    }
    cout << "\n\n";
    for (int i = 0; i < vertices; i++)          // ��� ������ �������
    {
        cout << "X" << i + 1 << "   ";          // ��� ������ ������������
        for (int j = 0; j < vertices; j++)      // ��� ���� ���
        {
            printf ("%-5d", mtrxS[i][j]);       // ����� �������
        }
        printf ("\n\n");
    }
}

void outputMatricaIncedent()            // ����� ������� ������������
{
    if (mtrxIInput == false)            // ���� ������� �� �������� � �� ������������ 
    {                                   // ����� ��������� ���� �� �������� (������ ���������)
        mtrxI = new int *[vertices*4];  // �������� ������ ��� ����� (����. ��������� ���-�� ����)
        bool orientedEdge = true;       // ��������� ���������� ����� �� ���������������
        edges = 0;                      // ������� ����
        for (int i = 0; i < vertices; i++)      // ��� ���� ������
        {
            for (int edge : graph[i+1])         // ��� ���� ��� ������ �������
            {
                mtrxI[edges] = new int [vertices];  // �������� ������ ��� ������ (�����)
                for (int j = 0; j < vertices; j++)  
                {
                    mtrxI[edges][j] = 0;            // �������� ������
                }

                if (i != edge - 1)      // ���� ������� ���. �� ����� ������� �����
                {
                    // ����� �� ��������� ����������������� �����:
                    // �� �������� ���� 1 - 2. ������ ��������� �� 2 ������� ������� 1
                    for (short tempGraph : graph[edge]) 
                    {
                        if (tempGraph == i + 1)     // ���� �������
                        {
                            orientedEdge = false;   // ������ ����� ����������������   
                        }                           // ����� ������� ���������������
                    }
                    if (orientedEdge)               // ���� ����� ��������������
                    {                               // ���������� � ������� � ����������
                        mtrxI[edges][i] = -1;       // ������� ����
                        mtrxI[edges][edge - 1] = 1;
                        edges++;
                    }
                    // ���� ����� ����������������, ������ �������� ����� � ������ ���������
                    // ��������� ������.
                    // ���� �� ������� 1 � 2, ����� �� 2 �������, � �������� 1
                    // �� ������� ��� ������ ��� �������� ������
                    // ����� �������� ������ ���������� ��������
                    // ���� ��� ����� (�� �����) ������ �������� ����� ������� ������, 
                    // ������ ������� ������. �������� �������� ���� ���� 1 �������
                    // ������ �������� 2, ����� ����������, ����� ���
                    // ������: 1 < 2 - ����������, � ��� 2 < 1 - ���
                    // ����� ������� ��������. ����� ����� �������� ��� ������� - 1 ���
                    else if (edge - 1 < i)
                    {
                        mtrxI[edges][i] = 1;
                        mtrxI[edges][edge - 1] = 1;
                        edges++;                        // ���������� ������� ����
                    }
                }
                else    // ����� ���� ��� �����, ���������� 2
                {
                    mtrxI[edges][i] = 2;
                    edges++;                // ���������� ������� ����
                }
                orientedEdge = true;        // ���������� �������� �������� �����������������   
            }                               // ��� ���������� �����
        }
        mtrxIInput = true;      // ��������, ��� ������������ ������� �������������
    }

    cout << "\n     ";
    for (int i = 1; i <= vertices; i++)     // ��� ������ ������������
    {
        cout << "X" << i << "   ";
    }
    cout << "\n\n";
    for (int i = 0; i < edges; i++)         // ��� ���� ����
    {
        cout << "E" << i + 1 << "   ";
        for (int j = 0; j < vertices; j++)  // ��� ���� ������
        {
            printf ("%-5d", mtrxI[i][j]);   // ������� ��������
        }
        cout << "\n\n";
    }
}

void outputSpisokSmezhn()               // ����� ����� ������ ��������� 
{
    cout << "����� ����� ����� ������ ���������...\n\n";
    string output;                      // ��� ������������ ������ ������ ������
    for (int i = 1; i <= vertices; i++) // ��� ���� ������
    {
        output = to_string(i) + ": ";        // ������� ��� ������ ������
        for (int j : graph[i])              // ��� ���� ��� ������ �������
        {
            output.append(to_string(j) + ", "); // ���������� � ������ - ����������
        }
        output.append("0");                       
        cout << output << "\n";                 // ������� ������ - ���������
    }
    cout << "\n";
}

void clearMemory()                          // �������� ������
{
    for (int i = 1; i <= vertices; i++)     // �.�. ��� ����� ����� �� ������� ������ � �������
    {                                       // �� � ������������ ������� �� ������
        graph[i].clear();
    }
    if (mtrxSInput)                     // ���� �������� ������ ��� ������� ���������
    {                                   // ����������� �
        for (int i = 0; i < vertices; i++)
        {
            delete mtrxS[i];
        }
        delete []mtrxS;
    }
    if (mtrxIInput)                     // ���� �������� ������ ��� ������� �������������
    {                                   // ����������� �
        for (int i = 0; i < edges; i++)
        {
            delete mtrxI[i];
        }
        delete []mtrxI;
    }
    spisokInput = false;                // �������� ��� ���� �������, ��� ������ �������
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
        cout << "\n������. ��� ����� � ������!\n\n";
        return;
    }
    set<int> used;
    int vertex;
    do
    {
        cout << "\n������� ����� �������, �� ������� ����� �������� �����: ";
        cin >> vertex;
        if (vertex < 1 || vertex > vertices)
        {
            cout << "������, ��������� ����!\n\n";
        }
    } while (vertex < 1 || vertex > vertices);
    cout << "\n�������� ����� � �������. ������� ���������� �������:\n\n";
    dfs(vertex, used);
    cout << "\n\n����� ��������.\n\n";
}

void breadthSearch()
{
   if (!(spisokInput || mtrxSInput || mtrxIInput))
    {
        cout << "\n������. ��� ����� � ������!\n\n";
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
        cout << "\n������� ����� �������, �� ������� ����� �������� �����: ";
        cin >> vertex;
        if (vertex < 1 || vertex > vertices)
        {
            cout << "������, ��������� ����!\n\n";
        }
    } while (vertex < 1 || vertex > vertices);
    distances[vertex] = 0;
    queue<int> q;
    q.push(vertex);

    cout << "\n�������, � ������� �� ������:\n\n";

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
    cout << "\n\n����� ��������!\n\n";
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
        cout << "\n������� ��������� �������: ";
        cin >> start_vertex;
        if (start_vertex < 1 || start_vertex > vertices)
        {
            cout << "������, ��������� ����!\n\n";
        }
    } while (start_vertex < 1 || start_vertex > vertices);

    do
    {
        cout << "\n������� �������� �������: ";
        cin >> end_vertex;
        if (end_vertex < 1 || end_vertex > vertices)
        {
            cout << "������, ��������� ����!\n\n";
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
        cout << "\n����� ���� ����������. ���� �������� ������������� ����!\n\n";
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
        cout << "���������� ������� �� ������� " << start_vertex << " � ������� " << end_vertex;
        cout << "!\n\n";
        return;
    }
    cout << "\n����������� ���� = " << distances[end_vertex];
    cout << "\n����: ";
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
        mtrxS = new int*[vertices];         // �������� ������ ��� ������� - ������
        for (int i = 0; i < vertices; i++)  // ��� ������ �������
        {
            mtrxS[i] = new int[vertices];   // �������� ������ ��� ������ ������
            for (int j = 0; j < vertices; j++)  // ��� ���� ���
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
        for (int i = 0; i < vertices; i++)      // ��� ���� ������
        {
            for (int currentEdge : graph[i+1])  // ��� �������� �� ��������
            {
                if (currentEdge == i + 1)       // ���� ������� ������ = ������� �����
                {                               // ������ ��� �����
                    mtrxS[i][i] = 2;            // � � ������� ������� 2
                }
                else                            // ����� ���������� 1
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
        cout << "\n������� ��������� �������: ";
        cin >> start_vertex;
        if (start_vertex < 1 || start_vertex > vertices)
        {
            cout << "������, ��������� ����!\n\n";
        }
    } while (start_vertex < 1 || start_vertex > vertices);

    do
    {
        cout << "\n������� �������� �������: ";
        cin >> end_vertex;
        if (end_vertex < 1 || end_vertex > vertices)
        {
            cout << "������, ��������� ����!\n\n";
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
        cout << "���������� ������� �� ������� " << start_vertex << " � ������� " << end_vertex;
        cout << "!\n\n";
        return;
    } 
    cout << "\n����������� ���� = " << path[j-1][start_vertex-1];
    cout << "\n����: ";
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
    SetConsoleCP(1251); SetConsoleOutputCP(1251);   // ��� ������ ������� �������� � �������
    short choice;                                   // ����� ������������ � ����
    do 
    {
        cout << "����:\n";
        cout << "1. ���� �����\n";
        cout << "2. ����� �����\n";
        cout << "3. ����� ����� � �������\n";
        cout << "4. ����� ����� � ������\n";
        cout << "5. ���������� ������������ ���� : ���� - �������\n";
        cout << "6. ���������� ������������ ���� : ������� - �����\n";
        cout << "7. ���������� ���������\n\n";
        cout << "������� ����� ������ ������: ";
        cin >> choice;                              // ���� ������
        switch (choice)                             // � ����������� �� ������
        {
            case 1:                                 // ��������� ���� �����
                short inputChoice;
                do
                {
                    cout << "\n���� �����:\n";
                    cout << "1. ������� ���������\n";
                    cout << "2. ������� �������������\n";
                    cout << "3. ������ ���������\n";
                    cout << "4. ��������� ������� � ������� ����\n\n";
                    cout << "������� ��� �����: ";
                    cin >> inputChoice;             // ����� ������������
                    if ((inputChoice < 1) || (inputChoice > 4))
                    {
                        cout << "\n�������� �����, ��������� ��� ����!\n";
                    }
                    // ���� �� �������� ���������� �������� - ������ ��
                } while ((inputChoice < 1) || (inputChoice > 4));
                // ���� ������ ��� ������, ����� ������� � ��� ������ �����
                if ((inputChoice != 4) && (spisokInput || mtrxSInput || mtrxIInput))
                {
                    clearMemory();
                }
                switch (inputChoice)    // � ����������� �� ������ ������ ��� ��� ���� ���������
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
                        cout << "\n���� ������:\n";
                        cout << "1. ������� ���������\n";
                        cout << "2. ������� �������������\n";
                        cout << "3. ������ ���������\n";
                        cout << "4. ��������� � ������� ����\n\n";
                        cout << "������� ��� �����: ";
                        cin >> outputChoice;        // ����� ������������
                        // ���� �� ������� ���������� ������ - ������ ��
                        if ((outputChoice < 1) || (outputChoice > 4))
                        {
                            cout << "\n�������� �����, ��������� ���� ����!\n";
                        }
                    } while ((outputChoice < 1) || (outputChoice > 4));
                    if ((spisokInput || mtrxSInput || mtrxIInput) || (outputChoice == 4)) 
                    // ���� ������ ����� ���� � ������ ��� ������������ �������
                    {
                        switch (outputChoice)   // � ����������� �� ������ ������� ����������� 
                        {                       // ��������
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
                    {       // ���� ��� ������ ����� � ������, ������ ��������� �� ������
                        cout << "\n������! �� �� ����� ������ ����� ��� �� ������!\n\n";
                    }
                }
                while (outputChoice != 4);   // ���� ������������ �� ������� � ������� ����
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
                cout << "\n����!\n\n";  
                // ���� ����� ������� ������ ������ (� ��������� ������������) - ������� �
                if (spisokInput || mtrxIInput || mtrxSInput)
                {
                    clearMemory();
                }
                break;
            default:       // �������� � �������� ����� 
                cout << "\n�������� �����, ��������� ���� ����!\n\n";
        }
    }  
    while (choice != 7);    // ���� ������������ �� ������� �����

    system("pause");        // �� ��������� ����� �������
    return 0;               // ��� 0 - �������� ���������� ���������
}