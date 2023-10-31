void heapify(int *array, int size, int i);

/************************************************************************************
 * Method: heapSort: 
 * 
 * - The heapSort function takes two parameters:
 *   - int *array: A pointer to an array of integers that you want to sort.
 *   - int size: The number of elements in the array.
 * - The first loop is used to build a max-heap from the elements in the array. 
 * It starts by initializing i to the index of the last non-leaf node in the 
 * binary heap. The last non-leaf node is at index size / 2 - 1.
 * - Inside the loop, the heapify function is called to maintain the max-heap 
 * property. This function ensures that the element at index i and its children 
 * satisfy the max-heap property, where each parent node is greater than or equal 
 * to its children. This loop iterates from the last non-leaf node towards the 
 * root of the heap.
 * - After the first loop, the elements in the array are organized as a max-heap.
 * - The second loop performs the sorting phase of Heap Sort. It iterates from 
 * the last element to the first (from size - 1 to 1). In each iteration, the 
 * largest element, which is the root of the max-heap (located at index 0), 
 * is swapped with the element at the current position i.
 * - After the swap, the max-heap property may be violated at the root node 
 * (index 0), so the heapify function is called on the reduced heap 
 * (with a size of i) to restore the max-heap property. This ensures that the 
 * largest element "bubbles down" to its correct position in the sorted portion 
 * of the array.
 * - The second loop continues to reduce the size of the heap and swap elements
 * until the entire array is sorted in ascending order.
 *
 * Input: int *array, int size.
 *
 * Output: Sorted List.
 *
************************************************************************************/
void heapSort(int *array, int size)
{
    int i;
    for (i = size / 2 - 1; i >= 0; i--)
        heapify(array, size, i);

    for (i = size - 1; i > 0; i--)
    {
        int temp = array[0];
        array[0] = array[i];
        array[i] = temp;

        heapify(array, i, 0);
    }
}

/************************************************************************************
 * Method: heapSort: 
 * 
 * - The heapify function takes three parameters:
 *   - int *array: A pointer to an array of integers representing the binary heap.
 *   - int size: The current size of the heap (the number of elements in the array).
 *   - int i: The index of the element to be considered as the root of the subtree 
 *     where the max-heap property will be maintained.
 * - Inside the function, it initializes a variable largest with the value of i, 
 * indicating that the element at index i is currently assumed to be the largest 
 * within the subtree.
 * - It calculates the indices of the left and right children of the element at 
 * index i. In a binary heap, the left child is typically at 2 * i + 1, and the 
 * right child is at 2 * i + 2.
 * - The function checks whether the left child exists (i.e., left < size) and 
 * whether the value of the left child (in array[left]) is greater than the value 
 * of the element currently assumed to be the largest (array[largest]). If both 
 * conditions are met, it updates the largest variable to the index of the 
 * left child.
 * - It then performs a similar check for the right child. If the right child 
 * exists (i.e., right < size) and its value is greater than the current largest, 
 * it updates the largest variable again.
 * - If the value of largest has changed during the above checks 
 * (i.e., it is no longer equal to i), it means that one of the child nodes has 
 * a larger value than the current node. In this case, it swaps the element at 
 * index i with the element at index largest to maintain the max-heap property.
 * - After the swap, the function recursively calls itself on the affected 
 * subtree with the new value of largest. This ensures that the max-heap 
 * property is maintained throughout the entire heap.
 *
 * Input: int *array, int size, int i.
 *
 * Output: Comparing an element with its left and right children within a binary 
 * heap, and if necessary, swapping it with the largest of its children.
 *
************************************************************************************/
void heapify(int *array, int size, int i)
{
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < size && array[left] > array[largest])
        largest = left;
    
    if (right < size && array[right] > array[largest])
        largest = right;

    if (largest != i)
    {
        int temp = array[i];
        array[i] = array[largest];
        array[largest] = temp;

        heapify(array, size, largest);
    }
}