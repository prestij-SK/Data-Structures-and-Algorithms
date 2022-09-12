#ifndef BS_TREE_H
#define BS_TREE_H

#include <queue>
#include <iostream>
#include <fstream>
#include <utility> // for swap only

namespace skt {

// Binary Search Tree
template <typename T>
class bs_tree {

private:
    struct Node {
        T m_data;
        Node* m_left;
        Node* m_right;

        Node();
        Node(const T&);
        
        void insert_node(Node*, const T&);
        void copy_node(Node*, Node*);
        void destruct_node(Node*);
        Node* remove_node(Node*, const T&);
        Node* min_element_node(Node*);
        Node* max_element_node(Node*);
        void show_inorder_node(Node*);
        void show_level_order_node(Node*);
        void write_into_file_node(Node*, const std::string&);
        void read_from_file_node(Node*, const std::string&); 
        
    } *m_root;

public:
    bs_tree();
    bs_tree(const T&);
    bs_tree(const bs_tree<T>&);
    bs_tree(bs_tree<T>&&);
    bs_tree(std::initializer_list<T>);
    ~bs_tree();

public:
    void insert(const T&);
    void remove(const T&);
    T min_element();
    T max_element();
    void show_inorder();
    void show_level_order();

public:
    // BONUSES
    void write_into_file(const std::string&);
    void read_from_file(const std::string&);
};
////////////////////////////////////////////////////////////////////////////////////
///////////////////// NODE /////////////////////////////////////////////////////////
template <typename T>
bs_tree<T>::Node::Node() : m_data{}, m_left{}, m_right{} {}

template <typename T>
bs_tree<T>::Node::Node(const T& data) : Node() {
    m_data = data;
}

template <typename T>
void bs_tree<T>::Node::insert_node(Node* root, const T& data) {
    if (!root) {
        return;
    }

    if (data < root->m_data) {
        if (!root->m_left) {
            root->m_left = new Node(data);
            return;
        }
        insert_node(root->m_left, data);
    }
    else {
        if (!root->m_right) {
            root->m_right = new Node(data);
            return;
        }
        insert_node(root->m_right, data);
    }
}

template <typename T>
void bs_tree<T>::Node::copy_node(Node* root, Node* cpy_root) {
    if (!cpy_root) {
        return;
    }

    if (cpy_root->m_left) {
        root->m_left = new Node(cpy_root->m_left->m_data);
    }
    if (cpy_root->m_right) {
        root->m_right = new Node(cpy_root->m_right->m_data);
    }

    copy_node(root->m_left, cpy_root->m_left);
    copy_node(root->m_right, cpy_root->m_right);
}

template <typename T>
void bs_tree<T>::Node::destruct_node(Node* root) {
    if (!root) {
        return;
    }

    destruct_node(root->m_left);
    destruct_node(root->m_right);
    delete root;
    root = nullptr;
}

template <typename T>
typename bs_tree<T>::Node* bs_tree<T>::Node::remove_node(Node* root, const T& data) {
    if (!root) {
        return root;
    }

    if (data < root->m_data) {
        root->m_left = remove_node(root->m_left, data);
    }
    else if (data > root->m_data) {
        root->m_right = remove_node(root->m_right, data);
    }
    else {
        if (!root->m_left && !root->m_right) {
            delete root;
            root = nullptr;
        }
        else if (root->m_left && !root->m_right) {
            Node* temp = root;
            root = root->m_left;
            delete temp;
        }
        else if (root->m_right && !root->m_left) {
            Node* temp = root;
            root = root->m_right;
            delete temp;
        }
        else {
            Node* temp = root->min_element_node(root->m_right);
            root->m_data = temp->m_data;
            root->m_right = remove_node(root->m_right, data);
        }
    }
    return root;
}

template <typename T>
typename bs_tree<T>::Node* bs_tree<T>::Node::min_element_node(Node* root) {
    if (!root->m_left) {
        return root;
    }
    return min_element_node(root->m_left);
}

template <typename T>
typename bs_tree<T>::Node* bs_tree<T>::Node::max_element_node(Node* root) {
    if (!root->m_right) {
        return root;
    }
    return max_element_node(root->m_right);
}

template <typename T>
void bs_tree<T>::Node::show_inorder_node(Node* root) {
    if (root != nullptr) {
        show_inorder_node(root->m_left);
        std::cout << root->m_data << " ";
        show_inorder_node(root->m_right);
    }
}

template <typename T>
void bs_tree<T>::Node::show_level_order_node(Node* root) {
    if (!root) {
        return;
    }
    std::queue<Node*> que;
    que.push(root);
    while (!que.empty()) {
        Node* temp = que.front();
        std::cout << temp->m_data << " ";
        
        if (temp->m_left) {
            que.push(temp->m_left);
        }
        if (temp->m_right) {
            que.push(temp->m_right);
        }
        que.pop();
    }
}
///////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
template <typename T>
bs_tree<T>::bs_tree() : m_root{} {}

template <typename T>
bs_tree<T>::bs_tree(const T& data) : m_root{new Node(data)} {}

template <typename T>
bs_tree<T>::bs_tree(const bs_tree<T>& other) : bs_tree() {
    if (other.m_root != nullptr) {
        m_root = new Node(other.m_root->m_data);
        m_root->copy_node(m_root, other.m_root);
    }
}

template <typename T>
bs_tree<T>::bs_tree(bs_tree<T>&& other) : m_root{other.m_root}{
    other.m_root = nullptr;
}

template <typename T>
bs_tree<T>::bs_tree(std::initializer_list<T> list) {
    auto it = list.begin();
    m_root = new Node(*it);
    ++it;

    for(;it != list.end(); ++it) {
        m_root->insert_node(m_root, *it);
    }
}

template <typename T>
bs_tree<T>::~bs_tree() {
    if (m_root) {
        m_root->destruct_node(m_root);
        m_root = nullptr;
    }
}

template <typename T>
void bs_tree<T>::insert(const T& data) {
    if (m_root) {
        m_root->insert_node(m_root, data);
    }
    else {
        m_root = new Node(data);
    }
}

template <typename T>
void bs_tree<T>::remove(const T& data) {
    m_root->remove_node(m_root, data);
}

template <typename T>
T bs_tree<T>::min_element() {
    Node* temp = m_root->min_element_node(m_root);
    return temp->m_data;
}

template <typename T>
T bs_tree<T>::max_element() {
    Node* temp = m_root->max_element_node(m_root);
    return temp->m_data;
}

template <typename T>
void bs_tree<T>::show_inorder(){
    if (m_root) {
        m_root->show_inorder_node(m_root);
    }
    std::cout << "\n";
}

template <typename T>
void bs_tree<T>::show_level_order() {
    if (m_root){
        m_root->show_level_order_node(m_root);
    }
    std::cout << "\n";
}



///////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////BONUSES////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////
// std::vector<std::vector<int>> vec;
//         std::queue<TreeNode*> que;
//         que.push(root);
        
//         while (!que.empty()) {
//             std::vector<int> vec_temp;
//             std::queue<TreeNode*> que_temp;
//             while (!que.empty()) {
//                 TreeNode* temp = que.front();
//                 vec_temp.push_back(temp->val);
//                 if (temp->left) {
//                     que_temp.push(temp->left);
//                 }
//                 if (temp->right) {
//                     que_temp.push(temp->right);
//                 }
//                 que.pop();
//             }
//             vec.push_back(vec_temp);
//             que = que_temp;
//         }

template <typename T>
void bs_tree<T>::Node::write_into_file_node(Node* root, const std::string& path) {
    std::ofstream fout;
    fout.open(path);

    if (fout.is_open()) {
        std::queue<Node*> que;
        que.push(root);
        while (!que.empty()) {
            std::queue<Node*> que_temp = que;
            std::queue<Node*> empty;
            std::swap(que, empty);
            while (!que_temp.empty()) {
                Node* temp = que_temp.front();
                fout << temp->m_data << " ";

                if (temp->m_left) {
                    que.push(temp->m_left);
                }
                if (temp->m_right) {
                    que.push(temp->m_right);
                }
                que_temp.pop();
            }
            fout << "\n";
        }
    }
    else {
        return;
    }
} 

template <typename T>
void bs_tree<T>::write_into_file(const std::string& path) {
    if (m_root && path.length() != 0) {
        m_root->write_into_file_node(m_root, path);
    }
}    

template <typename T>
void bs_tree<T>::read_from_file(const std::string& path) {
    std::ifstream fin;
    fin.open(path);

    if (fin.is_open()) {
        while (!fin.eof()) {
            std::string token;
            fin >> token;
            if (token.length() != 0) {
                this->insert(std::stoi(token));
            }
        }
    }
    else {
        return;
    }
}

} // skt

#endif // BS_TREE_H