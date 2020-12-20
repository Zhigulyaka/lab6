#pragma once
#ifndef _ARRLIST_
#define _ARRLIST_

#include <iostream>

using namespace std;

template <class T>
class ArrListIterator;



template <class T>
class ArrList
{
protected:
    T* data;
    int* links;
    int size;
    int count;
    int root;
public:
  
    ArrList(int _size);
    ~ArrList();
    ArrList(ArrList<T>& other);

  void Ins(ArrListIterator<T>& d, T elem);
  void InsFirst(T elem);
  void InsLast(T elem);

  ArrList<T>& operator =(ArrList<T>& other);


  bool IsFull() const;
  bool IsEmpty() const;

  void DelFirst();
  void DelLast();
  void Del(ArrListIterator<T>& d);

  ArrListIterator<T> begin();
  ArrListIterator<T> end();

  T GetFirst();
  T GetLast();
  int GetMiddle(T elem);
  void Rotate();

  template <class T>
  friend ostream& operator<< (ostream& ostr, const ArrList<T> &A);
  template <class T>
  friend istream& operator >> (istream& istr, ArrList<T> &A);

  int GetCount();

  template <class T>
  friend class ArrListIterator;
};

template <class T>
class ArrListIterator
{
protected:
    ArrList<T>& list;
    int index;
public:
    ArrListIterator(ArrList<T>& other, int _index = -1);
    ArrListIterator(ArrListIterator<T>& other);
    ~ArrListIterator();

    bool IsGoNext();
    void GoNext();

    bool operator==(ArrListIterator<T>& other);
    bool operator!=(ArrListIterator<T>& other);

    void operator++();
    void operator--();
    ArrListIterator<T>& operator=(const ArrListIterator<T>& other);

    T& operator*();
    T& operator*(int);

    T GetData();
    int GetIndex();
};

template <class T>
ostream& operator<< (ostream& ostr, const ArrList<T> &A) 
{
    int i = A.root;
    for(;i!=-2;)
    {
        ostr << A.data[i]<<"->";
        i=A.links[i];
    }
  return ostr<<-2<<endl;
}

template <class T>
istream& operator >> (istream& istr, ArrList<T> &A)
{
    int count;
    istr >> count;
  for (int i = 0; i < count; i++) 
  {
      T d;
    istr >> d;
    A.InsLast(d);
  }
  return istr;
}


template <class T>
ArrList<T>::ArrList(ArrList<T>& other)
{
  count = other.count;
  size= other.size;
  data = new T[size];
  links = new int[size];
  for (int i = 0; i < size; i++)
  {
      links[i] = other.links[i];
      data[i] = other.data[i];
  }
}
template<class T>
inline void ArrList<T>::Ins(ArrListIterator<T>& d, T elem)
{
    if (this->IsFull())
        throw logic_error("list_is_full");
    if (this->IsEmpty())
        this->InsFirst(elem);
    ArrListIterator<T> i(*this, root);
    if (d.IsGoNext()>0)
        data[d.GetIndex()] = elem;
    else
    {
    while (links[i.GetIndex()] < d.GetIndex());
    i.GoNext();
    links[d.GetIndex()] = links[i.GetIndex()];
    links[i.GetIndex()] = d.GetIndex();
    data[d.GetIndex()] = elem;
    }
    count++;
}
template<class T>
inline void ArrList<T>::InsFirst(T elem)
{
    if (this->IsFull())
        throw logic_error("list_is_full");
    if (this->IsEmpty())
    {
        root = 0;
        data[0] = elem;
        links[0] = -2;
    }
    else
    {
    ArrListIterator<T> i(*this, 0);
    int k = links[i.GetIndex()];
    while (links[i.GetIndex()] >= 0)
    {
        i.operator++();
    }
    data[i.GetIndex()] = elem;
    links[i.GetIndex()] = root;
    root = i.GetIndex();
    }

    count++;
}
template<class T>
inline void ArrList<T>::InsLast(T elem)
{
    ArrListIterator<T> end(*this, root);
    ArrListIterator<T> i(*this, 0);
    if (this->IsFull())
        throw logic_error("list_is_full");
    if (this->IsEmpty())
    {
        root = 0;
        data[0] = elem;
        links[0] = -2;
    }
    else
    {
        if (links[root] == -2)
        {
            end.operator++();
            data[end.GetIndex()] = elem;
            links[root] = end.GetIndex();
            links[end.GetIndex()] = -2;
        }
        else
        {
        while (links[end.GetIndex()] >=0)
            end.GoNext();
        while (links[i.GetIndex()] >= 0)
            i.operator++();
        i.operator++();
    data[i.GetIndex()] = elem;
    links[i.GetIndex()] = -2;
    links[end.GetIndex()] = i.GetIndex();
        }

    }
    count++;
}
template<class T>
inline ArrList<T>::ArrList(int _size)
{
    if (_size <= 0)
        throw logic_error("size_is_wrong");
    size = _size;
    data = new T[size];
    links = new int[size];
    count = 0;
    for (int i = 0; i < size; i++)
    {
        links[i] = -1;
    }
    root = -1;
}
template <class T>
ArrList<T>::~ArrList()
{
    if (this->data != 0)
    {
        delete[] data;
        delete[] links;
         count = 0;
         data = 0;
         links = 0;
         size = 0;
         root = -1;
    }
    
}

template <class T>
ArrList<T>& ArrList<T>::operator =(ArrList<T>& other)
{
    if (this == &other)
        return (*this);
    if (this->size != other.size)
    {
        delete[] data;
        delete[] links;
        data = new T[other.size];
        links = new int[other.size];

    }
    count = other.count;
    size = other.size;
    root = other.root;
    for (int i = 0; i < size; i++)
    {
        links[i] = other.links[i];
        data[i] = other.data[i];
    }
    return *this;
}

template<class T>
inline T ArrList<T>::GetFirst()
{
    if ((*this).IsEmpty())
        throw logic_error("list_is_empty");
    return data[root];
}

template<class T>
inline T ArrList<T>::GetLast()
{
    if ((*this).IsEmpty())
        throw logic_error("list_is_empty");
    ArrListIterator<T> end (*this, root);
    while (links[end.GetIndex()] != -2)
        end.GoNext();
    return end.GetData();
}

template<class T>
inline int ArrList<T>::GetMiddle(T elem)
{
    if (this->IsEmpty())
        throw logic_error("list_is_empty");
    ArrListIterator<T> i(*this, root);
    while (i.IsGoNext()==1)
    {
        if (i.GetData() == elem)
            break;
        i.GoNext();
    }
    return i.GetIndex();
}

template<class T>
inline void ArrList<T>::Rotate()
{
    int t = 0;
    int i = 0;
    int j = size - 1;
    for (; i < j; i++, j--)
    {
        t = data[i];
        data[i] = data[j];
        data[j] = t;
    }

}


template <class T>
int ArrList<T>::GetCount()
{
  return count;
}

template<class T>
inline bool ArrList<T>::IsFull() const
{
    return count == size;
}

template<class T>
inline bool ArrList<T>::IsEmpty() const
{
    return (count==0);
}

template<class T>
inline void ArrList<T>::DelFirst()
{
    if ((*this).IsEmpty())
        throw logic_error("list_is_empty");
    int i = root;
    root = links[root];
    links[i] = -1;
    count--;

}

template<class T>
inline void ArrList<T>::DelLast()
{
    if ((*this).IsEmpty())
        throw logic_error("list_is_empty");
    if (links[root] == -2)
    {
    links[root] = -1;
    root = -1;
    }
    else
    {
        ArrListIterator<T> pEnd (*this, root);
        ArrListIterator<T> end(*this, links[root]);
        while (end.IsGoNext() == 1)
        {
            pEnd.GoNext();
            end.GoNext();
        }
        links[pEnd.GetIndex()] = -2;
        links[end.GetIndex()] = -1;
    }

        

    count--;

}
template<class T>
inline void ArrList<T>::Del(ArrListIterator<T>& d)
{
    if (this->IsEmpty())
        throw logic_error("list_is_empty");
    if (links[d.GetIndex()]==-1)
        throw logic_error("element_is_empty");
    ArrListIterator<T> i (*this,root);
    while(links[i.GetIndex()]!=d.GetIndex())
    {
        i.GoNext();
    }
    links[i.GetIndex()] = links[d.GetIndex()];
    links[d.GetIndex()] = -1;
    data[d.GetIndex()] = NULL;
    count--;

}
template<class T>
inline ArrListIterator<T> ArrList<T>::begin()
{
    return ArrListIterator<T>(*this, root);
}

template<class T>
inline ArrListIterator<T> ArrList<T>::end()
{
    return ArrListIterator<T>(*this, -1);
}





template<class T>
inline ArrListIterator<T>::ArrListIterator(ArrList<T>& other, int _index):list(other)
{
    this->index = _index;
}

template<class T>
inline ArrListIterator<T>::ArrListIterator(ArrListIterator<T>& other):list(other.list),index(other.index)
{
}

template<class T>
inline ArrListIterator<T>::~ArrListIterator()
{
    index = -1;
}

template<class T>
inline bool ArrListIterator<T>::IsGoNext()
{
    return (index >= 0);
}

template<class T>
inline void ArrListIterator<T>::GoNext()
{
    if (IsGoNext())
        index = list.links[index];
}

template<class T>
inline bool ArrListIterator<T>::operator==(ArrListIterator<T>& other)
{
    return ((index==other.index)&&(*list==*(other.list)));
}

template<class T>
inline bool ArrListIterator<T>::operator!=(ArrListIterator<T>& other)
{
    return ((index != other.index) || (*list != *(other.list)));
}

template<class T>
inline void ArrListIterator<T>::operator++()
{
    index=index+1;
}

template<class T>
inline void ArrListIterator<T>::operator--()
{
    ArrListIterator<T> i(*this, root);
    while (links[i.GetIndex()] != GetIndex())
        i.GoNext();
    this->index = i.index;
}

template<class T>
inline ArrListIterator<T>& ArrListIterator<T>::operator=(const ArrListIterator<T>& other)
{
    list = other.list;
    index = other.index;
}
template<class T>
inline T& ArrListIterator<T>::operator*()
{
    return list.data[index];
}
template<class T>
inline T& ArrListIterator<T>::operator*(int)
{
    return list.data[index];
}
template<class T>
inline T ArrListIterator<T>::GetData()
{
    if (index < 0)
        throw logic_error("index_is_wrong");
    return list.data[index];
}
template<class T>
inline int ArrListIterator<T>::GetIndex()
{
    return index;
}
#endif