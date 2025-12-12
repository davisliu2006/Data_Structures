#pragma once

#include <type_traits>

namespace ds {
    template <class type>
    struct fenwick {
        static_assert(std::is_arithmetic<type>());

        private:
        type* arr;
        int _size;

        public:
        fenwick(int size): _size(size) {
            arr = new type[size+1]();
        }
        ~fenwick() {
            delete[] arr;
        }

        int size() {return size;}
        void update(int i, type dval) {
            while (i <= _size) {
                arr[i] += dval;
                i += (i&-i);
            }
        }
        type query(int i) {
            type val = 0;
            while (i > 0) {
                val += arr[i];
                i -= (i&-i);
            }
            return val;
        }
    };
}