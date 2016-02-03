#ifndef NODE_H
#define NODE_H

#include <cmath>
#include <queue>
#include <iomanip>
#include <ostream>

template <typename T>
class iterator_data
{
private:
  iterator_data(iterator_data *const); // hide copy constructor

public:
  T const *const _value;
  unsigned int const _count;

  iterator_data(T const *const value, unsigned int const count)
    : _value(value), _count(count)
  {
  }

  ~iterator_data()
  {
  }

};

template <typename T>
class Node
{
private:
  Node(Node<T> *const);

  Node(T const *value, signed int (*cmp)(T const *, T const *), Node *const p)
    : _value(value), _cmp(cmp), parent(p), _count(1), _iterator(NULL)
  {
    left = NULL;
    right = NULL;
    upToDate = false;
    parent = NULL;
  }

  T const *const _value;

  signed int (*const _cmp)(T const *, T const *);

  Node<T> *left;
  Node<T> *right;
  Node<T> *parent;

  bool upToDate;

  unsigned int _height, _size, _count;

  std::queue<Node *> *_iterator;

  inline void invalidate()
  {
    if (upToDate)
    {
      upToDate = false;
      if (_iterator)
      {
        delete _iterator;
        _iterator = NULL;
      }
      if (parent)
        parent->invalidate();
    }
  }

  inline Node *rotateRight();

  inline Node *rotateLeft();

  inline void update();

  void fill_list(std::queue<Node *> *);

  std::queue<Node *> *generate_iterator_list();

public:

  ~Node()
  {
    if (_iterator != NULL)
      delete _iterator;
  }

  unsigned int height();

  /**
   * returns number of nodes
   */
  unsigned int size();

  bool add(T const *value);

  Node *balance();

  static
  Node<T> *create(T *const value, signed int (*cmp)(T const *, T const *))
  {
    return new Node(value, cmp, NULL);
  }

  void free();

  void iterator();

  unsigned int get_count();

  iterator_data<T> *iterator_next();

  void iterator_generate();

  friend std::ostream& operator<<(std::ostream &out, Node<T> &node)
  {
    if (node.parent)
      return out << node.parent;
    else
    {
      std::queue<Node<T> *> worklist;
      unsigned nBreak = 2;
      unsigned nBreakNext = 0;
      int h = node.height();
      int widthCorrection = 1 + ((h-1) << 1);
      worklist.push(&node);
      while (!worklist.empty())
      {
        Node<T> *next = worklist.front();
        worklist.pop();

        if (!--nBreak) {
          out << "\n";
          nBreak = nBreakNext;
          nBreakNext = 0;
          widthCorrection = (h-- << 1 / (worklist.size() + 1));
        }
        for (int i = 0; i < (1 << h) + widthCorrection; ++i)
          out << "  ";
        if (next->left)
        {
          worklist.push(next->left);
          ++nBreakNext;
        }
        if (next->right)
        {
          worklist.push(next->right);
          ++nBreakNext;
        }

        out << *(next->_value);
      }
      if (--nBreak)
        return out;
      return out << std::endl;
    }
  }
};


template <typename T>
unsigned int Node<T>::height()
{
  if (upToDate)
  {
    return _height;
  }
  update();
  return _height;
}

template <typename T>
inline Node<T> *Node<T>::rotateLeft()
{
  Node *newRoot = left;
  left = newRoot->right;
  newRoot->parent = parent;
  parent = newRoot;
  newRoot->right = this;
  newRoot->invalidate();
  invalidate();
  return newRoot;
}

template <typename T>
inline Node<T> *Node<T>::rotateRight()
{
  Node *newRoot = right;
  right = newRoot->left;
  newRoot->parent = parent;
  parent = newRoot;
  newRoot->left = this;
  newRoot->invalidate();
  invalidate();
  return newRoot;
}

template <typename T>
inline void Node<T>::update()
{
  _size = 0;
  _height = 0;
  if (!left && !right)
  {
    upToDate = true;
    _size = 1;
    return;
  }
  else
  {
    if (left)
    {
      _height = left->height();
      _size += left->_size;
    }
    if (right)
    {
      unsigned int heightR = right->height();
      if (heightR > _height)
      {
        _height = heightR;
      }
      _size += right->_size;
    }
  }
  ++_height;
  ++_size;
  upToDate = true;
}
/**
 * returns number of nodes
 */
template <typename T>
unsigned int Node<T>::size()
{
  if (upToDate)
  {
    return _size;
  }
  update();
  return _size;
}

template <typename T>
bool Node<T>::add(T const *value)
{
  Node *node = this;
  while (true)
  {
    signed int const cmp = _cmp(node->_value, value);
    if (cmp == 0)
    {
      ++node->_count;
      node->invalidate();
      return true;
    }
    else if (cmp < 0)
    {
      if (!node->right)
      {
        node->right = new Node(value, _cmp, node);
        node->right->parent = node;
        node->invalidate();
        return true;
      }
      else
      {
        node = node->right;
      }
    }
    else
    {
      if (!node->left)
      {  
        node->left = new Node(value, _cmp, node);
        node->left->parent = node;
        node->invalidate();
        return true;
      }
      else
      {
        node = node->left;
      }
    }
  }
}

template <typename T>
Node<T> *Node<T>::balance()
{
  signed int balance = 0;
  if (right)
  {
    right = right->balance();
    if (right->parent != this)
    {
      right->parent = this;
    }
    balance -= right->height() + 1;
  }
  if (left) 
  {
    left = left->balance();
    if (left->parent != this)
    {
      left->parent = this;
    }
    balance += left->height() + 1;
  }
  if (balance <= -2)
  {
    if (right->left)
    {
      if (!right->right) 
      {
        right = right->rotateLeft();
        // assert right->parent == this;
      }
      else if (right->right->height() < right->left->height())
      {
        right = right->rotateLeft();
        // assert right->parent == this;
      }
    return rotateRight();
    }
  }
  else if (balance >= 2)
  {
    if (left->right)
    {
      if (!left->left) 
      {
        left = left->rotateRight();
        // assert left->parent == this;
      }
      else if (left->left->height() < left->right->height())
      {
        left = left->rotateRight();
        // assert left->parent == this;
      }
    return rotateRight();
    }
  }
  return this;
}

template <typename T>
void Node<T>::free() {
  if (parent) {
    parent->free();
    parent = NULL;
  } 
  else
  {
    if (left)
    {
      left->parent = NULL;
      left->free();
      left = NULL;
    }
    if (right)
    {
      right->parent = NULL;
      right->free();
      right = NULL;
    }
    delete(this);
  }
}

template <typename T>
unsigned int Node<T>::get_count()
{
  return _count;
}

template <typename T>
void Node<T>::iterator_generate()
{
  generate_iterator_list();
}

template <typename T>
iterator_data<T> *Node<T>::iterator_next()
{
  if (_iterator == NULL)
    return NULL;
  if (_iterator->empty())
    return NULL;
  Node *head = _iterator->front();
  T const *value = head->_value;
  unsigned int count = head->_count;
  iterator_data<T> *data = new iterator_data<T>(value, count);
  _iterator->pop();
  return data;
}

template <typename T>
void Node<T>::fill_list(std::queue<Node<T> *> *list)
{
  if (list == NULL)
    return;
  if (left)
    left->fill_list(list);
  list->push(this);
  if (right)
    right->fill_list(list);
}

template <typename T>
std::queue<Node<T> *> *Node<T>::generate_iterator_list()
{
  if (parent)
    return parent->generate_iterator_list();
  if (_iterator)
  {
    delete _iterator;
  }
  _iterator = new std::queue<Node<T> *>();
  fill_list(_iterator);
  return _iterator;
}
#endif

