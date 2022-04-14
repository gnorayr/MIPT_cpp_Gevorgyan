#include <iostream>

struct Node {
    int val;
    Node *next;
};

struct Stack {
    unsigned size;
    Node *head;
    Node *tail;
};

Node *createNode(int value) {
    return new Node{value, nullptr};
}

Node *ith_node(Stack *list, unsigned idx) {
    Node *node = list->head;
    for (int i = 0; i < idx; ++i) {
        node = node->next;
    }
    return node;
}

void push(Stack *list, int new_val) {
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

int pop(Stack *list) {
    if (list->size == 0) {
        std::cout << "WRONG" << std::endl;
        return 0;
    }
    int tail_val = list->tail->val;
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
    return tail_val;
}

int top(Stack *list) {
    if (list->size == 0)
        return 0;
    return list->tail->val;
}

bool empty ( Stack * stack ) {
    return stack->size == 0;
}

void print(Stack *list) {
    if (list->size != 0) {
        for (int idx = 0; idx < list->size; ++idx) {
            std::cout << ith_node(list, idx)->val << " ";
        }
        std::cout << std::endl;
    } else
        std::cout << "list is empty" << std::endl;
}


void clear(Stack *list) {
    for (unsigned i = list->size; i > 0; --i) {
        pop(list);
    }
}

Stack *createList(unsigned size) {
    Stack *tmp = new Stack{0, nullptr, nullptr};
    for (int i = 0; i < size; ++i) {
        push(tmp, 0);
    }
    return tmp;
}

int main() {
    Stack list1 = *createList(2);
    print(&list1);
}
