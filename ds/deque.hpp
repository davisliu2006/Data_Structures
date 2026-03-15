#pragma once

#include <cstdlib>
#include <cstring>
#include <new>

namespace ds {
    /**
     * Contiguous version of deque.
     */
    template <class type>
    struct contig_deque {
        private:
        type* arr;
        int _front = 0;
        int _size = 0;
        int _capacity;

        int _back() const {return (_front+_size-1)%_capacity;}
        size_t _raw_capacity() const {return _capacity*sizeof(type);}
        void destroy_elements() {
            for (int i = _front; i < _front+_size; i++) {
                arr[i%_capacity].~type();
            }
        }

        public:
        contig_deque(int capacity = 16): _capacity(capacity) {
            arr = (type*)::operator new(_raw_capacity());
        }
        ~contig_deque() {
            destroy_elements();
            ::operator delete(arr);
        }

        int size() const {return _size;}
        int capacity() const {return _capacity;}
        bool empty() const {return _size == 0;}
        type& front() {return arr[_front];}
        const type& front() const {return arr[_front];}
        type& back() {return arr[_back()];}
        const type& back() const {return arr[_back()];}

        type& operator[](int i) {
            return arr[(_front+i)%_capacity];
        }
        const type& operator[](int i) const {
            return arr[(_front+i)%_capacity];
        }

        void reserve(int new_capacity) {
            assert(new_capacity >= _size);
            type* temp = (type*)::operator new(new_capacity*sizeof(type));
            for (int i = 0; i < _size; i++) {
                new (&temp[i%new_capacity]) type((*this)[i]);
                arr[i%_capacity].~type();
            }
            ::operator delete(arr);
            arr = temp;
            _front = 0;
            _capacity = new_capacity;
        }
        void push_back(const type& val) {
            if (_size == _capacity) {reserve(_capacity*2);}
            _size++;
            new (&back()) type(val);
        }
        void push_front(const type& val) {
            if (_size == _capacity) {reserve(_capacity*2);}
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

        contig_deque(const contig_deque& dq):
        _front(0), _size(dq._size), _capacity(dq._capacity) {
            arr = (type*)::operator new(_raw_capacity());
            for (int i = 0; i < _size; i++) {
                new (&arr[i%_capacity]) type(dq[i]);
            }
        }
        contig_deque& operator =(const contig_deque& dq) {
            if (this == &dq) {return *this;}
            destroy_elements();
            ::operator delete(arr);
            _front = 0; _size = dq.size(); _capacity = dq.capacity();
            arr = (type*)::operator new(_raw_capacity());
            for (int i = 0; i < _size; i++) {
                new (&arr[i%_capacity]) type(dq[i]);
            }
            return *this;
        }
        contig_deque(contig_deque&& dq) noexcept:
        _capacity(dq._capacity), _size(dq._size), arr(dq.arr) {
            dq._size = 0; dq._capacity = 0; dq._front = 0;
            dq.arr = NULL;
        }
        contig_deque& operator=(contig_deque&& dq) noexcept {
            if (this == &dq) {return *this;}
            destroy_elements();
            ::operator delete(arr);
            _front = dq._front; _size = dq._size; _capacity = dq._capacity;
            arr = dq.arr;   
            dq._size = 0; dq._capacity = 0; dq._front = 0;
            dq.arr = NULL;
            return *this;
        }
        bool operator ==(const contig_deque& dq) const {
            if (this->size() != dq.size()) {return false;}
            for (int i = 0 ; i < _size; i++) {
                if ((*this)[i] != dq[i]) {return false;}
            }
            return true;
        }
    };
}