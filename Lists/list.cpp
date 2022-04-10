#include <iostream>

struct Node {
    int val;
    Node *next;
};

struct List {
    unsigned size;
    Node *head;
    Node *tail;
};

Node *createNode(int value) {
    return new Node{value, nullptr};
}

Node *ith_node(List *list, unsigned idx) {
    Node *node = list->head;
    for (int i = 0; i < idx; ++i) {
        node = node->next;
    }
    return node;
}

void push_back(List *list, int new_val) {
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

void push_front(List *list, int new_val) {
    Node *new_node = createNode(new_val);
    if (list->size != 0) {
        new_node->next = list->head;
        list->head = new_node;
    } else {
        list->tail = new_node;
        list->head = new_node;
    }
    list->size++;
}

List *createList(unsigned size) {
    List *tmp = new List{0, nullptr, nullptr};
    for (int i = 0; i < size; ++i) {
        push_back(tmp, 0);
    }
    return tmp;
}

void insert(List *list, unsigned idx, int new_val) {
    Node *node = ith_node(list, idx);
    Node *next_node = node->next;
    Node *new_node = createNode(new_val);
    node->next = new_node;
    new_node->next = next_node;
    if (idx == list->size - 1) {
        list->tail = new_node;
    }
    list->size++;
}

int pop_back(List *list) {

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

int pop_front(List *list) {
    int head_val = list->head->val;
    Node *new_head = list->head->next;
    delete list->head;

    list->size--;
    list->head = new_head;

    if (list->size == 0) {
        list->tail = nullptr;
    }
    return head_val;
}

int remove(List *list, unsigned idx) {
    if (idx == 0)
        return pop_front(list);
    if (idx == list->size - 1)
        return pop_back(list);

    Node *previous_node = ith_node(list, idx - 1);
    Node *next_node = previous_node->next->next;
    int node_val = previous_node->next->val;
    delete previous_node->next;
    previous_node->next = next_node;
    list->size--;
    return node_val;

}

unsigned length(List *list) {
    return list->size;
}

int get(List *list, unsigned idx) {
    return ith_node(list, idx)->val;
}


void print(List *list) {
    if (list->size != 0) {
        for (int idx = 0; idx < list->size; ++idx) {
            std::cout << ith_node(list, idx)->val << " ";
        }
        std::cout << std::endl;
    } else
        std::cout << "list is empty" << std::endl;
}

void clear(List *list) {
    for (unsigned i = list->size; i > 0; --i) {
        pop_back(list);
    }
}

int main() {
    List list1 = *createList(2);
    print(&list1);
}
