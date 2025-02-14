#include <stdio.h>
#include <stdlib.h>

typedef struct Block {
    int size;
    int allocated;
    struct Block* next;
} Block;

Block* create_block(int size) {
    Block* block = (Block*)malloc(sizeof(Block));
    block->size = size;
    block->allocated = 0;
    block->next = NULL;
    return block;
}

Block* first_fit(Block* head, int size) {
    Block* current = head;
    while (current != NULL) {
        if (!current->allocated && current->size >= size) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

Block* best_fit(Block* head, int size) {
    Block* best_block = NULL;
    Block* current = head;
    while (current != NULL) {
        if (!current->allocated && current->size >= size) {
            if (best_block == NULL || current->size < best_block->size) {
                best_block = current;
            }
        }
        current = current->next;
    }
    return best_block;
}

void allocate(Block* block, int size) {
    block->allocated = 1;
    printf("Allocated block of size %d\n", size);
}

void deallocate(Block* block) {
    block->allocated = 0;
    printf("Deallocated block of size %d\n", block->size);
}

void print_memory(Block* head) {
    Block* current = head;
    while (current != NULL) {
        printf("Block size: %d, allocated: %d\n", current->size, current->allocated);
        current = current->next;
    }
}

int main() {
    // Create memory blocks
    Block* head = create_block(100);
    head->next = create_block(50);
    head->next->next = create_block(30);
    head->next->next->next = create_block(120);

    printf("Initial memory blocks:\n");
    print_memory(head);

    // First fit allocation
    Block* block = first_fit(head, 40);
    if (block != NULL) {
        allocate(block, 40);
    } else {
        printf("No suitable block found for allocation (first fit)\n");
    }

    // Best fit allocation
    block = best_fit(head, 60);
    if (block != NULL) {
        allocate(block, 60);
    } else {
        printf("No suitable block found for allocation (best fit)\n");
    }

    printf("\nMemory blocks after allocations:\n");
    print_memory(head);

    // Deallocate a block
    deallocate(head->next);

    printf("\nMemory blocks after deallocation:\n");
    print_memory(head);

    // Free allocated memory blocks
    while (head != NULL) {
        Block* temp = head;
        head = head->next;
        free(temp);
    }

    return 0;
}

//gcc -o Q1 Q1.c
//./Q1
