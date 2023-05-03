template<class T> class Refhandle
{
private:
	size_t* refptr;
	T* p; /*necessary to have pointers to T and size_t both because if they are objects
	then they would be local to the class instance but we need many instances
	accessing the same object and ref count, and thus they must be pointers*/
};