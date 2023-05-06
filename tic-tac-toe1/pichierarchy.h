#include <iostream>
#pragma once
class Picture;
class Pic_base;
class Frame_Pic;
class HCat_Pic;
class VCat_Pic;
class String_Pic;
Picture frame(const Picture&);
Picture hcat(const Picture&, const Picture&);
Picture vcat(const Picture&, const Picture&);
std::ostream& operator<<(std::ostream&, const Picture&);