#include <unordered_map>
#include <vector>


struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

/////////// HELPER FUNCTIONS ///////////
void remove_node(ListNode* node) {
    if (!node) {
        return;
    }    
    ListNode* temp = node->next;
    if (temp) {
        node->val = node->next->val;
        node->next = node->next->next;
        // destruct or delete temp here, if you used dynamic allocation
        temp->next = nullptr;
    }
    else {
        delete node;
        node = nullptr;
    }
    return;
}

int make_list_num_rev(ListNode* head) {
    if (!head) {
        return 0;
    }
    
    int sum = 0;
    int mul = 1;
    ListNode* temp = head;
    while (temp) {
        sum += temp->val * mul;
        mul *= 10;
        temp = temp->next;
    }
    return sum;
}
    
int number_digits(int num) {
    int count = 0;
    while (num) {
        num /= 10;
        ++count;
    }
    return count;
}

int num_power(int num, int p) {
    int sum = 1;
    while (p) {
        sum *= num;
        --p;
    }
    return sum;
}
////////////////////////////////


// 2.1
ListNode* delete_duplicates(ListNode* head) {
    if (!head) {
        return head;
    }
    
    std::unordered_map<int, bool> info;
    ListNode* temp = head;
    while (temp) {
        if (info[temp->val]) {
            remove_node(temp);
            continue;
        }
        info[temp->val] = true;
        temp = temp->next;
    }
    return head;
}

// 2.2
ListNode* kth_node(ListNode* head, int k) {
    if (!head) {
        return head;
    }
    int size = 0;
    ListNode* temp = head;
    while (temp) {
        ++size;
        temp = temp->next;
    }
    
    temp = head;
    size = size - k;
    while (size) {
        --size;
        temp = temp->next;
    }
    return temp;
}

// 2.3
ListNode* delete_middle_node(ListNode* head) {
    if (!head) {
        return head;
    }
    
    ListNode* slow = head;
    ListNode* fast = head;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    remove_node(slow);

    return head;
}

// 2.4
ListNode* partition_list(ListNode* head, int x) {
    if (!head) {
        return head;
    }
    
    std::vector<int> left;
    std::vector<int> right;
    ListNode* temp = head;
    while (temp) {
        if (temp->val < x) {
            left.push_back(temp->val);
        }
        else {
            right.push_back(temp->val);
        }
        temp = temp->next;
    }
    temp = head;
    
    for (int i = 0; i < left.size(); ++i) {
        temp->val = left[i];
        temp = temp->next;
    } 
    
    for (int i = 0; i < right.size(); ++i) {
        temp->val = right[i];
        temp = temp->next;
    }
    return head;
}

// 2.5
ListNode* sum_lists_reverse(ListNode* list1, ListNode* list2) {
    int num1 = make_list_num_rev(list1);
    int num2 = make_list_num_rev(list2);
    
    ListNode* temp = list1;
    if (num1 < num2) {
        temp = list2;
    }
    int sum = num1 + num2;
    int mul = num_power(10, number_digits(sum)) / 10;

    while (temp) {
        temp->val = sum / mul;
        sum %= mul;
        mul /= 10;
        temp = temp->next;
    }
    if (!sum) {
        temp->next = new ListNode(sum);
    }
    
    if (num1 < num2) {
        return list2;
    }
    return list1;
}

// 2.6
bool is_list_palindrom(ListNode* head) {
    std::vector<int> arr;
    
    ListNode* tmp = head;
    while (tmp) {
        arr.push_back(tmp->val);
        tmp = tmp->next;
    }
    
    int right_index = arr.size() - 1;
    for (int i = 0; i < arr.size()/2; ++i) {
        if (arr[i] != arr[right_index - i]) {
            return false;
        }
    }
    return true;
}

// 2.7
ListNode* get_intersection_node(ListNode *headA, ListNode *headB) {
    ListNode* tmp1 = headA;
    ListNode* tmp2 = headB;
    int count1 = 0;
    int count2 = 0;
    
    while (tmp1->next) {
        ++count1;
        tmp1 = tmp1->next;
    }
    
    while (tmp2->next) {
        ++count2;
        tmp2 = tmp2->next;
    }
    
    if (count1 < count2) {
        count1 = count2 - count1;
        tmp1 = headA;
        tmp2 = headB;
    }
    else {
        count1 = count1 - count2;
        tmp1 = headB;
        tmp2 = headA;
    }
    
    bool intersected = false;
    while (count1) {
        tmp2 = tmp2->next;
        --count1;
    }
    
    while (tmp2) {
        if (tmp2 == tmp1) {
            return tmp2;
        }
        tmp2 = tmp2->next;
        tmp1 = tmp1->next;
    }    
    return 0;
}

// 2.8
ListNode* detect_cycle(ListNode *head) {
    if (!head) {
        return head;
    }
    
    ListNode* slow = head;
    ListNode* fast = head;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) {
            break;
        }
    }
    if (!(fast && fast->next)) {
        return nullptr;
    }
    
    fast = head;
    while (fast != slow) {
        fast = fast->next;
        slow = slow->next;
    }
    return fast;
}