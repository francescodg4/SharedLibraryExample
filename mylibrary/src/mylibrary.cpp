#include "mylibrary.h"
#include <vector>

namespace mylibrary {

template <typename T>
struct Array<T>::ArrayImpl {
    std::vector<T> values;
};

template <typename T>
Array<T>::Array()
    : m_impl(new ArrayImpl())
{
}

template <typename T>
Array<T>::Array(size_t count, const T& value)
    : m_impl(new ArrayImpl())
{
    m_impl->values = std::vector<T>(count, value);
}

template <typename T>
Array<T>::Array(std::initializer_list<T> init)
    : m_impl(new ArrayImpl())
{
    m_impl->values = std::vector<T>(init);
}

template <typename T>
Array<T>::Array(iterator first, iterator last)
    : m_impl(new ArrayImpl())
{
    m_impl->values = std::vector<T>(first, last);
}

template <typename T>
Array<T>::~Array()
{
    if (m_impl) {
        delete m_impl;
    }
}

template <typename T>
Array<T>::Array(Array& other)
    : m_impl(new ArrayImpl())
{
    m_impl->values = other.m_impl->values;
}

template <typename T>
Array<T>& Array<T>::operator=(Array& other)
{
    Array<T> tmp(other);
    std::swap(tmp.m_impl, m_impl);
    return *this;
}

template <typename T>
Array<T>::Array(Array&& other)
    : m_impl(nullptr)
{
    std::swap(m_impl, other.m_impl);
}

template <typename T>
Array<T>& Array<T>::operator=(Array&& other)
{
    Array<T> tmp(std::move(other));
    std::swap(tmp.m_impl, m_impl);
    return *this;
}

template <typename T>
size_t Array<T>::size() const { return m_impl->values.size(); }

template <typename T>
bool Array<T>::empty() const { return m_impl->values.empty(); }

template <typename T>
void Array<T>::push_back(const T& value) { m_impl->values.push_back(value); }

template <typename T>
void Array<T>::push_back(T&& value) { m_impl->values.push_back(value); }

template <typename T>
T& Array<T>::operator[](size_t pos) { return m_impl->values[pos]; }

template <typename T>
const T& Array<T>::operator[](size_t pos) const { return m_impl->values[pos]; }

template <typename T>
T& Array<T>::front() { return m_impl->values.front(); }

template <typename T>
const T& Array<T>::front() const { return m_impl->values.front(); }

template <typename T>
T& Array<T>::back() { return m_impl->values.back(); }

template <typename T>
const T& Array<T>::back() const { return m_impl->values.back(); }

template <typename T>
T* Array<T>::data() { return m_impl->values.data(); }

template <typename T>
const T* Array<T>::data() const { return m_impl->values.data(); }

template <typename T>
typename Array<T>::iterator Array<T>::begin() { return m_impl->values.data(); }

template <typename T>
typename Array<T>::iterator Array<T>::end() { return m_impl->values.data() + m_impl->values.size(); }

template <typename T>
typename Array<T>::iterator Array<T>::begin() const { return m_impl->values.data(); }

template <typename T>
typename Array<T>::iterator Array<T>::end() const { return m_impl->values.data() + m_impl->values.size(); }

template <typename T>
typename Array<T>::iterator Array<T>::insert(iterator pos, const T& value)
{
    auto dist = std::distance(this->begin(), pos);
    auto it_v = m_impl->values.insert(m_impl->values.begin() + dist, value);
    return this->begin() + std::distance(m_impl->values.begin(), it_v);
}

template <typename T>
typename Array<T>::iterator Array<T>::erase(iterator pos)
{
    auto dist = std::distance(this->begin(), pos);
    auto it_v = m_impl->values.erase(m_impl->values.begin() + dist);
    return this->begin() + std::distance(m_impl->values.begin(), it_v);
}

template <typename T>
typename Array<T>::iterator Array<T>::erase(iterator first, iterator last)
{
    auto first_offset = std::distance(this->begin(), first);
    auto last_offset = std::distance(this->begin(), last);

    auto it_v = m_impl->values.erase(m_impl->values.begin() + first_offset, m_impl->values.begin() + last_offset);

    return this->begin() + std::distance(m_impl->values.begin(), it_v);
}

template <typename T>
void Array<T>::assign(size_t count, const T& value) { m_impl->values.assign(count, value); }

template <typename T>
void Array<T>::assign(iterator first, iterator last) { m_impl->values.assign(first, last); }

template <typename T>
void Array<T>::assign(std::initializer_list<T> ilist) { m_impl->values.assign(ilist); }

template <typename T>
bool operator==(const Array<T>& lhs, const Array<T>& rhs) { return lhs.m_impl->values == rhs.m_impl->values; }

// Template instantiations
template class Array<int>;
template bool operator==(const Array<int>& lhs, const Array<int>& rhs);

template class Array<double>;
template bool operator==(const Array<double>& lhs, const Array<double>& rhs);

template class Array<Object>;

} // namespace mylibrary
