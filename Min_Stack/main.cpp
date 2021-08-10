#include <iostream>
#include <string>
#include <vector>
#include <stack>


using namespace std;

struct Node{
    int number;
    Node* next;
    Node* pre;
};

class MinStack {
public:
    /** initialize your data structure here. */
    Node* minNodes;
    int length = 0; // length of linked list
    int minNum;
    stack<int> Mystack;
    MinStack() {
        // initialize the linked list
        minNodes = (Node*) malloc(sizeof (Node));
        minNodes->number = 100000000;
        minNodes->next = nullptr;
        Node* node = (Node*) malloc(sizeof (Node));
        node->number = 100;
        node->next = minNodes;
        minNodes->pre = node;
    }

    void push(int x) {
        if(length == 0){
            minNum = x;
            Node* node = (Node*) malloc(sizeof (Node));
            node->number = x;
            node->next = minNodes->next;
            node->pre = minNodes->pre;
            minNodes->next = node;
            minNodes = minNodes->next;
            length ++;
        }else{
            if(x <= minNum){
                minNum = x;
                Node* node = (Node*) malloc(sizeof (Node));
                node->number = x;
                node->next = minNodes->next;
                node->pre = minNodes;
                minNodes->next = node;
                minNodes = minNodes->next;
                length ++;
                cout << "current length is " << length << endl;
            }
        }
        Mystack.push(x);
    }

    void pop() {
        if(length == 0){
            return;
        }else{
            if(Mystack.top() == minNum){
                minNodes = minNodes->pre;
                minNodes->next = nullptr;
                minNum = minNodes->number;
                length--;
            }
        }
        Mystack.pop();
    }

    int top() {
        return Mystack.top();
    }

    int min() {
        return minNum;
    }
};


int main(){
    MinStack* obj = new MinStack;
    obj->push(2147483646);
    obj->push(2147483646);
    obj->push(2147483647);
    cout << obj->top() << endl;
    obj->pop();
    cout << obj->min() << endl;
    obj->pop();
    cout << obj->min() << endl;
    obj->pop();
    obj->push(2147483647);
    cout << obj->top() << endl;
    cout << obj->min() << endl;
    obj->push(-2147483648);
    cout << obj->top() << endl;
    cout << obj->min() << endl;
    obj->pop();
    cout << obj->min() << endl;
}
/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(x);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->min();
 */