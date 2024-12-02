#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

void parsing_numbers(char *line, int *nbrs)
{
    int i = 0;
    char n_str[6];
    int j = 0;
    int n;
    int k = 0;
    while (line[i])
    {
        while (isdigit(line[i]))
        {
            n_str[j++] = line[i++];
        }
        n_str[j] = '\0';
        n = atoi(n_str);
       //printf("nbrs[%d] = %d\n", k, n);
        nbrs[k++] = n;
        while (line[i] && !isdigit(line[i]))
            i++;
        j = 0;
    }

}

int is_it_valid(int *nbrs)
{
    int i;
    int increasing = 0;
    int diff;

    i = 0;
    if(nbrs[i] <= nbrs[i + 1])
    {
        increasing = 1;
    }
    while(nbrs[i] != -1 && nbrs[i + 1] != -1)
    {
        diff = nbrs[i + 1] - nbrs[i];
        if (increasing && (diff <= 0 || diff > 3))
        {
            return 0;
        }
        else if (!increasing && (diff >= 0 || diff < -3))
        {
            return 0;
        }
        i++;
    }
    return 1;
}


int try_removing_num(int *original, int remove_index)
{
    int temp[10];
    int j = 0;
    
    for (int i = 0; original[i] != -1; i++)
    {
        if (i != remove_index)
            temp[j++] = original[i];
    }
    temp[j] = -1;
    
    return is_it_valid(temp);
}



int main()
{
    FILE *file = fopen("input.txt", "r");
    char line[256];
    int *nbrs = malloc(10 * sizeof(int));

    size_t i = 0;
    size_t j = 0;
    int sum = 0;

    while (fgets(line, sizeof(line), file))
    {
        memset(nbrs, -1, 10 * sizeof(int));
        parsing_numbers(line, nbrs);
        if (!is_it_valid(nbrs))
        {
            int can_be_made_safe = 0;
            for (int i = 0; nbrs[i] != -1; i++)
            {
                if (try_removing_num(nbrs, i))
                {
                    can_be_made_safe = 1;
                    break;
                }
            }
            
            if (can_be_made_safe)
                sum++;
        }
        else
            sum++;
    }


    printf("%d\n", sum);
    fclose(file);
    free(nbrs);
    return 0;


}