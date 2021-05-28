#ifndef FT_QUEUE
#define FT_QUEUE

#include "List.hpp"
namespace ft {

template <class T, class Container = ft::list<T> >
class queue {
public:
    typedef T           value_type;
    typedef Container   container_type;
    typedef size_t      size_type;

    container_type _c;

    explicit queue (const container_type& ctnr = container_type()) { _c = ctnr; }
    bool empty() const { return _c.empty(); }
    size_type size() const { return _c.size(); }
    value_type& front(){ return _c.front(); }
    const value_type& front() const{ return _c.front(); }
    value_type& back(){ return _c.back(); }
    const value_type& back() const{ return _c.back(); }
    void push (const value_type& val){ return _c.push_back(val); }
    void pop(){ return _c.pop_front(); }

}; // class bracket

    template <class T, class Container>
    bool operator== (const queue<T,Container>& lhs, const queue<T,Container>& rhs)
    { return (lhs._c == rhs._c); }

    template <class T, class Container>
    bool operator!= (const queue<T,Container>& lhs, const queue<T,Container>& rhs)
    { return (lhs._c != rhs._c); }

    template <class T, class Container>
    bool operator<  (const queue<T,Container>& lhs, const queue<T,Container>& rhs)
    { return (lhs._c < rhs._c); }

    template <class T, class Container>
    bool operator<= (const queue<T,Container>& lhs, const queue<T,Container>& rhs)
    { return (lhs._c <= rhs._c); }

    template <class T, class Container>
    bool operator>  (const queue<T,Container>& lhs, const queue<T,Container>& rhs)
    { return (lhs._c > rhs._c); }

    template <class T, class Container>
    bool operator>= (const queue<T,Container>& lhs, const queue<T,Container>& rhs)
    { return (lhs._c >= rhs._c); }

} // namespace bracket

#endif