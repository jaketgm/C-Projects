void merge(char* arrLeft, char* arrRight, char* arr, int sizeArrLeft, int sizeArrRight, int size);

/************************************************************************************
 * Method: mergeSort: Implementation of merge sorting algorithm for an array of
 * characters (ID's).
 *
 * Input: char* arr, int size.
 *
 * Output: Sorted List.
 *
************************************************************************************/
void mergeSort(char* arr, int size)
{
    if (size <= 1) return; // base case

    int middle = size / 2;
    char leftArr[middle];
    char rightArr[size - middle];

    int i = 0; // left
    int j = 0; // right

    for (; i < size; i++)
    {
        if (i < middle)
        {
            leftArr[i] = arr[i];
        }
        else
        {
            rightArr[j] = arr[i];
            j++;
        }
    }
    mergeSort(leftArr, middle);
    mergeSort(rightArr, size - middle);
    merge(leftArr, rightArr, arr, middle, size - middle, size);
}

/************************************************************************************
 * Method: merge: Implementation of merge for the array of characters (ID's).
 *
 * Input: char* arrLeft, char* arrRight, char* arr, int sizeArrLeft, int sizeArrRight, int size.
 *
 * Output: Merged List.
 *
************************************************************************************/
void merge(char* arrLeft, char* arrRight, char* arr, int sizeArrLeft, int sizeArrRight, int size)
{
    int i = 0, l = 0, r = 0;

    //check conditions for merging
    while (l < sizeArrLeft && r < sizeArrRight)
    {
        if (strcmp(arrLeft + l, arrRight + r) <= 0)
        {
            strcpy(arr + i, arrLeft + l);
            i++;
            l++;
        }
        else
        {
            strcpy(arr + i, arrRight + r);
            i++;
            r++;
        }
    }
    while (l < sizeArrLeft)
    {
        strcpy(arr + i, arrLeft + l);
        i++;
        l++;
    }
    while (r < sizeArrRight)
    {
        strcpy(arr + i, arrRight + r);
        i++;
        r++;
    }
}