#include <iostream>             // ����������� ���������� �����/������
#include <cstdlib>              // ���������� ����������� ������� 
#include <vector>               // ���������� ��� ������ � ���������
#include "Windows.h"            // ���������� Windows
#include <algorithm>            // ���������� ��������� (� ��������� ����������)

using namespace std;            // ���������� ������������ ��� std

// �������, � ������� �� ����� ������� �����
// ����� ���� ����� ����� ��������� ������� �������
vector<int> graph[100]; 
int **mtrxI, **mtrxS;              // ���������� ��� ��������� ������ (������������� � ���������)
// ��������� ������, ��� �������� ������� ����� � ������ � ���������� ��������
bool mtrxIInput = false, mtrxSInput = false, spisokInput = false, vectSorted = false;;
// ���������� ��� �������� ���-�� ������, ����, ������ � ��������� �������� / ������
int vertices, edges, vertice, edge; 

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

void outputMatricaSmezhn()                  // ����� ����� ������� ���������
{                                           // ���� �� ����� �� �� �������� ����� �� ������� 
    if (mtrxSInput == false)                // � ��� � �� �����������
    {                                       // ����� ��������� ���� �� �������� (������ ���������)
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
                }
            }
        }
        mtrxSInput = true;      // �������� �������, ��� �� ������������ ������� ���������
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
        output = "";                    // ������� ��� ������ ������
        output.append(to_string(i) + ": "); // ��� ������������
        for (int j : graph[i])              // ��� ���� ��� ������ �������
        {
            output.append(to_string(j) + ", "); // ���������� � ������ - ����������
        }
        output.erase(output.end() - 2);         // ������� ������ ������� � �������� � �����
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

int main() 
{
    SetConsoleCP(1251); SetConsoleOutputCP(1251);   // ��� ������ ������� �������� � �������
    short choice;                                   // ����� ������������ � ����
    do 
    {
        cout << "����:\n";
        cout << "1. ���� �����\n";
        cout << "2. ����� �����\n";
        cout << "3. ���������� ���������\n\n";
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
    while (choice != 3);    // ���� ������������ �� ������� �����

    system("pause");        // �� ��������� ����� �������
    return 0;               // ��� 0 - �������� ���������� ���������
}