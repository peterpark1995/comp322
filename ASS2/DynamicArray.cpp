#include <iostream>
using namespace std;


template <class T> class DynamicArrayIterator;

template<class T>
class DynamicArray {
public:
  void add(T item);
  int size();
  T remove(int i);
  T& operator[](int);
  DynamicArray();
  ~DynamicArray();
  DynamicArrayIterator<T> begin();
  DynamicArrayIterator<T> end();
  DynamicArrayIterator<T> r_begin();
  DynamicArrayIterator<T> r_end();

  private:
  T* data;
  int capacity;
  int currentPosition;

};

template<class T>
DynamicArray<T>::DynamicArray() {
  currentPosition = 0;
  capacity = 10;
  data = new T[10];
}

template <class T>
DynamicArray<T>::~DynamicArray() {
  delete[] data;
}

template<class T>
DynamicArrayIterator<T> DynamicArray<T>::begin() {
  return DynamicArrayIterator<T>(this, 0, 1);
}

template<class T>
DynamicArrayIterator<T> DynamicArray<T>::end() {
  return DynamicArrayIterator<T>(this, this->size(), 1);
}

template<class T>
DynamicArrayIterator<T> DynamicArray<T>::r_begin() {
  return DynamicArrayIterator<T>(this, this->size() - 1, -1);
}

template<class T>
DynamicArrayIterator<T> DynamicArray<T>::r_end() {
  return DynamicArrayIterator<T>(this, -1, -1);
}


template <class T>
T& DynamicArray<T>::operator[](int i) {
  return this->data[i];
}

template <class T>
void DynamicArray<T>::add(T item) {
  if (currentPosition >= capacity) {
    T* copy = new T[2 * capacity];
    for (int i = 0; i < capacity; i++) {
      copy[i] = this->data[i];
    }

    delete this->data;
    this->data = copy;
    this->capacity = 2 * this->capacity;
    
  }

  this->data[currentPosition] = item;
  currentPosition++;
}

template<class T>
int DynamicArray<T>::size() {
  return this->currentPosition;
}

template<class T>
T DynamicArray<T>::remove(int i) {
  T toRemove = this->data[i];
  for (int j = i; j < this->currentPosition - 1; j++) {
    this->data[j] = this->data[j+1];
  }

  currentPosition--;
}

template<class T>
class DynamicArrayIterator {
private:
  DynamicArray<T>* array;
  int current;
  int dir;

public:
  DynamicArrayIterator(DynamicArray<T> *d, int position, int direction);
  void operator ++();
  bool operator ==(const DynamicArrayIterator& other);
  bool operator !=(const DynamicArrayIterator& other);
  T& operator*();

};

template<class T>
DynamicArrayIterator<T>::DynamicArrayIterator(DynamicArray<T> *d, int position, int direction) {
  this->array = d;
  this->current = position;
  this->dir = direction;
}

// prefix
template<class T>
void DynamicArrayIterator<T>::operator++() {
  this->current += dir;
  
}

template<class T>
bool DynamicArrayIterator<T>::operator == (const DynamicArrayIterator<T>& other) {
  return this->array == other.array && this->current == other.current && this->dir == other.dir;
}

template<class T>
bool DynamicArrayIterator<T>::operator != (const DynamicArrayIterator<T>& other) {
  return !(*this == other) ;
}


template<class T>
T& DynamicArrayIterator<T>::operator *() {
  return (*(this->array))[this->current];
}

int main() {
  DynamicArray<int> foo;
  foo.add(3);
  foo.add(2);
  cout << foo[1] << endl;
  foo[1] = 10;
  cout << foo[1] << endl;

  for(DynamicArrayIterator<int> a = foo.begin(); a != foo.end(); ++a) {
    cout << *a << endl;
  }

  for(DynamicArrayIterator<int> a = foo.r_begin(); a != foo.r_end(); ++a) {
    cout << *a << endl;
  }
}




