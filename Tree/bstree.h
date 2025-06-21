#include <iostream>
#include <optional>
using namespace std; //need to be deleted

template <typename T, typename U>
class BSNode {

public:
    T key;
    U value;
    BSNode<T, U>* left;
    BSNode<T, U>* right;

    BSNode<T, U>(const T& k, const U& v)
    {
        key = k;
        value = v;
        left = nullptr;
        right = nullptr;
    }

};

template<typename T, typename U>
class BSTree {

public:
    BSNode<T, U>* root = nullptr;
    ~BSTree() {
        removeall(root);
    }

    bool insert(const T& key, const U& value);
    U search(const T& key);
    bool remove(const T& key);

    //for checking
    void preorder(BSNode<T, U>*& node) {
        if (!node) return;

        std::cout << node->key << ": " << node->value << std::endl;
        preorder(node->left);
        preorder(node->right);
    }
    void inorder(BSNode<T, U>*& node) {
        if (!node) return;

        inorder(node->left);
        std::cout << node->key << ": " << node->value << std::endl;
        inorder(node->right);
    }

private:
    bool insert(BSNode<T, U>*& node, const T& key, const U& value);
    U search(BSNode<T, U>*& node, const T& key);
    BSNode<T, U>* remove(BSNode<T, U>*& node, const T& key);
    void removeall(BSNode<T, U>*& node);
};


template<typename T, typename U>
bool BSTree<T, U>::insert(const T& key, const U& value) {
    return insert(root, key, value);
}

template<typename T, typename U>
U BSTree<T, U>::search(const T& key) {
    return search(root, key);
}

template<typename T, typename U>
bool BSTree<T, U>::remove(const T& key) {
    if (!search(root, key)) return false;
    remove(root, key);
    return true;
}


template<typename T, typename U>
bool BSTree<T, U>::insert(BSNode<T, U>*& node, const T& key, const U& value) {
    //TODO
    
    BSNode<T, U>* temp = node;

    
    if (node == nullptr) {
        
        node = new BSNode<T, U>( key,value );
        
        temp = nullptr;
        return true;

    }
    else {
        BSNode<T, U>* tempPointer = root;
        
        while (temp != nullptr) {
            
            if (temp->key > key) {
                tempPointer = temp;
                temp = temp->left;
                
            }
            else {
                tempPointer = temp;
                temp = temp->right;
               
            }
            
        }
        temp = nullptr;
        
        if (tempPointer->key > key) {
            tempPointer->left = new BSNode<T, U>(key, value);
            tempPointer = nullptr;
            return true;
        }
        else if(tempPointer->key < key) {
            tempPointer->right = new BSNode<T, U>(key, value);
            tempPointer = nullptr;
            return true;
        }

        else {
            tempPointer->value = value;
            return false; //duplicate, so update
        }

    }

    return false;


}

template<typename T, typename U>
U BSTree<T, U>::search(BSNode<T, U>*& node, const T& key) {
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
BSNode<T, U>* BSTree<T, U>::remove(BSNode<T, U>*& node, const T& key) {
    //TODO

    if (!search(key)) {
        return nullptr;
    }
    BSNode<T, U>* temp = node;
    BSNode<T, U>* tempPointer = node;


    if (temp == nullptr) {
        return nullptr;
    }
    if (key < temp->key) {
        remove(temp->left, key);
    }
    else if (temp->key < key) {
        remove(temp->right, key);
    }

    else if (temp->left != nullptr && temp->right != nullptr) {
        
        BSNode<T, U>* findMin = temp->right;
        BSNode<T, U>* findMinTemp = temp->right;
        while (findMin != nullptr) {
            
            findMinTemp = findMin;
            findMin = findMin->left;

           
        }
        temp->value = findMinTemp->value;
        temp->key = findMinTemp->key;
       
        remove(temp->right, temp->key);
        delete findMin;
        findMin = nullptr;
    }
    else {
        BSNode<T, U>* oldNode = temp;
        node = (temp->left != nullptr) ? temp->left : temp->right;
        delete oldNode;
        oldNode = nullptr;

    }
    return nullptr;
 
    /*
    if (!search(node, key)) {
        return nullptr;
    }
    else {

        while (temp->key != key) {

            if (temp->key > key) {
                tempPointer = temp;
                temp = temp->left;
            }

            else {
                tempPointer = temp;
                temp = temp->right;
            }

       }
        
        if (temp->left == nullptr && temp->right == nullptr) {

            if (tempPointer->key > temp->key) {
                tempPointer->left = nullptr;
            }
            else {
                tempPointer->right = nullptr;
            }

            delete temp;
            temp = nullptr;
            
        }

        else {
            
           
        }*/




    

}




template<typename T, typename U>
void BSTree<T, U>::removeall(BSNode<T, U>*& node) {
    //TODO

    if (node) {
        removeall(node->left);
        removeall(node->right);
        delete node;
        node = nullptr;
    }
    return;

}

