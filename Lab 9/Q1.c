#include <stdio.h>
#include <stdlib.h>

typedef struct Block {
    int size;
    int allocated;
    struct Block *next;
} Block;

Block *createBlock(int size) {
    Block *block = (Block *)malloc(sizeof(Block));
    block->size = size;
    block->allocated = 0;
    block->next = NULL;
    return block;
}

void insertBlock(Block **head, Block *block) {
    if (*head == NULL) {
        *head = block;
    } else {
        Block *temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = block;
    }
}

void printBlocks(Block *head) {
    Block *temp = head;
    while (temp != NULL) {
        printf("Size: %d, Allocated: %d -> ", temp->size, temp->allocated);
        temp = temp->next;
    }
    printf("NULL\n");
}

int firstFit(Block *head, int processSize) {
    Block *temp = head;
    int blockIndex = 0;
    while (temp != NULL) {
        if (temp->allocated == 0 && temp->size >= processSize) {
            temp->allocated = 1;
            return blockIndex;
        }
        temp = temp->next;
        blockIndex++;
    }
    return -1;
}

int bestFit(Block *head, int processSize) {
    Block *temp = head;
    int bestIndex = -1;
    int bestSize = -1;
    int blockIndex = 0;

    while (temp != NULL) {
        if (temp->allocated == 0 && temp->size >= processSize) {
            if (bestSize == -1 || temp->size < bestSize) {
                bestSize = temp->size;
                bestIndex = blockIndex;
            }
        }
        temp = temp->next;
        blockIndex++;
    }

    if (bestIndex != -1) {
        temp = head;
        for (int i = 0; i < bestIndex; i++) {
            temp = temp->next;
        }
        temp->allocated = 1;
    }

    return bestIndex;
}

int main() {
    Block *head = NULL;
    int numBlocks, numProcesses;

    printf("Enter number of memory blocks: ");
    scanf("%d", &numBlocks);

    printf("Enter sizes of memory blocks:\n");
    for (int i = 0; i < numBlocks; i++) {
        int size;
        scanf("%d", &size);
        insertBlock(&head, createBlock(size));
    }

    printf("Enter number of processes: ");
    scanf("%d", &numProcesses);

    int processes[numProcesses];
    printf("Enter sizes of processes:\n");
    for (int i = 0; i < numProcesses; i++) {
        scanf("%d", &processes[i]);
    }

    printf("\nFirst Fit Allocation:\n");
    for (int i = 0; i < numProcesses; i++) {
        int blockIndex = firstFit(head, processes[i]);
        if (blockIndex != -1) {
            printf("Process %d (Size: %d) allocated to block %d\n", i, processes[i], blockIndex);
        } else {
            printf("Process %d (Size: %d) not allocated\n", i, processes[i]);
        }
    }
    printBlocks(head);

    Block *bestHead = NULL;
    Block *temp = head;
    while(temp!=NULL){
        insertBlock(&bestHead, createBlock(temp->size));
        temp=temp->next;
    }

    printf("\nBest Fit Allocation:\n");
    for (int i = 0; i < numProcesses; i++) {
        int blockIndex = bestFit(bestHead, processes[i]);
        if (blockIndex != -1) {
            printf("Process %d (Size: %d) allocated to block %d\n", i, processes[i], blockIndex);
        } else {
            printf("Process %d (Size: %d) not allocated\n", i, processes[i]);
        }
    }
    printBlocks(bestHead);

    return 0;
}
