#ifndef FT_VECTOR
#define FT_VECTOR

#include <memory>
#include <limits>
#include <cstddef> // linux

namespace ft {

template <bool condition, typename Type>
struct EnableIf;
 
template <typename Type>
struct EnableIf<true, Type>
{ typedef Type type; };


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

    explicit vector (const allocator_type& alloc = allocator_type()) 
	{
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
    vector (InputIterator first, typename ft::EnableIf<!std::numeric_limits<InputIterator>::is_integer, 
	InputIterator>::type last, const allocator_type& alloc = allocator_type())
	{
		_allocator = alloc;
		size_type n = 0;
		for(InputIterator tmp = first; tmp != last; tmp++)
			n++;
		_data = _allocator.allocate(n);
		pointer tmp_data = _data;
		for(InputIterator tmp = first; tmp != last; tmp++)
		{
			_allocator.construct(tmp_data, *tmp);
			tmp_data++;
		}
		_size = n;
		_capacity = n;
	}

    vector (const vector& x) 
	{
		_data = NULL;
		*this = x; 
	}

    vector& operator= (const vector& x)
	{
		if (_data)
		{
			this->clear();
			_allocator.deallocate(_data, _capacity);
		}
		_data = _allocator.allocate(x._capacity);
		_capacity = x._capacity;
		_size = x._size;
		this->assign(x.begin(), x.end());
		return *this;

	}

    ~vector()
	{
		this->clear();
		_allocator.deallocate(_data, _capacity);
	}

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
				if ((n - _capacity) > _capacity)
					this->reserve(n);
				else
					this->reserve(_capacity * 2);
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
			throw std::out_of_range("!!! VECTOR OUT OF RANGE !!!");
		else
			return _data[n];
	}
    const_reference at (size_type n) const { return this->at(n); }
    reference front() { return _data[0]; }
    const_reference front() const { return _data[0]; }
    reference back() { return _data[_size - 1]; }
    const_reference back() const { return _data[_size - 1]; }

/************* 5. MODIFIERS *************/

/* Assign vector content (range version) */
    template <class InputIterator>
    void assign (InputIterator first, InputIterator last, 
	typename ft::EnableIf<!std::numeric_limits<InputIterator>::is_integer, InputIterator>::type = 0)
	{
		this->clear();
		this->insert(this->begin(), first, last);
	}

/* Assign vector content (fill version) */
    void assign (size_type n, const value_type& val)
	{
		this->clear();
		this->insert(this->begin(), n, val);
	}

/* Add element at the end */
	void push_back (const value_type& val)
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

/* Delete last element */
    void pop_back()
	{
		_allocator.destroy(&(this->back()));
		_size--;
	}

/* Insert elements (single) */
    iterator insert (iterator position, const value_type& val)
	{
		iterator result = position;
		if((_size + 1) <= _capacity)
		{
			if (_size)
			{
				Iterator it = this->end() - 1;
				Iterator it_end = Iterator(_data + _size);
				while(it != (position - 1))
				{
					_allocator.construct(&(*it_end), *it);
				 	_allocator.destroy(&(*it));
					 it--;
					 it_end--;
				}
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
			result = tmp;
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
		return result;
	}

/* Insert elements (fill) */
    void insert (iterator position, size_type n, const value_type& val)
	{
		if((_size + n) <= _capacity)
		{
			if (_size)
			{
				Iterator it = this->end() - 1;
				Iterator it_end = Iterator(_data + _size + n - 1);
				while (it != (position - 1))
				{
					_allocator.construct(&(*it_end), *it);
				 	_allocator.destroy(&(*it));
					 it--;
					 it_end--;
				}
			}
			for (size_type i = 0; i < n; i++ )
			{
				_allocator.construct(&(*position), val);
				position++;
				_size++;
			}
		}
		else if ((_size + n) > _capacity && _capacity)
		{
			T *newdata = NULL;
			if (n < _capacity)
				newdata = _allocator.allocate(_capacity * 2);
			else
				newdata = _allocator.allocate(_size + n);
			T *tmp = newdata;
			for (Iterator it = this->begin(); it != position; it++)
			{
				_allocator.construct(tmp, *it);
				_allocator.destroy(&(*it));
				tmp++;
			}
			for (size_type i = 0; i < n; i++ )
			{
				_allocator.construct(tmp, val);
				tmp++;
			}
			for (Iterator it = position; it != this->end(); it++)
			{
				_allocator.construct(tmp, *it);
				_allocator.destroy(&(*it));
				tmp++;
			}
			_allocator.deallocate(_data, _capacity);
			_data = newdata;
			_size = _size + n;
			if (n < _capacity)
				_capacity *= 2;
			else
				_capacity = _size;
		}
		else if (!_capacity)
			for (size_type i = 0; i < n; i++)
				this->push_back(val);
	}

/* Insert elements (range) */
    template <class InputIterator>
    void insert (iterator position, InputIterator first, InputIterator last, 
	typename ft::EnableIf<!std::numeric_limits<InputIterator>::is_integer, InputIterator>::type = 0)
	{
		size_type len = 0;
		for (InputIterator it = first; it != last; it++)
			len++;
		
		if((_size + len) <= _capacity)
		{
			if (_size)
			{
				Iterator it = this->end() - 1;
				Iterator it_end = Iterator(_data + _size + len - 1);
				while (it != (position - 1))
				{
					_allocator.construct(&(*it_end), *it);
				 	_allocator.destroy(&(*it));
					 it--;
					 it_end--;
				}
			}
			for (InputIterator it = first; it != last; it++)
			{
				_allocator.construct(&(*position), *it);
				position++;
				_size++;
			}
		}
		else if ((_size + len) > _capacity && _capacity)
		{
			T *newdata = _allocator.allocate(_capacity * 2);
			T *tmp = newdata;
			for (Iterator it = this->begin(); it != position; it++)
			{
				_allocator.construct(tmp, *it);
				_allocator.destroy(&(*it));
				tmp++;
			}
			for (InputIterator it = first; it != last; it++)
			{
				_allocator.construct(tmp, *it);
				tmp++;
			}
			for (Iterator it = position; it != this->end(); it++)
			{
				_allocator.construct(tmp, *it);
				_allocator.destroy(&(*it));
				tmp++;
			}
			_allocator.deallocate(_data, _capacity);
			_data = newdata;
			_size = _size + len;
			_capacity *= 2;
		}
		else if (!_capacity)
			for (InputIterator it = first; it != last; it++)
				this->push_back(*it);
	}

/* Erase elements (single) */
    iterator erase (iterator position)
	{
		_allocator.destroy(&(*position));
		for (iterator it = position + 1; it != this->end(); it++)
		{
			_allocator.construct(&(*it) - 1, *it);
			_allocator.destroy(&(*it));	
		}
		_size--;
		return position;
	}

/* Erase elements (range) */
    iterator erase (iterator first, iterator last)
	{
		size_type len = 0;
		for (iterator it = first; it != last; it++)
		{
			_allocator.destroy(&(*it));
			len++;
		}
		iterator tmp = first;
		for(iterator it = last; it != this->end(); it++)
		{
			_allocator.construct(&(*tmp), *it);
			_allocator.destroy(&(*it));
			tmp++;
		}
		_size -= len;
		return last;
	}

/* Swap content */
    void swap (vector& x)
	{
		vector tmp = *this;
		*this = x;
		x = tmp;
	}

/* Clear content */
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
    bool operator==(CIterator const &src) { return (this->_current == src._current); }
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

	template <class T, class Alloc>
	bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		if (lhs.size() != rhs.size()) 
			return false;
		typename ft::vector<T>::const_iterator it_lhs = lhs.begin();
		typename ft::vector<T>::const_iterator it_rhs = rhs.begin();
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
	bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return !(rhs == lhs);
	}

	template <class T, class Alloc>
	bool operator<  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		if (!lhs.size() || !rhs.size())
			return (lhs.size() < rhs.size());
		typename ft::vector<T>::const_iterator it_lhs = lhs.begin();
		typename ft::vector<T>::const_iterator it_rhs = rhs.begin();
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
	bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return (!(rhs < lhs));
	}

	template <class T, class Alloc>
	bool operator>  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return (rhs < lhs);
	}

	template <class T, class Alloc>
	bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return (!(lhs < rhs));
	}

	template <class T, class Alloc>
	void swap (vector<T,Alloc>& x, vector<T,Alloc>& y)
	{
		x.swap(y);
	}

} // namespace bracket

#endif