#ifndef _D_LIST_H
#define _D_LIST_H

#include <iterator>
#include <memory>
#include <iostream>

namespace container {

template<class T>
class list {
private:
    struct node_t;
    
public:
    struct forward_iterator {
        using value_type = T;
        using reference = T&;
        using pointer = T*;
        using difference_type = ptrdiff_t;
        using iterator_category = std::forward_iterator_tag;

        forward_iterator(node_t* ptr) : ptr_(ptr) {};
        T& operator*();
        forward_iterator& operator++();
        forward_iterator operator++(int);
        bool operator==(const forward_iterator& it) const;
        bool operator!=(const forward_iterator& it) const;
        private:
            node_t* ptr_;
            friend list;
    };

    forward_iterator begin();
    forward_iterator end();
    void push(const T& value);
    void insert(const forward_iterator& it, const T& value);
    void insert(const int& pos, const T& value);
    void erase(const forward_iterator& it);
    void erase(int pos);
    void popFront();
    void printTail();
    list() = default;
    list(const list&) = delete;
    T operator[](int pos);

private:
    struct node_t {
        T value;
        std::unique_ptr<node_t> nextNode = nullptr;
        forward_iterator next();
        node_t(const T& value, std::unique_ptr<node_t> next) : value(value), nextNode(std::move(next)) {};
    };   
    std::unique_ptr<node_t> head = nullptr;
    node_t* tail = nullptr;
    list& operator=(const list&);
};

template<class T>
typename list<T>::forward_iterator list<T>::node_t::next() {
    return nextNode.get();
}

template<class T>
T& list<T>::forward_iterator::operator*() {
    return ptr_->value;
}

template<class T>
typename list<T>::forward_iterator& list<T>::forward_iterator::operator++() {
    *this = ptr_->next();
    return *this;
}

template<class T>
typename list<T>::forward_iterator list<T>::forward_iterator::operator++(int) {
    forward_iterator old = *this;
    ++*this;
    return old;
}

template<class T>
bool list<T>::forward_iterator::operator!=(const forward_iterator& it) const {
    return ptr_ != it.ptr_;
}

template<class T>
bool list<T>::forward_iterator::operator==(const forward_iterator& it) const {
    return ptr_ == it.ptr_;
}

template<class T>
typename list<T>::forward_iterator list<T>::begin() {
    return head.get();
}

template<class T>
typename list<T>::forward_iterator list<T>::end() {
    return nullptr;
}

template<class T>
void list<T>::push(const T& value) {
    insert(this->begin(), value);
}

template<class T>
void list<T>::insert(const forward_iterator& it, const T& value) {
    std::unique_ptr<node_t> newNode(new node_t(value, nullptr));
    if (head == nullptr) {
        head = std::move(newNode);
    } else if (head->nextNode == nullptr) {
        if (it.ptr_) {
            tail = head.get();
            newNode->nextNode = std::move(head);
            head = std::move(newNode);
        } else {
            tail = newNode.get();
            head->nextNode = std::move(newNode);
        }
    } else if (head.get() == it.ptr_) {
        newNode->nextNode = std::move(head);
        head = std::move(newNode);
    } else if (it.ptr_ == nullptr) {
        tail->nextNode = std::move(newNode);
        tail = newNode.get();
    } else {
        auto temp = this->begin();
        while (temp.ptr_->next() != it.ptr_) {
            ++temp;
        }
        
        newNode->nextNode = std::move(temp.ptr_->nextNode);
        temp.ptr_->nextNode = std::move(newNode);
    }
}

template<class T>
void list<T>::insert(const int& pos, const T& value) {
    int i = 0;
    auto temp = this->begin();
    if (pos == 0) {
        insert(temp, value);
        return;
    }
    while(i < pos) {
        if (temp.ptr_ == nullptr) {
            break;
        }
        ++temp;
        ++i;
    }
    if (i < pos) {
        throw std::logic_error("Out of bounds");
    }
    this->insert(temp, value);
}

template<class T>
void list<T>::popFront() {
    if (list<T>::head == nullptr) {
        throw std::logic_error("no elements");
    }
    erase(list<T>::begin());
}

template<class T>
void list<T>::erase(const forward_iterator& it) {
    if (it == nullptr) {
        throw std::logic_error("Invalid iterator");
    }
    if(head == nullptr) {
        throw std::logic_error("Deleting from empty list");
    }
    if (it == this->begin()) {
        head = std::move(head->nextNode);
    } else {
        auto temp = this->begin();
        while(temp.ptr_->next() != it.ptr_) {
            ++temp;
        }
        temp.ptr_->nextNode = std::move(it.ptr_->nextNode);
    }
}

template<class T>
void list<T>::erase(int pos) {
    auto temp = this->begin();
    int i = 0;
    while (i < pos) {
        if(temp.ptr_ == nullptr) {
            break;
        }
        ++temp;
        ++i;
    }
    if (temp.ptr_ == nullptr) {
        throw std::logic_error("Out of bounds");
    }
}

template<class T>
T list<T>::operator[](int pos) { 
    auto temp = this->begin();
    int i = 0;
    while (i < pos) {
        if (temp.ptr_ == nullptr) {
            break;
        }
        ++temp;
        ++i;
    }
    if (temp.ptr_ == nullptr) {
        throw std::logic_error("Out of bounds");
    } else {
        return temp.ptr_->value;
    }
}

}

#endif
