/*this file shall contain the pic hierarchy along with its functions that will
enable us to frame our 0s and Xs and concatenate them with ease, basically this file
features a class abstraction that solves a family of problems, one of which is
tic-tac-toe*/
//instances of classes derived from pic_base shall make us of the ptr handle we made
#include "C:\Users\gaura.YASH\source\repos\tic-tac-toe1\tic-tac-toe1\genrefhandle.h"
#include "C:\Users\gaura.YASH\source\repos\tic-tac-toe1\tic-tac-toe1\pichierarchy.h"
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
using std::vector; //global scope of a source file is simply just that file
using std::string; /*global scope of a header file is all the files
that include the header and the header itself*/

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

void HCat_Pic::display(std::ostream& os, ht_sz row, bool do_pad) const
{
	left->display(os, row, do_pad || row < right->height());
	right->display(os, row, do_pad);
}

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

Pic_base::wd_sz String_Pic::width() const {
	Pic_base::wd_sz n = 0;
	for (Pic_base::ht_sz i = 0; i != data.size(); ++i)
		n = std::max(n, data[i].size());
	return n;
}
Picture::Picture(const vector<string>& v) :
	p(new String_Pic(v)) {}

void String_Pic::display(std::ostream& os, ht_sz row, bool do_pad) const
{
	wd_sz start = 0;
	// write the row if we're still in range 
	if (row < height()) {
		os << data[row];
		start = data[row].size();
	}
	// pad the output if necessary 
	if (do_pad)
		pad(os, start, width());
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