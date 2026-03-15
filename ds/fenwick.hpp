#pragma once

#include <type_traits>

namespace ds {
    /**
     * Standard fenwick tree data structure.
     */
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

        int size() const {return size;}
        void update(int i, type dval) {
            while (i <= _size) {
                arr[i] += dval;
                i += (i&-i);
            }
        }
        type query(int i) const {
            type val = 0;
            while (i > 0) {
                val += arr[i];
                i -= (i&-i);
            }
            return val;
        }
    };
}