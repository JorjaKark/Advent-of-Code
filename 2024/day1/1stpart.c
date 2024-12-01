#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

int calculate(int *list1, int *list2, size_t n) {
    int total = 0;
    for (size_t i = 0; i < n; i++) {
        total += abs(list1[i] - list2[i]);
    }
    return total;
}


void bubble_sort(int *list, size_t size) 
{
    for (size_t i = 0; i < size - 1; ++i) {
        for (size_t j = 0; j < size - i - 1; ++j) {
            if (list[j] > list[j + 1]) {

                int temp = list[j];
                list[j] = list[j + 1];
                list[j + 1] = temp;
            }
        }
    }
}

void parsing_numbers(char *line, int *n1, int *n2)
{
    int i = 0;
    char n1_str[6];
    char n2_str[6];
    int j = 0;

    while (isdigit(line[i]))
    {
        n1_str[j++] = line[i++];
    }
    n1_str[j] = '\0';
    while (line[i] && !isdigit(line[i]) )
        i++;
    j = 0;
    while(isdigit(line[i]))
    {
        n2_str[j++] = line[i++];
    }
    n2_str[j] = '\0';
    *n1 = atoi(n1_str);
    *n2 = atoi(n2_str);

}

int main()
{
    FILE *file = fopen("input.txt", "r");
    char line[256];
    size_t i = 0;
    size_t j = 0;
    size_t size_lists = 1000;
    int n1;
    int n2;

    int *list1 = malloc(size_lists * sizeof(int));
    int *list2 = malloc(size_lists * sizeof(int));

    while (fgets(line, sizeof(line), file))
    {
        parsing_numbers(line, &n1, &n2);
        list1[i++] = n1;
        list2[j++] = n2;
    }
    bubble_sort(list1, i);
    bubble_sort(list2, j);

    int res;

    res = calculate(list1, list2, i);

    printf("%d\n", res);
    fclose(file);
    free(list1);
    free(list2);
    return 0;


}