template <class T, class Container = deque<T> > class queue;

explicit queue (const container_type& ctnr = container_type());
bool empty() const;
size_type size() const;
value_type& front();
const value_type& front() const;
value_type& back();
const value_type& back() const;
void push (const value_type& val);
void pop();