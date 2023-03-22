#include "AdptArray.h"
#include "book.h"
#include "Person.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>     


//Part of the code was taken from: Ariel University, C course test, 2023 Semester A Moed A, Q4


typedef struct AdptArray_
{
    int ArrSize;
    PElement* pElemArr;
	DEL_FUNC delFunc;
	COPY_FUNC copyFunc;
    PRINT_FUNC printFunc;
} AdptArray;

// creates a new array by allocate memory 
PAdptArray CreateAdptArray(COPY_FUNC copyFun, DEL_FUNC delFun, PRINT_FUNC printFun)
{
	PAdptArray pArr = (PAdptArray)malloc(sizeof(AdptArray));
	if (pArr == NULL)
		return NULL;
	pArr->ArrSize = 0;
	pArr->pElemArr = (PElement*)calloc(0, sizeof(PElement));
	pArr->delFunc = delFun;
	pArr->copyFunc = copyFun;
    pArr->printFunc = printFun;
	return pArr;
}


//sets a new element at a given index and return if succeeded or failed
Result SetAdptArrayAt(PAdptArray pArr, int index, PElement pNewElem)
{
    if (pArr == NULL)
        return FAIL;
    if (pArr->ArrSize <= index) {
        // Resize the array
        int newSize = index + 1;
        PElement* newElemArr = realloc(pArr->pElemArr, newSize*sizeof(PElement));
        if (newElemArr == NULL)
            return FAIL;
        // Initialize the new elements to NULL
        int i;
        for (i = pArr->ArrSize; i < newSize; i++)
            newElemArr[i] = NULL;
        pArr->pElemArr = newElemArr;
        pArr->ArrSize = newSize;
    }
    // Delete the previous element if exists
    if (pArr->pElemArr[index] != NULL)
        pArr->delFunc(pArr->pElemArr[index]);
    // Copy the new element
    pArr->pElemArr[index] = pArr->copyFunc(pNewElem);
    
    return SUCCESS;
}

// The following method returns an element at a given index, otherwise returns null 
PElement GetAdptArrayAt(PAdptArray pArr, int index){
    if (pArr == NULL || index >= pArr->ArrSize || index < 0)
        return NULL;
    if (pArr->pElemArr[index] != NULL)    
        return pArr->copyFunc(pArr->pElemArr[index]);
    return NULL;
}

//prints the array's elements
void PrintDB(PAdptArray pArr){
    if (pArr == NULL) 
        return;
    int i;
    for (i = 0; i < pArr->ArrSize; i++){
       if (pArr->pElemArr[i] != NULL)   //print only if there is a value
            pArr->printFunc(pArr->pElemArr[i]);
    }
}

// returns the array's size, -1 if null 
int GetAdptArraySize(PAdptArray pArr){
    if (pArr == NULL)
        return -1;
    return pArr->ArrSize;
}


//The following function deletes the array of elements and free the memory
void DeleteAdptArray(PAdptArray pArr)
{
	if (pArr == NULL)   //if there is no concrete value (NULL), don't do anything
		return;
    int i;
	for(i = 0; i < pArr->ArrSize; ++i)
	{
		if (pArr->pElemArr[i] != NULL)
            pArr->delFunc(pArr->pElemArr[i]);
	}
	free(pArr->pElemArr);
	free(pArr);
}