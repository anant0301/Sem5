int reverse(char in_string[], int str_len, char out_string[])
{
    for(int i = 0; i < str_len; ++i)
    {
        out_string[i] = in_string[str_len - i - 1];
    }   
    return 1;
}