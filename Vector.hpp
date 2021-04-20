#include <memory>

template <class T, class Alloc = std::allocator<T> >

class vector
{
private:
    T value_type;
    Alloc allocator_type;
    reference;
    const_reference;
    pointer;
    const_pointer;
    iterator;
    const_iterator;
    reverse_iterator;
    const_reverse_iterator;
    int difference_type;
    unsigned int size_type;
public:
    /* CONSTRUCTORS */
    explicit vector (const allocator_type& alloc = allocator_type()); // default constructor, empty container
    explicit vector (size_type n, const value_type& val = value_type(),
                 const allocator_type& alloc = allocator_type()); // container with n elements
    template <class InputIterator>
    vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type()); // range constructor	
    vector (const vector& x); // copy constructor

    ~vector();
    vector& operator= (const vector& x);

     /* ITERATORS */

    iterator begin();
    const_iterator begin() const;
    iterator end();
    const_iterator end() const;
    reverse_iterator rbegin();
    const_reverse_iterator rbegin() const;
    reverse_iterator rend();
    const_reverse_iterator rend() const;


     /* CAPACITY */

    size_type size() const;
    size_type max_size() const;
    void resize (size_type n, value_type val = value_type());
    size_type capacity() const;
    bool empty() const;
    void reserve (size_type n);


    /* ELEMENT ACCESS */

    reference operator[] (size_type n);
    const_reference operator[] (size_type n) const;
    reference at (size_type n);
    const_reference at (size_type n) const;
    reference front();
    const_reference front() const;
    reference back();
    const_reference back() const;


    /* MODIFIERS */

    template <class InputIterator>
    void assign (InputIterator first, InputIterator last);	
    void assign (size_type n, const value_type& val);
    void push_back (const value_type& val);
    void pop_back();
    iterator insert (iterator position, const value_type& val);
    void insert (iterator position, size_type n, const value_type& val);
    template <class InputIterator>
    void insert (iterator position, InputIterator first, InputIterator last);
    iterator erase (iterator position);
    iterator erase (iterator first, iterator last);
    void swap (vector& x);
    void clear();



};


template <class T, class Alloc>
  bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);

template <class T, class Alloc>
  bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);

template <class T, class Alloc>
  bool operator<  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);

template <class T, class Alloc>
  bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);

template <class T, class Alloc>
  bool operator>  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);

template <class T, class Alloc>
  bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);

template <class T, class Alloc>
  void swap (vector<T,Alloc>& x, vector<T,Alloc>& y);