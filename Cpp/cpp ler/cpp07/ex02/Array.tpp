#ifndef ARRAY_TPP
#define ARRAY_TPP

template <typename T>
Array<T>::Array() : data_(NULL), size_(0)
{
}

template <typename T>
Array<T>::Array(unsigned int n) : data_(NULL), size_(n)
{
    // "()" ile her eleman varsayılan değeri alır (int için 0).
    if (n > 0)
        data_ = new T[n]();
}

template <typename T>
Array<T>::Array(const Array & other) : data_(NULL), size_(other.size_)
{
    // Derin kopya: kendi belleğimizi ayırıp elemanları tek tek kopyalarız.
    if (size_ > 0)
    {
        data_ = new T[size_];
        for (unsigned int i = 0; i < size_; i++)
            data_[i] = other.data_[i];
    }
}

template <typename T>
Array<T> & Array<T>::operator=(const Array & other)
{
    if (this != &other)
    {
        // Önce yeni bellek: new hata atarsa eski veri bozulmadan kalır.
        T * newData = NULL;
        if (other.size_ > 0)
        {
            newData = new T[other.size_];
            for (unsigned int i = 0; i < other.size_; i++)
                newData[i] = other.data_[i];
        }
        delete[] data_;
        data_ = newData;
        size_ = other.size_;
    }
    return *this;
}

template <typename T>
Array<T>::~Array()
{
    delete[] data_;
}

template <typename T>
T & Array<T>::operator[](unsigned int index)
{
    if (index >= size_)
        throw OutOfBoundsException();
    return data_[index];
}

template <typename T>
const T & Array<T>::operator[](unsigned int index) const
{
    if (index >= size_)
        throw OutOfBoundsException();
    return data_[index];
}

template <typename T>
unsigned int Array<T>::size() const
{
    return size_;
}

template <typename T>
const char * Array<T>::OutOfBoundsException::what() const throw()
{
    return "Array: index out of bounds";
}

#endif
