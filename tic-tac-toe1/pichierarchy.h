#pragma once
#include <iostream>
#include <vector>
#include <string>
#include"C:\Users\gaura.YASH\source\repos\tic-tac-toe1\tic-tac-toe1\genrefhandle.h"
class Picture; /*these are forward declarations, not even declarations, you need
to give the declaration of the structure of the */
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
	typedef std::vector<std::string>::size_type ht_sz;
	typedef std::string::size_type wd_sz;

	//pic_base hierarchy implementation operations
	virtual ht_sz height() const = 0;
	virtual wd_sz width() const = 0;
	virtual void display(std::ostream&, ht_sz, bool) const = 0;/*the width shall be found
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
	Picture(const std::vector<std::string>& = std::vector<std::string>());

private:
	Ptr<Pic_base> p;
	Picture(Pic_base* ptr) : p(ptr) {}
};

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

class Frame_Pic : public Pic_base {
	friend Picture frame(const Picture&);
	Ptr<Pic_base> p;
	Frame_Pic(const Ptr<Pic_base>& pic) : p(pic) { }
	wd_sz width() const { return p->width() + 4; }
	ht_sz height() const { return p->height() + 4; }
	void display(std::ostream&, ht_sz, bool) const;
};

class HCat_Pic : public Pic_base {
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

class String_Pic : public Pic_base { //whole class private
	friend class Picture;
	std::vector<std::string> data;
	String_Pic(const std::vector<std::string>& v) : data(v) { }
	ht_sz height() const { return data.size(); }
	wd_sz width() const;
	void display(std::ostream&, ht_sz, bool) const;
};

Picture frame(const Picture&);
Picture hcat(const Picture&, const Picture&);
Picture vcat(const Picture&, const Picture&);
std::ostream& operator<<(std::ostream&, const Picture&);