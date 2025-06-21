#include <iostream>
using namespace std;

/* Merge two subarrays of the array in right order*/
void merge(int arr[], int const first, int const mid, int const last)
{
    //TODO



    int* leftArray = new int[mid - first + 1];
    int* rightArray = new int[last - mid ];
    int left = 0;
    int count = first;
    int right = 0;


    for (int i = 0; i < mid - first + 1; i++) {
        leftArray[i] = arr[first+i];


    }
    
    for (int j = 0; j < last - mid ; j++) {
        rightArray[j] = arr[mid + j+1];

    }


    while (count < (last  + 1)) {
        //cout << "count: " << count << endl;

        if (left >= mid - first + 1) {
            arr[count] = rightArray[right];
            right++;
        }

        else if (right >= last - mid) {
            arr[count] = leftArray[left];
            left++;
        }


        else if (leftArray[left] < rightArray[right]) {
                arr[count] = leftArray[left];
                left++;
         

        }

         else {
                arr[count] = rightArray[right];
                right++;
                
            }
        

        count++;

    }

    delete[] rightArray;
    delete[] leftArray;






}


/* Split the array into two, and merge-sort each subarray */
void mergeSort(int arr[], int const first, int const last)
{
    //TODO

    if (first < last) {
        int mid = (first + last) / 2;
       // cout << first << " " << mid << " " << last << endl;
        mergeSort(arr,first, mid);
        mergeSort(arr,mid + 1, last);
        


        merge(arr, first, mid, last);

    }
}