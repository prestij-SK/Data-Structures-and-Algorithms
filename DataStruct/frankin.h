#ifndef FRANKIN_H
#define FRANKIN_H

namespace skt {


// Frankinstein List
template <typename T>
class frank {
private:
    struct Node {
        T m_data;
        Node* m_next;
        Node* m_prev;
        Node* m_desc; // lower
        Node* m_asc; // higher

        Node();
        Node(const T&);
        ~Node();

        // void search_mid_node();
        void show_head_node();
        void show_tail_node();
        void show_ascending_node();
        void show_descending_node();

    } *m_head, *m_tail, *m_low, *m_high;

public:
    frank();
    frank(const T&);
    ~frank();

public:
    void push_back(const T&);
    void push_front(const T&);
    void insert(int, const T&);
    void insert_mid(Node*);
    void show_head();
    void show_tail();
    void show_ascending();
    void show_descending();
};
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
frank<T>::Node::Node() : m_data{}, m_next{}, m_prev{}, m_desc{}, m_asc{} {}

template <typename T>
frank<T>::Node::Node(const T& data) : Node() {
    m_data = data; 
}

template <typename T>
frank<T>::Node::~Node() {}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
void frank<T>::Node::show_head_node() {
    Node* temp = this;
    while (temp) {
        std::cout << temp->m_data << " -> ";
        temp = temp->m_next;
    }
}

template <typename T>
void frank<T>::Node::show_tail_node() {
    Node* temp = this;
    while (temp) {
        std::cout << temp->m_data << " -> ";
        temp = temp->m_prev;
    }
}

template <typename T>
void frank<T>::Node::show_ascending_node() {
    Node* temp = this;
    while (temp) {
        std::cout << temp->m_data << " < ";
        temp = temp->m_asc;
    }
}

template <typename T>
void frank<T>::Node::show_descending_node() {
    Node* temp = this;
    while (temp) {
        std::cout << temp->m_data << " > ";
        temp = temp->m_desc;
    }
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
frank<T>::frank() : m_head{}, m_tail{}, m_low{}, m_high{} {}

template <typename T>
frank<T>::frank(const T& data) {
    m_head = new Node(data);
    m_tail = m_head;
    m_low = m_head;
    m_high = m_head;
}

template <typename T>
frank<T>::~frank() {
    
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
void frank<T>::insert_mid(Node* curr) {
    Node* temp = m_low->m_asc;
    while (temp != m_high) {
        if (curr->m_data <= temp->m_data) {
            curr->m_asc = temp;
            curr->m_desc = temp->m_desc;
            temp->m_desc->m_asc = curr;
            temp->m_desc = curr;
            return;
        }
        temp = temp->m_asc;
    }
    curr->m_asc = temp;
    curr->m_desc = temp->m_desc;
    temp->m_desc->m_asc = curr;
    temp->m_desc = curr;
}  

template <typename T>
void frank<T>::push_back(const T& data) {
    if (!m_head) {
        m_head = new Node(data);
        m_tail = m_head;
        m_low = m_head;
        m_high = m_head;
        return;
    }
    m_tail->m_next = new Node(data);
    m_tail->m_next->m_prev = m_tail;
    m_tail = m_tail->m_next;

    if (m_tail->m_data <= m_low->m_data) {
        m_tail->m_asc = m_low;
        m_low->m_desc = m_tail;
        m_tail->m_desc = nullptr;
        m_low = m_tail;
    }
    else if (m_tail->m_data >= m_high->m_data) {
        m_tail->m_desc = m_high;
        m_high->m_asc = m_tail;
        m_tail->m_asc = nullptr;
        m_high = m_tail;
    }
    else {
        this->insert_mid(m_tail);
    }
}

template <typename T>
void frank<T>::push_front(const T& data) {
    if (!m_head) {
        m_head = new Node(data);
        m_tail = m_head;
        m_low = m_head;
        m_high = m_head;
        return;
    }
    m_head->m_prev = new Node(data);
    m_head->m_prev->m_next = m_head;
    m_head = m_head->m_prev;

    if (m_head->m_data <= m_low->m_data) {
        std::cout << "\ninto_low:  " << data << "\n";
        m_head->m_asc = m_low;
        m_low->m_desc = m_head;
        m_head->m_desc = nullptr;
        m_low = m_head;
    }
    else if (m_head->m_data >= m_high->m_data) {
        std::cout << "\ninto_high:  " << data << "\n";
        m_head->m_desc = m_high;
        m_high->m_asc = m_head;
        m_head->m_asc = nullptr;
        m_high = m_head;
    }
    else {
        std::cout << "\ninto_mid:";
        this->insert_mid(m_head);
    }
}

template <typename T>
void frank<T>::insert(int pos, const T& data) {
    if (pos < 0) {
        return;
    }
    if (!m_head && pos > 0) {
        return;
    }

    Node* temp = m_head;
    int count = 0;
    while (temp && count < pos) {
        temp = temp->m_next;
        ++count;
    }

    if (temp == m_head) {
        this->push_front(data);
        return;
    }

    Node* node_new = new Node(data);
    temp->m_prev->m_next = node_new;
    node_new->m_next = temp;
    node_new->m_prev = temp->m_prev;
    temp->m_prev = node_new;
    
    if (node_new->m_data <= m_low->m_data) {
        std::cout << "\ninto_low:  " << data << "\n";
        node_new->m_asc = m_low;
        m_low->m_desc = node_new;
        node_new->m_desc = nullptr;
        m_low = node_new;
    }
    else if (node_new->m_data >= m_high->m_data) {
        std::cout << "\ninto_high:  " << data << "\n";
        node_new->m_desc = m_high;
        m_high->m_asc = node_new;
        node_new->m_asc = nullptr;
        m_high = node_new;
    }
    else {
        std::cout << "\ninto_mid:";
        this->insert_mid(node_new);
    }
}

template <typename T>
void frank<T>::show_head() {
    if (m_head) {
        m_head->show_head_node();
    }
    std::cout << "\n";
}

template <typename T>
void frank<T>::show_tail() {
    if (m_head) {
        m_tail->show_tail_node();
    }
    std::cout << "\n";
}

template <typename T>
void frank<T>::show_ascending() {
    if (m_head) {
        m_low->show_ascending_node();
    }
    std::cout << "\n";
}

template <typename T>
void frank<T>::show_descending() {
    if (m_head) {
            m_high->show_descending_node();
    }
    std::cout << "\n";
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

} // skt

#endif // FRANKIN_H
