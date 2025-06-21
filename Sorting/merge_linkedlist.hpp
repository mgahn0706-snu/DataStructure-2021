#include <iostream>
using namespace std;

class Node {
public:
    int data;
    Node* next;
};

/* Return length of the linked list */
int length(Node* head)
{
    //TODO
    int len = 0;
    Node* pointer = head;
    while (pointer != nullptr) {
        pointer = pointer->next;
        len++;
    }
    return len;
}



/* Merge two sub-linked-list in the right order*/
void merge(Node** first, Node** last, Node** _first, Node** _last)
{       
    bool isSwapped = false;
        if ((*first)->data > (*_first)->data) { //코드 2번쓰기 싫어서 무조건 first가 작게한다
            Node* temp1 = *first;
            Node* temp2 = *last;
            *first = *_first;
            *last = *_last;
            *_first = temp1;
            *_last = temp2;
            isSwapped = true;
        }
        

        Node* curr = *first;
        Node* option1 = curr->next;
        Node* temp = *_first;
        Node* option2 = temp;
        Node* lastTemp = *last;
        Node* _lastTemp = *_last;



        while (option1 != lastTemp->next && option2 != _lastTemp->next) {

            if (option1->data > option2->data) {
                
                curr->next = option2;

                option2 = option2->next;
                
            }
            else {
                curr->next = option1;
                option1 = option1->next;

            }

            curr = curr->next;


        }


        if (curr == lastTemp) { //현재 줄 소진
            if (isSwapped) {
                curr->next = option2;
                _lastTemp->next = option1;
            }
            else {
                curr->next = option2;
            }
        }
        else { //반대줄 소진

            if (isSwapped) {
                curr->next = option1;
            }

            else {
                curr->next = option1;
                lastTemp->next = option2;
            }
        }
   

    }


/* Merge-sort the linked list */
void mergeSort(Node** head)
{
    //TOD
    if (*head == nullptr) { //빈 리스트
        return;
    }
    else {
        Node* first = *head; //첫 덩어리 만들기
        Node* connect = nullptr;
        Node* temp =  *head;
        int len = length(*head);
        
        for (int i = 1; i < len; i = 2 * i) {
             bool isFirst = true;
            
            while(first!=nullptr){
               

                Node* last = first;
                int count = 1;


                while (last->next != nullptr && count < i) {

         
                    count++;
                    last = last->next;


                }
                

                Node* _first = last->next;
                
                if (_first == nullptr) { //2^n 이 아닌경우
                    break;
                }

                Node* _last = &(*_first);



                count = 1;
                while (_last->next != nullptr && count < i) {
                    _last = _last->next;
                    count++;
                }



                Node* nextMerge = _last->next;
/*
                printList(first, last);
                cout << "and ";
                printList(_first, _last); */

                merge(&first, &last, &_first, &_last);
                
              


                *head = first;



                if (isFirst) {
                    temp = *head;
                    isFirst = false;
                }
                else {
                    connect->next = first;
                }


                first = nextMerge;
                connect = (last->data > _last->data ? last : _last);
/*
                cout << "last: " << connect->data << endl;
                printList(temp);
                */
           
                }    

            
                

                *head = temp;
                first = *head;
              /*  cout << "after, : ";
                printList(*head); */


     


       


        }
       




    }
}





/* Delete nodes in order to avoid memory leak*/
void removeall(Node* head)
{
    //TODO
    Node* currPtr = head;
    while (currPtr != nullptr) {
        Node* nextPtr = currPtr->next;
        delete currPtr;
        currPtr = nextPtr;
    }
    head = nullptr;
}