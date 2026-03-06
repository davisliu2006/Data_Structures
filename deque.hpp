#pragma once

#include <cstdlib>
#include <cstring>
#include <new>

namespace ds {
    /*
    Contiguous version of deque.
    */
    template <class type>
    struct circular_deque {
        private:
        type* arr;
        int _front = 0;
        int _size = 0;
        int _capacity;

        int _back() {return (_front+_size-1)%_capacity;}
        size_t _raw_capacity() {return _capacity*sizeof(type);}

        public:
        circular_deque(int capacity = 16): _capacity(capacity) {
            arr = (type*)malloc(_raw_capacity());
            if (!arr) {throw std::bad_alloc();}
        }
        ~circular_deque() {
            for (int i = _front; i < _front+_size; i++) {
                arr[i%_capacity].~type();
            }
            free(arr);
        }

        int size() const {return _size;}
        int capacity() const {return _capacity;}
        type& front() {return arr[_front];}
        type& back() {return arr[_back()];}

        void realloc() {
            type* temp = (type*)malloc(_raw_capacity()*2);
            if (!temp) {throw std::bad_alloc();}
            for (int i = _front; i < _front+_size; i++) {
                new (&temp[i%(_capacity*2)]) type(arr[i%_capacity]);
                arr[i%_capacity].~type();
            }
            free(arr);
            arr = temp;
            _capacity *= 2;
        }
        void push_back(const type& val) {
            if (_size == _capacity) {realloc();}
            _size++;
            new (&back()) type(val);
        }
        void push_front(const type& val) {
            if (_size == _capacity) {realloc();}
            _front = (_front-1+_capacity)%_capacity;
            _size++;
            new (&front()) type(val);
        }
        void pop_back() {
            back().~type();
            _size--;
        }
        void pop_front() {
            front().~type();
            _front = (_front+1)%_capacity;
            _size--;
        }

        type& operator[](int i) {
            return arr[(_front+i)%_capacity];
        }
        const type& operator[](int i) const {
            return arr[(_front+i)%_capacity];
        }

        circular_deque(const circular_deque& dq):
        _front(dq._front), _size(dq._size), _capacity(dq._capacity) {
            arr = (type*)malloc(_raw_capacity());
            if (!arr) {throw std::bad_alloc();}
            for (int i = _front; i < _front+_size; i++) {
                new (&arr[i%_capacity]) type(dq.arr[i%_capacity]);
            }
        }
        circular_deque& operator =(const circular_deque& dq) {
            if (this == &dq) {return *this;}
            for (int i = _front; i < _front+_size; i++) {
                arr[i%_capacity].~type();
            }
            free(arr);
            _front = dq._front; _size = dq.size(); _capacity = dq.capacity();
            arr = (type*)malloc(_raw_capacity());
            if (!arr) {throw std::bad_alloc();}
            for (int i = _front; i < _front+_size; i++) {
                new (&arr[i%_capacity]) type(dq.arr[i%_capacity]);
            }
            return *this;
        }
        circular_deque(const circular_deque&& dq) noexcept:
        _capacity(dq._capacity), _size(dq._size), arr(dq.arr) {
            dq._size = 0; dq._capacity = 0; dq._front = 0;
            dq.arr = nullptr;
        }
        circular_deque& operator=(circular_deque&& dq) noexcept {
            if (this == &dq) {return *this;}
            for (int i = _front; i < _front+_size; i++) {
                arr[i%_capacity].~type();
            }
            free(arr);
            _front = dq._front; _size = dq._size; _capacity = dq._capacity;
            arr = dq.arr;   
            dq._size = 0; dq._capacity = 0; dq._front = 0;
            dq.arr = nullptr;
            return *this;
        }
    };
}