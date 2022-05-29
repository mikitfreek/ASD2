#include <iostream>
#include <vector>

//#include <ctime>
//#include <cstdlib>

typedef std::vector<int> Heap;

void print_state(const Heap h, int end) {

    for (int i = end + 2; --i >= 0; )
        std::cout << h[i] << " ";

    std::cout << '\n';
}

void siftDown(Heap& h, int start, int end) {

    //source: https://en.wikipedia.org/wiki/Heapsort#Pseudocode

    int root = start;

    while (2 * root + 1 <= end) {
        int child = 2 * root + 1; //left child
        int swap = root;

        if (h[swap] < h[child]) {
            swap = child;
        }

        int child1 = child + 1;
        if (child1 <= end && h[swap] < h[child1]) {
            swap = child + 1;
        }

        if (swap == root) {
            break;
        }
        else {
            std::swap(h[root], h[swap]);
            root = swap;
        }
    }
}

void heapify(Heap& h, int it) {

    int start = (int)floor(((it - 1) - 1) / 2);
    while (start >= 0) {
        siftDown(h, start, it - 1);
        --start;
    }
}

void heapsort(Heap& h) {

    int it = (int)h.size();
    heapify(h, it);
    int end = it - 1;
    while (end > 0) {
        std::swap(h[end], h[0]);
        --end;
        siftDown(h, 0, end);
        print_state(h, end);
    }
}

void print_heap(const Heap h) {

    for (const auto& n : h) {
        std::cout << n << " ";
    }
    std::cout << '\n';
}

int main()
{

    //srand(time(NULL));
    int it;
    std::cin >> it;
    for (int i = 0; i < it; ++i) {

        Heap h;

        int ct;
        std::cin >> ct;
        for (int k = 0; k < ct; ++k) {

            int in;
            std::cin >> in;
            //in = rand() % 100 + 1;
            h.push_back(in);
        }

        heapsort(h);

        print_heap(h);
        //std::cout << "done" << '\n';

    }

    return 0;
}