#include <memory>
namespace ft {

template <class T, class Alloc = std::allocator<T> >
class vector
{
private:
	T * _data;
  Alloc _allocator;
	int _capacity;
	int _size;
public:
    typedef T value_type;
    typedef Alloc allocator_type;
    typedef value_type& reference;
    typedef const value_type& const_reference;
	typedef  value_type* pointer;
    typedef const value_type* const_pointer;
//     typedef iterator ; // struct random_access_iterator_tag to value_type  тип итератора для контейнера данного типа
//     typedef const_iterator ; // struct random_access_iterator_tag to const value_type
//     typedef reverse_iterator reverse_iterator<iterator>; // template <class Iterator> class reverse_iterator;
//     typedef const_reverse_iterator reverse_iterator<const_iterator>;
    typedef ptrdiff_t difference_type; // iterator_traits<iterator>::difference_type  значение разницы между двумя итераторами
    typedef size_t size_type; // значение размера наибольшего возможного контейнера данного типа

public:

    /* CONSTRUCTORS && DESTRUCTOR*/

    explicit vector (const allocator_type& alloc = allocator_type()) {
      _allocator = alloc;
      _data = NULL;
      _size = 0;
      _capacity = 0;
    }

    explicit vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()) {
      _allocator = alloc;
      _data = _allocator.allocate(n);
      pointer tmp = _data;
      for(int i = 0; i < n; i++)
      {
          _allocator.construct(tmp, val);
          tmp++;
      }
    //   pointer end = _data + n;
    //   for(pointer i = _data; i != end; i++)
    //   {
    //     _allocator.construct(i, val);
    //   }
      
      _size = n;
      _capacity = n;
    }

//     template <class InputIterator>
//     vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type()); // range constructor, including first excluding last

//     vector (const vector& x) { *this = x; } // copy constructor

//     ~vector();  // destroy elements and deallocate capacity

//     vector& operator= (const vector& x);

//      /* ITERATORS */

//     iterator begin(); // return random access iterator pointing to first element
//     const_iterator begin() const;
//     iterator end(); // return iterator reffering next after last element. iterator is alias
//     const_iterator end() const;
//     reverse_iterator rbegin(); // last element
//     const_reverse_iterator rbegin() const;
//     reverse_iterator rend(); // theoretical element before first
//     const_reverse_iterator rend() const;


//      /* CAPACITY */

    size_type size() const { return _size; }
//     size_type max_size() const; // return maximum number of elements (potential), in reference is 1073741823
//     void resize (size_type n, value_type val = value_type()); // change size, if n < container reduces and destroy other elements, 
// 	// if n > container expanded, if n > capacity reallocate storage
    size_type capacity() const { return _capacity; }
//     bool empty() const { return (_size == 0 ? 1 : 0); } // if size = 0 return true, else return false
//     void reserve (size_type n); // request change of capacity, if n < current capacity, do nothing


//     /* ELEMENT ACCESS */

    reference operator[] (size_type n) { return _data[n]; } // return reference to element at position n
//     const_reference operator[] (size_type n) const;
//     reference at (size_type n); // same as [], but can throw exception if out of range
//     const_reference at (size_type n) const;
//     reference front(); // return reference to first element, UB if empty vector. reference is alias
//     const_reference front() const; 
//     reference back(); // return reference to last element, UB if empty vector. reference is alias
//     const_reference back() const;


//     /* MODIFIERS */

//     template <class InputIterator>
//     void assign (InputIterator first, InputIterator last);	// replace content on range (destroy all old elements)
//     void assign (size_type n, const value_type& val); // replace content of n elements, each value is val
//     void push_back (const value_type& val); // add new element at the end, increase container size by 1
//     void pop_back(); // remove the last element, decrease size by 1
//     iterator insert (iterator position, const value_type& val); // insert new element before position
//     void insert (iterator position, size_type n, const value_type& val); // insert n elements before position
//     template <class InputIterator>
//     void insert (iterator position, InputIterator first, InputIterator last); // insert range elements before position
//     iterator erase (iterator position); // remove element on position
//     iterator erase (iterator first, iterator last); // remove range of elements
//     void swap (vector& x); // swap content
//     void clear(); // removes all elements, leaving container size = 0

// };

// /* NON-MEMBER OVERLOADS */

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


}; // class bracket
} // namespace bracket