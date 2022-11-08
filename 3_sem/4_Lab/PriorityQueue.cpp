#include <chrono>
#include <iostream>
#include <random>

std::mt19937 rng(std::chrono::system_clock::now().time_since_epoch().count());

template<typename T>
struct Comparator {
    virtual bool operator( )(T const &, T const &) const = 0;
};

template<typename T>
struct SimpleComparator : Comparator<T> {
    bool operator( )(T const &lha, T const &rha) const override {
        return lha < rha;
    }
};

template<typename T>
struct Node {
    T val;
    Node *next;
    Node *previous;

    Node (T val, Node* next, Node *previous): val(val), next(next), previous(previous) { }
    Node (T val): val(val), next(nullptr), previous(nullptr) { }
};

template<typename T>
struct Queue {
private:
    unsigned size;
    Node<T> *head;
    Node<T> *tail;
    Comparator<T> &comp;
public:
    Queue(unsigned size, Node<T> *head, Node<T> *tail, Comparator<T> &comp): size(size), head(head), tail(tail), comp(comp) { }
    Queue(Comparator<T> &comp): size(0), head(nullptr), tail(nullptr), comp(comp){ }

    void push(T val) {
        auto *new_Node = new Node<T>(val);

        auto curr_Node = head;
        if (size == 0) {
            head = new_Node;
            head->previous = nullptr;
            head->next = nullptr;
            tail = new_Node;
            tail->previous = nullptr;
            tail->next = nullptr;
        } else {
            while(curr_Node != nullptr and comp(curr_Node->val, new_Node->val)) {
                curr_Node = curr_Node->next;
            }
            if (curr_Node == nullptr) {
                new_Node->previous = tail;
                tail->next = new_Node;
                tail = new_Node;
                new_Node->next = nullptr;
            } else {
                new_Node->previous = curr_Node->previous;
                new_Node->next = curr_Node;
                if (curr_Node->previous != nullptr) {
                    curr_Node->previous->next = new_Node;
                } else {
                    head = new_Node;
                }
                curr_Node->previous = new_Node;
            }
        }
        size++;
    }
    T peek() {
        if (tail != nullptr)
            return tail->val;
        else
            std::cout << "queue is empty" << std::endl;
    }

    void poll() {
        if (size == 1) {
            delete tail;
            head = nullptr;
            tail = nullptr;
        } else {
            tail = tail->previous;
            delete tail->next;
            tail->next = nullptr;
        }
        size--;
    };

    bool is_empty() {
        return size;
    }
};

int main() {
    SimpleComparator<int> comp;
    Queue<int> pq(comp);

    std::uniform_int_distribution<int> distrib(0, 100);
    int n = 20;

    for (int i = 0; i < n; ++i) {
        int a = distrib(rng);
        std::cout << a << ',' << ' ';
        pq.push(a);
    }
    std::cout << std::endl;
    for (int i = 0; i < n; ++i) {
        std::cout << pq.peek() << ',' << ' ';
        pq.poll();
    }
}
