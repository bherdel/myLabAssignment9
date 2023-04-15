//Brendan Herdel
//Lab Assignment 9

#include <stdio.h>
#include <stdlib.h>

// RecordType
struct RecordType
{
    int id;
    char name;
    int order;
    struct RecordType *next;
};

// Fill out this structure
struct HashType
{
    struct RecordType *record;
};

// Compute the hash function
int hash(int x, int tableSize)
{
   return x % tableSize;
}

// parses input file to an integer array
int parseData(char *inputFileName, struct RecordType **ppData)
{
    FILE *inFile = fopen(inputFileName, "r");
    int dataSz = 0;
    int i, n;
    char c;
    struct RecordType *pRecord;
    *ppData = NULL;

    if (inFile)
    {
        fscanf(inFile, "%d\n", &dataSz);
        *ppData = (struct RecordType *)malloc(sizeof(struct RecordType) * dataSz);
        // Implement parse data block
        if (*ppData == NULL)
        {
            printf("Cannot allocate memory\n");
            exit(-1);
        }
        for (i = 0; i < dataSz; ++i)
        {
            pRecord = *ppData + i;
            fscanf(inFile, "%d ", &n);
            pRecord->id = n;
            fscanf(inFile, "%c ", &c);
            pRecord->name = c;
            fscanf(inFile, "%d ", &n);
            pRecord->order = n;
            pRecord->next = NULL;
        }

        fclose(inFile);
    }

    return dataSz;
}

// prints the records
void printRecords(struct RecordType pData[], int dataSz)
{
    int i;
    printf("\nRecords:\n");
    for (i = 0; i < dataSz; ++i)
    {
        printf("\t%d %c %d\n", pData[i].id, pData[i].name, pData[i].order);
    }
    printf("\n\n");
}

// insert record into the hash table
void insertRecord(struct HashType *hashTable, struct RecordType *record, int tableSize)
{
    int index = hash(record->id, tableSize);

    if (hashTable[index].record == NULL)
    {
        hashTable[index].record = record;
        record->next = NULL;
    }
    else
    {
        struct RecordType *currentRecord = hashTable[index].record;
        while (currentRecord->next != NULL)
        {
           currentRecord = currentRecord->next;
        }
        currentRecord->next = record;
        record->next = NULL;
    }
}

// display records in the hash structure
// skip the indices which are free
// the output will be in the format:
// index x -> id, name, order -> id, name, order ....
void displayRecordsInHash(struct HashType *hashTable, int tableSize)
{
	struct RecordType *currentRecord;
    int i;

    for (i = 0; i < tableSize; i++)
    {
        printf("Index %d -> ", i);

        if (hashTable[i].record == NULL)
        {
            printf("NULL\n");
        }
        else
        {
            currentRecord = hashTable[i].record;

            while (currentRecord != NULL)
            {
                printf("%d, %c, %d -> ", currentRecord->id, currentRecord->name, currentRecord->order);
                currentRecord = currentRecord->next;
            }

            printf("NULL\n");
        }
    }
}

int main(void)
{
    struct RecordType *pRecords;
    int recordSz = 0;

    recordSz = parseData("input.txt", &pRecords);
    printRecords(pRecords, recordSz);

    int hashTableSize = 10;
    struct HashType *hashTable = (struct HashType *)calloc(hashTableSize, sizeof(struct HashType));

    for (int i = 0; i < recordSz; i++)
    {
        insertRecord(hashTable, &pRecords[i], hashTableSize);
    }

    displayRecordsInHash(hashTable, hashTableSize);

    free(pRecords);
    free(hashTable);

    return 0;
}
