/*
	LinkedList.h - V1.1 - Generic LinkedList implementation
	Works better with FIFO, because LIFO will need to
	search the entire List to find the last one;

	For instructions, go to https://github.com/ivanseidel/LinkedList

	Created by Ivan Seidel Gomes, March, 2013.
	Released into the public domain.
*/
/* This file was modified by Eckart Schlottmann, 2015
 * Added the support for indexOf and support for Object handling together with sorting.
 * Still released into the public domain.
 */


#ifndef LinkedObjectList_h
#define LinkedObjectList_h

template<class T>
struct ListObjectNode
{
	T data;
	ListObjectNode<T> *next;
};

template <typename T>
class LinkedObjectList{

protected:
	int _size;
	ListObjectNode<T> *root;
	ListObjectNode<T>	*last;

	// Helps "get" method, by saving last position
	ListObjectNode<T> *lastNodeGot;
	int lastIndexGot;
	// isCached should be set to FALSE
	// everytime the list suffer changes
	bool isCached;

	ListObjectNode<T>* getNode(int index);

public:
	LinkedObjectList();
	virtual ~LinkedObjectList();

	/*
		Returns current size of LinkedList
	*/
	virtual int size();
	/*
		Adds a T object in the specified index;
		Unlink and link the LinkedList correcly;
		Increment _size
	*/
	virtual bool add(int index, T);
	/*
		Adds a T object in the end of the LinkedList;
		Increment _size;
	*/
	virtual bool add(T);
	/*
		Adds a T object in the start of the LinkedList;
		Increment _size;
	*/
	virtual bool unshift(T);
	/*
		Set the object at index, with T;
		Increment _size;
	*/
	virtual bool set(int index, T);
	/*
		Remove object at index;
		If index is not reachable, returns false;
		else, decrement _size
	*/
	virtual T remove(int index);
	/*
		Remove last object;
	*/
	virtual T pop();
	/*
		Remove first object;
	*/
	virtual T shift();
	/*
		Get the index'th element on the list;
		Return Element if accessible,
		else, return false;
	*/
	virtual T get(int index);

	/*
		Clear the entire array
	*/
	virtual void clear();

    virtual void sort();
    
    virtual int indexOf(T obj);
    
    private:
    virtual void sortInternal(ListObjectNode<T> *headNode);

};

// Initialize LinkedList with false values
template<typename T>
LinkedObjectList<T>::LinkedObjectList()
{
	root=false;
	last=false;
	_size=0;

	lastNodeGot = root;
	lastIndexGot = 0;
	isCached = false;
}

// Clear Nodes and free Memory
template<typename T>
LinkedObjectList<T>::~LinkedObjectList()
{
	ListObjectNode<T>* tmp;
	while(root!=false)
	{
		tmp=root;
		root=root->next;
		delete tmp;
	}
	last = false;
	_size=0;
	isCached = false;
}

/*
	Actualy "logic" coding
*/

template<typename T>
ListObjectNode<T>* LinkedObjectList<T>::getNode(int index){

	int _pos = 0;
	ListObjectNode<T>* current = root;

	// Check if the node trying to get is
	// immediatly AFTER the previous got one
	if(isCached && lastIndexGot <= index){
		_pos = lastIndexGot;
		current = lastNodeGot;
	}

	while(_pos < index && current){
		current = current->next;

		_pos++;
	}

	// Check if the object index got is the same as the required
	if(_pos == index){
		isCached = true;
		lastIndexGot = index;
		lastNodeGot = current;

		return current;
	}

	return false;
}

template<typename T>
int LinkedObjectList<T>::size(){
	return _size;
}

template<typename T>
bool LinkedObjectList<T>::add(int index, T _t){

	if(index >= _size)
		return add(_t);

	if(index == 0)
		return unshift(_t);

	ListObjectNode<T> *tmp = new ListObjectNode<T>(),
				 *_prev = getNode(index-1);
	tmp->data = _t;
	tmp->next = _prev->next;
	_prev->next = tmp;

	_size++;
	isCached = false;

	return true;
}

template<typename T>
bool LinkedObjectList<T>::add(T _t){

	ListObjectNode<T> *tmp = new ListObjectNode<T>();
	tmp->data = _t;
	tmp->next = false;
	
	if(root){
		// Already have elements inserted
		last->next = tmp;
		last = tmp;
	}else{
		// First element being inserted
		root = tmp;
		last = tmp;
	}

	_size++;
	isCached = false;

	return true;
}

template<typename T>
bool LinkedObjectList<T>::unshift(T _t){

	if(_size == 0)
		return add(_t);

	ListObjectNode<T> *tmp = new ListObjectNode<T>();
	tmp->next = root;
	tmp->data = _t;
	root = tmp;
	
	_size++;
	isCached = false;
	
	return true;
}

template<typename T>
bool LinkedObjectList<T>::set(int index, T _t){
	// Check if index position is in bounds
	if(index < 0 || index >= _size)
		return false;

	getNode(index)->data = _t;
	return true;
}

template<typename T>
T LinkedObjectList<T>::pop(){
	if(_size <= 0)
		return T();
	
	isCached = false;

	if(_size >= 2){
		ListObjectNode<T> *tmp = getNode(_size - 2);
		T ret = tmp->next->data;
		delete(tmp->next);
		tmp->next = false;
		last = tmp;
		_size--;
		return ret;
	}else{
		// Only one element left on the list
		T ret = root->data;
		delete(root);
		root = false;
		last = false;
		_size = 0;
		return ret;
	}
}

template<typename T>
T LinkedObjectList<T>::shift(){
	if(_size <= 0)
		return T();

	if(_size > 1){
		ListObjectNode<T> *_next = root->next;
		T ret = root->data;
		delete(root);
		root = _next;
		_size --;
		isCached = false;

		return ret;
	}else{
		// Only one left, then pop()
		return pop();
	}

}

template<typename T>
T LinkedObjectList<T>::remove(int index){
	if (index < 0 || index >= _size)
	{
		return T();
	}

	if(index == 0)
		return shift();
	
	if (index == _size-1)
	{
		return pop();
	}

	ListObjectNode<T> *tmp = getNode(index - 1);
	ListObjectNode<T> *toDelete = tmp->next;
	T ret = toDelete->data;
	tmp->next = tmp->next->next;
	delete(toDelete);
	_size--;
	isCached = false;
	return ret;
}


template<typename T>
T LinkedObjectList<T>::get(int index){
	ListObjectNode<T> *tmp = getNode(index);

	return (tmp ? tmp->data : T());
}

template<typename T>
void LinkedObjectList<T>::clear(){
	while(size() > 0)
		shift();
}


template<typename T>
void LinkedObjectList<T>::sortInternal(ListObjectNode<T> *headNode){
  if (!headNode->next)
    return;
  ListObjectNode<T> *nextNode = headNode->next;
  this->sortInternal(nextNode);      
  if ((*nextNode->data)<(*headNode->data))
  {
    T swap = headNode->data;
    headNode->data = nextNode->data;
    nextNode->data=swap;    
    this->sortInternal(headNode);              
  }  
}


template<typename T>
void LinkedObjectList<T>::sort(){
  isCached = false;  
  if (root)
    this->sortInternal(root);
}

template<typename T>
int LinkedObjectList<T>::indexOf(T obj)
{
  int index = 0;
  ListObjectNode<T> *node = root;

  while (node)
  {
    if (node->data == obj)
    return index;
    index++;
    node = node->next;
  }
  return -1;
}

#endif
