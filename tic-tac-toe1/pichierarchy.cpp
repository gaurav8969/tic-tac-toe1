/*this file shall contain the pic hierarchy along with its functions that will
enable us to frame our 0s and Xs and concatenate them with ease, basically this file
features a class abstraction that solves a family of problems, one of which is 
tic-tac-toe*/
//instances of classes derived from pic_base shall make us of the ptr handle we made
#include "genrefhandle.h"
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
using std::vector; //global scope of a source file is simply just that file
using std::string; /*global scope of a header file is all the files 
that include the header and the header itself*/

class Picture; /*declaration, forward declaration to be specific,must not add
braces, failing to do so is an insidious source of errors */
class Pic_base {
	/*the derived friend classes, check accelerated c++ sec 15.2.7 for the 
	explanation to this, i.e so the height function calls using pointers to 
	pic_base*s(Frame_Pic instances etc.) can actually access the
	function(height function)*/
	
	friend std::ostream& operator<<(std::ostream&, const Picture&);
	friend class Frame_Pic;
	friend class HCat_Pic;
	friend class VCat_Pic;
	friend class String_Pic;
	//height and width of the pictures
	typedef vector<string>::size_type ht_sz;
	typedef string::size_type wd_sz;
	
	//pic_base hierarchy implementation operations
	virtual ht_sz height() const= 0;
	virtual wd_sz width() const= 0;
	virtual void display(std::ostream&,ht_sz,bool) const = 0;/*the width shall be found
	out eventually by looking at the strings and finding the longest one, the 
	height will be determined by the number of elements in the picture vector*/
	protected:
		static void pad(std::ostream& os, wd_sz start, wd_sz end)
		{
			while (start++ != end)
			os << " ";
		}
};

class Picture {
	friend std::ostream& operator<<(std::ostream&, const Picture&);
	friend Picture frame(const Picture&);
	friend Picture hcat(const Picture&, const Picture&);
	friend Picture vcat(const Picture&, const Picture&);
	
	public:
		Picture(const vector<string>& = vector<string>());

	private:
		Ptr<Pic_base> p;
		Picture(Pic_base* ptr): p(ptr){}
};

class Frame_Pic : public Pic_base {
	friend Picture frame(const Picture&);
	Ptr<Pic_base> p;
	Frame_Pic(const Ptr<Pic_base>& pic) : p(pic) { }
	wd_sz width() const { return p->width() + 4; }
	ht_sz height() const { return p->height() + 4; }
	void display(std::ostream&, ht_sz, bool) const;
};

void Frame_Pic::display(std::ostream& os, ht_sz row, bool do_pad) const
{
	if (row >= height()) {
		// out of range 
		if (do_pad)
			pad(os, 0, width());
	}
	else {
		if (row == 0 || row == height() - 1) {
			// top or bottom row
			os << string(width(), '*');
		}
		else if (row == 1 || row == height() - 2) {
			// second from top or bottom row
			os << "*";
			pad(os, 1, width() - 1);
			os << "*";
		}
		else {
			// interior row
			os << "* ";
			p->display(os, row - 2, true);
			os << " *";
		}
	}
}

class HCat_Pic: public Pic_base {
	friend Picture hcat(const Picture&, const Picture&);
	Ptr<Pic_base> left, right;
	HCat_Pic(const Ptr<Pic_base>& l, const Ptr<Pic_base>& r) :
		left(l), right(r) { }
	wd_sz width() const { return left->width() + right->width(); }
	ht_sz height() const
	{
		return std::max(left->height(), right->height());
	}
	void display(std::ostream&, ht_sz, bool) const;
};

void HCat_Pic::display(std::ostream& os, ht_sz row, bool do_pad) const
{
	left->display(os, row, do_pad || row < right->height());
	right->display(os, row, do_pad);
}

class VCat_Pic : public Pic_base {
	friend Picture vcat(const Picture&, const Picture&);
	Ptr<Pic_base> top, bottom;
	VCat_Pic(const Ptr<Pic_base>& t, const Ptr<Pic_base>& b) :
		top(t), bottom(b) { }
	wd_sz width() const
	{
		return std::max(top->width(), bottom->width());
	}
	ht_sz height() const
	{
		return top->height() + bottom->height();
	}
	void display(std::ostream&, ht_sz, bool) const;
};

void VCat_Pic::display(std::ostream& os, ht_sz row, bool do_pad) const
{
	wd_sz w = 0;
	if (row < top->height()) {
		// we are in the top subpicture
		top->display(os, row, do_pad);
		w = top->width();
	}
	else if (row < height()) {
		// we are in the bottom subpicture
		bottom->display(os, row - top->height(), do_pad);
		w = bottom->width();
	}
	if (do_pad)
		pad(os, w, width());
}

class String_Pic : public Pic_base {
	friend class Picture;
	vector<string> data;
	String_Pic(const std::vector<std::string>& v) : data(v) { }
	ht_sz height() const { return data.size(); }
	wd_sz width() const;
	void display(std::ostream&, ht_sz, bool) const;
};

Pic_base::wd_sz String_Pic::width() const {
	Pic_base::wd_sz n = 0;
	for (Pic_base::ht_sz i = 0; i != data.size(); ++i)
		n = std::max(n, data[i].size());
	return n;
}


//operations on "pictures"
Picture frame(const Picture& pic) {
	return new Frame_Pic(pic.p);
}
Picture hcat(const Picture& l, const Picture& r) {
	return new HCat_Pic(l.p, r.p);
}
Picture vcat(const Picture& t, const Picture& b) {
	return new VCat_Pic(t.p, b.p);
}

std::ostream& operator<<(std::ostream& os, const Picture& picture)
{
	const Pic_base::ht_sz ht = picture.p->height(); /* operator<< is a non-member
	overloaded operator, it is a friend of picture, since it accesses its member
	p and since picture forwards the call to height function of pic_base class, we
	must also declare it to be a friend of the pic_base class*/
	for (Pic_base::ht_sz i = 0; i != ht; ++i) {
		picture.p->display(os, i, false);
		os << std::endl;
	}
	return os;
};