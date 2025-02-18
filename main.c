#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct HashNode {
    int key;
    int value;
    struct HashNode* next;
};

bool containsNearbyDuplicate(int* nums, int numsSize, int k) {
    struct HashNode** hashMap = (struct HashNode**)calloc(numsSize, sizeof(struct HashNode*));

    for (int i = 0; i < numsSize; ++i) {
        int currentNum = nums[i];
        int hashIndex = abs(currentNum) % numsSize;

        struct HashNode* node = hashMap[hashIndex];
        while (node) {
            if (node->key == currentNum) {
                if (i - node->value <= k) {
                    // Liberar memória antes de retornar
                    for (int j = 0; j < numsSize; ++j) {
                        struct HashNode* temp = hashMap[j];
                        while (temp) {
                            struct HashNode* toFree = temp;
                            temp = temp->next;
                            free(toFree);
                        }
                    }
                    free(hashMap);
                    return true;
                } else {
                    node->value = i;
                    break;
                }
            }
            node = node->next;
        }

        if (!node) {
            node = (struct HashNode*)malloc(sizeof(struct HashNode));
            node->key = currentNum;
            node->value = i;
            node->next = hashMap[hashIndex];
            hashMap[hashIndex] = node;
        }
    }

    // Liberar memória antes de retornar falso
    for (int j = 0; j < numsSize; ++j) {
        struct HashNode* temp = hashMap[j];
        while (temp) {
            struct HashNode* toFree = temp;
            temp = temp->next;
            free(toFree);
        }
    }
    free(hashMap);
    return false;
}

int main() {
    int nums[] = {1, 2, 3, 1}; // Exemplo de entrada
    int numsSize = sizeof(nums) / sizeof(nums[0]);
    int k = 3; // Distância máxima

    if (containsNearbyDuplicate(nums, numsSize, k)) {
        printf("Ha um numero duplicado dentro da distancia %d.\n", k);
    } else {
        printf("Nao há numeros duplicados dentro da distancia %d.\n", k);
    }

    return 0;
}
