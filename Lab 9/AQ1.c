#include <stdio.h>
#include <stdlib.h>

typedef struct Block {
    int size;
    int is_free;
    int id;  // Process ID if allocated
    struct Block* next;
} Block;

Block* create_block(int size) {
    Block* new_block = (Block*)malloc(sizeof(Block));
    new_block->size = size;
    new_block->is_free = 1;
    new_block->id = -1;
    new_block->next = NULL;
    return new_block;
}

void insert_block(Block** head, int size) {
    Block* new_block = create_block(size);
    if (*head == NULL) {
        *head = new_block;
    } else {
        Block* temp = *head;
        while (temp->next) temp = temp->next;
        temp->next = new_block;
    }
}

void display_blocks(Block* head) {
    printf("Memory Blocks:\n");
    while (head) {
        printf("Size: %d | %s", head->size, head->is_free ? "Free\n" : "Allocated to P");
        if (!head->is_free) printf("%d\n", head->id);
        head = head->next;
    }
}

void worst_fit_allocate(Block* head, int process_id, int process_size) {
    Block* worst = NULL;
    Block* temp = head;

    while (temp) {
        if (temp->is_free && temp->size >= process_size) {
            if (worst == NULL || temp->size > worst->size)
                worst = temp;
        }
        temp = temp->next;
    }

    if (worst) {
        worst->is_free = 0;
        worst->id = process_id;
        printf("Process %d allocated %d KB\n", process_id, process_size);
    } else {
        printf("Process %d can't be allocated (Insufficient space)\n", process_id);
    }
}

int main() {
    Block* memory = NULL;

    // Sample memory blocks
    insert_block(&memory, 100);
    insert_block(&memory, 500);
    insert_block(&memory, 200);
    insert_block(&memory, 300);
    insert_block(&memory, 600);

    display_blocks(memory);

    // Allocations
    worst_fit_allocate(memory, 1, 212);
    worst_fit_allocate(memory, 2, 417);
    worst_fit_allocate(memory, 3, 112);
    worst_fit_allocate(memory, 4, 426);

    display_blocks(memory);

    return 0;
}
