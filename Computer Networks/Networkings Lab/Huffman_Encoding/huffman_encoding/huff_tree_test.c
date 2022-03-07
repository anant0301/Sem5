#include "../headers.h"

int main(int argc, char *argv[])
{
    struct huffman_heap tree;
    char writeFile[] = "encoded_file.txt";
    char buf[BUFFER_SIZE] = "\0";
    tree.length = 0;
    huffman_encoding_tree(argv[1], &tree);
    make_heap(&tree);
    FILE *write_fp = fopen(writeFile, "w");
    fprintf(write_fp, "%d\n", tree.length);
    create_tree(&tree);
    tree.arr[0]-> code[0] = 0; 
    traversal(tree.arr[0], tree.arr[0]-> code, write_fp);
    return 0;
}