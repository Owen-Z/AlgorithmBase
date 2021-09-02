#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

struct Mymap{
    int key;
    int value;
    Mymap* pre;
    Mymap* next;
};

class LRUCache {
public:
    int capacity;
    int curSize;
    Mymap* LRU;

    // Initialize the capacity of LRU
    LRUCache(int capacity) {
        LRU = (Mymap*) malloc(sizeof (Mymap));
        this->capacity = capacity;
        curSize = 0;
    }

    int get(int key) {
        if(curSize == 0){
            return -1;
        }
        Mymap* searchNode = (Mymap*) malloc(sizeof (Mymap));
        searchNode = LRU;
        // Travel the link list
        while(searchNode->pre && searchNode->key != key){
            searchNode = searchNode->pre;
        }

        // Return the selected value
        if(searchNode->key != key){
            return -1;
        }else{
            // The node has pre node
            if(searchNode->pre){
                if(searchNode->next){
                    searchNode->next->pre = searchNode->pre;
                    searchNode->pre->next = searchNode->next;
                }
                Mymap* addNode = (Mymap*) malloc(sizeof (Mymap));
                addNode->key = key;
                addNode->value = searchNode->value;
                addNode->pre = LRU;
                addNode->next = nullptr;
                LRU->next = addNode;
                LRU = addNode;
            }else{
                // Search the place of the first node
                if(capacity != 1 && searchNode->next != nullptr){
                    searchNode->next->pre = nullptr;
                    Mymap* addNode = (Mymap*) malloc(sizeof (Mymap));
                    addNode->key = key;
                    addNode->value = searchNode->value;
                    addNode->pre = LRU;
                    addNode->next = nullptr;
                    LRU->next = addNode;
                    LRU = addNode;
                }
            }


            return searchNode->value;
        }
    }

    void put(int key, int value) {
        if(curSize == 0){
            // When the capacity is zero
            LRU->key = key;
            LRU->value = value;
            LRU->pre = nullptr;
            LRU->next = nullptr;
            curSize++;
        }else if(curSize < capacity && get(key) == -1){
            // When the current capacity less than capacity
            // Create new node and add to the linklist
            Mymap* curNode = (Mymap*) malloc(sizeof (Mymap));
            curNode->key = key;
            curNode->value = value;
            curNode->pre = LRU;
            curNode->next = nullptr;
            LRU->next = curNode;
            LRU = curNode;
            curSize++;
        }else{
            // When the size is not enough
            // Two condition
            // find the node which is not used in longest time
            int flag = get(key);
            if(get(key) == -1){
                Mymap* curNode = (Mymap*) malloc(sizeof (Mymap));
                curNode->key = key;
                curNode->value = value;
                curNode->pre = LRU;
                curNode->next = nullptr;
                LRU->next = curNode;
                LRU = curNode;
                Mymap* deleteNode = (Mymap*) malloc(sizeof (Mymap));
                deleteNode = curNode;
                int target = deleteNode->key;
                while(deleteNode->pre){
                    deleteNode = deleteNode->pre;
                    target = deleteNode->key;
                }
                deleteNode->next->pre = nullptr;
                free(deleteNode);
            }else{
                Mymap* searchNode = (Mymap*) malloc(sizeof (Mymap));
                searchNode = LRU;
                // Travel the link list
                while(searchNode->pre && searchNode->key != key){
                    searchNode = searchNode->pre;
                }
                searchNode->value = value;
            }

        }
    }
};

int main(){
    LRUCache* lRUCache = new LRUCache(2);
//    lRUCache->put(1, 1); // 缓存是 {1=1}
    lRUCache->put(2, 1); // 缓存是 {1=1, 2=2}
    lRUCache->get(2);
    lRUCache->put(2,2);
//    cout << lRUCache->get(1) << endl;    // 返回 1
//    lRUCache->put(3, 3); // 该操作会使得关键字 2 作废，缓存是 {1=1, 3=3}
    cout << lRUCache->get(2) << endl;    // 返回 -1 (未找到)
    lRUCache->put(1, 1); // 该操作会使得关键字 1 作废，缓存是 {4=4, 3=3}
    lRUCache->put(4, 1);
    cout << lRUCache->get(2) << endl;    // 返回 -1 (未找到)
//    cout << lRUCache->get(3) << endl;    // 返回 3
//    cout << lRUCache->get(4) << endl;    // 返回 4

}