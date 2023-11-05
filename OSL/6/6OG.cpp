#include <bits/stdc++.h>
using namespace std;

bool ispresent(int n, vector<int> &pageframe)
{
    for (auto it : pageframe)
    {
        if (it == n)
            return true;
    }
    return false;
}

bool isfull(vector<int> &pf)
{
    for (auto it : pf)
    {
        if (it == -1)
            return 0;
    }
    return 1;
}

void inplace(int n, int tgt, vector<int> &pf)
{
    for (int i = 0; i < pf.size(); i++)
    {
        if (pf[i] == n)
        {
            pf[i] = tgt;
            return;
        }
    }
}

int find_victim(map<int, int> &mp)
{
    int mini = INT_MAX;
    for (auto it : mp)
    {
        mini = min(mini, it.second);
    }

    for (auto it : mp)
    {
        if (mini == it.second)
        {
            return it.first;
        }
    }
    return -1;
}

bool equal(int tgt, vector<int> &pageframe, vector<int> &found)
{
    for (int i = 0; i < pageframe.size(); i++)
    {
        if (pageframe[i] == tgt)
        {
            found[i] = 1;
            return 1;
        }
    }
    return 0;
}

int find_vic(int i, string &s, vector<int> &pageframe)
{
    map<int, int> mp;
    int timer = 0;
    vector<int> found(pageframe.size(), 0);
    for (int j = s.length() - 1; j >= i; j--)
    {
        timer++;
        if (equal(s[j] - '0', pageframe, found))
        {
            mp[s[j] - '0'] = timer;
        }
    }

    for (int j = 0; j < found.size(); j++)
    {
        if (found[j] == 0)
        {
            return pageframe[j];
        }
    }

    int mini = INT_MAX;
    for (auto it : mp)
    {
        mini = min(mini, it.second);
    }

    for (auto it : mp)
    {
        if (it.second == mini)
        {
            return it.first;
        }
    }
    return -1;
}

void fifo(vector<int> &pageframe, vector<int> &ispf, string &s, vector<vector<int>> &v)
{

    queue<int> q;
    bool isf = 0;
    for (int i = 0; i < s.length(); i++)
    {
        if (ispresent(s[i] - '0', pageframe))
        {
            ispf[i] = 0;
            v.push_back(pageframe);
            continue;
        }

        q.push(s[i] - '0');

        if (isf || isfull(pageframe))
        {
            isf = 1;
            int rp = q.front();
            q.pop();
            inplace(rp, s[i] - '0', pageframe);
        }
        else
            pageframe[i] = s[i] - '0';
        v.push_back(pageframe);
    }
}

void lru(vector<int> &pageframe, vector<int> &ispf, string &s, vector<vector<int>> &v)
{

    int timer = 0;
    bool isf = 0;
    map<int, int> mp;
    for (int i = 0; i < s.length(); i++)
    {
        timer++;
        mp[s[i] - '0'] = timer;
        if (ispresent(s[i] - '0', pageframe))
        {
            ispf[i] = 0;
            v.push_back(pageframe);
            continue;
        }

        if (isf || isfull(pageframe))
        {
            isf = 1;
            int vic = find_victim(mp);
            mp[vic] = INT_MAX;
            inplace(vic, s[i] - '0', pageframe);
        }
        else
            pageframe[i] = s[i] - '0';
        v.push_back(pageframe);
    }
}

void optimal(vector<int> &pageframe, vector<int> &ispf, string &s, vector<vector<int>> &v)
{

    bool isf = 0;
    for (int i = 0; i < s.length(); i++)
    {
        if (ispresent(s[i] - '0', pageframe))
        {
            ispf[i] = 0;
            v.push_back(pageframe);
            continue;
        }

        if (isf || isfull(pageframe))
        {
            isf = 1;
            int vic = find_vic(i + 1, s, pageframe);
            cout << "victim : " << vic << endl;
            inplace(vic, s[i] - '0', pageframe);
        }
        else
            pageframe[i] = s[i] - '0';
        v.push_back(pageframe);
    }
}

int main()
{

    cout << "Enter the process string : " << endl;
    string s;
    cin >> s;

    cout << "Enter the page frame size : " << endl;
    int pfs;
    cin >> pfs;

    vector<int> pageframe(pfs, -1);
    vector<int> ispf(s.length(), 1);
    vector<vector<int>> v;
    int hits = 0, miss = 0;

    cout << " 1.  First In First Out " << endl;
    cout << " 2.  Least Recently Used " << endl;
    cout << " 3.  Optimal " << endl
         << endl;
    cout << "Enter your choice : " << endl;
    int ch;
    cin >> ch;

    switch (ch)
    {
    case 1:
        fifo(pageframe, ispf, s, v);
        break;
    case 2:
        lru(pageframe, ispf, s, v);
        break;
    case 3:
        optimal(pageframe, ispf, s, v);
        break; // Add this break statement
    default:
        break;
    }

    cout << endl;
    for (int i = 0; i < s.length(); i++)
        cout << s[i] << "   ";
    cout << endl
         << endl;

    for (int i = 0; i < pfs; i++)
    {
        for (int j = 0; j < v.size(); j++)
        {
            if (v[j][i] == -1)
                cout << "x"
                     << "   ";
            else
                cout << v[j][i] << "   ";
        }
        cout << endl;
    }
    cout << endl;

    int cnt = 0;
    int pageFaults = 0;
    int pageHits = 0;
    cout << "Page Faults : " << endl;
    for (auto it : ispf)
    {
        if (it == 1)
            pageFaults++;
        else
            pageHits++;
        cout<< it << "   ";
    }
    cout << endl
         << endl;
    
    cout << "Total Page Faults: " << pageFaults << endl;
    cout << "Total Page Hits: " << pageHits << endl
         << endl;
}
// 637216357271