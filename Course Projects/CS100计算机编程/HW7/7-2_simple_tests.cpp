#include <iostream>
#include <type_traits>

/**********************************************************/

// #include or paste your code here and compile this code.
#include <cstddef>
#include <iterator>
#include <type_traits>
#include <utility>

// The node structure of the linked-list.
template <typename T>
struct Slist_node {
  T value;
  Slist_node<T> *next;
  // Add constructors if you need.
  Slist_node() = default;
  Slist_node(T value, Slist_node<T> *next) : value(value), next(next) {}
};

// A declaration for the 'Slist' class.
template <typename T>
class Slist;

// When 'is_const' is true, this is a const_iterator.
// Otherwise, it is a normal iterator.
template <typename T, bool is_const>
class Slist_iterator {
 public:
  // The 'using' declaration is used to declare type aliases, just as 'typedef'.
  // For example,
  //      typedef long long LL;
  // is equivalent to
  //      using LL = long long;
  // But the 'using' type alias declaration has more readability.

  // Every STL-style iterator should have the following five type aliases.
  // value_type:
  //      The type of values that can be obtained by dereferencing the iterator.
  // difference_type:
  //      A type that can be used to identify distance between iterators.
  //      It is most likely to be defined as 'ptrdiff_t'.
  // pointer:
  //      Defines a pointer to the type iterated over.
  //      Note: for a const_iterator, 'pointer' should be 'const T *'.
  // reference:
  //      Defines a reference to the type iterated over.
  //      Note: for a const_iterator, 'reference' should be 'const T &'.
  // iterator_category:
  //      The category of the iterator. All kinds of iterators are classified
  //      into five categories: input-iterator, output-iterator,
  //      forward-iterator, bidirectional-iterator and random-access-iterator.
  //      Since our Slist is a singly-linked list, the iterator can only be
  //      moved forward and cannot go backwards. So our iterator falls into the
  //      'forward_iterator' category.
  using value_type = T;
  using difference_type = typename Slist<T>::difference_type;
  // What is std::conditional<...>::type? Have a guess.
  using pointer = typename std::conditional<is_const, const T *, T *>::type;
  using reference = typename std::conditional<is_const, const T &, T &>::type;
  using iterator_category = std::forward_iterator_tag;

 private:
  using node_t = Slist_node<T>;
  using self_t = Slist_iterator<T, is_const>;

  // The current position that this iterator is pointing to.
  node_t *m_cur;

 public:
  Slist_iterator() = default;
  Slist_iterator(node_t *pos = nullptr) : m_cur(pos) {}

  // Allow conversion from iterator to const_iterator, but not vice versa.
  // You don't need to understand the definition of this function.
  template <typename Other,
            typename = typename std::enable_if<
                is_const &&
                std::is_same<Other, Slist_iterator<T, false>>::value>::type>
  Slist_iterator(const Other &oi) : m_cur(oi.base()) {}
  ~Slist_iterator() = default;
  // You may need these two functions in your Slist.
  node_t *base() const {
    return m_cur;
  }

  self_t next() const {
    return self_t(m_cur->next);
  }

  // Dereference operator.
  reference operator*() const {
    return m_cur->value;
  }

  // This operator is a little bit tricky.
  // To work in consistence with operator*, it is always defined as follows.
  pointer operator->() const {
    return &(m_cur->value);
  }

  // Prefix operator++, as in '++iter'.
  self_t &operator++() {
    m_cur = m_cur->next;
    return *this;
  }

  // Postfix operator++, as in 'iter++'.
  self_t operator++(int) {
    self_t tmp = *this;
    m_cur = m_cur->next;
    return tmp;
  }
};
///////////////////////////////////////////////////////////////////////////
// Comparison between iterator and const_iterator should be allowed.
template <typename T, bool C1, bool C2>
inline bool operator==(const Slist_iterator<T, C1> &lhs,
                       const Slist_iterator<T, C2> &rhs) {
  return lhs.base() == rhs.base();
}

template <typename T, bool C1, bool C2>
inline bool operator!=(const Slist_iterator<T, C1> &lhs,
                       const Slist_iterator<T, C2> &rhs) {
  return !(lhs == rhs);
}
//////////////////////////////////////////////////////////////////////////
template <typename T>
class Slist {
 public:
  // Every STL container should have the following type aliases.
  using value_type = T;
  using size_type = std::size_t;
  using difference_type = std::ptrdiff_t;
  using pointer = T *;
  using reference = T &;
  using const_pointer = const T *;
  using const_reference = const T &;

  using iterator = Slist_iterator<T, false>;
  using const_iterator = Slist_iterator<T, true>;

 private:
  using node_t = Slist_node<T>;

  // m_head is the head of the linked-list.
  // m_length is the number of elements stored in the list.
  node_t *m_head;
  size_type m_length;

 public:
  // You also need to implement the default-constructor, copy-constructor,
  // copy-assignment operator and destructor.

  // The default-constructor initializes an empty linked-list.

  // Both the copy-constructor and the copy-assignment operator provide
  // 'value-semantics', which means that they copy all the elements stored in
  // the list instead of copying only the 'm_head' pointer.

  // For the copy-assignment operator, we highly recommend using the
  // 'copy-and-swap' technique. If you don't know what it is, you can refer to
  // the reference solution of hw5-1.

  // The destructor should destroy every node and deallocate the memory they
  // take up.

  // YOUR CODE HERE
  void swap(Slist &other) {
    std::swap(m_head, other.m_head);
    std::swap(m_length, other.m_length);
  }
  Slist() : m_head(nullptr), m_length(0) {}
  Slist(const Slist &other) {
    //降低复杂度
    if (other.m_head == nullptr) {
      m_head = nullptr;
      m_length = 0;
    } else {
      m_head = new node_t;
      m_head->value = other.m_head->value;
      m_head->next = nullptr;
      node_t *p = m_head;
      node_t *q = other.m_head->next;
      while (q != nullptr) {
        p->next = new node_t;
        p->next->value = q->value;
        p->next->next = nullptr;
        p = p->next;
        q = q->next;
      }
      m_length = other.m_length;
    }
  }
  Slist &operator=(const Slist &other) {
    Slist tmp(other);
    swap(tmp);
    return *this;
  }
  ~Slist() {
    while (m_head) {
      node_t *tmp = m_head;
      m_head = m_head->next;
      delete tmp;
    }
  }
  // Insert an element with given value to be the front of the list.
  void push_front(const value_type &value) {
    node_t *tmp = new node_t(value, m_head);
    m_head = tmp;
    ++m_length;
  }
  // Remove the element at the beginning of the list.
  void pop_front() {
    if (m_head) {
      node_t *tmp = m_head;
      m_head = m_head->next;
      delete tmp;
      --m_length;
    }
  }

  // Insert an element with given value to be the end of the list.
  void push_back(const value_type &value) {
    //记录一个表尾指针，每次插入都指向最后一个节点，不要遍历所有节点
    node_t *tail = m_head;
    if (tail == nullptr) {
      m_head = new node_t(value, nullptr);
      ++m_length;
      return;
    }
    while (tail->next) {
      tail = tail->next;
    }
    tail->next = new node_t(value, nullptr);
    ++m_length;
  }

  // Remove the element at the end of the list.
  void pop_back() {
    //记录一个表尾指针，每次删除都指向最后一个节点，不要遍历所有节点
    node_t *tail = m_head;
    if (tail == nullptr) {
      return;
    }
    while (tail->next) {
      tail = tail->next;
    }
    delete tail;
    tail = nullptr;
    --m_length;
  }


  // Insert an element with given value after the position denoted by 'pos'.
  // Return an iterator pointing to the element that has been inserted.
  iterator insert_after(const_iterator pos, const value_type &value) {
    if (pos == end()) {
      push_back(value);
      return end();
    } 
    else {
      node_t *tmp = pos.base();
      node_t *new_node = new node_t(value, tmp->next);
      tmp->next = new_node;
      ++m_length;
      return iterator(new_node);
    }
  }

  // Erase the element after the position denoted by 'pos'.
  void erase_after(const_iterator pos) {
    if (pos == end()) {
      pop_back();
    } 
    else {
      node_t *tmp = pos.base()->next;
      pos.base()->next = tmp->next;
      delete tmp;
      --m_length;
    }
  }

  // You also need to implement size(), empty(), clear(),
  // which all follow the STL fashion.

  // Note that:
  // size() should return a value of the type 'size_type'.
  // After clear(), the list should contain zero elements and size() == 0.

  // YOUR CODE HERE
  size_type size() const {
    return m_length;
  }
  bool empty() const {
    return m_length == 0;
  }
  void clear() {
    while (m_head) {
      node_t *tmp = m_head;
      m_head = m_head->next;
      delete tmp;
    }
    m_length = 0;
  }

  // The following are the well-known 'begin' and 'end' functions.
  iterator begin() {
    return iterator(m_head);
  }

  iterator end() {
    return iterator(nullptr);
  }

  // Why do we need these two functions? Think about this.
  const_iterator begin() const {
    return const_iterator(m_head);
  }

  const_iterator end() const {
    return const_iterator(nullptr);
  }

  // Note:
  // It was not until C++11 that cbegin() and cend() were added to the standard.
  const_iterator cbegin() const {
    return begin();
  }

  const_iterator cend() const {
    return end();
  }
};

// Two Slists are thought of as equal if and only if they are of the same
// length, and every pair of corresponding elements are equal.
// It is guaranteed that we will only use this operator when
// bool operator==(const T &, const T &) is defined.
// Hint: Use std::equal and the iterators you have defined.
template <typename T>
inline bool operator==(const Slist<T> &lhs, const Slist<T> &rhs) {
  if (lhs.size() != rhs.size()) {
    return false;
  }
  else{
    return std::equal(lhs.begin(), lhs.end(), rhs.begin());
  }
}

// Lexicographical-order comparison.
// It is guaranteed that we will only use this operator when
// bool operator<(const T &, const T &) is defined.
// Hint: Use std::lexicographical_compare and the iterators you have defined.
template <typename T>
inline bool operator<(const Slist<T> &lhs, const Slist<T> &rhs) {
  return std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());   
}

// Why do we define the following functions like this? Think about it.
template <typename T>
inline bool operator!=(const Slist<T> &lhs, const Slist<T> &rhs) {
  return !(lhs == rhs);
}

template <typename T>
inline bool operator>(const Slist<T> &lhs, const Slist<T> &rhs) {
  return rhs < lhs;
}

template <typename T>
inline bool operator<=(const Slist<T> &lhs, const Slist<T> &rhs) {
  return !(lhs > rhs);
}

template <typename T>
inline bool operator>=(const Slist<T> &lhs, const Slist<T> &rhs) {
  return !(lhs < rhs);
}

/**********************************************************/

// This type is not default-constructible and not copy-assignable.
// You should make sure that your Slist can store such thing.
class Special_type {
  int x;

 public:
  Special_type() = delete;
  Special_type(const Special_type &) = default;
  Special_type &operator=(const Special_type &) = delete;
  Special_type(int xx) : x(xx) {}
  int get() const {
    return x;
  }
};

inline bool operator==(const Special_type &lhs, const Special_type &rhs) {
  return lhs.get() == rhs.get();
}

inline bool operator<(const Special_type &lhs, const Special_type &rhs) {
  return lhs.get() < rhs.get();
}

// The following are some compile-time checks.

static_assert(std::is_default_constructible<Slist<int>>::value,
              "Slist should be default-constructible.");

static_assert(std::is_copy_constructible<Slist<int>>::value,
              "Slist should be copy-constructible.");

static_assert(std::is_copy_assignable<Slist<int>>::value,
              "Slist should be copy-assignable.");

// Note: even if the following two assertions succeed, your Slist may still have
// some problem when storing data of the Special_type. These static-assertions
// only deduce whether the relevant functions are callable, without actually
// calling them. You need to try on your own to test whether any error arises
// when some functions are called.

static_assert(std::is_default_constructible<Slist<Special_type>>::value,
              "Slist<T> should be default-constructible even if T is not.");

static_assert(std::is_copy_assignable<Slist<Special_type>>::value,
              "Slist<T> should be copy-assignable even if T is not.");

static_assert(
    std::is_same<decltype(++std::declval<Slist_iterator<int, false>>()),
                 Slist_iterator<int, false> &>::value,
    "Prefix operator++ should return reference to the object itself.");

namespace detail {

template <typename T = Slist_iterator<int, false>,
          typename = decltype(((const T *)nullptr)->operator*())>
std::true_type deref_const_helper(int);

std::false_type deref_const_helper(double);

constexpr bool deref_is_const = decltype(deref_const_helper(0))::value;

template <typename T = Slist<int>,
          typename = decltype(((const T *)nullptr)->size())>
std::true_type size_const_helper(int);

std::false_type size_const_helper(double);

constexpr bool size_is_const = decltype(size_const_helper(0))::value;

template <typename T = Slist<int>,
          typename = decltype(((const T *)nullptr)->empty())>
std::true_type empty_const_helper(int);

std::false_type empty_const_helper(double);

constexpr bool empty_is_const = decltype(empty_const_helper(0))::value;

constexpr bool size_return_size_type =
    std::is_same<decltype(std::declval<Slist<int>>().size()),
                 Slist<int>::size_type>::value;

constexpr bool assignment_return_ref =
    std::is_same<decltype(std::declval<Slist<int>>().operator=(
                     std::declval<Slist<int>>())),
                 Slist<int> &>::value;

} // namespace detail

static_assert(detail::deref_is_const,
              "Why don't you define Slist_iterator::operator* as a const "
              "member function?");

static_assert(detail::size_is_const,
              "Why don't you define Slist::size as a const member function?");

static_assert(detail::empty_is_const,
              "Why don't you define Slist::empty as a const member function?");

static_assert(
    detail::size_return_size_type,
    "The return-type of Slist<T>::size() should be Slist<T>::size_type.");

static_assert(
    detail::assignment_return_ref,
    "operator= should return reference to the object on the left-hand side.");

#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_RESET "\x1b[0m"

#define SET_COLOR(COLOR, STRING) (ANSI_COLOR_##COLOR STRING ANSI_COLOR_RESET)

#define RED(STRING) SET_COLOR(RED, STRING)
#define GREEN(STRING) SET_COLOR(GREEN, STRING)

inline void report_if_wrong(bool condition, long line) {
  if (!condition) {
    std::cout << ANSI_COLOR_RED "Wrong on line " << line << ANSI_COLOR_RESET
              << std::endl;
    exit(0);
  }
}

#ifdef assert
#undef assert
#endif

#define assert(COND) report_if_wrong(COND, __LINE__)

int main() {
  std::cout << GREEN("You've passed the compile-time tests.") << std::endl;

  int a[] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
  Slist<int> list;
  for (auto x : a)
    list.push_front(x);
  assert(list.size() == 10);
  assert(!list.empty());
  int num = 0;
  for (auto x : list)
    assert(x == num++);

  for (auto i = 0; i != 5; ++i)
    list.pop_front();
  assert(list.size() == 5);
  assert(!list.empty());
  num = 5;
  for (auto x : list)
    assert(x == num++);

  --*list.begin();
  --*list.begin();
  list.insert_after(list.cbegin(), 5);
  list.insert_after(list.cbegin(), 4);
  assert(list.size() == 7);
  assert(!list.empty());
  num = 3;
  for (auto x : list)
    assert(x == num++);

  for (auto i = 0; i != 4; ++i)
    list.erase_after(list.begin());
  assert(list.size() == 3);
  assert(!list.empty());
  *list.begin() = 7;
  num = 7;
  for (auto x : list)
    assert(x == num++);

  list.clear();
  assert(list.size() == 0);
  assert(list.empty());
  assert(list.begin() == list.end());

  std::cout << GREEN("Congratulations! You've passed the simple test.")
            << std::endl;
  return 0;
}