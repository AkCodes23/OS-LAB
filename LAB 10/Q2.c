#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int framesCount, numPages, faults = 0;
    printf("Enter number of frames: ");
    scanf("%d", &framesCount);
    printf("Enter number of pages: ");
    scanf("%d", &numPages);

    int *pages = malloc(numPages * sizeof(int));
    if (!pages) exit(1);
    printf("Enter page reference string (space-separated): ");
    for (int i = 0; i < numPages; i++)
        scanf("%d", &pages[i]);

    int *frames = malloc(framesCount * sizeof(int));
    int *lastUsed = malloc(framesCount * sizeof(int));
    if (!frames || !lastUsed) exit(1);
    for (int i = 0; i < framesCount; i++) {
        frames[i] = -1;
        lastUsed[i] = -1;
    }

    
    for (int i = 0; i < numPages; i++) {
        int hit = 0;
        for (int j = 0; j < framesCount; j++) {
            if (frames[j] == pages[i]) {
                lastUsed[j] = i;  
                hit = 1;
                break;
            }
        }
        if (hit)
            continue;
        // Find an empty frame if available.
        int index = -1;
        for (int j = 0; j < framesCount; j++) {
            if (frames[j] == -1) {
                index = j;
                break;
            }
        }
        
        if (index == -1) {
            int lru = 0;
            for (int j = 1; j < framesCount; j++) {
                if (lastUsed[j] < lastUsed[lru])
                    lru = j;
            }
            index = lru;
        }
        frames[index] = pages[i];
        lastUsed[index] = i;
        faults++;
    }
    printf("\nLRU Page Faults: %d\n", faults);

    free(pages);
    free(frames);
    free(lastUsed);
    return 0;
}
