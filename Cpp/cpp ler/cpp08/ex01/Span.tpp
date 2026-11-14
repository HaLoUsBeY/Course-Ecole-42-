#ifndef SPAN_TPP
#define SPAN_TPP

template <typename Iterator>
void Span::addRange(Iterator first, Iterator last)
{
    std::size_t count = static_cast<std::size_t>(std::distance(first, last));

    // Hepsi sığmıyorsa hiçbirini ekleme
    if (numbers_.size() + count > max_)
        throw std::out_of_range("not enough space in Span for this range");
    numbers_.insert(numbers_.end(), first, last);
}

#endif
