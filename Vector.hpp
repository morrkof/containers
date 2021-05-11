#ifndef FT_VECTOR
#define FT_VECTOR

#include <memory>
#include <limits>
#include <cstddef> // linux
#include <type_traits> // enable if

namespace ft {

template <class T, class Alloc = std::allocator<T> >
class vector {
private:
	T * _data;
	Alloc _allocator;
	size_t _capacity;
	size_t _size;



public:
    class Iterator;
    class CIterator;
    class RIterator;
    class CRIterator;

    typedef T			value_type;
    typedef Alloc		allocator_type;
    typedef T&			reference;
    typedef const T&	const_reference;
	typedef	T*			pointer;
    typedef const T*	const_pointer;
    typedef Iterator	iterator;
    typedef CIterator	const_iterator;
    typedef RIterator	reverse_iterator;
    typedef CRIterator	const_reverse_iterator;
    typedef ptrdiff_t	difference_type;
    typedef size_t		size_type;

/************* 1. CONSTRUCTORS && DESTRUCTOR *************/

    explicit vector (const allocator_type& alloc = allocator_type()) {
      _allocator = alloc;
      _data = NULL;
      _size = 0;
      _capacity = 0;
    }

    explicit vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()) 
	{
      _allocator = alloc;
      _data = _allocator.allocate(n);
      pointer tmp = _data;
      for(size_type i = 0; i < n; i++)
      {
          _allocator.construct(tmp, val);
          tmp++;
      }
      _size = n;
      _capacity = n;
    }

    template <class InputIterator>
    vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(),
	typename std::enable_if<!std::numeric_limits<InputIterator>::is_specialized>::type* = NULL)
	{
		
		_allocator = alloc;
		size_type n = 0;
		for(iterator tmp = first; tmp != last; tmp++)
			n++;
		_data = _allocator.allocate(n);
		pointer tmp_data = _data;
		for(iterator tmp = first; tmp != last; tmp++)
		{
			_allocator.construct(tmp_data, *tmp);
			tmp_data++;
		}
		_size = n;
		_capacity = n;
	}

    vector (const vector& x) { *this = x; }

    ~vector()
	{
		this->clear();
		_allocator.deallocate(_data, _capacity);
	}

//  замещает содержимое текущего вектора копией вектора х
    // vector& operator= (const vector& x)
	// {
	// 	// аллокатор нужен новый, перенести в него элементы
	// }




/************* 2. ITERATORS *************/

    iterator begin() { return Iterator(_data); }
    const_iterator begin() const { return CIterator(_data); } 
    iterator end()  { return Iterator(_data + _size); }
    const_iterator end() const { return CIterator(_data + _size); }
    reverse_iterator rbegin() { return RIterator(_data + _size - 1); }
    const_reverse_iterator rbegin() const { return CRIterator(_data + _size - 1); }
    reverse_iterator rend() { return RIterator(_data - 1); }
    const_reverse_iterator rend() const { return CRIterator(_data - 1); }



/************* 3. CAPACITY *************/

    size_type size() const { return _size; }
	size_type max_size() const{ return (std::numeric_limits<size_type>::max() / sizeof(value_type)); }
    
	void resize (size_type n, value_type val = value_type())
	{
		if (n < _size)
		{
			for(size_type i = _size; i != n; i--)
				this->pop_back();
		}
		else if (n > _size)
		{
			if (n <= _capacity)
				for(size_type i = _size; i != n; i++)
					this->push_back(val);
			else
			{
				this->reserve(n);
				for(size_type i = _size; i != n; i++)
				{
					_allocator.construct(_data + i, val);
					_size++;
				}
			}
		}
	}

    size_type capacity() const { return _capacity; }
    bool empty() const { return (_size == 0 ? 1 : 0); }

    void reserve (size_type n)
	{
		if (n > _capacity)
		{
			T *newdata = _allocator.allocate(n);
			for(size_type i = 0; i < _size; i++) 
				_allocator.construct(newdata + i, _data[i]);
			for(size_type i = 0; i < _capacity; i++)
					_allocator.destroy(_data + i);
			_allocator.deallocate(_data, _capacity);
			_data = newdata;
			_capacity = n;
		}
	}


/************* 4. ELEMENT ACCESS *************/

    reference operator[] (size_type n) { return _data[n]; }
    const_reference operator[] (size_type n) const { return _data[n]; }
    reference at (size_type n)
	{
		if(n < 0 || n > _size)
			throw std::out_of_range("!!! OUT OF RANGE !!!");
		else
			return _data[n];
	}
    const_reference at (size_type n) const { return this->at(n); }
    reference front() { return _data[0]; }
    const_reference front() const { return _data[0]; }
    reference back() { return _data[_size - 1]; }
    const_reference back() const { return _data[_size - 1]; }





/************* 5. MODIFIERS *************/

//  эквивалентно clear + insert(begin, first, last)
//     template <class InputIterator>
//     void assign (InputIterator first, InputIterator last);	// replace content on range (destroy all old elements)

//  эквивалентно clear + insert(begin, n, u)
//     void assign (size_type n, const value_type& val); // replace content of n elements, each value is val

	void push_back (const value_type& val) // add new element at the end, increase container size by 1
    {
    	if (_size < _capacity)
    	{
        	_allocator.construct(_data + _size, val);
        	_size++;
        	return;
      	}
      	else if (_capacity)
      	{
        	T *newdata = _allocator.allocate(_capacity * 2);
        	for(size_type i = 0; i < _capacity; i++) {
				_allocator.construct(newdata + i, _data[i]);
        	}
			_allocator.construct(newdata +_capacity, val);
			_size++;
			for(size_type i = 0; i < _capacity; i++) {
				_allocator.destroy(_data + i);
			}
			_allocator.deallocate(_data, _capacity);
			_data = newdata;
			_capacity *= 2;
    	}
		else
		{
			T *newdata = _allocator.allocate(1);
			_allocator.construct(newdata, val);
			_data = newdata;
			_capacity = 1;
			_size++;
		}
    }

    void pop_back()
	{
		_allocator.destroy(&(this->back()));
		_size--;
	}

    iterator insert (iterator position, const value_type& val)
	{
		if((_size + 1) <= _capacity)
		{
			for (Iterator it = Iterator(_data + _size); it != position - 1; it--)
			{
				_allocator.construct(&(*it), *(it - 1));
				_allocator.destroy(&(*(it - 1)));
			}
			_allocator.construct(&(*position), val);
			_size++;
		}
		else if ((_size + 1) > _capacity && _capacity)
		{
			T *newdata = _allocator.allocate(_capacity * 2);
			
			T *tmp = newdata;
			for (Iterator it = this->begin(); it != position; it++)
			{
				_allocator.construct(tmp, *it);
				_allocator.destroy(&(*it));
				tmp++;
			}
			_allocator.construct(tmp, val);
			tmp++;
			for (Iterator it = position; it != this->end(); it++)
			{
				_allocator.construct(tmp, *it);
				_allocator.destroy(&(*it));
				tmp++;
			}
			_allocator.deallocate(_data, _capacity);
			_data = newdata;
			_size++;
			_capacity *= 2;
		}
		else if (!_capacity)
			this->push_back(val);
		
		
		return position;
	}

//  вставляет n элементов начиная с позиции
//     void insert (iterator position, size_type n, const value_type& val); // insert n elements before position

//  вставляет диапазон элементов начиная с позиции
//     template <class InputIterator>
//     void insert (iterator position, InputIterator first, InputIterator last); // insert range elements before position

//  удаляет элемент на позиции, возвращает итератор на следующий после удалённым элемент, либо end если удалили последний
    // iterator erase (iterator position)
	// {

	// }

// удаляет диапазон элементов, возвращает то же
    // iterator erase (iterator first, iterator last)
	// {

	// }

    // void swap (vector& x)
	// {

	// }

    void clear()
	{
		pointer tmp = _data;
		for(size_type i = 0; i < _size; i++)
		{
			_allocator.destroy(tmp);
			tmp++;
		}
		_size = 0;
	}


// TODO!! сделать остальные итераторы наследниками
class Iterator {
private:
    pointer _current;
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

    Iterator operator+(size_type n) const { return Iterator(_current + n); }
    Iterator &operator+=(size_type n)  { return Iterator(_current + n); }
    Iterator operator-(size_type n) const { return Iterator(_current - n); }
    Iterator &operator-=(size_type n) { return Iterator(_current - n); }
};

class CIterator {
private:
    const_pointer _current;
public:
    CIterator() { _current = NULL; }
    CIterator(CIterator const &src) { *this = src; }
    CIterator &operator=(CIterator const &src) { this->_current = src._current; return *this; }
    CIterator(T * const ptr) { _current = ptr; }
    ~CIterator() {}

    const_reference operator*() { return *_current; }
    CIterator &operator++() { _current++; return *this; } // prefix
    CIterator &operator--() { _current--; return *this; } // prefix
    CIterator operator++(int) { CIterator tmp = *this; _current++; return tmp; } // postfix
    CIterator operator--(int) { CIterator tmp = *this; _current--; return tmp; } // postfix
    bool operator==(CIterator const &src) { return (this->_current == src._current); } // friend?
    bool operator!=(CIterator const &src) { return (this->_current != src._current); }
    bool operator<=(CIterator const &src) { return (this->_current <= src._current); }
    bool operator<(CIterator const &src) { return (this->_current < src._current); }
    bool operator>=(CIterator const &src) { return (this->_current >= src._current); }
    bool operator>(CIterator const &src) { return (this->_current > src._current); }

    CIterator &operator+(size_type n) { return (_current + n); }
    CIterator &operator+=(size_type n) { return (_current + n); }
    CIterator &operator-(size_type n) { return (_current - n); }
    CIterator &operator-=(size_type n) { return (_current - n); }
};

class RIterator {
private:
    pointer _current;
public:
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

class CRIterator {
private:
    const_pointer _current;
public:
    CRIterator() { _current = NULL; }
    CRIterator(CRIterator const &src) { *this = src; }
    CRIterator &operator=(CRIterator const &src) { this->_current = src._current; return *this; }
    CRIterator(T * const ptr) { _current = ptr; }
    ~CRIterator() {}

    const_reference operator*() { return *_current; }
    CRIterator &operator++() { _current--; return *this; } // prefix
    CRIterator &operator--() { _current++; return *this; } // prefix
    CRIterator operator++(int) { CRIterator tmp = *this; _current--; return tmp; } // postfix
    CRIterator operator--(int) { CRIterator tmp = *this; _current++; return tmp; } // postfix
    bool operator==(CRIterator const &src) { return (this->_current == src._current); }
    bool operator!=(CRIterator const &src) { return (this->_current != src._current); }
    bool operator<=(CRIterator const &src) { return (this->_current <= src._current); }
    bool operator<(CRIterator const &src) { return (this->_current < src._current); }
    bool operator>=(CRIterator const &src) { return (this->_current >= src._current); }
    bool operator>(CRIterator const &src) { return (this->_current > src._current); }

    CRIterator &operator+(size_type n) { return (_current - n); }
    CRIterator &operator+=(size_type n) { return (_current - n); }
    CRIterator &operator-(size_type n) { return (_current + n); }
    CRIterator &operator-=(size_type n) { return (_current + n); }
};

}; // class bracket

/************* 6. NON-MEMBER OVERLOADS *************/

// template <class T, class Alloc>
//   bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs); // comparing sizes, if match - comparing elements

// template <class T, class Alloc>
//   bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);

// template <class T, class Alloc>
//   bool operator<  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs); // lexicographical_compare 

// template <class T, class Alloc>
//   bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);

// template <class T, class Alloc>
//   bool operator>  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);

// template <class T, class Alloc>
//   bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);

// template <class T, class Alloc>
//   void swap (vector<T,Alloc>& x, vector<T,Alloc>& y); // containers exchange references to their data, without copy or move elements


} // namespace bracket

#endif