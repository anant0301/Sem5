#ifndef header_q8
#define header_q8

struct determinant_param
{
    int **arr;
    int order;
    int determinant;
};
struct cofactor_param
{
    int **arr;
    int order;
    int missing_row;
    int missing_col;

};

#endif