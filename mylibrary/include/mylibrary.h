#ifndef MYLIBRARY_H
#define MYLIBRARY_H

// clang-format off
#if defined(_WIN32)
    #if defined(BUILD_LIBTYPE_SHARED)
        #define MYLIBRARY_API __declspec(dllexport)     // We are building the library as a Win32 shared library (.dll)
    #elif defined(USE_LIBTYPE_SHARED)
        #define MYLIBRARY_API __declspec(dllimport)     // We are using the library as a Win32 shared library (.dll)
    #endif
#else
    #if defined(BUILD_LIBTYPE_SHARED)
        #define MYLIBRARY_API __attribute__((visibility("default"))) // We are building as a Unix shared library (.so/.dylib)
    #endif
#endif

#ifndef MYLIBRARY_API
    #define MYLIBRARY_API
#endif
// clang-format on

#include <cstddef>
#include <iterator>
#include <vector>

namespace mylibrary {

struct Object {
    int a;
    int b;
};

MYLIBRARY_API bool is_shared();

template <typename T>
class Array {
public:
    using value_type = T;

    class iterator;
    using reverse_iterator = std::reverse_iterator<iterator>;

    MYLIBRARY_API Array();

    MYLIBRARY_API Array(size_t count, const T& value = T());

    MYLIBRARY_API Array(std::initializer_list<T> init);

    MYLIBRARY_API Array(iterator first, iterator last);

    MYLIBRARY_API ~Array();

    MYLIBRARY_API Array(Array&);

    MYLIBRARY_API Array& operator=(Array&);

    MYLIBRARY_API Array(Array&&);

    MYLIBRARY_API Array& operator=(Array&&);

    MYLIBRARY_API size_t size() const;

    MYLIBRARY_API bool empty() const;

    MYLIBRARY_API void push_back(const T& value);

    MYLIBRARY_API void push_back(T&& value);

    MYLIBRARY_API T& operator[](size_t pos);

    MYLIBRARY_API const T& operator[](size_t pos) const;

    MYLIBRARY_API T& front();

    MYLIBRARY_API const T& front() const;

    MYLIBRARY_API T& back();

    MYLIBRARY_API const T& back() const;

    MYLIBRARY_API T* data();

    MYLIBRARY_API const T* data() const;

    MYLIBRARY_API iterator begin() const;

    MYLIBRARY_API iterator begin();

    MYLIBRARY_API iterator end() const;

    MYLIBRARY_API iterator end();

    MYLIBRARY_API reverse_iterator rbegin() { return reverse_iterator(end()); }

    MYLIBRARY_API reverse_iterator rend() { return reverse_iterator(begin()); }

    MYLIBRARY_API iterator insert(iterator pos, const T& value);

    MYLIBRARY_API iterator erase(iterator pos);

    MYLIBRARY_API iterator erase(iterator first, iterator last);

    MYLIBRARY_API void assign(size_t count, const T& value);

    MYLIBRARY_API void assign(iterator first, iterator last);

    MYLIBRARY_API void assign(std::initializer_list<T> ilist);

    static Array<T> from(const std::vector<T>& in)
    {
        return Array<T>(const_cast<T*>(in.data()), const_cast<T*>(in.data() + in.size()));
    }

    std::vector<T> to_std_vector() const
    {
        return std::vector<T>(data(), data() + size());
    }

    template <typename T_>
    MYLIBRARY_API friend bool operator==(const Array<T_>& lhs, const Array<T_>& rhs);

    class iterator {
    public:
        using iterator_category = std::random_access_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = T;
        using pointer = T*;
        using reference = T&;

    public:
        iterator(pointer p)
            : m_ptr(p)
        {
        }

        reference operator*() const { return *m_ptr; }

        pointer operator->() { return m_ptr; }

        iterator& operator++()
        {
            // Prefix increment
            m_ptr++;
            return *this;
        }

        iterator operator++(int)
        {
            // Postfix increment
            iterator tmp = *this;
            ++(*this);
            return tmp;
        }

        iterator& operator--()
        {
            // Prefix decrement
            m_ptr--;
            return *this;
        }

        iterator operator--(int)
        {
            // Postfix decrement
            iterator tmp = *this;
            --(*this);
            return tmp;
        }

        iterator operator+(difference_type n) const { return iterator(m_ptr + n); }

        iterator operator-(difference_type n) const { return iterator(m_ptr - n); }

        difference_type operator-(const iterator& other) const { return m_ptr - other.m_ptr; }

        // Compound assignment
        iterator& operator+=(difference_type n)
        {
            m_ptr += n;
            return *this;
        }

        iterator& operator-=(difference_type n)
        {
            m_ptr -= n;
            return *this;
        }

        // Comparison operators (must be implemented for all iterators)
        bool operator==(const iterator& other) const { return m_ptr == other.m_ptr; }

        bool operator!=(const iterator& other) const { return m_ptr != other.m_ptr; }

        // Comparison for random access iterators
        bool operator<(const iterator& other) const { return m_ptr < other.m_ptr; }

        bool operator>(const iterator& other) const { return m_ptr > other.m_ptr; }

        bool operator<=(const iterator& other) const { return m_ptr <= other.m_ptr; }

        bool operator>=(const iterator& other) const { return m_ptr >= other.m_ptr; }

    private:
        T* m_ptr;
    };

private:
    struct ArrayImpl;
    ArrayImpl* m_impl;
};

template <typename T_>
extern MYLIBRARY_API bool operator==(const Array<T_>& lhs, const Array<T_>& rhs);

template <typename T>
bool operator!=(const Array<T>& lhs, const Array<T>& rhs) { return !(lhs == rhs); }

extern template MYLIBRARY_API class Array<int>;
extern template MYLIBRARY_API bool operator==(const Array<int>& lhs, const Array<int>& rhs);

extern template MYLIBRARY_API class Array<double>;
extern template MYLIBRARY_API bool operator==(const Array<double>& lhs, const Array<double>& rhs);

extern template MYLIBRARY_API class Array<Object>;

} // namespace mylibrary

#endif // MYLIBRARY_H
