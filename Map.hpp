#ifndef FT_MAP
#define FT_MAP

#include <memory>
#include <limits>
#include <functional> // less
#include <utility> // pair

namespace ft {

template < class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<std::pair<const Key,T> > >
class map {


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

	private:
    struct		Node {
        bool    red;
        Node    *parent;
        Node	*left;
        Node	*right;
        std::pair<const Key, T> *data;

		Node *max_node()
		{
			Node *tmp = this;
			while(tmp && tmp->right)
				tmp = tmp->right;
			return tmp;
		}

		Node *min_node()
		{
			Node *tmp = this;
			while(tmp && tmp->left)
				tmp = tmp->left;
			return tmp;
		}

		};

		Alloc _allocator;
		key_compare _comparator;
		size_t _size;
		Node *_root;

/************* 1. CONSTRUCTORS && DESTRUCTOR *************/
	public:
    explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
	{
		_allocator = alloc;
		_comparator = comp;
		_size = 0;
		_root = NULL;
	}

    template <class InputIterator>
    map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), 
	const allocator_type& alloc = allocator_type())
	{
		_allocator = alloc;
		_comparator = comp;
		_size = 0;
		_root = NULL;
		for (InputIterator it = first; it != last; it++)
			insert(*(it));
	}

    map (const map& x) 
	{
		_allocator = x._allocator;
		_comparator = x._comparator;
		_size = 0;
		_root = NULL;
		*this = x;
	}

    map& operator= (const map& x)
	{
		this->clear();
		this->insert(x.begin(), x.end());
		return *this;
	}

    ~map() { this->clear(); }


/************* 2. ITERATORS *************/

    iterator begin() { return Iterator(_root->min_node()); }
    const_iterator begin() const { return CIterator(_root->min_node()); } 
    iterator end()  { return Iterator(NULL); }
    const_iterator end() const { return CIterator(NULL); }
    reverse_iterator rbegin() { return RIterator(_root->max_node()); }
    const_reverse_iterator rbegin() const { return CRIterator(_root->max_node()); }
    reverse_iterator rend() { return RIterator(NULL); }
    const_reverse_iterator rend() const { return CRIterator(NULL); }



/************* 3. CAPACITY *************/

    bool empty() const { return (_size == 0 ? 1 : 0); }
    size_type size() const { return _size; }
    size_type max_size() const{ return (std::numeric_limits<size_type>::max() / sizeof(value_type)); }
    

/************* 4. ELEMENT ACCESS *************/
/* ищет по k и возвращает референс на связанное с этим k значение
** если не находит, то добавляет новый элемент с таким ключом и дефолтным значением и возвращает его
** в случае неудачи увеличивает размер на 1 */
mapped_type& operator[] (const key_type& k)
{
	
}


/************* 5. MODIFIERS *************/
    // insert single element если такой ключ уже есть, то не вставляется а возвращается итератор на существующий
    // элемент
private:
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

	Node *add_node(Node *cur, Node *parent, const value_type& val, bool &added)
	{
		if (!cur)
		{
			// std::cout << "adding " << val.first  << std::endl;
			added = 1;
			_size++;
			cur = new_node(val);
			cur->parent = parent;
			return cur;
		}
		if (cur->data->first == val.first)
			return cur;
		else if (_comparator(cur->data->first, val.first))
		{
			// std::cout << "try to add " << val.first  <<  " : " << cur->data->first << " ---> " << std::endl;
			cur->right = add_node(cur->right, cur, val, added);
		}
		else
		{
			// std::cout << "try to add " << val.first  <<  " : " << "  <--- " << cur->data->first << std::endl;
			cur->left = add_node(cur->left, cur, val, added);
		}
		return cur;
	}

	Node *find_node (const key_type& k)
	{
		Node *tmp = _root;
		while (tmp)
		{
			if(tmp->data->first == k)
				return (tmp);
			if (_comparator(tmp->data->first, k))
				tmp = tmp->right;
			else
				tmp = tmp->left;
		}
		return (NULL);
	}

public:
    std::pair<iterator,bool> insert (const value_type& val)
	{
		bool added = 0;
		_root = add_node(_root, NULL, val, added);
		return (std::make_pair(find(val.first), added));
	}

    // insert with hint позиция должна указывать на элемент предшествующий месту вставки, это просто подсказка для ускорения
    iterator insert (iterator position, const value_type& val)
	{
		bool added = 0;
		Node *tmp = find_node(*(position).first);
		if (_comparator(*(position).first, val.first))
			tmp = add_node(tmp, tmp->parent, val, added);
		else
			_root = add_node(_root, NULL, val, added);
		return find(val.first);
	}

    // range insert
    template <class InputIterator> 
    void insert (InputIterator first, InputIterator last)
	{
		for (InputIterator it = first; it != last; it++)
			insert(*(it));
	}

    //  удаляет либо на позиции, либо по ключу, либо диапазон
    // void erase (iterator position);
    // size_type erase (const key_type& k);
    // void erase (iterator first, iterator last);

    // void swap (map& x);

	void annihilate_node(Node *src)
	{
		if (!src)
			return;
		if (src->left)
			annihilate_node(src->left);
		if (src->right)
			annihilate_node(src->right);
		_allocator.destroy(src->data);
		_allocator.deallocate(src->data, 1);
		src->left = NULL;
		src->right = NULL;
		src->parent = NULL;
		delete src;
	}

    void clear() // removes all elements, leaving container size = 0
	{
		annihilate_node(_root);
		_root = NULL;
		_size = 0;
	}

// };

/************* 6. OBSERVERS *************/
// возвращает функцию, которая сравнивает ключи / объекты с ключами
key_compare key_comp() const { return _comparator; }
value_compare value_comp() const { return new ValueComp(_comparator); }

/************* 7. OPERATIONS *************/

iterator find (const key_type& k)
{
	Node *tmp = _root;
	while (tmp)
	{
		if(tmp->data->first == k)
			return (Iterator(tmp));
		if (_comparator(tmp->data->first, k))
			tmp = tmp->right;
		else
			tmp = tmp->left;
	}
	return (Iterator(NULL));
}

const_iterator find (const key_type& k) const
{
	Node *tmp = _root;
	while (tmp)
	{
		if(tmp->data->first == k)
			return (CIterator(tmp));
		if (_comparator(tmp->data->first, k))
			tmp = tmp->right;
		else
			tmp = tmp->left;
	}
	return (CIterator(NULL));
}

// возвращает 1 если элемент с таким ключом есть и 0 если нет
size_type count (const key_type& k) const
{
	if (this->find(k) == this->end())
		return 0;
	else
		return 1;
}

// нахождение ближайшего большего или точного ключа так чтоб ключ смог встать отсортированно
// ловер - чтоб ключ встал до, аппер - после
iterator lower_bound (const key_type& k)
{
	Node *tmp = _root;
	Node *result = _root;
	while (tmp)
	{
		if (_comparator(tmp->data->first, k))
			tmp = tmp->right;
		else
		{
			result = tmp;
			tmp = tmp->left;
		}
	}
	return iterator(result);
}
// const_iterator lower_bound (const key_type& k) const;
// iterator upper_bound (const key_type& k);
// const_iterator upper_bound (const key_type& k) const;

std::pair<const_iterator,const_iterator> equal_range (const key_type& k) const
{
	const_iterator it = this->find(k);
	return (std::make_pair(it, it));
}

std::pair<iterator,iterator>             equal_range (const key_type& k)
{
	iterator it = this->find(k);
	return (std::make_pair(it, it));
}


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

class Iterator {
private:
    Node * _current;
public:
    Iterator() { _current = NULL; }
    Iterator(Iterator const &src) { *this = src; }
    Iterator &operator=(Iterator const &src) { this->_current = src._current; return *this; }
    Iterator(Node * const ptr) { _current = ptr; }
    ~Iterator() {}

    reference operator*() { return *(_current->data); }
    Iterator &operator++()  // prefix
	{
		if (_current->right)
		{
			// std::cout << "!!! current " << _current->data->first << std::endl;
			_current = _current->right->min_node();
			// std::cout << "!!! current " << _current->data->first << std::endl;
		}
		else
		{
			// std::cout << "!!! current " << _current->data->first << std::endl;
			while (_current->parent && (_current->parent->left != _current))
				_current = _current->parent;
			_current = _current->parent;
			// std::cout << "!!! current " << _current->data->first << std::endl;
		}
		return *this;
	}

    Iterator &operator--() // prefix
	{
		// if (!_current)
		// 	_current = _root.max_node();
		if (_current->left)
			_current = _current->left->max_node();
		else
		{
			while (_current->parent && (_current->parent->right != _current))
				_current = _current->parent;
			_current = _current->parent;
		}
		return *this;
	}

    Iterator operator++(int) // postfix
	{ 
		Iterator tmp = *this; 
		if (_current->right)
			_current = _current->right->min_node();
		else
		{
			while (_current->parent && (_current->parent->left != _current))
				_current = _current->parent;
			_current = _current->parent;
		}
		return tmp; 
	}

    Iterator operator--(int) // postfix
	{ 
		Iterator tmp = *this;
		// if (!_current)
		// 	_current = _root.max_node();
		if (_current->left)
			_current = _current->left->max_node();
		else
		{
			while (_current->parent && (_current->parent->right != _current))
				_current = _current->parent;
			_current = _current->parent;
		}
		return tmp; 
	}

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

    const_reference operator*() { return *(_current->data); }
    CIterator &operator++()  // prefix
	{
		if (_current->right)
		{
			// std::cout << "!!! current " << _current->data->first << std::endl;
			_current = _current->right->min_node();
			// std::cout << "!!! current " << _current->data->first << std::endl;
		}
		else
		{
			// std::cout << "!!! current " << _current->data->first << std::endl;
			while (_current->parent && (_current->parent->left != _current))
				_current = _current->parent;
			_current = _current->parent;
			// std::cout << "!!! current " << _current->data->first << std::endl;
		}
		return *this;
	}

    CIterator &operator--() // prefix
	{
		// if (!_current)
		// 	_current = _root.max_node();
		if (_current->left)
			_current = _current->left->max_node();
		else
		{
			while (_current->parent && (_current->parent->right != _current))
				_current = _current->parent;
			_current = _current->parent;
		}
		return *this;
	}

    CIterator operator++(int) // postfix
	{ 
		CIterator tmp = *this; 
		if (_current->right)
			_current = _current->right->min_node();
		else
		{
			while (_current->parent && (_current->parent->left != _current))
				_current = _current->parent;
			_current = _current->parent;
		}
		return tmp; 
	}

    CIterator operator--(int) // postfix
	{ 
		CIterator tmp = *this;
		// if (!_current)
		// 	_current = _root.max_node();
		if (_current->left)
			_current = _current->left->max_node();
		else
		{
			while (_current->parent && (_current->parent->right != _current))
				_current = _current->parent;
			_current = _current->parent;
		}
		return tmp; 
	}
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

    reference operator*() { return *(_current->data); }
    RIterator &operator--()  // prefix
	{
		if (_current->right)
		{
			// std::cout << "!!! current " << _current->data->first << std::endl;
			_current = _current->right->min_node();
			// std::cout << "!!! current " << _current->data->first << std::endl;
		}
		else
		{
			// std::cout << "!!! current " << _current->data->first << std::endl;
			while (_current->parent && (_current->parent->left != _current))
				_current = _current->parent;
			_current = _current->parent;
			// std::cout << "!!! current " << _current->data->first << std::endl;
		}
		return *this;
	}

    RIterator &operator++() // prefix
	{
		// if (!_current)
		// 	_current = _root.max_node();
		if (_current->left)
			_current = _current->left->max_node();
		else
		{
			while (_current->parent && (_current->parent->right != _current))
				_current = _current->parent;
			_current = _current->parent;
		}
		return *this;
	}

    RIterator operator--(int) // postfix
	{ 
		RIterator tmp = *this; 
		if (_current->right)
			_current = _current->right->min_node();
		else
		{
			while (_current->parent && (_current->parent->left != _current))
				_current = _current->parent;
			_current = _current->parent;
		}
		return tmp; 
	}

    RIterator operator++(int) // postfix
	{ 
		RIterator tmp = *this;
		// if (!_current)
		// 	_current = _root.max_node();
		if (_current->left)
			_current = _current->left->max_node();
		else
		{
			while (_current->parent && (_current->parent->right != _current))
				_current = _current->parent;
			_current = _current->parent;
		}
		return tmp; 
	}
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

    const_reference operator*() { return *(_current->data); }
    CRIterator &operator--()  // prefix
	{
		if (_current->right)
		{
			// std::cout << "!!! current " << _current->data->first << std::endl;
			_current = _current->right->min_node();
			// std::cout << "!!! current " << _current->data->first << std::endl;
		}
		else
		{
			// std::cout << "!!! current " << _current->data->first << std::endl;
			while (_current->parent && (_current->parent->left != _current))
				_current = _current->parent;
			_current = _current->parent;
			// std::cout << "!!! current " << _current->data->first << std::endl;
		}
		return *this;
	}

    CRIterator &operator++() // prefix
	{
		// if (!_current)
		// 	_current = _root.max_node();
		if (_current->left)
			_current = _current->left->max_node();
		else
		{
			while (_current->parent && (_current->parent->right != _current))
				_current = _current->parent;
			_current = _current->parent;
		}
		return *this;
	}

    CRIterator operator--(int) // postfix
	{ 
		CRIterator tmp = *this; 
		if (_current->right)
			_current = _current->right->min_node();
		else
		{
			while (_current->parent && (_current->parent->left != _current))
				_current = _current->parent;
			_current = _current->parent;
		}
		return tmp; 
	}

    CRIterator operator++(int) // postfix
	{ 
		CRIterator tmp = *this;
		// if (!_current)
		// 	_current = _root.max_node();
		if (_current->left)
			_current = _current->left->max_node();
		else
		{
			while (_current->parent && (_current->parent->right != _current))
				_current = _current->parent;
			_current = _current->parent;
		}
		return tmp; 
	}
    bool operator==(CRIterator const &src) { return (this->_current == src._current); }
    bool operator!=(CRIterator const &src) { return (this->_current != src._current); }
};



}; // class bracket
} // namespace bracket

#endif