#include <iostream>

struct Node {
    int val;
    Node *next;
    Node *prev;
};

struct DoubleList {
    unsigned size;
    Node *head;
    Node *tail;
};

Node *createNode(int value) {
    return new Node{value, nullptr, nullptr};
}

Node *ith_node(DoubleList *list, unsigned idx) {
    if(idx < 0 || idx >= list->size)
        return nullptr;
    Node *node = list->head;
    for (int i = 0; i < idx; ++i) {
        node = node->next;
    }
    return node;
}

void push_back(DoubleList *list, int new_val) {
    Node *new_node = createNode(new_val);
    if (list->size != 0) {
        list->tail->next = new_node;
        new_node->prev = list->tail;
        list->tail = new_node;
    } else {
        list->tail = new_node;
        list->head = new_node;
    }
    list->size++;
}

void push_front(DoubleList *list, int new_val) {
    Node *new_node = createNode(new_val);
    if (list->size != 0) {
        new_node->next = list->head;
        list->head->prev = new_node;
        list->head = new_node;
    } else {
        list->tail = new_node;
        list->head = new_node;
    }
    list->size++;
}

DoubleList *createList(unsigned size) {
    auto *tmp = new DoubleList{0, nullptr, nullptr};
    for (int i = 0; i < size; ++i) {
        push_back(tmp, i);
    }
    return tmp;
}

void insert(DoubleList *list, unsigned idx, int new_val) {
    if (idx != 0) {
        if (idx < 0 || idx >= list->size) {
            std::cout << "I can't do it" << std::endl;
            return;
        }
    }
    if (idx == 0) {
        push_front(list, new_val);
        return;
    }
    Node *new_node = createNode(new_val);
    if (idx == list->size - 1) {
        push_back(list, new_val);
        return;
    }
    Node *node = ith_node(list, idx);
    Node *next_node = node->next;
    new_node->prev = node;
    node->next = new_node;
    new_node->next = next_node;
    next_node->prev = new_node;
    list->size++;
}

int pop_back(DoubleList *list) {
    if (list->size == 0) {
        std::cout << "I can't do it" << std::endl;
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

int pop_front(DoubleList *list) {
    if (list->size == 0) {
        std::cout << "I can't do it" << std::endl;
        return 0;
    }

    int head_val = list->head->val;
    Node *new_head = list->head->next;
    delete list->head;

    list->size--;
    list->head = new_head;
    if (list->size != 0) {
        list->head->prev = nullptr;
    }
    if (list->size == 0) {
        list->tail = nullptr;
    }
    return head_val;
}

int remove(DoubleList *list, unsigned idx) {
    if (idx == 0)
        return pop_front(list);
    if (idx == list->size - 1)
        return pop_back(list);

    Node *previous_node = ith_node(list, idx - 1);
    Node *next_node = previous_node->next->next;
    int node_val = previous_node->next->val;
    delete previous_node->next;
    previous_node->next = next_node;
    next_node->prev = previous_node;
    list->size--;
    return node_val;

}

unsigned length(DoubleList *list) {
    return list->size;
}

int get(DoubleList *list, unsigned idx) {
    if (ith_node(list, idx) == nullptr) {
        std::cout << "I can't do it" << std::endl;
        return 0;
    }
    return ith_node(list, idx)->val;
}


void print(DoubleList *list) {
    if (list->size != 0) {
        for (int idx = 0; idx < list->size; ++idx) {
            std::cout << ith_node(list, idx)->val << " ";
        }
        std::cout << std::endl;
    } else
        std::cout << "list is empty" << std::endl;
}

void printReverse(DoubleList *list) {
    if (list->size != 0) {
        Node *node = list->tail;
        for (int idx = 0; idx < list->size; ++idx) {
            std::cout << node->val << " ";
            node = node->prev;
        }
        std::cout << std::endl;
    } else
        std::cout << "list is empty" << std::endl;
}

void clear(DoubleList *list) {
    for (unsigned i = list->size; i > 0; --i) {
        pop_back(list);
    }
}

int main() {
    DoubleList list1 = *createList(0);
    print(&list1);
    pop_back(&list1);
    printReverse(&list1);
    clear(&list1);
    printReverse(&list1);
}
