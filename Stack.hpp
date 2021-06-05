#ifndef FT_STACK
#define FT_STACK

#include "Vector.hpp"

namespace ft {

template <class T, class Container = ft::vector<T> > 
class stack {
public:
    typedef T           value_type;
    typedef Container   container_type;
    typedef size_t      size_type;

    container_type _c;

    explicit stack (const container_type& ctnr = container_type()) { _c = ctnr; }
    bool empty() const { return _c.empty(); }
    size_type size() const { return _c.size(); }
    value_type& top() { return _c.back(); }
    const value_type& top() const { return _c.back(); }
    void push (const value_type& val) { return _c.push_back(val); }
    void pop() { return _c.pop_back(); }

}; // class bracket

    template <class T, class Container>
    bool operator== (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
    { return (lhs._c == rhs._c); }

    template <class T, class Container>
    bool operator!= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
    { return (lhs._c != rhs._c); }

    template <class T, class Container>
    bool operator<  (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
    { return (lhs._c < rhs._c); }

    template <class T, class Container>
    bool operator<= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
    { return (lhs._c <= rhs._c); }

    template <class T, class Container>
    bool operator>  (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
    { return (lhs._c > rhs._c); }

    template <class T, class Container>
    bool operator>= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
    { return (lhs._c >= rhs._c); }

} // namespace bracket

#endif