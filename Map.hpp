#ifndef FT_MAP
#define FT_MAP

#include <memory>
#include <limits>
#include <functional> // less
#include <utility> // pair

namespace ft {

template < class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<std::pair<const Key,T> > >
class map {
private:
    struct		Node {
        bool    red;
        Node    *parent;
        Node	*left;
        Node	*right;
        std::pair<const Key, T> *data; 
		};

		Alloc _allocator;
		Compare _comparator;
		size_t _size;
		Node *_root;

public:

    class Iterator;
    class CIterator;
    class RIterator;
    class CRIterator;
	class ValueComp;

    typedef Key                             key_type;
    typedef T                               mapped_type;
    typedef std::pair<const Key, T>         value_type;
    typedef Compare                         key_compare;
    typedef Alloc                           allocator_type;
    typedef value_type&						reference;
    typedef const value_type&				const_reference;
	typedef typename allocator_type::pointer         pointer;
    typedef typename allocator_type::const_pointer   const_pointer;
    typedef Iterator                        iterator;
    typedef CIterator                       const_iterator;
    typedef RIterator                       reverse_iterator;
    typedef CRIterator                      const_reverse_iterator;
    typedef ptrdiff_t                       difference_type;
    typedef size_t                          size_type;
	typedef	ValueComp						value_compare;

	class ValueComp
	{
		// friend class map;
		protected:
  			Compare comp;
			ValueComp (Compare c) : comp(c) {}  // constructed with map's comparison object
		public:
			typedef bool result_type;
			typedef value_type first_argument_type;
			typedef value_type second_argument_type;
			bool operator() (const value_type& x, const value_type& y) const  { return comp(x.first, y.first); }
	};


/************* 1. CONSTRUCTORS && DESTRUCTOR *************/

    explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
	{
		_allocator = alloc;
		_comparator = comp;
		_size = 0;
		_root = NULL;
	}

    // template <class InputIterator>
    // map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type());

    // map (const map& x) { *this = x; }

    // map& operator= (const map& x);

    // ~map();  // destructor




/************* 2. ITERATORS *************/
// бегин - первый элемент в порядке сортировки! 
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
    size_type size() const { return _size; }
    // size_type max_size() const{ return (std::numeric_limits<size_type>::max() / sizeof(value_type)); }
    

/************* 4. ELEMENT ACCESS *************/
/* ищет по k и возвращает референс на связанное с этим k значение
** если не находит, то добавляет новый элемент с таким ключом и дефолтным значением и возвращает его
** в случае неудачи увеличивает размер на 1 */
// mapped_type& operator[] (const key_type& k);


/************* 5. MODIFIERS *************/
    // insert single element если такой ключ уже есть, то не вставляется а возвращается итератор на существующий
    // элемент
	Node *new_node(const value_type& val)
	{
		Node *tmp = new Node;
		tmp->parent = NULL;
		tmp->left = NULL;
		tmp->right = NULL;
		tmp->red = 1;
		tmp->data = _allocator.allocate(1);
		_allocator.construct(tmp->data, val);
		return tmp;
	}

    std::pair<iterator,bool> insert (const value_type& val)
	{
		if (!_root)
		{
			_root = new_node(val);
			_size++;
			return (std::make_pair(iterator(_root), true));
		}
		return (std::make_pair(iterator(_root), true));
	}

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
// возвращает функцию, которая сравнивает ключи / объекты с ключами
// key_compare key_comp() const;
// value_compare value_comp() const;

/************* 7. OPERATIONS *************/
// ищет ключ и дделает итератор на найденное, если не найшлось возвращает итератор end 
// iterator find (const key_type& k);
// const_iterator find (const key_type& k) const;

// возвращает 1 если элемент с таким ключом есть и 0 если нет
// size_type count (const key_type& k) const;

// нахождение ближайшего большего или точного ключа так чтоб ключ смог встать отсортированно
// ловер - чтоб ключ встал до, аппер - после
// iterator lower_bound (const key_type& k);
// const_iterator lower_bound (const key_type& k) const;
// iterator upper_bound (const key_type& k);
// const_iterator upper_bound (const key_type& k) const;

// возвращает элемент? 
// pair<const_iterator,const_iterator> equal_range (const key_type& k) const;
// pair<iterator,iterator>             equal_range (const key_type& k);




class Iterator {
private:
    Node * _current;
public:
    Iterator() { _current = NULL; }
    Iterator(Iterator const &src) { *this = src; }
    Iterator &operator=(Iterator const &src) { this->_current = src._current; return *this; }
    Iterator(Node * const ptr) { _current = ptr; }
    ~Iterator() {}

    // reference operator*() { return *(_current->value); }
    // Iterator &operator++() { _current = _current->next; return *this; } // prefix
    // Iterator &operator--() { _current = _current->prev; return *this; } // prefix
    // Iterator operator++(int) { Iterator tmp = *this; _current = _current->next; return tmp; } // postfix
    // Iterator operator--(int) { Iterator tmp = *this; _current = _current->prev; return tmp; } // postfix
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

    // const_reference operator*() { return *(_current->value); }
    // CIterator &operator++() { _current = _current->next; return *this; } // prefix
    // CIterator &operator--() {  _current = _current->prev; return *this; } // prefix
    // CIterator operator++(int) { CIterator tmp = *this; _current = _current->next; return tmp; } // postfix
    // CIterator operator--(int) { CIterator tmp = *this; _current = _current->prev; return tmp; } // postfix
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

    // reference operator*() { return *(_current->value); }
    // RIterator &operator++() {  _current = _current->prev; return *this; } // prefix
    // RIterator &operator--() {  _current = _current->next; return *this; } // prefix
    // RIterator operator++(int) { RIterator tmp = *this; _current = _current->prev; return tmp; } // postfix
    // RIterator operator--(int) { RIterator tmp = *this; _current = _current->next; return tmp; } // postfix
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

    // const_reference operator*() { return *(_current->value); }
    // CRIterator &operator++() {  _current = _current->prev; return *this; } // prefix
    // CRIterator &operator--() {  _current = _current->next; return *this; } // prefix
    // CRIterator operator++(int) { CRIterator tmp = *this; _current = _current->prev; return tmp; } // postfix
    // CRIterator operator--(int) { CRIterator tmp = *this; _current = _current->next; return tmp; } // postfix
    bool operator==(CRIterator const &src) { return (this->_current == src._current); }
    bool operator!=(CRIterator const &src) { return (this->_current != src._current); }
};



}; // class bracket
} // namespace bracket

#endif