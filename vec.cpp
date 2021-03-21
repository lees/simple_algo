#include <iostream>
#include <chrono>
#include <stack>
#include <vector>
 
using namespace std;
using timer = std::chrono::high_resolution_clock;
using microseconds =  std::chrono::microseconds;

const int ELEMENTS = 500000;
const int BLOCK = 4096;

void bench(void func(), int N) {
    for (; N > 0; N--){
        std::chrono::time_point t0 = timer::now();
        func();
        std::chrono::time_point t1 = timer::now();
        auto us = std::chrono::duration_cast<microseconds>(t1 - t0);
        cout << us.count() << "us" << endl;
    }
}


class LinkedArraysStack {
    struct Node {
        int idx;
        Node *prev;
        int *data;
    };

    private:
        Node *head;
        Node *free;
        int sz;

        Node* add_node() {
            Node *node = new Node;
            node->idx = 0;
            node->prev = head;
            node->data = new int[BLOCK];
            return node;
        }

    public:
        LinkedArraysStack() {
            sz = 0;
            head = NULL;
            free = NULL;
            head = add_node();
        }

        int size() {
            return sz;
        }

        void push(int val) {
            if (head->idx == BLOCK) {
                if (free != NULL) {
                    free->prev = head;
                    free->idx = 0;
                    head = free;
                    free = NULL;
                } else {
                    head = add_node();
                }
            }
            head->data[head->idx++] = val;
            sz++;
        }

        int pop() {
            if (sz == 0) {
                throw invalid_argument("stack underflow");
            }
            if (head->idx == 0) {
                if (free != NULL) {
                    delete [] free->data;
                    delete free;
                }
                free = head;
                head = head->prev;
            }
            sz--;
            return head->data[--head->idx];
        }
};

class LinkedListStack {
    struct Node {
        int val;
        Node *prev;
    };

    private:
        Node *head;
        int sz;

    public:
        LinkedListStack() {
            sz = 0;
            head = NULL;
        }

        int size() {
            return sz;
        }

        void push(int val) {
            Node *node = new Node;
            node->val = val;
            node->prev = head;
            sz++;
            head = node;
        }

        int pop() {
            if (sz == 0) {
                throw invalid_argument("stack underflow");
            }
            int val = head->val;
            Node *new_head = head->prev;
            delete head;
            head = new_head;
            sz--;
            return val;
        }
};

class ArrayStack {
    private:
        int idx;
        int capacity;
        int *data;

        void resize(int new_capacity) {
            int *new_data = new int[new_capacity];
            for (int i = 0; i <= idx; i ++) {
                new_data[i] = data[i];
            }
            delete [] data;
            data = new_data;
            // cout << "Resized from " << capacity << " to " << new_capacity << endl;
            capacity = new_capacity;
        }

    public:
        ArrayStack(int cap = 32) {
            idx = 0;
            capacity = cap;
            data = new int [capacity];
        }

        int size() {
            return idx;
        }

        void push(int val) {
            if (idx + 1 == capacity) {
                resize(capacity * 2);
            }
            data[idx++] = val;
        }

        int pop() {
            if (idx == 0) {
                throw invalid_argument("stack underflow");
            }
            int res = data[--idx];
            if (idx * 4 < capacity && capacity > 32) {
                resize(capacity / 2);
            }
            return res;
        }
};

class VectorStack {
    private:
        int idx;
        vector <int> data;
    public:
        VectorStack(int capacity) {
            idx = 0;
            data = vector<int>(capacity);
        }
        
        VectorStack() {
            VectorStack(32);
        }

        int size() {
            return idx;
        }

        void push(int val) {
            data.push_back(val);
        }

        int pop() {
            if (data.empty()) {
                throw invalid_argument("stack underflow");
            }
            idx--;
            int res = data.back();
            data.pop_back();
            return res;
        }
};

void push_with_realloc() {
    vector <int> vector_int;
    for (int i = 0; i < ELEMENTS; i++) {
        vector_int.push_back(i);
    }
}

void push_prealloc() {
    vector <int> vector_int(ELEMENTS+1);
    for (int i = 0; i < ELEMENTS; i++) {
        vector_int.push_back(i);
    }
}

void test_stack() {
    ArrayStack st = ArrayStack();

    for (int i = 0; i < ELEMENTS; i ++ ) {
        st.push(i);
        st.push(i);
        st.pop();
    }

    while (st.size() > 0) {
        st.push(st.size());
        st.pop();
        st.pop();
        int el = st.pop();
        if (el != st.size()) {
            cout << el << st.size() << endl;
        }
    }

}

void test_linked_stack() {
    auto st = LinkedListStack();
    // auto st = VectorStack(16);

    for (int i = 0; i < ELEMENTS; i ++ ) {
        st.push(i);
        st.push(i);
        st.pop();
    }

    while (st.size() > 0) {
        st.push(st.size());
        st.pop();
        st.pop();
        int el = st.pop();
        if (el != st.size()) {
            cout << el << st.size() << endl;
        }
    }

}

void test_linked_arrays_stack() {
    auto st = LinkedArraysStack();

    for (int i = 0; i < ELEMENTS; i ++ ) {
        st.push(i);
        st.push(i);
        st.pop();
    }

    while (st.size() > 0) {
        st.push(st.size());
        st.pop();
        st.pop();
        int el = st.pop();
        if (el != st.size()) {
            cout << "ERROR: " << el << st.size() << endl;
        }
    }

}

void test_std_stack() {
    stack <int> st = stack<int>();

    for (int i = 0; i < ELEMENTS; i ++ ) {
        st.push(i);
        st.push(i);
        st.pop();
    }

    while (st.size() > 0) {
        st.push(st.size());
        st.pop();
        st.pop();
        int el = st.top();
        st.pop();
        if (size_t(el) != st.size()) {
            cout << el << st.size() << endl;
        }
    }

}
 
int main() {
    // cout << "With realloc" << endl;
    // bench(push_with_realloc, 10);

    // cout << "Prealloc" << endl;
    // bench(push_with_realloc, 10);

    cout << "Array" << endl;
    bench(test_stack, 10);
    cout << "Std" << endl;
    bench(test_std_stack, 10);
    cout << "Linked" << endl;
    bench(test_linked_stack, 10);
    cout << "Linked arrays" << endl;
    bench(test_linked_arrays_stack, 10);

    return 0;
}