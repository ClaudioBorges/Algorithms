#include <iostream>
#include <queue>
#include <vector>
#include <functional>

using namespace std;

typedef priority_queue<int, vector<int>, greater<int> > min_heap;

void
showq(const min_heap & pq) {
    min_heap q = pq;

    while( !q.empty() ) {
        cout << "\t" << q.top();
        q.pop();
    }
    cout << endl;
}

int
main() {
    min_heap pq;
    pq.push(1);
    pq.push(31);
    pq.push(12);
    pq.push(22);
    pq.push(2);
    pq.push(7);
    pq.push(17);

    cout << "Priority queue:" << endl;
    showq( pq );
}
