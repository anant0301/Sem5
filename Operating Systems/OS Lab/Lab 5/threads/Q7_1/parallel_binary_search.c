#include "../headers.h"
#include "header_q7_1.h"
void *parallel_binary_search(void * param)
{
    struct q7_main* this = (struct q7_main*) param;
    int mid;
	if(this-> beg < this-> end)
	{
		mid = (this-> end + this-> beg) / 2;
        printf("Middle \t\t%d %d %d\n", this-> beg, mid, this-> end);

    	if(this-> arr[mid] == this-> x)
		{
            this-> index = mid;
            pthread_t tid_u;
            pthread_t tid_l;
            struct q7_main * low = NULL;
            struct q7_main * up = NULL;
            if(this-> end != this-> beg)
            {
                // if(this-> side != 'l')
                // {
                    up = (struct q7_main*)malloc(sizeof(struct q7_main));
                    up-> arr = this-> arr;
                    up-> x = this-> x;
                    // up-> len = this-> len;
                    up-> beg = mid + 1;
                    up-> end = this-> end;
                    up-> side = 'u';
                    pthread_create(&tid_u, NULL, parallel_binary_search, up);
                // }
                // if(this-> side != 'u')
                // {
                    low = (struct q7_main*)malloc(sizeof(struct q7_main));
                    low-> arr = this-> arr;
                    low-> x = this-> x;
                    // low-> len = this-> len;
                    low-> beg = this-> beg;
                    low-> end = mid - 1;
                    low-> side = 'l';
                    pthread_create(&tid_l, NULL, parallel_binary_search, low);
                // }
                // if(low)
                // {
                    pthread_join(tid_l, NULL);
                    if(low-> index != -1 && low-> index < this-> index)
                    {
                        this-> beg = low-> beg;
                    }
                    else if(low-> index == -1)
                    {
                        this-> beg = low-> end;
                    }
                // }
                // if(up)
                // {
                    pthread_join(tid_u, NULL);
                    if(up-> index != -1 && up-> index > this-> index)
                    {
                        this-> end = up-> beg;
                    }
                    else if(up-> index == -1)
                    {
                        this-> end = this-> index;
                    }
                // }
            }
            return this;
		}
        else if(this-> arr[mid] > this-> x)
		{
            this-> end = mid - 1;
			parallel_binary_search(this);
		}
		else if(this-> arr[mid] < this-> x)
		{
            this-> beg = mid + 1;
			parallel_binary_search(this);
		}
	}
    else if(this-> end == this-> beg)
    {
        if(this-> arr[this-> beg] == this-> x)
        {
            this-> index = this-> beg;
            printf("Single \t\t%d %d %d\n", this-> beg, this-> index, this-> end);
            if (h_beg > this-> beg)
                h_beg = this-> beg;
            if (h_end < this-> end)
                h_end = this-> end;
        }
        else
        {
            this-> index = -1;
        }
        return this;
    }
	else
	{
        this-> index =  -1;
		return NULL;
	}
    
}