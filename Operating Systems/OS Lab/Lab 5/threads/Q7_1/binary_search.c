#include "../headers.h"
#include "header_q7_1.h"
void * binary_search(void * param)
{
	int mid;
	struct q7_main * this = (struct q7_main*)param;
	int beg = this-> beg;
	int end = this-> end;
	int x = this-> x;
	int *arr = this-> arr;
	if(end >= beg)
	{
		mid = (end + beg) / 2;
		if(arr[mid] == x)
		{
			this-> index = mid;
		    if(this-> beg != this-> end)
			{
				pthread_t tid_low;
				pthread_t tid_up;
				struct q7_main * lower = (struct q7_main*)malloc(sizeof(struct q7_main));
				struct q7_main * upper = (struct q7_main*)malloc(sizeof(struct q7_main));
				if(this-> side != 'l')
                {
                    upper = (struct q7_main*)malloc(sizeof(struct q7_main));
                    upper-> arr = arr;
                    upper-> x = x;
                    upper-> beg = mid + 1;
                    upper-> end = end;
                    upper-> side = 'u';
                    pthread_create(&tid_up, NULL, binary_search, upper);
                }
                if(this-> side != 'u')
                {
                    lower = (struct q7_main*)malloc(sizeof(struct q7_main));
                    lower-> arr = arr;
                    lower-> x = x;
                    lower-> beg = beg;
                    lower-> end = mid - 1;
                    lower-> side = 'l';
                    pthread_create(&tid_low, NULL, binary_search, lower);
                }
                if(lower)
                {
                    pthread_join(tid_low, NULL);
					if(arr[lower-> beg] == x)
						this-> beg = lower-> beg;
					else if(arr[lower-> index] == x)
						this-> beg = lower-> end;
                }
                if(upper)
                {
                    pthread_join(tid_up, NULL);
                    if(arr[upper-> end] == x)
                        this-> end = upper-> end;
                    else if(arr[upper-> index] == x)
                        this-> end = upper-> index;
                }
            }
			return NULL;
		}
		else if(arr[mid] > x)
		{
            this-> end = mid - 1;
			binary_search(this);
		}
		else if(arr[mid] < x)
		{
            this-> beg = mid + 1;
			binary_search(this);
		}
	}
	else
	{
		return NULL;
	}
}