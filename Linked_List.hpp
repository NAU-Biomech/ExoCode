#ifndef LINKED_LIST_HEADER
#define LINKED_LIST_HEADER
#include <cstddef>

template <class T>
class Node;

template <class T>
class ListIterator {
private:
  Node<T>* next_node;
public:
  ListIterator(Node<T>* start_node);
  T next();
  bool hasNext();
};

template <class T>
class LinkedList {
private:
  int count = 0;
  Node<T>* first = NULL;
  Node<T>* last = NULL;
  Node<T>* getNode(int pos);
  void addNode(Node<T>* node);
public:
  unsigned int size();
  void clear();
  void append(T value);
  T operator[] (int);
  ListIterator<T> getIterator();
  ~LinkedList();
};

template <class T>
class Node {
private:
  T value;
  Node<T>* next = NULL;
public:
  Node(T value);
  T getValue();
  void setNext(Node<T>* next);
  Node<T>* getNext();
};

template <class T>
Node<T>::Node(T value){
  this->value = value;
}

template <class T>
T Node<T>::getValue(){
  return value;
}

template <class T>
void Node<T>::setNext(Node<T>* next){
  this->next = next;
}

template <class T>
Node<T>* Node<T>::getNext(){
  return next;
}

template <class T>
Node<T>*  LinkedList<T>::getNode(int pos){
  if (pos >= count){
    return NULL;
  }

  Node<T>* current = first;
  for (int i = 0; i < pos; i++){
    current = current->getNext();
  }
  return current;
}

template <class T>
T LinkedList<T>::operator[] (int pos){
  Node<T>* node = getNode(pos);
  return node->getValue();
}

template <class T>
void LinkedList<T>::addNode(Node<T>* node){
  if (count == 0){
    first = node;
    last = node;
  } else {
    last->setNext(node);
  }
  count++;
}

template <class T>
unsigned int LinkedList<T>::size(){
  return count;
}

template <class T>
void LinkedList<T>::append(T value){
  Node<T>* node = new Node<T>(value);
  addNode(node);
}

template <class T>
ListIterator<T> LinkedList<T>::getIterator(){
  return ListIterator<T>();
}

template <class T>
void LinkedList<T>::clear(){

  Node<T>* next;
  while(first != NULL){
    next = first->getNext();
    delete first;
    first = next;
  }
  first = NULL;
  last = NULL;
  count = 0;
}

template <class T>
LinkedList<T>::~LinkedList(){
  clear();
}

template <class T>
ListIterator<T>::ListIterator(Node<T>* start_node){
  next_node = start_node;
}

template <class T>
T ListIterator<T>::next(){
  T value = next_node.getValue();
  next_node = next_node.getNext();
  return value;
}

template <class T>
bool ListIterator<T>::hasNext(){
  return next_node != NULL;
}


#endif
