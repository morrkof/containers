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

    typedef Key										key_type;
    typedef T										mapped_type;
    typedef std::pair<const Key, T>					value_type;
    typedef Compare									key_compare;
    typedef Alloc									allocator_type;
    typedef value_type&								reference;
    typedef const value_type&						const_reference;
	typedef typename allocator_type::pointer		pointer;
    typedef typename allocator_type::const_pointer	const_pointer;
    typedef Iterator								iterator;
    typedef CIterator								const_iterator;
    typedef RIterator								reverse_iterator;
    typedef CRIterator								const_reverse_iterator;
    typedef ptrdiff_t								difference_type;
    typedef size_t									size_type;
	typedef	ValueComp								value_compare;

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
		value_compare _vcomporator;
		size_t _size;
		Node *_root;

/* support functions */

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
			added = 1;
			_size++;
			cur = new_node(val);
			cur->parent = parent;
			return cur;
		}
		if (cur->data->first == val.first)
			return cur;
		else if (_comparator(cur->data->first, val.first))
			cur->right = add_node(cur->right, cur, val, added);
		else
			cur->left = add_node(cur->left, cur, val, added);
		cur = balance(cur);
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

	Node *rotate_left(Node *top) // когда красный справа
	{
		Node *child = top->right;
		top->right = child->left;
		if (top->right)
			top->right->parent = top;
		child->left = top;
		child->parent = top->parent;
		top->parent = child;
		if (child->parent)
		{
			if (child->parent->left == top)
				child->parent->left = child;
			else
				child->parent->right = child;
		}
		child->red = child->left->red;
		child->left->red = 1;
		return child;
	}

	Node *rotate_right(Node *top) // когда два красных один за другим
	{
		Node *child = top->left;
		top->left = child->right;
		if (top->left)
			top->left->parent = top;
		child->right = top;
		child->parent = top->parent;
		top->parent = child;
		if (child->parent)
		{
			if (child->parent->left == top)
				child->parent->left = child;
			else
				child->parent->right = child;
		}
		else _root = child;
		child->red = child->right->red;
		child->right->red = 1;
		return child;
	}

	void	color_flip(Node *src) // когда два красных ребёнка у одного родителя
	{
		if (src->left && src->right && 
		((src->left->red && src->right->red && !src->red) ||
		(!src->left->red && !src->right->red && src->red)))
		{
			src->red = !src->red;
			src->left->red = !src->left->red;
			src->right->red = !src->right->red;
		}
	}

	Node *balance(Node *src)
	{
		if (src->right && src->right->red)
			src = rotate_left(src);
		if (src->left && src->left->red && src->left->left && src->left->left->red)
			src = rotate_right(src);
		if (src->left && src->left->red && src->right && src->right->red)
			color_flip(src);
		return src;
	}

	Node *move_right(Node *src)
	{
		color_flip(src);
		if (src->left && src->left->left && src->left->left->red)
		{
			src = rotate_right(src);
			color_flip(src);
		}
		return src;
	}

	Node *move_left(Node *src)
	{
		color_flip(src);
		if (src->right && src->right->left && src->right->left->red)
		{
			src->right = rotate_right(src->right);
			src = rotate_left(src);
			color_flip(src);
		}
		return src;
	}

	void kill_node(Node *src)
	{
		_allocator.destroy(src->data);
		_allocator.deallocate(src->data, 1);
		
		if (src->parent)
		{
			if (src->parent->left == src)
				src->parent->left = NULL;
			else
				src->parent->right = NULL;
		}
		src->parent = NULL;
		src->left = NULL;
		src->right = NULL;
		delete src;
		_size--;
		src = NULL;
	}

	Node *delete_min(Node *src)
	{
		if (!src->left)
		{
			Node *tmp = NULL;
			if (src->right && !src->left)
			{
				tmp = src->right;
				src->right->parent = src->parent;
			}
			kill_node(src);
			return tmp;
		}
		if (!src->left->red && src->left->left && !src->left->left->red)
			src = move_left(src);
		src->left = delete_min(src->left);
		return balance(src);
	}

	Node *delete_node(Node *src, const key_type& k)
	{
		if (!src)
			return NULL;
		if (_comparator(k, src->data->first) && src->left)
		{
			if (!src->left->red && src->left->left && !src->left->left->red)
				src = move_left(src);
			src->left = delete_node(src->left, k);
		}
		else
		{
			if (src->left && src->left->red)
				src = rotate_right(src);
			if (src->data->first == k && !src->right)
			{
				Node *tmp = NULL;
				if (src->left && !src->right)
				{
					tmp = src->left;
					src->left->parent = src->parent;
				}
				kill_node(src);
				return tmp;
			}
			if (src->right && !src->right->red && src->right->left && !src->right->left->red)
				src = move_right(src);
			if (src->data->first == k && src->right)
			{
				std::pair<const Key, T> *tmp_pair = (src->right->min_node())->data;
				(src->right->min_node())->data = src->data;
				src->data = tmp_pair;
				src->right = delete_min(src->right);
			}
			else
				src->right = delete_node(src->right, k);
		}
		return balance(src);
	}

	void annihilate_node(Node *src)
	{
		if (!src)
			return;
		if (src->left)
			annihilate_node(src->left);
		if (src->right)
			annihilate_node(src->right);
		kill_node(src);
	}


/************* 1. CONSTRUCTORS && DESTRUCTOR *************/
public:
    explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
	: _vcomporator(comp)
	{
		_allocator = alloc;
		_comparator = comp;
		_vcomporator = ValueComp(comp);
		_size = 0;
		_root = NULL;
	}

    template <class InputIterator>
    map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), 
	const allocator_type& alloc = allocator_type()) : _vcomporator(comp)
	{
		_allocator = alloc;
		_comparator = comp;
		_vcomporator = ValueComp(comp);
		_size = 0;
		_root = NULL;
		for (InputIterator it = first; it != last; it++)
			insert(*it);
	}

    map (const map& x) : _vcomporator(x._comparator)
	{
		_allocator = x._allocator;
		_comparator = x._comparator;
		_vcomporator = x._vcomporator;
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
    size_type max_size() const{ return (std::numeric_limits<difference_type>::max() / sizeof(value_type)); }
    

/************* 4. ELEMENT ACCESS *************/

	mapped_type& operator[] (const key_type& k)
	{
		if (!count(k))
			insert(std::make_pair(k, mapped_type()));
		return (*(find(k))).second;
	}


/************* 5. MODIFIERS *************/

    std::pair<iterator,bool> insert (const value_type& val)
	{
		bool added = 0;
		_root = add_node(_root, NULL, val, added);
		if (_root) _root->red = 0;
		return (std::make_pair(find(val.first), added));
	}

    iterator insert (iterator position, const value_type& val)
	{
		bool added = 0;
		Node *tmp = find_node((*position).first);
		if (_comparator((*position).first, val.first))
		{
			tmp = add_node(tmp, tmp->parent, val, added);
			while (tmp->parent)
			{
				tmp = balance(tmp);
				tmp = tmp->parent;
			}
		}
		else
			_root = add_node(_root, NULL, val, added);
		if (_root) _root->red = 0;
		return find(val.first);
	}

    template <class InputIterator> 
    void insert (InputIterator first, InputIterator last)
	{
		for (InputIterator it = first; it != last; it++)
			insert(*it);
	}

    void erase (iterator position)
	{
		erase((*position).first);
	}

    size_type erase (const key_type& k)
	{
		if (find(k) == end())
			return 0;
		else
		{
			if (_root->right && _root->left && !_root->right->red && !_root->left->red)
				_root->left->red = 1;
			_root = delete_node(_root, k);
		}
		if (_root) _root->red = 0;
		return 1;
	}

    void erase (iterator first, iterator last)
	{
		map<Key, T> tmp(first,last);
		for (iterator it = tmp.begin(); it != tmp.end(); it++)
			this->erase((*it).first);
	}

    void swap (map& x)
	{
		map tmp;
		tmp = *this;
		*this = x;
		x = tmp;
	}

    void clear()
	{
		annihilate_node(_root);
		_root = NULL;
		_size = 0;
	}


/************* 6. OBSERVERS *************/

key_compare key_comp() const { return _comparator; }
value_compare value_comp() const { return _vcomporator; }

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

size_type count (const key_type& k) const
{
	if (this->find(k) == this->end())
		return 0;
	else
		return 1;
}

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

const_iterator lower_bound (const key_type& k) const
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
	return const_iterator(result);
}

iterator upper_bound (const key_type& k)
{
	Node *tmp = _root;
	Node *result = _root;
	while (tmp)
	{
		if (_comparator(k, tmp->data->first))
		{
			result = tmp;
			tmp = tmp->left;
		}
		else
			tmp = tmp->right;
	}
	return iterator(result);
}

const_iterator upper_bound (const key_type& k) const
{
	Node *tmp = _root;
	Node *result = _root;
	while (tmp)
	{
		if (_comparator(k, tmp->data->first))
		{
			result = tmp;
			tmp = tmp->left;
		}
		else
			tmp = tmp->right;
	}
	return const_iterator(result);
}

std::pair<const_iterator,const_iterator> equal_range (const key_type& k) const
{
	const_iterator it = this->find(k);
	return (std::make_pair(it, ++it));
}

std::pair<iterator,iterator>             equal_range (const key_type& k)
{
	iterator it = this->find(k);
	return (std::make_pair(it, ++it));
}


class ValueComp
{
protected:
	Compare comp;
public:
	ValueComp (Compare c) : comp(c) {}
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

    reference operator*() { return *(_current->data);
	}
    Iterator &operator++()  // prefix
	{
		if (_current->right)
			_current = _current->right->min_node();
		else
		{
			while (_current->parent && (_current->parent->left != _current))
				_current = _current->parent;
			_current = _current->parent;
		}
		return *this;
	}

    Iterator &operator--() // prefix
	{
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
			_current = _current->right->min_node();
		else
		{
			while (_current->parent && (_current->parent->left != _current))
				_current = _current->parent;
			_current = _current->parent;
		}
		return *this;
	}

    CIterator &operator--() // prefix
	{
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
			_current = _current->right->min_node();
		else
		{
			while (_current->parent && (_current->parent->left != _current))
				_current = _current->parent;
			_current = _current->parent;
		}
		return *this;
	}

    RIterator &operator++() // prefix
	{
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
			_current = _current->right->min_node();
		else
		{
			while (_current->parent && (_current->parent->left != _current))
				_current = _current->parent;
			_current = _current->parent;

		}
		return *this;
	}

    CRIterator &operator++() // prefix
	{
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


template <class T, class Alloc>
  void swap (map<T,Alloc>& x, map<T,Alloc>& y)
  {
	  x.swap(y);
  }

} // namespace bracket

#endif