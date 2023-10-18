#include <vector>
#include <iostream>
#include <unordered_map>
#include <algorithm>
using namespace std;

typedef struct
{
    int value;
    int pre;
    int next;
    bool exist;
} node;

typedef struct
{
    int value;
    unordered_map<int, bool> link;
} hashnode;

void hash_insert(unordered_map<int, hashnode> &map, int index, int value)
{
    map[value].link[index] = 1;
}

void insert(vector<node> &list, int &count, int k, int v, unordered_map<int, hashnode> &map)
{
    if (list[k].exist == false)
    {
        cout << "!" << endl;
        return;
    }
    count++;
    list[list[k].next].pre = count;
    list[count].next = list[k].next;
    list[count].pre = k;
    list[k].next = count;

    list[count].value = v;
    list[count].exist = true;

    hash_insert(map, count, v);
    if (list[count].pre == 0)
        cout << -1 << " ";
    else
        cout << list[list[count].pre].value << " ";

    int max_idx = list.size() - 1;
    if (list[count].next == max_idx)
        cout << -1 << endl;
    else
        cout << list[list[count].next].value << endl;
}

void hash_remove(unordered_map<int, hashnode> &map, int index, int value)
{
    map[value].link.erase(index);
}

void hash_remove_all(unordered_map<int, hashnode> &map, int value, vector<node> &list)
{
    cout << map[value].link.size() << endl;
    for (unordered_map<int, bool>::iterator iter = map[value].link.begin(); iter != map[value].link.end(); iter++)
    {
        list[list[iter->first].pre].next = list[iter->first].next;
        list[list[iter->first].next].pre = list[iter->first].pre;
        list[iter->first].exist = false;
    }
    map[value].link.clear();
}

void change(vector<node> &list, int k, int v, unordered_map<int, hashnode> &map)
{
    if (list[k].exist == false)
    {
        cout << "!" << endl;
        return;
    }
    cout << list[k].value << endl;
    hash_remove(map, k, list[k].value);
    list[k].value = v;
    hash_insert(map, k, v);
}

void remove(vector<node> &list, int v, unordered_map<int, hashnode> &map)
{
    int max_idx = list.size() - 1, i = 0, total = 0;
    i = list[0].next;
    while (i != max_idx)
    {
        if (list[i].value == v)
        {
            list[list[i].pre].next = list[i].next;
            list[list[i].next].pre = list[i].pre;
            list[i].exist = false;
            total++;
        }
        i = list[i].next;
    }
    cout << total << endl;
}

void print(vector<node> &list)
{
    int max_idx = list.size() - 1, i = 0;
    i = list[0].next;
    while (i != max_idx)
    {
        printf("%d ", list[i].value);
        i = list[i].next;
    }
}

int main()
{
    int n;
    scanf("%d", &n);
    getchar();
    node init_node;
    init_node.exist = false;
    vector<node> list(n + 2, init_node);
    list[0].next = n + 1;
    list[0].exist = true;
    list[n + 1].pre = 0;
    list[n + 1].exist = true;
    int count = 0;

    unordered_map<int, hashnode> map;
    for (int i = 0; i < n; i++)
    {
        int op;
        scanf("%d", &op);
        if (op == 1)
        {
            int k, v;
            scanf("%d %d", &k, &v);
            getchar();
            insert(list, count, k, v, map);
        }
        else if (op == 2)
        {
            int k, v;
            scanf("%d %d", &k, &v);
            getchar();
            change(list, k, v, map);
        }
        else
        {
            int v;
            scanf("%d", &v);
            getchar();
            hash_remove_all(map, v, list);
        }
    }
    print(list);
}