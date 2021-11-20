#include <stdio.h>
#include <string.h>


enum priority
{
    LOWEST,
    LOW,
    NORMAL,
    HIGH,
    HIGHEST
};

struct entry
{
    enum priority priority;
    char message[32];
};

struct pqueue
{
    struct entry entries[10];
    int counter;
};

int isEmpty(struct pqueue* pqueue)
{
    return pqueue->counter == 0 ? 1 : 0;
}

int isFull(struct pqueue* pqueue)
{
    return pqueue->counter == 10 ? 1 : 0;
}

void printQueueLength(struct pqueue* pqueue)
{
    int length = pqueue->counter;

    printf("\npriority queue now contains %i ", length);

    if (length==1)
        printf("entry");
    else
        printf("entries");
}

void enqueue(struct pqueue* pqueue, struct entry entry)
{
    if ( isFull(pqueue) )
    {
        printf("\npriority queue already full!");
    }
    else
    {
        // find position (pos) to insert entry
        int pos;
        for(pos=0; pqueue->entries[pos].priority>=entry.priority && pos<pqueue->counter; pos++);

        // right-shift entries higher than pos in queue
        for(int i=9; i>pos; i--)
        {
            pqueue->entries[i] = pqueue->entries[i-1];
        }

        // insert entry at pos
        pqueue->entries[pos] = entry;
        pqueue->counter++;

        printf("\ninserting at pos=%i",pos);

        // print length of priority queue
        printQueueLength(pqueue);
    }
}

void dequeue(struct pqueue* pqueue)
{
    if( isEmpty(pqueue) )
        printf("\npriority queue is empty!");
    else
    {
        printf("\nMessage: %s", pqueue->entries[0].message);

        // left-shift entries
        for(int i=1; i<10; i++)
        {
            pqueue->entries[i-1] = pqueue->entries[i];
        }
        pqueue->counter--;

        // print length of priority queue
        printQueueLength(pqueue);
    }
}

char priority2char(enum priority priority)
{
    char out;

    switch(priority)
    {
        case HIGHEST : out='H' ; break;
        case HIGH    : out='h' ; break;
        case NORMAL  : out='n' ; break;
        case LOW     : out='l' ; break;
        case LOWEST  : out='L' ; break;
        default      : out='?' ; break;
    }

    return out;
}

enum priority char2priority(char priority)
{
    enum priority out;

    switch(priority)
    {
        case 'H' : out=HIGHEST   ; break;
        case 'h' : out=HIGH      ; break;
        case 'n' : out=NORMAL    ; break;
        case 'l' : out=LOW       ; break;
        case 'L' : out=LOWEST    ; break;
    }

    return out;
}

void printQueue(struct pqueue* pqueue)
{
    if( isEmpty(pqueue) )
    {
        printf("\nempty queue");
    }
    else
    {
        for (int i=0; i<pqueue->counter; i++)
        {
            printf("\n%c: %s", priority2char(pqueue->entries[i].priority), pqueue->entries[i].message);
        }
    }
}

char getMenu()
{
    char input='?';

    printf("\nChoose action: print queue (p), enqueue entry (e), dequeue entry (d) or exit (x): ");
    scanf(" %c",&input);

    while((input!='p') && (input!='e') && (input!='d') && (input!='d') && (input != 'x'))
    {
        printf("\nInput invalid! Try again: ");
        scanf(" %c",&input);
    }

    return input;
}

struct entry getNewEntry()
{
    char prio='?', message[32];
    struct entry newEntry;

    printf("\nChoose prio: lowest (L), low (l), normal (n), high (h), highest (H): ");
    scanf(" %c",&prio);

    while(prio != 'L' && prio != 'l' && prio != 'n' && prio != 'h' && prio != 'H')
    {
        printf("\nInput invalid! Try again: ");
        scanf(" %c",&prio);
    }

    printf("\nChoose message: ");
    scanf("%32s",&message[0]);

    newEntry.priority = char2priority(prio);
    strcpy(newEntry.message, message);

    return newEntry;
}

int main()
{
    // initialize priority queue
    struct pqueue myQueue;
    myQueue.counter = 0;

    /*
    struct entry myEntry;
    myEntry.priority = HIGH;
    strcpy(myEntry.message,"test");
    enqueue(&myQueue, myEntry);
    */

    // provide priority queue as an app (menu) to user
    char input='?'; // init user input with opaque character
    while(input != 'x')
    {
        input = getMenu();

        switch(input)
        {
            case 'p':
                printQueue(&myQueue);
            break;

            case 'e':
                enqueue(&myQueue, getNewEntry());
            break;

            case 'd':
                dequeue(&myQueue);
            break;

            case 'x':
                // do nothing here, as while loop will terminate this application in this case
            break;
        }
    }

    return 0;
}
