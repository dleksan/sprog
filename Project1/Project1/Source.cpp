// Tetris.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>




struct Node {
    int x;
    Node* next;
};

Node* temp = NULL;

Node* head = NULL;
void Insert(int x)
{
    if (temp == NULL)
    {
        temp = new Node();
        temp->x = x;
        head = temp;
    }

    else
    {
        temp->next = new Node();
        temp->next->x = x;
        temp = temp->next;
    }
}

void Print()
{
    temp = head;
    while (temp != NULL)
    {
        std::cout << temp->x;
        temp = temp->next;
    }


}

void Delete(int index)
{
    Node* temp1;
    for (int i = 0; i < index-1; i++)
    {
        temp = temp->next;
    }

    temp1 = temp->next;
    temp->next = temp->next->next;
    temp = temp1;
    delete temp;

}

void RemoveDuplicates()
{
    Node* temp1 = head;
    Node* temp2 = head;

    while (temp1 != NULL)
    {
        while (temp2 != NULL)
        {
            if (temp1->x == temp2->x)
            {

            }
        }
    }
}

int main()
{
    for (int i = 0; i < 10; i++)
    {
        Insert(i);
    }
    Print();
    Delete(3);
    Print();
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
