#include <stdio.h>

#define MAX 100

void fifoPageReplacement(int pages[], int n, int frames_count) {
    int frames[frames_count];
    int front = 0, count = 0, page_faults = 0;

    for (int i = 0; i < frames_count; i++) frames[i] = -1;

    for (int i = 0; i < n; i++) {
        int found = 0;
        
        // Check if page is already in frames
        for (int j = 0; j < frames_count; j++) {
            if (frames[j] == pages[i]) {
                found = 1;
                break;
            }
        }

        if (!found) {
            // Replace the oldest page
            frames[front] = pages[i];
            front = (front + 1) % frames_count;
            page_faults++;
        }

        // Print current frames
        printf("Frames: ");
        for (int j = 0; j < frames_count; j++) {
            if (frames[j] != -1)
                printf("%d ", frames[j]);
            else
                printf("- ");
        }
        printf("\n");
    }

    printf("Total Page Faults = %d\n", page_faults);
}

int main() {
    int pages[] = {1, 3, 0, 3, 5, 6};
    int n = sizeof(pages) / sizeof(pages[0]);
    int frames = 3;

    fifoPageReplacement(pages, n, frames);
    return 0;
}
