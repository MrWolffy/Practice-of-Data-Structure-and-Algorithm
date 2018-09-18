#include <iostream>
using namespace std;

const int MAX = 50000;
int parent[MAX + 10];
int relation[MAX + 10];
int lie = 0;

int getroot(int a) {
    if (a != parent[a]) {
        int t = getroot(parent[a]);
        relation[a] = (relation[a] + relation[parent[a]]) % 3;
        parent[a] = t;
    }
    return parent[a];
}

void merge(int a, int b, int d) {
    int ra = getroot(a), rb = getroot(b);
    if (ra == rb) {
        if ((relation[b] - relation[a] + 3) % 3 != d - 1) {
            lie += 1;
        }
        return;
    }
    parent[rb] = ra;
    relation[rb] = (3 + (d - 1) + relation[a] - relation[b]) % 3;
}

int main() {
    int n, k, d, x, y;
    cin >> n >> k;
    for (int i = 0; i <= n; ++i) {
        parent[i] = i;
        relation[i] = 0;
    }
    for (int i = 0; i < k; ++i) {
        cin >> d >> x >> y;
        if (x > n || y > n || (x == y && d == 2)) {
            lie += 1;
            continue;
        }
        merge(x, y, d);
    }
    cout << lie << endl;
    return 0;
}