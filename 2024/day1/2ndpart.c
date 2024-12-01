#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define HASH_SIZE 2000

typedef struct HashNode {
    int key;
    int value;
    int flag_n1;
    int value_n1;
    struct HashNode *next;
} HashNode;


void to_hash(HashNode* hash_map[],int key, int flag_n1) {
    int index = key % HASH_SIZE; 

    HashNode* node = hash_map[index];
    int does_it_exist = 0;

    while (node != NULL) 
    {
        if (node->key == key) {
            if (flag_n1) {
                node->flag_n1 = 1;
                node->value_n1 += 1;
            }
            else {
                node->value += 1;
            }
            does_it_exist = 1;
            break;
        }
        node = node->next;
    }

    if (!does_it_exist) {
        HashNode* new_node = (HashNode*)malloc(sizeof(HashNode));
            new_node->key = key;
            new_node->flag_n1 = flag_n1;
            if (flag_n1)
                new_node->value_n1 = 1;
            new_node->value = 0;
            if(!flag_n1)
                new_node->value = 1;
            new_node->next = hash_map[index];
            hash_map[index] = new_node;


    }
}

void free_hash_map(HashNode* hash_map[]) {
    for (int i = 0; i < HASH_SIZE; i++) {
        HashNode* node = hash_map[i];
        while (node != NULL) {
            HashNode* temp = node;
            node = node->next;
            free(temp);
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

int main() {
    FILE* file = fopen("input.txt", "r");

    char line[256];
    int n1, n2;
    size_t size_lists = 1000;
    int curr_index = 0;
    HashNode* hash_map[HASH_SIZE] = { NULL };

    while (fgets(line, sizeof(line), file))
    {

        parsing_numbers(line, &n1, &n2);


        to_hash(hash_map, n1, 1);


        to_hash(hash_map, n2, 0);  
    }

    fclose(file);

    int sum = 0;
    int i = 0;
    while(i < HASH_SIZE) 
    {
        HashNode* node = hash_map[i];
        while (node != NULL)
        {
            if (node->flag_n1 == 1) {
                sum += (node->value * node->key) * (node->value_n1);  
            }
            node = node->next;
        }
        i++;
    }

    printf("%d\n", sum);

    free_hash_map(hash_map);

    return 0;
}
