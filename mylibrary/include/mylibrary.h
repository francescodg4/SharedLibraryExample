#ifndef MYLIBRARY_H
#define MYLIBRARY_H

#include <cstddef>
#include <iterator>
#include <vector>

namespace mylibrary {

struct Object {
    int a;
    int b;
};

template <typename T>
class Array {
public:
    using value_type = T;

    class iterator;
    using reverse_iterator = std::reverse_iterator<iterator>;

    Array();

    Array(size_t count, const T& value = T());

    Array(std::initializer_list<T> init);

    Array(iterator first, iterator last);

    ~Array();

    Array(Array&);

    Array& operator=(Array&);

    Array(Array&&);

    Array& operator=(Array&&);

    size_t size() const;

    bool empty() const;

    void push_back(const T& value);

    void push_back(T&& value);

    T& operator[](size_t pos);

    const T& operator[](size_t pos) const;

    T& front();

    const T& front() const;

    T& back();

    const T& back() const;

    T* data();

    const T* data() const;

    iterator begin() const;

    iterator begin();

    iterator end() const;

    iterator end();

    reverse_iterator rbegin() { return reverse_iterator(end()); }

    reverse_iterator rend() { return reverse_iterator(begin()); }

    iterator insert(iterator pos, const T& value);

    iterator erase(iterator pos);

    iterator erase(iterator first, iterator last);

    void assign(size_t count, const T& value);

    void assign(iterator first, iterator last);

    void assign(std::initializer_list<T> ilist);

    static Array<T> from(const std::vector<T>& in)
    {
        return Array<T>(const_cast<T*>(in.data()), const_cast<T*>(in.data() + in.size()));
    }

    std::vector<T> to_std_vector() const
    {
        return std::vector<T>(data(), data() + size());
    }

    template <typename T_>
    friend bool operator==(const Array<T_>& lhs, const Array<T_>& rhs);

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

template <typename T>
bool operator!=(const Array<T>& lhs, const Array<T>& rhs) { return !(lhs == rhs); }

extern template class Array<int>;
extern template class Array<double>;
extern template class Array<Object>;

} // namespace mylibrary

#endif // MYLIBRARY_H
