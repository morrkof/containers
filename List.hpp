#ifndef FT_LIST
#define FT_LIST

#include <memory>
#include <limits>

namespace ft {

template < class T, class Alloc = std::allocator<T> >
class list {

private:
	struct		Node {
        Node    *prev;
        Node	*next;
        T		*value; };

		Alloc _allocator;
		size_t _size;
		Node *_head;


	void swap_nodes(Node *first, Node *second)
	{
		first->prev->next = second;
		second->next->prev = first;
		first->next = second->next;
		second->prev = first->prev;
		first->prev = second;
		second->next = first;
	}

public:
    class Iterator;
	class CIterator;
    class RIterator;
	class CRIterator;

    typedef T					value_type;
    typedef Alloc				allocator_type;
    typedef value_type&			reference;
    typedef const value_type&	const_reference;
	typedef  value_type*		pointer;
    typedef const value_type*	const_pointer;
    typedef Iterator            iterator;
    typedef CIterator           const_iterator;
    typedef RIterator           reverse_iterator;
    typedef CRIterator          const_reverse_iterator;
    typedef ptrdiff_t			difference_type;
    typedef size_t				size_type;
		
	
/************* 1. CONSTRUCTORS && DESTRUCTOR *************/

    explicit list (const allocator_type& alloc = allocator_type()) 
	{
		_allocator = alloc;
		_size = 0;
		_head = new Node;
		_head->prev = _head;
		_head->next = _head;
		_head->value = NULL;
	 }

    explicit list (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type())
	{
		_allocator = alloc;
		_head = new Node;
		Node *tmp = _head;
		for (size_type i = 0; i < n; i++)
		{
			tmp->next = new Node;
			tmp->next->next = _head;
			tmp->next->prev = tmp;
			tmp->next->value = _allocator.allocate(1);
			_allocator.construct(tmp->next->value, val);
			tmp = tmp->next;
		}
		_head->prev = tmp;
		_size = n;
	}

    template <class InputIterator>
    list (InputIterator first, typename ft::EnableIf<!std::numeric_limits<InputIterator>::is_integer, 
	InputIterator>::type last, const allocator_type& alloc = allocator_type())
	{
		_allocator = alloc;
		_head = new Node;
		Node *tmp = _head;
		size_type n = 0;
		for(InputIterator it = first; it != last; it++)
			n++;
		for(InputIterator it = first; it != last; it++)
		{
			tmp->next = new Node;
			tmp->next->next = _head;
			tmp->next->prev = tmp;
			tmp->next->value = _allocator.allocate(1);
			_allocator.construct(tmp->next->value, *it);
			tmp = tmp->next;
		}
		_head->prev = tmp;
		_size = n;
	}

    list (const list& x) 
	{ 
		_size = 0;
		_head = new Node;
		_head->prev = _head;
		_head->next = _head;
		_head->value = NULL;
		*this = x; 
	}

    list& operator= (const list& x) 
	{
		this->clear();
		this->assign(x.begin(), x.end());
		return *this;
	}

	~list()
	{
		this->clear();
		delete _head;
	}

/************* 2. ITERATORS *************/

    iterator begin() { return Iterator(_head->next); }
    const_iterator begin() const { return CIterator(_head->next); } 
    iterator end()  { return Iterator(_head); }
    const_iterator end() const { return CIterator(_head); }
    reverse_iterator rbegin() { return RIterator(_head->prev); }
    const_reverse_iterator rbegin() const { return CRIterator(_head->prev); }
    reverse_iterator rend() { return RIterator(_head); }
    const_reverse_iterator rend() const { return CRIterator(_head); }



/************* 3. CAPACITY *************/

    bool empty() const { return (_size == 0 ? 1 : 0); }
    size_type size() const { return _size; }
    size_type max_size() const{ return (std::numeric_limits<size_type>::max() / sizeof(value_type)); }
    

/************* 4. ELEMENT ACCESS *************/

    reference front() { return *(_head->next->value); }
    const_reference front() const { return *(_head->next->value); }
    reference back() { return *(_head->prev->value); }
    const_reference back() const { return *(_head->prev->value); }


/************* 5. MODIFIERS *************/

    template <class InputIterator>
    void assign (InputIterator first, InputIterator last, 
	typename ft::EnableIf<!std::numeric_limits<InputIterator>::is_integer, InputIterator>::type = 0)
	{
		// if (_head)
			this->clear();
		this->insert(this->begin(), first, last);
	}

    void assign (size_type n, const value_type& val)
	{
		// if (_head)
			this->clear();
		this->insert(this->begin(), n, val);
	}

    void push_front (const value_type& val)
	{
		Node *newnode = new Node;
		newnode->value = _allocator.allocate(1);
		_allocator.construct(newnode->value, val);
		newnode->next = _head->next;
		newnode->prev = _head;
		newnode->next->prev = newnode;
		_head->next = newnode;
		_size++;
	}

    void pop_front()
	{
		Node *tmp = _head->next;
		tmp->next->prev = _head;
		_head->next = tmp->next;
		_allocator.destroy(tmp->value);
		_allocator.deallocate(tmp->value, 1);
		delete tmp;
		_size--;
	}

	void push_back (const value_type& val)
	{
		Node *newnode = new Node;
		newnode->value = _allocator.allocate(1);
		_allocator.construct(newnode->value, val);
		newnode->next = _head;
		newnode->prev = _head->prev;
		newnode->prev->next = newnode;
		_head->prev = newnode;
		_size++;
	}

    void pop_back()
	{
		Node *tmp = _head->prev;
		tmp->prev->next = _head;
		_head->prev = tmp->prev;
		_allocator.destroy(tmp->value);
		_allocator.deallocate(tmp->value, 1);
		delete tmp;
		_size--;
	}
    iterator insert (iterator position, const value_type& val)
	{
		this->insert(position, 1, val);
		return position;
	}

    void insert (iterator position, size_type n, const value_type& val)
	{
		Node *pos = _head->next;
		for (Iterator it = this->begin(); it != position; it++)
			pos = pos->next;
		pos = pos->prev;
		Node *tail = pos->next;
		for (size_type i = 0; i < n; i++)
		{
			pos->next = new Node;
			pos->next->value = _allocator.allocate(1);
			_allocator.construct(pos->next->value, val);
			pos->next->prev = pos;
			pos = pos->next;
			_size++;
		}
		pos->next = tail;
		tail->prev = pos;
	}

    template <class InputIterator>
    void insert (iterator position, InputIterator first, InputIterator last, 
	typename ft::EnableIf<!std::numeric_limits<InputIterator>::is_integer, InputIterator>::type = 0)
	{
		Node *pos = _head->next;
		for (Iterator it = this->begin(); it != position; it++)
			pos = pos->next;
		pos = pos->prev;
		Node *tail = pos->next;
		for(InputIterator it = first; it != last; it++)
		{
			pos->next = new Node;
			pos->next->value = _allocator.allocate(1);
			_allocator.construct(pos->next->value, *it);
			pos->next->prev = pos;
			pos = pos->next;
			_size++;
		}
		pos->next = tail;
		tail->prev = pos;
	}

    iterator erase (iterator position)
	{
		Node *pos = _head->next;
		for (Iterator it = this->begin(); it != position; it++)
			pos = pos->next;
		position++;
		pos->next->prev = pos->prev;
		pos->prev->next = pos->next;
		_allocator.destroy(pos->value);
		_allocator.deallocate(pos->value, 1);
		delete pos;
		_size--;
		return position;
	}
    iterator erase (iterator first, iterator last)
	{
		size_type n = 0;
		Node *pos = _head->next;
		for (Iterator it = this->begin(); it != first; it++)
			pos = pos->next;
		for(iterator it = first; it != last; it++)
			n++;
		Node *front = pos->prev;
		for(size_type i = 0; i < n; i++)
		{
			Node *tmp = pos;
			pos = pos->next;
			_allocator.destroy(tmp->value);
			_allocator.deallocate(tmp->value, 1);
			delete tmp;
			_size--;
		}
		front->next = pos;
		pos->prev = front;
		return last;
	}
    void swap (list& x)
	{
		list tmp;
		tmp = *this;
		*this = x;
		x = tmp;
	}

    void resize (size_type n, value_type val = value_type())
	{
		if (n < _size)
		{
			for(size_type i = _size; i != n; i--)
				this->pop_back();
		}
		else if (n > _size)
		{
			for(size_type i = _size; i != n; i++)
				this->push_back(val);
		}
	}

    void clear()
	{
		Node *tmp = _head->next;
		while (tmp != _head)
		{
			_allocator.destroy(tmp->value);
			_allocator.deallocate(tmp->value, 1);
			tmp = tmp->next;
			delete tmp->prev;
			_size--;
		}
		_head->next =_head;
		_head->prev = _head;
	}

/************* 6. OPERATIONS *************/
// переносит элемент из х в наш контейнер на позицию, без конструкторов, тупо перенос, размер
// меняется у всех контейнеров. 1- переносит все, 2- переносит один, 3- переносит диапазон
// непонятно как менять размер у второго контейнера!!!1
    void splice (iterator position, list& x)
	{
		Node *pos = _head->next;
		for (Iterator it = this->begin(); it != position; it++)
			pos = pos->next;
		pos = pos->prev;
		Node *tail = pos->next;
		pos->next = x._head->next;
		x._head->next->prev = pos;
		x._head->prev->next = tail;
		tail->prev = x._head->prev;
		_size += x._size;
		x._size = 0;
		x._head->next = x._head;
		x._head->prev = x._head;
	}
    void splice (iterator position, list& x, iterator i)
	{
		Node *pos = _head->next;
		Node *src = x._head->next;
		for (Iterator it = this->begin(); it != position; it++)
			pos = pos->next;
		pos = pos->prev;
		Node *tail = pos->next;
		for (Iterator it = x.begin(); it != i; it++)
			src = src->next;
		src->prev->next = src->next;
		src->next->prev = src->prev;
		pos->next = src;
		src->next = tail;
		tail->prev = src;
		src->prev = pos;
		_size++;
		x._size--;
	}
    void splice (iterator position, list& x, iterator first, iterator last)
	{
		size_type len = 0;
		for (Iterator it = first; it != last; it++)
			len++;
		Node *pos = _head->next;
		Node *src_beg = x._head->next;
		Node *src_end = x._head->next;
		for (Iterator it = this->begin(); it != position; it++)
			pos = pos->next;
		pos = pos->prev;
		Node *tail = pos->next;
		for (Iterator it = x.begin(); it != first; it++)
			src_beg = src_beg->next;
		for (Iterator it = x.begin(); it != last; it++)
			src_end = src_end->next;
		src_end = src_end->prev;
		pos->next = src_beg;
		tail->prev = src_end;
		src_beg->prev->next = src_end->next;
		src_end->next->prev = src_beg->prev;
		src_beg->prev = pos;
		src_end->next = tail;
		_size += len;
		x._size -= len;
	}

// удаляет всё где валью = вал, вызывает деструктор и уменьшает размер
    void remove (const value_type& val)
	{
		for (Node *pos = _head->next; pos != _head; pos = pos->next)
		{
			Node *prev = pos->prev;
			if (*(pos->value) == val)
			{
				this->erase(iterator(pos));
				pos = prev;
			}
		}
	}

	
    template <class Predicate>
    void remove_if (Predicate pred)
	{
		for (Node *pos = _head->next; pos != _head; pos = pos->next)
		{
			Node *prev = pos->prev;
			if (pred(*(pos->value)))
			{
				this->erase(iterator(pos));
				pos = prev;
			}
		}
	}

	// в каждой группе одинаковых элементов удаляет всё кроме первого, сравнение по порядку с предшествующим
	// и сработает нормально только на отсортированном списке
	// как ремув, но если равняется
    void unique()
	{
		for (Node *pos = _head->next->next; pos != _head; pos = pos->next)
		{
			Node *prev = pos->prev;
			if (*(pos->value) == *(pos->prev->value))
			{
				this->erase(iterator(pos));
				pos = prev;
			}
		}
	}


	// сравнивает по два элемента через функцию и удаляет старший если она вернёт 1 (i , i-1) - удалит i
    template <class BinaryPredicate>
    void unique (BinaryPredicate binary_pred)
	{
		for (Node *pos = _head->next->next; pos != _head; pos = pos->next)
		{
			Node *prev = pos->prev;
			if (binary_pred(*(pos->value), *(pos->prev->value)))
			{
				this->erase(iterator(pos));
				pos = prev;
			}
		}
	}


	// сливает два упорядоченных списка в один, в первом увел размер, а во втором размер = 0
	// идти по первому, insert элементы из второго в нужные места	
    void merge (list& x)
	{
		for (Node *xpos = x._head->next; xpos != x._head; xpos = xpos->next)
		{
			Node *prev = xpos->prev;
			for (Node *pos = _head->next; pos != _head; pos = pos->next)
			{
				if (*(xpos->value) < *(pos->value))
				{
					this->insert(iterator(pos), *(xpos->value));
					x.erase(iterator(xpos));
					xpos = prev;
					break;
				}
				else if (pos->next == _head)
				{
					this->push_back(*(xpos->value));
					x.erase(iterator(xpos));
					xpos = prev;
					break;
				}
			}
		}
	}


	// то же самое, только элементы сравниваются через функцию
    template <class Compare>
    void merge (list& x, Compare comp)
	{
		for (Node *xpos = x._head->next; xpos != x._head; xpos = xpos->next)
		{
			Node *prev = xpos->prev;
			for (Node *pos = _head->next; pos != _head; pos = pos->next)
			{
				if (comp(*(xpos->value), *(pos->value)))
				{
					this->insert(iterator(pos), *(xpos->value));
					x.erase(iterator(xpos));
					xpos = prev;
					break;
				}
				else if (pos->next == _head)
				{
					this->push_back(*(xpos->value));
					x.erase(iterator(xpos));
					xpos = prev;
					break;
				}
			}
		}
	}

	

    void sort()
	{
		size_type flag = 1;
		while (flag)
		{
			flag = 0;
			Node *cur = _head->next;
			for (size_type i = 0; i < (_size -1); i++)
			{
				if (*(cur->next->value) < *(cur->value))
				{
					swap_nodes(cur, cur->next);
					flag = 1;
				}
				else
					cur = cur->next;
			}
		}
	}
	
    template <class Compare>
    void sort (Compare comp)
	{
		size_type flag = 1;
		while (flag)
		{
			flag = 0;
			Node *cur = _head->next;
			for (size_type i = 0; i < (_size -1); i++)
			{
				if (comp(*(cur->next->value), *(cur->value)))
				{
					swap_nodes(cur, cur->next);
					flag = 1;
				}
				else
					cur = cur->next;
			}
		}
	}

    void reverse()
	{
		Node *cur = _head->next;
		Node *tmp;
		for (size_type i = 0; i < _size; i++)
		{
			tmp = cur->next;
			cur->next = cur->prev;
			cur->prev = tmp;
			cur = tmp;
		}
		tmp = _head->next;
		_head->next = _head->prev;
		_head->prev = tmp;
	}


class Iterator {
public:
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


/************* 7. NON-MEMBER OVERLOADS *************/

template <class T, class Alloc>
  bool operator== (const list<T,Alloc>& lhs, const list<T,Alloc>& rhs)
  {
	  if (lhs.size() != rhs.size()) 
			return false;
	typename ft::list<T>::const_iterator it_lhs = lhs.begin();
	typename ft::list<T>::const_iterator it_rhs = rhs.begin();
	while (it_lhs != lhs.end() && it_rhs != rhs.end())
	{
		if(*it_lhs != *it_rhs)
			return false;
		it_lhs++;
		it_rhs++;
	}
	return true;
  }

template <class T, class Alloc>
  bool operator!= (const list<T,Alloc>& lhs, const list<T,Alloc>& rhs)
  {
	  return !(rhs == lhs);
  }

template <class T, class Alloc>
  bool operator<  (const list<T,Alloc>& lhs, const list<T,Alloc>& rhs)
  {
	if (!lhs.size() || !rhs.size())
		return (lhs.size() < rhs.size());
	typename ft::list<T>::const_iterator it_lhs = lhs.begin();
	typename ft::list<T>::const_iterator it_rhs = rhs.begin();
	while (it_lhs != lhs.end() && it_rhs != rhs.end())
	{
		if(*it_lhs < *it_rhs)
			return true;
		if(*it_lhs > *it_rhs)
			return false;
		it_lhs++;
		it_rhs++;
	}
	return false;
  }

template <class T, class Alloc>
  bool operator<= (const list<T,Alloc>& lhs, const list<T,Alloc>& rhs)
  {
	  return (!(rhs < lhs));
  }

template <class T, class Alloc>
  bool operator>  (const list<T,Alloc>& lhs, const list<T,Alloc>& rhs)
  {
	  return (rhs < lhs);
  }

template <class T, class Alloc>
  bool operator>= (const list<T,Alloc>& lhs, const list<T,Alloc>& rhs)
  {
	  return (!(lhs < rhs));
  }

template <class T, class Alloc>
  void swap (list<T,Alloc>& x, list<T,Alloc>& y)
  {
	  x.swap(y);
  }

} // namespace bracket

#endif