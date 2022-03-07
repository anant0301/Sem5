#include "../headers.h" 
#include "header_q9.h" 
void * longest_common_subsequence(void * param)
{
    struct q9_main* this = param; 
    if(this-> n_str_1 == strlen(this-> str_1) || this-> n_str_2 == strlen(this-> str_2))
    {
        return NULL;
    }
    if(this-> str_1[this-> n_str_1] == this-> str_2[this-> n_str_2])
    {
        this-> lcs[this-> len_lcs] = this-> str_1[this-> n_str_1];
        this-> n_str_1 = this-> n_str_1 + 1; 
        this-> n_str_2 = this-> n_str_2 + 1; 
        this-> len_lcs = this-> len_lcs + 1;
        longest_common_subsequence(this);
        return NULL; 
    }
    else 
    {
        struct q9_main* ret_1 = (struct q9_main*)malloc(sizeof(struct q9_main)); 
        struct q9_main* ret_2 = (struct q9_main*)malloc(sizeof(struct q9_main)); 
        ret_1-> str_1 = ret_2-> str_1 = this-> str_1; 
        ret_1-> str_2 = ret_2-> str_2 = this-> str_2; 
        ret_1-> str_2 = ret_2-> str_2 = this-> str_2; 
        ret_1-> n_str_2 = this-> n_str_2;  
        ret_2-> n_str_1 = this-> n_str_1;  
        ret_1-> n_str_1 = this-> n_str_1 + 1; 
        ret_2-> n_str_2 = this-> n_str_2 + 1;  
        ret_2-> len_lcs = ret_1-> len_lcs  = 0;  
        
        pthread_t tid_1; 
        pthread_t tid_2; 
        pthread_attr_t attr; 
        pthread_attr_init(&attr); 
        pthread_create(&tid_1, &attr, longest_common_subsequence, ret_1);   
        pthread_create(&tid_2, &attr, longest_common_subsequence, ret_2);
        pthread_join(tid_1, NULL); 
        pthread_join(tid_2, NULL); 
        if (ret_1-> len_lcs > ret_2-> len_lcs)
        {
            this-> len_lcs += ret_1-> len_lcs;
            strcat(this-> lcs, ret_1-> lcs); 
        }
        else 
        {
            this-> len_lcs += ret_2-> len_lcs;
            strcat(this-> lcs, ret_2-> lcs);
        }
        return NULL;
    }
}