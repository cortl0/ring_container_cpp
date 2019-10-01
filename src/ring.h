//************************************************//
//                                                //
//  ring container C++                            //
//  created by Ilya Shishkin                      //
//  cortl@8iter.ru                                //
//  http://8iter.ru                               //
//  https://github.com/cortl0/ring_container_cpp  //
//  licensed by GPL v3.0                          //
//                                                //
//************************************************//

#ifndef RING_H
#define RING_H

#include <stdexcept>

template<class T>
class ring
{
    struct item
    {
        T *source;
        item *previous;
        item *next;
        item(T *source = nullptr) : source(source) {}
    };
public:
    class iterator
    {
        item *item_current;
    public:
        iterator(item *pointer = nullptr) : item_current(pointer) {}
        iterator(const iterator& other) : item_current(other.item_current) {}
        iterator operator++()
        {
            if(item_current != nullptr)
                item_current = item_current->next;
            return iterator(*this);
        }
        iterator operator--()
        {
            if(item_current != nullptr)
                item_current = item_current->previous;
            return iterator(*this);
        }
        iterator operator++(int)
        {
            iterator temp(*this);
            if(item_current != nullptr)
                item_current = item_current->next;
            return temp;
        }
        iterator operator--(int)
        {
            iterator temp(*this);
            if(item_current != nullptr)
                item_current = item_current->previous;
            return temp;
        }
        T& operator*() const { return *item_current->source; }
        friend class ring;
    };
private:
    iterator iterator_current = iterator();
    unsigned long long size = 0;
public:
    ~ring() { clear(); }
    void clear() { while(size) erase(); }
    iterator erase()
    {
        delete move();
        return iterator(iterator_current);
    }
    iterator get_iterator_current() { return iterator(iterator_current); }
    unsigned long long get_size() { return size; }
    iterator insert(T *source)
    {
        if (source == nullptr)
            throw std::runtime_error("ring.h: invalid source");
        item *temp = new item(source);
        if (size > 0)
        {
            temp->next = iterator_current.item_current;
            temp->previous = iterator_current.item_current->previous;
            iterator_current.item_current->previous->next = temp;
            iterator_current.item_current->previous = temp;
            iterator_current.item_current = temp;
        }
        else
        {
            iterator_current.item_current = temp;
            iterator_current.item_current->next = iterator_current.item_current;
            iterator_current.item_current->previous = iterator_current.item_current;
        }
        size++;
        return iterator(iterator_current);
    }
    iterator insert_next(T *source)
    {
        ++iterator_current;
        return insert(source);
    }
    T* move()
    {
        T *item_temp = nullptr;
        if (size > 1)
        {
            item_temp = iterator_current.item_current->source;
            iterator_current.item_current->next->previous = iterator_current.item_current->previous;
            iterator_current.item_current->previous->next = iterator_current.item_current->next;
            item *item_current_temp = iterator_current.item_current->next;
            delete iterator_current.item_current;
            iterator_current.item_current = item_current_temp;
            size--;
        }
        else if (size == 1)
        {
            item_temp = iterator_current.item_current->source;
            delete iterator_current.item_current;
            iterator_current.item_current = nullptr;
            size--;
        }
        else
            throw std::runtime_error("ring.h: moving from an empty container");
        return item_temp;
    }
};

#endif // RING_H
