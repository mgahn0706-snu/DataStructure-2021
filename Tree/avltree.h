#include <iostream>
#include <algorithm>
#include <optional>

template <typename T, typename U>
class AVLNode {

public:
    T key;
    U value;
    AVLNode<T, U>* left;
    AVLNode<T, U>* right;
    int height;

    AVLNode<T, U>(const T& k, const U& v)
    {
        key = k;
        value = v;
        left = nullptr;
        right = nullptr;
        height = 1;
    }

};

template <typename T, typename U>
class AVLTree {
public:
    AVLNode<T, U>* root = nullptr;
    ~AVLTree() {
        removeall(root);
    }

    void insert(const T& key, const U& value);
    U search(const T& key);
    bool remove(const T& key);

    //for checking
    void preorder(AVLNode<T, U>*& node) {
        if (!node) return;

        std::cout << node->key << ": " << node->value << std::endl;
        preorder(node->left);
        preorder(node->right);
    }
    void inorder(AVLNode<T, U>*& node) {
        if (!node) return;

        inorder(node->left);
        std::cout << node->key << ": " << node->value << std::endl;
        inorder(node->right);
    }


private:
    int getHeight(AVLNode<T, U>*& node);
    int getBalance(AVLNode<T, U>*& node);
    void updateHeight(AVLNode<T, U>*& node);
    AVLNode<T, U>* rotate_left(AVLNode<T, U>* node);
    AVLNode<T, U>* rotate_right(AVLNode<T, U>* node);

    AVLNode<T, U>* insert(AVLNode<T, U>*& node, const T& key, const U& value);
    U search(AVLNode<T, U>*& node, const T& key);
    AVLNode<T, U>* remove(AVLNode<T, U>*& node, const T& key);
    void removeall(AVLNode<T, U>*& node);

};

template <typename T, typename U>
int AVLTree<T, U>::getHeight(AVLNode<T, U>*& node) {
    if (!node) return 0;
    return node->height;
}

template <typename T, typename U>
int AVLTree<T, U>::getBalance(AVLNode<T, U>*& node) {
    if (!node) return 0;
    return getHeight(node->left) - getHeight(node->right);
}

template<typename T, typename U>
void AVLTree<T, U>::insert(const T& key, const U& value) {
    root = insert(root, key, value);
}

template<typename T, typename U>
U AVLTree<T, U>::search(const T& key) {
    return search(root, key);
}

template<typename T, typename U>
bool AVLTree<T, U>::remove(const T& key) {
    if (!search(root, key)) return false;
    root = remove(root, key);
    return true;
}

template<typename T, typename U>
AVLNode<T, U>* AVLTree<T, U>::rotate_left(AVLNode<T, U>* node) {
    //TODO    
    AVLNode<T, U>* rightNode = node->right;
    AVLNode<T, U>* leftOver = rightNode->left;

    node->right = leftOver;
    rightNode->left = node;//rotation

    updateHeight(node);
    updateHeight(rightNode);

    return rightNode;


}

template<typename T, typename U>
AVLNode<T, U>* AVLTree<T, U>::rotate_right(AVLNode<T, U>* node) {
    //TODO

    AVLNode<T, U>* leftNode = node->left;
    AVLNode<T, U>* leftOver = leftNode->right;

    node->left = leftOver;
    leftNode->right = node; //rotate

    updateHeight(node);
    updateHeight(leftNode);

    return leftNode;

}

template<typename T, typename U>
AVLNode<T, U>* AVLTree<T, U>::insert(AVLNode<T, U>*& node, const T& key, const U& value) {
    //TODO
    AVLNode<T, U>* temp = node;


    if (node == nullptr) {

        node = new AVLNode<T, U>(key, value);

        return node;

    }
    else if (key < node->key) {

        node->left = insert(temp->left, key, value);
    }

    else if (key > node->key) {

        node->right = insert(temp->right, key, value);
    }
    else {
        node->value = value;
        return node;
    }

    updateHeight(node);


    int balance = getBalance(node);

    if (balance >= 2) { //left unbalance
       //case2
        if (node->left->key < key) {


            node->left = rotate_left(node->left);

        }
        return rotate_right(node);
    }
    else if (balance <= -2) {//right unbalance
        if (node->right->key > key) {
            node->right = rotate_right(node->right);

        }
        return rotate_left(node);
    }

    return node;

}

template<typename T, typename U>
void AVLTree<T, U>::updateHeight(AVLNode<T, U>*& node) {
    int leftHeight = getHeight(node->left);
    int rightHeight = getHeight(node->right);
    //calculate height, could be shortened using std::max
    if (leftHeight > rightHeight) {

        node->height = leftHeight + 1;
    }
    else {
        node->height = rightHeight + 1;
    }
    return;
}

template<typename T, typename U>
U AVLTree<T, U>::search(AVLNode<T, U>*& node, const T& key) {
    //TODO
    int value;
    if (node->key == key) {
        return node->value;
    }
    else if (node->key > key) {
        if (node->left == nullptr) {
            return 0;
        }
        else {
             value = search(node->left, key);
        }
    }
    else {
        if (node->right == nullptr) {
            return 0;
        }
        else {
            value = search(node->right, key);
        }
    }
    return value;

}

template<typename T, typename U>
AVLNode<T, U>* AVLTree<T, U>::remove(AVLNode<T, U>*& node, const T& key) {
    //TODO


    AVLNode<T, U>* temp = node;


    if (temp == nullptr) {
        return nullptr;
    }
    else if (key < temp->key) {
        node->left = remove(temp->left, key);
    }
    else if (temp->key < key) {
        node->right = remove(temp->right, key);
    }

    else if (temp->left != nullptr && temp->right != nullptr) {

        AVLNode<T, U>* findMin = temp->right;
        AVLNode<T, U>* findMinTemp = temp->right;
        while (findMin != nullptr) { //two children

            findMinTemp = findMin;
            findMin = findMin->left;


        }
        temp->key = findMinTemp->key;
        node->right = remove(node->right, findMinTemp->key);
    }


    else { //one child
        AVLNode<T, U>* oldNode = temp;
        oldNode = (temp->left != nullptr) ? temp->left : temp->right;
        delete node;
        node = nullptr;
        return oldNode;


    }

    if (temp == nullptr) {
        return nullptr;
    }

    updateHeight(node);

    int balance = getBalance(node);

    if (balance >= 2) { //left unbalance
       //case2
        if (node->left->key < key) {


            node->left = rotate_left(node->left);

        }
        return rotate_right(node);
    }
    else if (balance <= -2) {//right unbalance
        if (node->right->key > key) {
            node->right = rotate_right(node->right);

        }
        return rotate_left(node);
    }

    return node;



}

template<typename T, typename U>
void AVLTree<T, U>::removeall(AVLNode<T, U>*& node) {
    //TODO
    if (node != nullptr) {
        removeall(node->left);
        removeall(node->right);
        delete node;
    }
    return;
}

