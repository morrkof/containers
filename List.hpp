#ifndef FT_LIST
#define FT_LIST

#include <memory>
#include <limits>

namespace ft {

template < class T, class Alloc = std::allocator<T> >
class list {

public:
    class Iterator;
    class RIterator;

    typedef T					value_type;
    typedef Alloc				allocator_type;
    typedef value_type&			reference;
    typedef const value_type&	const_reference;
	typedef  value_type*		pointer;
    typedef const value_type*	const_pointer;
    typedef Iterator            iterator;
    typedef Iterator            const_iterator;
    typedef RIterator           reverse_iterator;
    typedef RIterator           const_reverse_iterator;
    typedef ptrdiff_t			difference_type;
    typedef size_t				size_type;

    struct      Node {
        Node    *prev;
        Node	*next;
        T		value;
    };
	private:
		Node *head;
	
/************* 1. CONSTRUCTORS && DESTRUCTOR *************/

    // explicit list (const allocator_type& alloc = allocator_type()) { }

    // explicit list (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()); { }

    // template <class InputIterator>
    // list (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type()); // range constructor, including first excluding last

    // list (const list& x) { *this = x; } // copy constructor

    // ~list();  // destroy elements and deallocate capacity

    // list& operator= (const list& x);


/************* 2. ITERATORS *************/

    // iterator begin() {  }
    // const_iterator begin() const {  } 
    // iterator end()  {  }
    // const_iterator end() const {  }
    // reverse_iterator rbegin() {  }
    // const_reverse_iterator rbegin() const {  }
    // reverse_iterator rend() {  }
    // const_reverse_iterator rend() const {  }



/************* 3. CAPACITY *************/

    // bool empty() const { return (_size == 0 ? 1 : 0); }
    // size_type size() const { return _size; }
    // size_type max_size() const{ return (std::numeric_limits<size_type>::max() / sizeof(value_type)); }
    

/************* 4. ELEMENT ACCESS *************/

    // reference front() { return _data[0]; }
    // const_reference front() const { return _data[0]; }
    // reference back() { return _data[_size - 1]; }
    // const_reference back() const { return _data[_size - 1]; }


/************* 5. MODIFIERS *************/

    // template <class InputIterator>
    // void assign (InputIterator first, InputIterator last);	// replace content on range (destroy all old elements)

    // void assign (size_type n, const value_type& val); // replace content of n elements, each value is val
    // void push_front (const value_type& val);
    // void pop_front();
	// void push_back (const value_type& val); // add new element at the end, increase container size by 1
    // void pop_back(); // remove the last element, decrease size by 1
    // iterator insert (iterator position, const value_type& val); // insert new element before position
    // void insert (iterator position, size_type n, const value_type& val); // insert n elements before position

    // template <class InputIterator>
    // void insert (iterator position, InputIterator first, InputIterator last); // insert range elements before position

    // iterator erase (iterator position); // remove element on position
    // iterator erase (iterator first, iterator last); // remove range of elements
    // void swap (list& x); // swap content
    // void resize (size_type n, value_type val = value_type());
    // void clear(); // removes all elements, leaving container size = 0

// };


/************* 6. OPERATIONS *************/

    // void splice (iterator position, list& x); // transfer elements from list to list
    // void splice (iterator position, list& x, iterator i);
    // void splice (iterator position, list& x, iterator first, iterator last);

    // void remove (const value_type& val); // remove elements with specific value

    // template <class Predicate>
    // void remove_if (Predicate pred); // Remove elements fulfilling condition

    // void unique();

    // template <class BinaryPredicate>
    // void unique (BinaryPredicate binary_pred); // Remove duplicate values

    // void merge (list& x); // merge sorted list

    // template <class Compare>
    // void merge (list& x, Compare comp);

    // void sort();
	
    // template <class Compare>
    // void sort (Compare comp);

    // void reverse();



/************* 7. NON-MEMBER OVERLOADS *************/

// template <class T, class Alloc>
//   bool operator== (const list<T,Alloc>& lhs, const list<T,Alloc>& rhs); // comparing sizes, if match - comparing elements

// template <class T, class Alloc>
//   bool operator!= (const list<T,Alloc>& lhs, const list<T,Alloc>& rhs);

// template <class T, class Alloc>
//   bool operator<  (const list<T,Alloc>& lhs, const list<T,Alloc>& rhs); // lexicographical_compare 

// template <class T, class Alloc>
//   bool operator<= (const list<T,Alloc>& lhs, const list<T,Alloc>& rhs);

// template <class T, class Alloc>
//   bool operator>  (const list<T,Alloc>& lhs, const list<T,Alloc>& rhs);

// template <class T, class Alloc>
//   bool operator>= (const list<T,Alloc>& lhs, const list<T,Alloc>& rhs);

// template <class T, class Alloc>
//   void swap (list<T,Alloc>& x, list<T,Alloc>& y); // containers exchange references to their data, without copy or move elements


class Iterator {
private:
    T * _current;
public:
    Iterator() { _current = NULL; }
    Iterator(Iterator const &src) { *this = src; }
    Iterator &operator=(Iterator const &src) { this->_current = src._current; return *this; }
    Iterator(T * const ptr) { _current = ptr; }
    ~Iterator() {}

    reference operator*() { return *_current; }
    Iterator &operator++() { _current++; return *this; } // prefix
    Iterator &operator--() { _current--; return *this; } // prefix
    Iterator operator++(int) { Iterator tmp = *this; _current++; return tmp; } // postfix
    Iterator operator--(int) { Iterator tmp = *this; _current--; return tmp; } // postfix
    bool operator==(Iterator const &src) { return (this->_current == src._current); }
    bool operator!=(Iterator const &src) { return (this->_current != src._current); }
    bool operator<=(Iterator const &src) { return (this->_current <= src._current); }
    bool operator<(Iterator const &src) { return (this->_current < src._current); }
    bool operator>=(Iterator const &src) { return (this->_current >= src._current); }
    bool operator>(Iterator const &src) { return (this->_current > src._current); }

    Iterator &operator+(size_type n) { return (_current + n); }
    Iterator &operator+=(size_type n) { return (_current + n); }
    Iterator &operator-(size_type n) { return (_current - n); }
    Iterator &operator-=(size_type n) { return (_current - n); }
};

class RIterator {
public:
    T * _current;
    RIterator() { _current = NULL; }
    RIterator(RIterator const &src) { *this = src; }
    RIterator &operator=(RIterator const &src) { this->_current = src._current; return *this; }
    RIterator(T * const ptr) { _current = ptr; }
    ~RIterator() {}

    reference operator*() { return *_current; }
    RIterator &operator++() { _current--; return *this; } // prefix
    RIterator &operator--() { _current++; return *this; } // prefix
    RIterator operator++(int) { RIterator tmp = *this; _current--; return tmp; } // postfix
    RIterator operator--(int) { RIterator tmp = *this; _current++; return tmp; } // postfix
    bool operator==(RIterator const &src) { return (this->_current == src._current); }
    bool operator!=(RIterator const &src) { return (this->_current != src._current); }
    bool operator<=(RIterator const &src) { return (this->_current <= src._current); }
    bool operator<(RIterator const &src) { return (this->_current < src._current); }
    bool operator>=(RIterator const &src) { return (this->_current >= src._current); }
    bool operator>(RIterator const &src) { return (this->_current > src._current); }

    RIterator &operator+(size_type n) { return (_current - n); }
    RIterator &operator+=(size_type n) { return (_current - n); }
    RIterator &operator-(size_type n) { return (_current + n); }
    RIterator &operator-=(size_type n) { return (_current + n); }
};



}; // class bracket
} // namespace bracket

#endif