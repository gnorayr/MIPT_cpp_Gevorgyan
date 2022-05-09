#include <iostream>

template<typename DataType>
struct ListNode {
    int key; // key to access the data and compare nodes
    DataType data; // raw data
    ListNode *left; // pointer to left node
    ListNode *right; // pointer to right node
    ListNode *p; // parent pointer
};

template<typename DataType>
ListNode<DataType> *search(ListNode<DataType> *root, int key) {
    if (root == nullptr or key == root->key)
        return root;
    if (key < root->key)
        return search(root->left, key);
    else
        return search(root->right, key);
}

template<typename DataType>
ListNode<DataType> *find_minimum(ListNode<DataType> *root) {
    while (root->left != nullptr)
        root = root->left;
    return root;
}

template<typename DataType>
ListNode<DataType> *find_maximum(ListNode<DataType> *root) {
    while (root->right != nullptr)
        root = root->right;
    return root;
}

template<typename DataType>
struct SimpleTree {
    ListNode<DataType> *root;
};

template<typename DataType>
void insert(SimpleTree<DataType> *Tree, ListNode<DataType> *z) {
    ListNode<DataType> *y = nullptr;
    ListNode<DataType> *x = Tree->root;
    while (x != nullptr) {
        y = x;
        if (z->key < x->key)
            x = x->left;
        else
            x = x->right;
    }
    z->p = y;
    if (y == nullptr)
        Tree->root = z;
    else if (z->key < y->key)
        y->left = z;
    else
        y->right = z;
}

template<typename DataType>
void transplant(SimpleTree<DataType> *T, ListNode<DataType> *u, ListNode<DataType> *v) {
    if (u->p == nullptr)
        T->root = v;
    else if (u == u->p->left)
        u->p->left = v;
    else
        u->p->right = v;
    if (v != nullptr)
        v->p = u->p;
}

template<typename DataType>
void remove (SimpleTree<DataType> *T, ListNode<DataType> *z) {
    if (z->left == nullptr)
        transplant(T, z, z->right);
    else if (z->right == nullptr)
        transplant(T, z, z->left);
    else {
        ListNode<DataType> *y = find_minimum(z->right);
        if (y->p != z) {
            transplant(T, y, y->right);
            y->right = z->right;
            y->right->p = y;
        }
        transplant(T, z, y);
        y->left = z->left;
        y->left->p = y;
    }
}

template<typename DataType>
ListNode<DataType> *createNode(int key, DataType data) {
    return new ListNode<DataType>{key, data, nullptr, nullptr, nullptr};
}

template<typename DataType>
SimpleTree<DataType> *createTree(ListNode<DataType> *root) {
    return new SimpleTree<DataType>{root};
}

int main() {
    SimpleTree<int> *a = createTree<int>(nullptr);
    for (int i = 10; i > 0; --i) {
        insert<int>(a, createNode(i, 1));
    }
    std::cout << a->root->left->left->key;
    remove<int>(a, search<int>(a->root, 8));
    std::cout << a->root->left->key;
    std::cout << a->root->left->left->key;
}
