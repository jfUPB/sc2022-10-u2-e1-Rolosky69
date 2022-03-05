#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifdef DOLOG
#define LOG(...) fprintf(log, __VA_ARGS__);
#else
#define LOG(...)
#endif

struct array
{
    int *pdata;
    int size;
};

void initArray(struct array *);
void getArray(struct array *);
void arrayCommon(struct array *, struct array *, struct array *);
void printArray(struct array *);
void freeMemory(struct array *, struct array *, struct array *);

void initArray(struct array *arr){
    arr->pdata = NULL;
    arr->size = -1;
}

void printArray(struct array *parr)
{
    for (int i = 0; i < parr->size; i++)
    {
        printf("%d ", parr->pdata[i]);
    }
    printf("\n");
}
//funcion 1
void getArray(struct array *parr)
{
    char tamano[12];
    char entradas_al_tamano[12];

    if (fgets(tamano, 6, stdin) != NULL)
    {
        tamano[strlen(tamano) -1] = 0;
        int transformar = sscanf(tamano,"%d", &parr->size);
        if(transformar == 1)
        {
     
            parr->pdata = malloc(parr->size*sizeof(int));

            for(int i = 0; i < parr->size; i++)
            {
                if (fgets(entradas_al_tamano, 6, stdin) != NULL)
                {
                    int transformar2 = sscanf(entradas_al_tamano, " %d ", parr->pdata + i);
                }
            }
        }

    }
}

void arrayCommon(struct array *arrIn1, struct array *arrIn2, struct array *arrOut)
{
    int size=0, i, j, h, tempVal1, tempVal2;
    struct array *arrTemp = malloc(sizeof(struct array) * 1);

    arrTemp->size=69;
    arrTemp->pdata = malloc(arrTemp->size * sizeof(int));

    arrOut->size=0;

    for(i = 0; i < arrTemp->size; i++)
    {
        *(arrTemp->pdata+i) = -1;
    }

    for(i = 0; i < arrIn1->size; i++)
    {
        for(j = 0; j < arrIn2->size; j++)
        {
            tempVal1 = *(arrIn1->pdata+i);
            tempVal2 = *(arrIn2->pdata+j);

            if( tempVal1 == tempVal2)
            {
                int verificador= 0;

                for(h = 0; h < arrTemp->size; h++)
                {
                    int valTemp = *(arrTemp->pdata+h);
                    if(tempVal1 == valTemp)
                    {
                        h = arrTemp->size;
                        verificador =-1;
                    }
                }

                if(verificador==0)
                {
                    *(arrTemp->pdata+arrOut->size)= tempVal1;
                    arrOut->size++;
                }
            }
        }
    }

    arrOut->pdata = malloc(arrOut->size * sizeof(int));

    for(i = 0; i<arrOut->size; i++)
    {
        *(arrOut->pdata+i) = *(arrTemp->pdata+i);
    } 
}

void freeMemory(struct array *arr1, struct array *arr2, struct array *arr3)
{
    free(arr1->pdata);
    free(arr1);

    free(arr2->pdata);
    free(arr2);

    free(arr3->pdata);
    free(arr3);
}

int main(void)
{

#ifdef DOLOG
    FILE *log = fopen("log", "w");
    if (log == NULL)
    {
        perror("log file creation fails: ");
        return EXIT_FAILURE;
    }
#endif

    char commandBuf[64];

    LOG("creating an object for each array\n");

    struct array *arr1 = malloc(sizeof(struct array) * 1);
    initArray(arr1);
    struct array *arr2 = malloc(sizeof(struct array) * 1);
    initArray(arr2);    
    struct array *arr3 = malloc(sizeof(struct array) * 1);
    initArray(arr3);


    LOG("Init command loop\n");

    while (fgets(commandBuf, sizeof(commandBuf), stdin) != NULL)
    {
        commandBuf[strlen(commandBuf) - 1] = 0;

        if (strncmp(commandBuf, "arr1", strlen("arr1")) == 0)
        {
            LOG("getting array1\n");
            getArray(arr1);
        }
        else if (strncmp(commandBuf, "arr2", strlen("arr2")) == 0)
        {
            LOG("getting array2\n");
            getArray(arr2);
        }
        else if (strncmp(commandBuf, "printArr1", strlen("printArr1")) == 0)
        {
            LOG("printing arr1\n");
            printArray(arr1);
        }
        else if (strncmp(commandBuf, "printArr2", strlen("printArr2")) == 0)
        {
            LOG("printing arr2\n");
            printArray(arr2);
        }
        else if (strncmp(commandBuf, "compare", strlen("compare")) == 0)
        {
            LOG("Compare arrays\n");
            arrayCommon(arr1, arr2, arr3);
        }
        else if (strncmp(commandBuf, "printResult", strlen("printResult")) == 0)
        {
            LOG("printing compare result\n");
            printf("%d\n", arr3->size);
            if (arr3->size != 0)
            {
                printArray(arr3);
            }
        }
        else if (strncmp(commandBuf, "exit", strlen("exit")) == 0)
        {
            LOG("running exit command\n");
            freeMemory(arr1,arr2,arr3);
            break;
        }
    }

    return EXIT_SUCCESS;
}
