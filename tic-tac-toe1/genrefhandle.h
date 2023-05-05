#pragma once
/*template classes need to be inline declared in the header in the same fashion
as the source file of the header, the member functions etc. defined separately
from the class declaration need(should) not be included(defined) in the header
file, if there is a complaint about "incomplete type", it probably boils down 
to this*/
template<class T> class Ptr
{
public:

	Ptr() : refptr(new size_t(1)), p(0) {}
	Ptr(T* t) : refptr(new size_t(1)), p(t) {}
	Ptr(const Ptr& h) : refptr(h.refptr), p(h.p)
	{
		++* refptr;
	}
	void make_unique() //implicit argument, makes the class instance it acts on unique
	{
		p = p ? p->clone() : 0; //p must have a clone constructor takes allocates a new space that 
		//is initialized with values of old p, but has a new address, it returns the address.
		--* refptr;
		refptr = new size_t(1);
	}
	Ptr& operator=(const Ptr&);
	~Ptr();
	operator bool() const { return p; }
	T* operator-> () const {
		return p;
	}
	T& operator* () const {
		return *p;
	}

private:
	size_t* refptr;
	T* p;
};

template<class T>
Ptr<T>& Ptr<T>::operator=(const Ptr& rhs) { //writing further <T> after refhandle<T> is optional
	++* rhs.refptr;
	if (-- * refptr == 0) { //this.refptr not needed since we are inside "this"
		//right now, and so we can access its members directly without needing any access operator
		delete p;
		delete refptr; //delete both(all) objects occupying memory and free that memory
	}
	refptr = rhs.refptr;
	p = rhs.p;
}
template<class T>
Ptr<T>::~Ptr() { //class instance as implicit argument
	if (-- * refptr == 0) /*basically we just need to decrease the reference
		count by 1 in general, the underlying storage object is only destroyed when all the
		handles referring to it are gone*/
	{
		delete refptr;
		delete p;
	}
}