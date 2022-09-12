#ifndef RB_TREE_H
#define RB_TREE_H

namespace skt {

// RED BLACK TREE
template <typename T>
class rb_tree {

private:
    struct Node {
        T m_data;
        bool m_rb; // 1 red, 0 black
        Node* m_left;
        Node* m_right;
        Node* m_parent;

        Node();
        Node(const T&);

        // void make_red();
        // void make_black();
        void insert_node(Node*, const T&);
        void balance_node_pos(Node*);

        void show_inorder_node(Node* root) {
            if (root != nullptr) {
                show_inorder_node(root->m_left);

                std::cout << root->m_data << "(";
                if (root->m_rb) {
                    std::cout << "red" << ") ";
                }
                else {
                    std::cout << "black" << ") ";
                }

                // if (root->m_parent) {
                //     if (root->m_rb) {
                //         std::cout << "red" << " ";
                //     }
                //     else {
                //         std::cout << "black" << " ";
                //     }
                // }

                show_inorder_node(root->m_right);
            }
        }

        void force(Node* root) {
            std::cout << root->m_data << " ";
            std::cout << root->m_left->m_data << " ";
            std::cout << root->m_right->m_data << " ";
            std::cout << root->m_right->m_left->m_data << " ";
            std::cout << root->m_right->m_right->m_data << " ";
        }

    } *m_root;

public:
    rb_tree();
    rb_tree(const T&);

public:
    void insert(const T&);

    void tester() {
        if (m_root) {
            m_root->show_inorder_node(m_root);
        }
        std::cout << "\n-------\n";
    }

    void force_test() {
        m_root->force(m_root);
        std::cout << "\n============\n";
    }
    
};
////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
rb_tree<T>::Node::Node() : m_data{}, m_rb{}, m_left{}, m_right{}, m_parent{} {}

template <typename T>
rb_tree<T>::Node::Node(const T& data) : Node() {
    m_data = data;
}

// template <typename T>
// void rb_tree<T>::Node::make_red() {m_rb = true;}

// template <typename T>
// void rb_tree<T>::Node::make_black() {m_rb = false;}













template <typename T>
void rb_tree<T>::Node::balance_node_pos(Node* current) {
    // if root, just exit
    if (!current->m_parent || (current->m_parent->m_rb == 0)) {
        return;
    }
    // std::cout << "\ncurr_par: " << current->m_parent->m_data << "\n";

    Node* grand_parent = current->m_parent->m_parent;
    
    // checking node parent was right or left node
    if (current->m_parent == current->m_parent->m_parent->m_right) {
        // parent was right node
        std::cout << "\ncurrent_is_right: " << current->m_data << "   color: " << current->m_rb << "\n";
        std::cout << "\ncurrent_par_is_right: " << current->m_parent->m_data 
                  << "   color: " << current->m_parent->m_rb << "\n";
        Node* uncle = current->m_parent->m_parent->m_left;
        if (uncle) {
             std::cout << "\nuncle: " << uncle->m_data << "   color: " << uncle->m_rb << "\n";
        }
        if (uncle) {
            if (uncle->m_rb) { // if uncle is red, change colors of current's parent and uncle
                std::cout << "color change\n";
                current->m_parent->m_rb = !current->m_parent->m_rb;
                uncle->m_rb = !uncle->m_rb;
                std::cout << "\ngrand_color_before:  " << current->m_parent->m_parent->m_rb << "\n";
                if (grand_parent->m_parent) {
                    grand_parent->m_rb = !grand_parent->m_rb;
                    std::cout << "\ngrand_color_after:  " << current->m_parent->m_parent->m_rb << "\n";
                }
                balance_node_pos(grand_parent);
                return;
            }
        }
        if (current == current->m_parent->m_left) { // checking current is left or right node
            // current was left node, do R L rotate
            // Node* temp = current;
            current->m_parent->m_parent->m_right = current;
            current->m_right = current->m_parent;
            current->m_parent->m_left = nullptr;
            current->m_parent = current->m_right->m_parent;
            current->m_right->m_parent = current;

            Node* temp = current->m_parent;
            if (current->m_parent == current->m_parent->m_parent->m_right) { // checking parent is left or right node
                // parent is right node
                current->m_parent->m_parent->m_right = current;
            }
            else {
                // parent is left node
                current->m_parent->m_parent->m_left = current;
            }
            // rotating current and current->parent
            current->m_rb = !current->m_rb;
            current->m_parent->m_rb = !current->m_parent->m_rb;
            current->m_parent = current->m_parent->m_parent;
            current->m_left = temp;
            temp->m_parent = current;
            temp->m_right = nullptr;
        }
        else {
            // <<<<<<<<<<<<<<<<<<<<<??>>>>>>>>>>>>>>>>>>>>>
            return;
        }
        // std::cout << "\n\nROTATE\n\n";
        // std::cout << "\ncurrent_is_right: " << current->m_data << "   color: " << current->m_rb << "\n";
        // std::cout << "\ncurrent_par_is_right: " << current->m_parent->m_data 
        //           << "   color: " << current->m_parent->m_rb << "\n";
    }
    else {
        // parent was left node
        Node* uncle = current->m_parent->m_parent->m_right;
        if (uncle) {
            if (uncle->m_rb) { // if uncle is red, change colors of current's parent and uncle
                current->m_parent->m_rb = !current->m_parent->m_rb;
                uncle->m_rb = !uncle->m_rb;
                if (grand_parent->m_parent) {
                    grand_parent->m_rb = !grand_parent->m_rb;
                }
                balance_node_pos(grand_parent);
                return;
            }
        }

        if (current == current->m_parent->m_right) { // checking current is left or right node
            // current was right node, do L R
            // Node* temp = current->m_parent;
            current->m_parent->m_parent->m_left = current;
            current->m_left = current->m_parent;
            current->m_parent->m_right = nullptr;
            current->m_parent = current->m_left->m_parent;
            current->m_left->m_parent = current;
        }
        // now do L L
        Node* temp = current->m_parent;
        if (current->m_parent == current->m_parent->m_parent->m_right) { // checking parent is left or right node
            // parent is right node
            current->m_parent->m_parent->m_right = current;
        }
        else {
            // parent is left node
            current->m_parent->m_parent->m_left = current;
        }
        // rotating current and current->parent
        current->m_rb = !current->m_rb;
        current->m_parent->m_rb = !current->m_parent->m_rb;
        current->m_parent = current->m_parent->m_parent;
        current->m_right = temp;
        temp->m_parent = current;
        temp->m_left = nullptr;
    }
}










template <typename T>
void rb_tree<T>::Node::insert_node(Node* root, const T& data) {
    if (!root) {
        return;
    }

    if (data < root->m_data) {
        if (!root->m_left) {
            root->m_left = new Node(data);
            root->m_left->m_parent = root;
            root->m_left->m_rb = true;
            
            if (root->m_rb) {
                balance_node_pos(root->m_left);
            }
            return;
        }
        insert_node(root->m_left, data);
    }
    else {
        if (!root->m_right) {
            root->m_right = new Node(data);
            root->m_right->m_parent = root;
            root->m_right->m_rb = true;

            if (root->m_rb) {
                std::cout << "\n " << data << " right\n";
                balance_node_pos(root->m_right);
            }
            return;
        }
        insert_node(root->m_right, data);
    }
}
////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
rb_tree<T>::rb_tree() : m_root{nullptr} {}

template <typename T>
rb_tree<T>::rb_tree(const T& data) : m_root{new Node(data)} {}
////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
void rb_tree<T>::insert(const T& data) {
    if (m_root) {
        m_root->insert_node(m_root, data);
    }
    else {
        m_root = new Node(data);
    }
}
////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////

}

#endif // RB_TREE_H