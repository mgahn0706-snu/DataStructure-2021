#pragma once
#include <iostream>
using namespace std;

void swap(int* a, int* b)
{
    //TODO
    int* temp = a;
    a = b;
    b = temp;

}


/* Take one element as pivot,
place it in the right position of the given array */
int position(int arr[], int const first, int const last)
{
    //TODO
    //cout << "position function: " << first << " " << last << endl;


    if (first >= last) {

  /*      for (auto i = 0; i < last + 1; i++)
            cout << arr[i] << " ";
        cout << "after swapping" << endl; */



        return first;

    }

    int center = (first + last) / 2;
    int pivot;

    if (arr[first] > arr[center]) {
        swap(arr[first], arr[center]);
    }
    if (arr[center] < arr[last]) {
        swap(arr[center], arr[last]);
    }
    if (arr[first] > arr[last]) {
        swap(arr[first], arr[last]);
    }

    pivot = arr[last];
   // cout << "pivot: " << pivot << endl;
    //cout << "pivot is " << pivot << endl;
    int left = first + 1;
    int right = last - 1;

     /*       for (auto i = 0; i < last + 1; i++)
            cout << arr[i] << " ";
        cout << "before swapping" << endl; */



    while (left<=right) {


        while (arr[left] < pivot) {
            left++;
        }

        while (arr[right] >pivot && left<=right) {
            right--;
        }
  
        //cout << left << " " << right << endl;
        
        if (left <= right) {
            //cout << "swapped " << arr[left] << " and " << arr[right] << endl;
            swap(arr[left], arr[right]);

            left++;
            right--;
        }



    }
    swap(arr[left], arr[last]);

 /*   for (auto i = 0; i < last + 1; i++)
        cout << arr[i] << " ";
    cout << "after swapping" << endl; */



    return left;


}


/* Quick-sort the given array */
void quickSort(int arr[], int const first, int const last)
{
    //TODO
    int q;
  

    

    if (first < last) {

        q = position(arr, first, last);
       // cout << "first:" << first << " " << q - 1 << endl;

        quickSort(arr, first, q - 1);
    


       // cout << "second:" << q+1 << " " << last << endl;


        quickSort(arr, q+1, last);
        
       
    }



}
