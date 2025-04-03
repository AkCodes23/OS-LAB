#include <stdio.h>
#include <stdlib.h>


int inFrames(int *frames, int count, int page) {
    for (int i = 0; i < count; i++)
        if (frames[i] == page)
            return 1;
    return 0;
}

int main(void) {
    int framesCount, numPages, faults;
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
    if (!frames) exit(1);

    // ----- FIFO Algorithm -----
    for (int i = 0; i < framesCount; i++)
        frames[i] = -1;
    faults = 0;
    int pointer = 0;
    for (int i = 0; i < numPages; i++) {
        if (!inFrames(frames, framesCount, pages[i])) {
            frames[pointer] = pages[i];
            pointer = (pointer + 1) % framesCount;
            faults++;
        }
    }
    printf("\nFIFO Page Faults: %d\n", faults);

    
    for (int i = 0; i < framesCount; i++)
        frames[i] = -1;
    faults = 0;
    for (int i = 0; i < numPages; i++) {
        if (inFrames(frames, framesCount, pages[i]))
            continue;
        
        int placed = 0;
        for (int j = 0; j < framesCount; j++) {
            if (frames[j] == -1) {
                frames[j] = pages[i];
                faults++;
                placed = 1;
                break;
            }
        }
        if (placed)
            continue;
       
        int replaceIndex = -1, farthest = i;
        for (int j = 0; j < framesCount; j++) {
            int k;
            for (k = i + 1; k < numPages; k++) {
                if (frames[j] == pages[k]) {
                    if (k > farthest) {
                        farthest = k;
                        replaceIndex = j;
                    }
                    break;
                }
            }
            if (k == numPages) { 
                replaceIndex = j;
                break;
            }
        }
        if (replaceIndex == -1)
            replaceIndex = 0;
        frames[replaceIndex] = pages[i];
        faults++;
    }
    printf("Optimal Page Faults: %d\n", faults);

    free(pages);
    free(frames);
    return 0;
}
