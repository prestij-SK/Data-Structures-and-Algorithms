#ifndef ALGOS_H
#define ALGOS_H

#include <string>

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

// 1.1
bool has_unique_chars(const std::string&);
// 1.2
bool check_permutation_of_strings(const std::string&, const std::string&);
// 1.3
std::string insert_in_spaces(const std::string&, const std::string&);
// 1.4
bool palindrom_permutation(const std::string&);
// 1.5
bool can_be_same_one_oper(const std::string&, const std::string&); 
// 1.6
std::string compressor(const std::string&);
// 1.7
int** rotated_matrix(int**, int);
// 1.8
void set_to_zero_rows_and_columns(int** , int, int);
// 1.9
bool is_string_rotation(const std::string&, const std::string&);



// helper functions
void remove_node(ListNode*);
int make_list_num_rev(ListNode*);
int number_digits(int);
int num_power(int, int);
// 2.1
ListNode* delete_duplicates(ListNode*);
// 2.2
ListNode* kth_node(ListNode*, int);
// 2.3
ListNode* delete_middle_node(ListNode*);
// 2.4
ListNode* partition_list(ListNode*, int);
// 2.5
ListNode* sum_lists_reverse(ListNode*, ListNode*);
// 2.6
bool is_list_palindrom(ListNode*);
// 2.7
ListNode* get_intersection_node(ListNode*, ListNode*);
// 2.9
ListNode* detect_cycle(ListNode*);

#endif