#include <iostream>
using namespace std;

const int MAX = 2000;
int parent[MAX + 10];
int relation[MAX + 10];

int getroot(int a) {
    if (parent[a] != a) {
        int t = getroot(parent[a]);
        relation[a] = (relation[a] + relation[parent[a]] + 1) % 2;
        parent[a] = t;
    }
    return parent[a];
}

bool merge(int a, int b) {
    int ra = getroot(a), rb = getroot(b);
    if (ra == rb) {
        return relation[b] == relation[a];
    }
    parent[rb] = ra;
    relation[rb] = (relation[a] - relation[b]) % 2;
    return false;
}

int main() {
    int t;
    scanf("%d", &t);
    for (int j = 1; j <= t; ++j) {
        int n, k, x, y;
        bool flag = true;
        scanf("%d %d", &n, &k);
        for (int i = 0; i < n + 10; ++i) {
            parent[i] = i;
            relation[i] = 1;
        }
        while (k--) {
            scanf("%d %d", &x, &y);
            if (merge(x, y)) flag = false;
        }
        printf("Scenario #%d:\n", j);
        if (!flag) printf("Suspicious bugs found!\n\n");
        else printf("No suspicious bugs found!\n\n");
    }
}