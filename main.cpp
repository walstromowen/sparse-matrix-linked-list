/*
    Sparse Matrix Implementation Linked List Implementation.
    Author: Owen Walstrom
    Date: 9/8/2024
    
*/

#include <iostream>
using namespace std;

struct Node{
    int row, column, value;
    Node* next;
};

class SparseMatrix{
    private:
        int rows, columns;
        Node* head;
    public:
        SparseMatrix(int row, int columns){
            this->rows = rows;
            this->columns = columns;
            head = NULL;
        }
        void addValue(int row, int column, int value){
            if(value == 0){
                return;
            }
            Node* newNode = new Node();//create new node
            newNode->row = row;
            newNode->column = column;
            newNode->value = value;
            newNode->next = head;//new node's next value is = to the current head node (meaning new nodes are linked before previous nodes)
            head = newNode; //head is updated to point to most recently created node
        }
        int getValue(int row, int column){
            Node* p = head;
            while(p){
                if(p->row == row && p->column == column){
                    return p->value;
                }
                p = p->next;
            }
            return 0;
        }
        void setValue(int row, int column, int value){
            Node* p = head;
            while(p){
                if(p->row == row && p->column == column){
                    p->value = value;
                    return;
                }
                p = p->next;
            }
        }
        void deleteNode(int row, int column){
            Node* previous = NULL;
            Node* p = head;
            while(p){
                if(p->row == row && p->column == column){
                    if(previous == NULL){//If first node in chain 
                        head = p->next;
                        return;
                    }
                   previous->next = p->next;
                   return;
                }
                previous = p;
                p = p->next;
                
            }
        }
        void display(){
            Node* p = head;
            cout << "Sparse Matrix:" << endl;
            while(p){
                cout << "(" << p->row << ", " << p->column << ") " << "value: " << p->value << endl;
                p = p->next;
            }
        }
};


int main() {
    SparseMatrix myMatrix(5, 5);
    myMatrix.addValue(0, 2, 3);
    myMatrix.addValue(0, 4, 4);
    myMatrix.addValue(1, 2, 5);
    myMatrix.addValue(1, 3, 7);
    myMatrix.addValue(3, 1, 2);
    myMatrix.addValue(3, 2, 6);

    myMatrix.display();

    myMatrix.setValue(1, 2, 50);

    //cout << myMatrix.getValue(1, 2);

    myMatrix.deleteNode(1, 2);

    myMatrix.display();


    return 0;
}



















/*
#include <iostream>

struct Node {
    int row, col, value;
    Node* next;
    Node(int row, int column, int value) : row(row), col(column), value(value), next(nullptr) {}//Member Initializer List (function like this->property = coresponding parameter)
};

class SparseMatrix {
private:
    int rows, columns;
    Node** rowHeads; // "**" means pointer to a pointer 

public:
    SparseMatrix(int rows, int columns) : rows(rows), columns(columns) {
        rowHeads = new Node*[rows];//???
        for (int i = 0; i < rows; ++i) {
            rowHeads[i] = nullptr;
        }
    }

    ~SparseMatrix() {
        for (int i = 0; i < rows; ++i) {
            Node* current = rowHeads[i];
            while (current) {
                Node* temp = current;
                current = current->next;
                delete temp;
            }
        }
        delete[] rowHeads;
    }

    void insert(int row, int col, int value) {
        if (value == 0) {
            return; 
        }

        Node* newNode = new Node(row, col, value);
        Node* current = rowHeads[row];
        Node* prev = nullptr;

        while (current && current->col < col) {//while the current node exsits and while the current node's column is less than the desired column of the new node
            prev = current;
            current = current->next;
        }

        if (prev == nullptr) {//after correct node is found (meaning that the currently selected node has a column less than the desired column of the new node)
            newNode->next = rowHeads[row]; //the new nodes next is equal to the 
            rowHeads[row] = newNode;
        } else {
            prev->next = newNode;
            newNode->next = current;
        }
    }

    void display() {
        for (int i = 0; i < rows; ++i) {
            Node* current = rowHeads[i];
            for (int j = 0; j < columns; ++j) {
                if (current && current->col == j) {
                    std::cout << current->value << " ";
                    current = current->next;
                } else {
                    std::cout << "0 ";
                }
            }
            std::cout << std::endl;
        }
    }
};

int main() {
    SparseMatrix matrix(3, 4);
    matrix.insert(0, 1, 5);
    matrix.insert(1, 2, 8);
    matrix.insert(2, 0, 3);

    matrix.display();
    return 0;
}
*/







/*
#include <iostream>
#include <vector>
using namespace std;

class FloatList{
    private:
        struct ListNode{
            float info;
            struct ListNode *link;
        };
        ListNode *head; // List head pointer
    public:
        FloatList(){ 
            head = NULL; 
        }
        ~FloatList(){
            ListNode *nodePtr, *nextNode;
            nodePtr = head;
            while (nodePtr != NULL){
                nextNode = nodePtr->link;
                delete nodePtr;
                nodePtr = nextNode;
            }
        }
        void appendNode(float num){
            ListNode *newNode, *nodePtr;
            newNode = new ListNode;  // Allocate a new node & store num
            newNode->info = num;
            newNode->link = NULL;
            if(!head){ // If there are no nodes in the list make newNode the first node
                head = newNode;
            }else{ // Otherwise, insert newNode at end
                nodePtr = head; // Initialize nodePtr to head of list
                while (nodePtr->link)  // Find the last node in the list
                nodePtr = nodePtr->link; // Insert newNode as the last node
                nodePtr->link = newNode;
            }
        }
        void insertNode(float num){
            ListNode *newNode, *nodePtr, *previousNode;
            newNode = new ListNode; // Allocate a new node & store Num
            newNode->info = num;
            if(!head){  // If there are no nodes in the list make newNode the first node
                head = newNode;
                newNode->link = NULL;
            }else{ // Otherwise, insert newNode.
                nodePtr = head;  // Initialize nodePtr to head of list
                while(nodePtr != NULL && nodePtr->info < num){ // Skip all nodes whose info member is less than num.
                    previousNode = nodePtr;
                    nodePtr = nodePtr->link;
                }
            }
            if(previousNode == NULL){ // If the new mode is to be the 1st in the list, insert it before all other nodes.
                head = newNode;
                newNode->link = nodePtr;
            }else{
                previousNode->link = newNode;
                newNode->link = nodePtr;
            }
        }
        void deleteNode(float num){
            ListNode *nodePtr, *previousNode;
            if(!head){// If the list is empty, do nothing.
                   return;
            }
            if(head->info == num){  // Determine if the first node is the one.
                nodePtr = head->link;
                delete head;
                head = nodePtr;
            }else{
                nodePtr = head; // Initialize nodePtr to head of list
                while (nodePtr != NULL && nodePtr->info != num){ // Skip all nodes whose info member is not equal to num.
                    previousNode = nodePtr;
                    nodePtr = nodePtr->link;
                }
                previousNode->link = nodePtr->link; // Link the previous node to the node after nodePtr, then delete nodePtr.
                delete nodePtr;
            }
        }
        void displayList(){
            if(!head){
                cout << "There is no node in the list." << endl;
            }else{
                ListNode *nodePtr;
                nodePtr = head;
                while (nodePtr){
                    cout << nodePtr->info << endl;
                    nodePtr = nodePtr->link;
                }
            }
        }
};


class SparseMatrix{
    private:
        

    public:
        SparseMatrix(){
           

        }
        void addValue(int row, int column, int value){
            
            
        }
        int getValue(int targetRow, int targetColumn){
            
            return 0;
        }
        void setValue(int targetRow, int targetColumn, int newValue){
            
        }
        void deleteValue(int targetRow, int targetColumn){
            
        }
        void display(){
            
        }
};




int main() {
    FloatList list;// Build the list
    list.appendNode(2.5);
    list.appendNode(7.9);
    list.appendNode(12.9);
    // Insert a node in the middleof the list
    list.insertNode(10.5);
    // Dispay the list
    list.displayList();
   


    SparseMatrix myMatrix;
   
    return 0;
};
*/