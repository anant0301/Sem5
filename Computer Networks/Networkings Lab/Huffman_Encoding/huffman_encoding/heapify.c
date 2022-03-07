#include "../headers.h"
void heapify(struct huffman_heap *tree, int len, int i) 
{ 
    int f_index = i;
    int left_ = 2 * i + 1; 
    int right_ = 2 * i + 2; 
  
    if (left_ < len && tree-> arr[left_]-> freq < tree-> arr[f_index]-> freq) 
    {
        f_index = left_; 
    }
    if (right_ < len && tree-> arr[right_]-> freq < tree-> arr[f_index]-> freq) 
    {
        f_index = right_; 
    }
    if (f_index != i) 
    { 
        struct huffman_node *temp = tree-> arr[i];
        tree-> arr[i] = tree-> arr[f_index];
        tree-> arr[f_index] = temp;
        heapify(tree, len, f_index); 
    } 
} 