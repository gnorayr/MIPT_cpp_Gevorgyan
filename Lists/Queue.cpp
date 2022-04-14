#include <iostream>

struct Node {
    int val;
    Node *next;
};

struct Queue {
    unsigned size;
    Node *head;
    Node *tail;
};

Node *createNode(int value) {
    return new Node{value, nullptr};
}

Node *ith_node(Queue *list, unsigned idx) {
    Node *node = list->head;
    for (int i = 0; i < idx; ++i) {
        node = node->next;
    }
    return node;
}

void enQueue(Queue *list, int new_val) {
    Node *new_node = createNode(new_val);
    if (list->size != 0) {
        list->tail->next = new_node;
        list->tail = new_node;
    } else {
        list->tail = new_node;
        list->head = new_node;
    }
    list->size++;
}

int deQueue(Queue *list) {

    int head_val = list->head->val;
    delete list->tail;

    list->size--;
    if (list->size != 0) {
        Node *new_tail = ith_node(list, list->size - 1);
        list->tail = new_tail;
        new_tail->next = nullptr;
    } else {
        list->head = nullptr;
        list->tail = nullptr;
    }
    return head_val;
}

int front(Queue *queue) {
    if (queue->size == 0)
        return 0;
    return queue->head->val;
}

int rear(Queue *queue) {
    if (queue->size == 0)
        return 0;
    return queue->tail->val;
}

unsigned length(Queue *list) {
    return list->size;
}

void print(Queue *list) {
    if (list->size != 0) {
        for (int idx = 0; idx < list->size; ++idx) {
            std::cout << ith_node(list, idx)->val << " ";
        }
        std::cout << std::endl;
    } else
        std::cout << "list is empty" << std::endl;
}


void clear(Queue *list) {
    for (unsigned i = list->size; i > 0; --i) {
        deQueue(list);
    }
}

Queue *createList(unsigned size) {
    Queue *tmp = new Queue{0, nullptr, nullptr};
    for (int i = 0; i < size; ++i) {
        enQueue(tmp, 0);
    }
    return tmp;
}

int main() {
    Queue list1 = *createList(2);
    print(&list1);
}
