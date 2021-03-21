#ifndef LINK_LIST
#define LINK_LIST

#include <iostream>
using namespace std;

template <typename T>
struct Int_Node
{
	T value;
	Int_Node<T> *pre, *next;
};

template <typename T>
class Link_List
{
	template <typename U>
	friend ostream &operator<<(ostream &, const Link_List<U> &);  	// print all integers in the list
	template <typename U>
	friend istream &operator>>(istream &, Link_List<U> &);			// input a value at the back of the list, like insert_node(val);

public:
	Link_List();										// default constructor
	Link_List(const Link_List &);						// copy constructor
	~Link_List();
	int getSize() const;
	
	const Link_List &operator=(const Link_List &);		// assignment operator
	bool operator==(const Link_List &) const;			// equality operator
	bool operator!=(const Link_List &right) const		// inequality operator
	{
		return !(*this == right);
	}

	T &operator[](int index);							// subscript operator for non-const objects
	T operator[](int index) const;						// subscript operator for const objects

	bool insert_node(T value);							// insert an integer at the back of link list
	bool delete_node();									// delete the last node
	bool insert_node(int index, T value);				// insert an integer after the i_th position
	bool delete_node(int index);						// delete the i_th node

private:
	int size;
	Int_Node<T> *head, *tail;								// pointer to the first and the last element of Link_List
};

// implement
template <typename T>
Link_List<T>::Link_List(){
	head=0;
	tail=0;
	size=0;	
}
template <typename T>
Link_List<T>::Link_List(const Link_List &L){
	head=L.head;
	tail=L.tail;
	size=L.size;
}
template <typename T>
Link_List<T>::~Link_List(){}
template <typename T>
const Link_List<T>& Link_List<T>::operator=(const Link_List<T> &L){
	head=L.head;
	tail=L.tail;
	size=L.size;
	return *this;
}

template <typename T>
bool Link_List<T>::operator==(const Link_List<T> &L) const{
	Int_Node<T> *ptr1=head;
	Int_Node<T> *ptr2=L.head;
	if(size!=L.size){
		return false;
	}
	while(ptr1&&ptr2){
		if(ptr1->value!=ptr2->value){
			return false;
		}
		ptr1=ptr1->next;
		ptr2=ptr2->next;
	}
	return true;
}
template <typename T>
T Link_List<T>::operator[](int index) const{
	Int_Node<T> *ptr=head;
	for(int i=0;i<index;i++){
		ptr=ptr->next;
	}
	return ptr->value;
}
template <typename T>
T& Link_List<T>::operator[](int index){
	Int_Node<T> *ptr=head;
	for(int i=0;i<index;i++){
		ptr=ptr->next;
	}
	return ptr->value;
}
template <typename T>
bool Link_List<T>::insert_node(T value){
	Int_Node<T> *ptr=head;
	if(!ptr){
		Int_Node<T> *new_node=new Int_Node<T>;
		new_node->next=0;
		new_node->pre=0;
		new_node->value=value;
		head=new_node;
		tail=new_node;
	}else{
		while(ptr->next!=0){
			ptr=ptr->next;
		}
		Int_Node<T> *new_node=new Int_Node<T>;
		new_node->value=value;
		new_node->next=0;
		ptr->next=new_node;
		ptr=ptr->next;
		tail=ptr;
	}
	size++;
	return true;
}
template <typename T>
bool Link_List<T>::insert_node(int index, T value){
	if(index>=size||index<0){
		cout<<"out of range!"<<endl;
		return false;
	}
	Int_Node<T> *ptr=head;
	for(int i=0;i<index-1;++i){
		ptr=ptr->next;
	}
	Int_Node<T> *new_node=new Int_Node<T>;
	new_node->value=value;
	if(index==0){
		new_node->next=head;
		head=new_node;
		size++;
		return true;
	}
	Int_Node<T> *temp=ptr->next;
	ptr->next=new_node;
	new_node->next=temp;
	size++;
	return true;
}
template <typename T>
int Link_List<T>::getSize() const{
	return size;
}
template <typename T>
bool Link_List<T>::delete_node(int index){
	if(index>=size||index<0){
		cout<<"out of range!"<<endl;
		return false;
	}
	Int_Node<T> *ptr=head;
	if(index==0){
		head=ptr->next;
		delete ptr;
		ptr=0;
	}else if(index==size-1){
		for(int i=0;i<index-1;i++){
			ptr=ptr->next;
		}
		ptr->next=0;
		tail=ptr;
	}else{
		for(int i=0;i<index-1;i++){
			ptr=ptr->next;
		}
		Int_Node<T> *temp=ptr->next;
		ptr->next=temp->next;
		delete temp;
		temp=0;
	}
	size--;
	return true;
}
template <typename T>
bool Link_List<T>::delete_node(){
	if(size==1){
		cout<<"can't delete!"<<endl;
		return false;
	}
	Int_Node<T> *ptr=head;
	while(ptr->next!=tail){
		ptr=ptr->next;
	}
	ptr->next=0;
	tail=ptr;
	size--;
	return true;
}
template <typename U>
ostream &operator<<(ostream &output, const Link_List<U> &L){
	Int_Node<U> *ptr=L.head;
	while(ptr){
		output<<ptr->value<<" ";
		ptr=ptr->next;
	}
	return output;
}
template <typename U>
istream &operator>>(istream &input, Link_List<U> &L){
	Int_Node<U> *ptr=L.head;
	if(!ptr){
		Int_Node<U> *new_node=new Int_Node<U>;
		new_node->next=0;
		new_node->pre=0;
		input>>new_node->value;
		L.head=new_node;
		L.tail=new_node;
		L.size++;
	}else{
		for(int i=0;i<L.size-1;i++){
			ptr=ptr->next;
		}
		Int_Node<U> *new_node=new Int_Node<U>;
		input>>new_node->value;
		ptr->next=new_node;
		ptr=ptr->next;
		L.tail=ptr;
		L.size++;
	}
	return input;
}


#endif // LINK_LIST
