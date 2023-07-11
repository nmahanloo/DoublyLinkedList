// Nima Mahanloo
// Doubly Linked List
// CISP 430
#include <iostream>
#include <fstream>
using namespace std;
// A structure as a doubly linked list node
struct node
{
    bool firstFlag = false;
    int number = 0;
    node* next = nullptr;
    node* prev = nullptr;
};
// A module to add a node to head of list
void addList (node* (&head))
{
    head->next = new node;
    head->next->prev = head;
    head = head->next;
}
// A module to push read number to list
void pushList(node* (&head), int num)
{
    if (head->firstFlag == false)
    {
        addList(head);
    }
    head->number = num;
    if (head->firstFlag == true)
    {
        head->firstFlag = false;
    }
}
// A module to read numbers from the input file and push them to list
void readFile (node* (&head))
{
    int num = 0;
    ifstream readNumber ("input.txt");
    if (readNumber.is_open())
    {
        while (!(readNumber.eof()))
        {
            readNumber >> num;
            pushList (head, num);
        }
    }
    else
    {
        cout << "Error: Can not open file!" << endl;
    }
    readNumber.close();
}
// A module to write final list numbers on the output file
void writeFile (node* tail)
{
    ofstream writeNumber ("output.txt");
    while (tail != nullptr)
    {
        writeNumber << tail->number << endl;
        tail = tail->next;
    }
    writeNumber.close();
}
// A module to delete a node by index number from tail
void delNode (node* (&head), node* (&tail), int nodeNum)
{
    node* curr = tail;
    int index = 1;
    while ((curr->next != nullptr) && (index < nodeNum))
    {
        curr = curr->next;
        index++;
    }
    if (curr->next != nullptr)
    {
        curr->next->prev = curr->prev;
    }
    if (curr->prev != nullptr)
    {
        curr->prev->next = curr->next;
    }
    if (curr == tail)
    {
        tail = curr->next;
    }
    if (curr == head)
    {
        head = curr->prev;
    }
    delete curr;
    curr = nullptr;
}
// A module to delete a node by index number from head
void delRNode (node* (&head), node* (&tail), int nodeRNum)
{
    node* curr = head;
    int index = 1;
    while ((curr->prev != nullptr) && (index < nodeRNum))
    {
        curr = curr->prev;
        index++;
    }
    if (curr->prev != nullptr)
    {
        curr->prev->next = curr->next;
    }
    if (curr->next != nullptr)
    {
        curr->next->prev = curr->prev;
    }
    if (curr == tail)
    {
        tail = curr->next;
    }
    if (curr == head)
    {
        head = curr->prev;
    }
    delete curr;
    curr = nullptr;
}
// A module to ask from user about nodes index number to delete and send them to delete modules
void mainMenu (node* (&head), node* (&tail))
{
    int userChoice;
    cout << "Which item do you want to delete from the beginning? ";
    cin >> userChoice;
    delNode (head, tail, userChoice);
    cout << "Which item do you want to delete end? ";
    cin >> userChoice;
    delRNode (head, tail, userChoice);
}
// A module to clear list exclude the tail
void clearList (node* (&head))
{
    node* temp = nullptr;
    while (head->prev != nullptr)
    {
        temp = head;
        head = head->prev;
        head->next = nullptr;
        delete temp;
        temp = nullptr;
    }
}

int main()
{
    // An object from structure 'node' as doubly linked list tail
    node* tail= new node;
    // An object from node as list head
    node* head = tail;
    // Initialize tail boolean member as first node
    tail->firstFlag = true;
    // Call a module to read numbers from input file and push them to the list
    readFile(head);
    // Call a module to ask from user about nodes to delete
    mainMenu (head, tail);
    // Call a module to write final list numbers on output file
    writeFile (tail);
    // Call a module to reset linked list
    clearList (head);
    // Clear heap and memory
    delete head;
    head = nullptr;
    delete tail;
    tail = nullptr;
    return 0;
}
