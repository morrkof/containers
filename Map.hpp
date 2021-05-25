#ifndef FT_MAP
#define FT_MAP

#include <memory>
#include <limits>
#include <functional> // less
#include <utility> // pair

namespace ft {

template < class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<std::pair<const Key,T> >
class Map {
private:
    struct		Node {
        bool    red;
        Node    *parent;
        Node	*left;
        Node	*right;
        std::pair<const Key, T> pair; };

		Alloc _allocator;
		size_t _size;
		Node *_head;
public:
    class Iterator;
    class CIterator;
    class RIterator;
    class CRIterator;

    typedef Key                             key_type;
    typedef T                               mapped_type;
    typedef pair<const Key, T>              value_type;
    typedef Compare                         key_compare;
    typedef ?                               value_compare;
    typedef Alloc                           allocator_type;
    typedef allocator_type::reference       reference;
    typedef allocator_type::const_reference const_reference;
	typedef allocator_type::pointer         pointer;
    typedef allocator_type::const_pointer   const_pointer;
    typedef Iterator                        iterator;
    typedef Iterator                        const_iterator;
    typedef RIterator                       reverse_iterator;
    typedef RIterator                       const_reverse_iterator;
    typedef ptrdiff_t                       difference_type;
    typedef size_t                          size_type;

/************* 1. CONSTRUCTORS && DESTRUCTOR *************/

    // explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type());

    // template <class InputIterator>
    // map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type());

    // map (const map& x) { *this = x; }

    // map& operator= (const map& x);

    // ~map();  // destructor




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
/* ищет по k и возвращает референс на связанное с этим k значение
** если не находит, то добавляет новый элемент с таким ключом и дефолтным значением и возвращает его
** в случае неудачи увеличивает размер на 1 */
// mapped_type& operator[] (const key_type& k);


/************* 5. MODIFIERS *************/
    // insert single element если такой ключ уже есть, то не вставляется а возвращается итератор на существующий
    // элемент
    // pair<iterator,bool> insert (const value_type& val);
    // insert with hint позиция должна указывать на элемент предшествующий месту вставки, это просто подсказка для ускорения
    // iterator insert (iterator position, const value_type& val);
    // range insert
    // template <class InputIterator> 
    // void insert (InputIterator first, InputIterator last);

    //  удаляет либо на позиции, либо по ключу, либо диапазон
    // void erase (iterator position);
    // size_type erase (const key_type& k);
    // void erase (iterator first, iterator last);

    // void swap (map& x);
    // void clear(); // removes all elements, leaving container size = 0

// };

/************* 6. OBSERVERS *************/

// key_compare key_comp() const;
// value_compare value_comp() const;

/************* 7. OPERATIONS *************/

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
    Node * _current;
public:
    Iterator() { _current = NULL; }
    Iterator(Iterator const &src) { *this = src; }
    Iterator &operator=(Iterator const &src) { this->_current = src._current; return *this; }
    Iterator(Node * const ptr) { _current = ptr; }
    ~Iterator() {}

    reference operator*() { return *(_current->value); }
    Iterator &operator++() { _current = _current->next; return *this; } // prefix
    Iterator &operator--() { _current = _current->prev; return *this; } // prefix
    Iterator operator++(int) { Iterator tmp = *this; _current = _current->next; return tmp; } // postfix
    Iterator operator--(int) { Iterator tmp = *this; _current = _current->prev; return tmp; } // postfix
    bool operator==(Iterator const &src) { return (this->_current == src._current); }
    bool operator!=(Iterator const &src) { return (this->_current != src._current); }
};

class CIterator {
private:
    Node * _current;
public:
    CIterator() { _current = NULL; }
    CIterator(CIterator const &src) { *this = src; }
    CIterator &operator=(CIterator const &src) { this->_current = src._current; return *this; }
    CIterator(Node * const ptr) { _current = ptr; }
    ~CIterator() {}

    const_reference operator*() { return *(_current->value); }
    CIterator &operator++() { _current = _current->next; return *this; } // prefix
    CIterator &operator--() {  _current = _current->prev; return *this; } // prefix
    CIterator operator++(int) { CIterator tmp = *this; _current = _current->next; return tmp; } // postfix
    CIterator operator--(int) { CIterator tmp = *this; _current = _current->prev; return tmp; } // postfix
    bool operator==(CIterator const &src) { return (this->_current == src._current); }
    bool operator!=(CIterator const &src) { return (this->_current != src._current); }
};

class RIterator {
private:
	Node * _current;
public:
    RIterator() { _current = NULL; }
    RIterator(RIterator const &src) { *this = src; }
    RIterator &operator=(RIterator const &src) { this->_current = src._current; return *this; }
    RIterator(Node * const ptr) { _current = ptr; }
    ~RIterator() {}

    reference operator*() { return *(_current->value); }
    RIterator &operator++() {  _current = _current->prev; return *this; } // prefix
    RIterator &operator--() {  _current = _current->next; return *this; } // prefix
    RIterator operator++(int) { RIterator tmp = *this; _current = _current->prev; return tmp; } // postfix
    RIterator operator--(int) { RIterator tmp = *this; _current = _current->next; return tmp; } // postfix
    bool operator==(RIterator const &src) { return (this->_current == src._current); }
    bool operator!=(RIterator const &src) { return (this->_current != src._current); }
};

class CRIterator {
private:
    Node * _current;
public:
    CRIterator() { _current = NULL; }
    CRIterator(CRIterator const &src) { *this = src; }
    CRIterator &operator=(CRIterator const &src) { this->_current = src._current; return *this; }
    CRIterator(Node * const ptr) { _current = ptr; }
    ~CRIterator() {}

    const_reference operator*() { return *(_current->value); }
    CRIterator &operator++() {  _current = _current->prev; return *this; } // prefix
    CRIterator &operator--() {  _current = _current->next; return *this; } // prefix
    CRIterator operator++(int) { CRIterator tmp = *this; _current = _current->prev; return tmp; } // postfix
    CRIterator operator--(int) { CRIterator tmp = *this; _current = _current->next; return tmp; } // postfix
    bool operator==(CRIterator const &src) { return (this->_current == src._current); }
    bool operator!=(CRIterator const &src) { return (this->_current != src._current); }
};



}; // class bracket
} // namespace bracket

#endif