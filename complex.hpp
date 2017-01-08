#ifndef COMPLEX_HPP_
#define COMPLEX_HPP_

#include <iostream>
#include <cmath>

namespace complex {

template <typename Dtype>
class Complex
{
public:
	Complex(Dtype a = 0, Dtype b = 0) : re(a), im(b) {}
	template <typename Stype> Complex(const Complex<Stype>& src);

	~Complex() {}

public:
	template <typename Stype> Complex<Dtype>& operator = (const Complex<Stype>& rhs);
	template <typename Stype> Complex<Dtype>& operator += (const Complex<Stype>& rhs);
	template <typename Stype> Complex<Dtype>& operator -= (const Complex<Stype>& rhs);
	template <typename Stype> Complex<Dtype>& operator *= (const Complex<Stype>& rhs);
	template <typename Stype> Complex<Dtype>& operator /= (const Complex<Stype>& rhs);

	template <typename Stype> operator Complex<Stype>() const;
	operator bool() const;
	
	Complex<Dtype> operator ~ ();	// È¡¹²éî

public:
	Dtype re;
	Dtype im;
};

template <typename Dtype> template <typename Stype>
Complex<Dtype>::Complex(const Complex<Stype>& src)
{
	re = (Dtype)src.re;
	im = (Dtype)src.im;
}

template <typename Dtype> template <typename Stype>
Complex<Dtype>& Complex<Dtype>::operator = (const Complex<Stype>& rhs)
{
	if ((void*)&rhs != (void*)this)
	{
		re = (Dtype)rhs.re;
		im = (Dtype)rhs.im;
	}

	return *this;
}

template <typename Dtype> template <typename Stype>
Complex<Dtype>& Complex<Dtype>::operator += (const Complex<Stype>& rhs)
{
	re += (Dtype)rhs.re;
	im += (Dtype)rhs.im;

	return *this;
}

template <typename Dtype> template <typename Stype>
Complex<Dtype>& Complex<Dtype>::operator -= (const Complex<Stype>& rhs)
{
	re -= (Dtype)rhs.re;
	im -= (Dtype)rhs.im;

	return *this;
}

template <typename Dtype> template <typename Stype>
Complex<Dtype>& Complex<Dtype>::operator *= (const Complex<Stype>& rhs)
{
	Dtype r = re;

	re = r * (Dtype)rhs.re - im * (Dtype)rhs.im;
	im = r * (Dtype)rhs.im + im * (Dtype)rhs.re;

	return *this;
}

template <typename Dtype> template <typename Stype>
Complex<Dtype>& Complex<Dtype>::operator /= (const Complex<Stype>& rhs)
{
	Dtype r = re;
	Dtype den = (Dtype)rhs.re * (Dtype)rhs.re + (Dtype)rhs.im * (Dtype)rhs.im;
	
	re = (r * (Dtype)rhs.re + im * (Dtype)rhs.im) / den;
	im = (r * (Dtype)rhs.im - im * (Dtype)rhs.re) / den;

	return *this;
}

template <typename Dtype>
Complex<Dtype> Complex<Dtype>::operator ~ ()
{
	Complex<Dtype> ret;

	ret.re = re;
	ret.im = -im;

	return ret;
}

template <typename Dtype> template <typename Stype>
Complex<Dtype>::operator Complex<Stype>() const
{
	Complex<Dtype> ret;
	ret.re = (Dtype)rhs.re;
	ret.im = (Dtype)rhs.im;

	return ret;
}

template <typename Dtype>
Complex<Dtype>::operator bool() const
{
	return re && im;
}

/////////////////////////////////////////////////////////////////////////////

template <typename Dtype>
std::ostream& operator << (std::ostream& out, const Complex<Dtype>& c)
{
	out << "(" << c.re << (c.im < 0 ? "" : "+") << c.im << "i)";
	return out;
}

template <typename Dtype>
std::istream& operator >> (std::istream& in, Complex<Dtype>& c)
{
	in >> c.re >> c.im;
	if (!in)
	{
		c = Complex<Dtype>();
	}

	return in;
}

template <typename Dtype>
Complex<Dtype> operator + (const Complex<Dtype>& lhs, const Complex<Dtype>& rhs)
{
	Complex<Dtype> ret(lhs);
	ret += rhs;

	return ret;
}

template <typename Dtype>
Complex<Dtype> operator - (const Complex<Dtype>& lhs, const Complex<Dtype>& rhs)
{
	Complex<Dtype> ret(lhs);
	ret -= rhs;

	return ret;
}

template <typename Dtype>
Complex<Dtype> operator - (const Complex<Dtype>& rhs)
{
	Complex<Dtype> ret;
	ret = Complex<Dtype>(0, 0) - rhs;

	return ret;
}

template <typename Dtype>
Complex<Dtype> operator * (const Complex<Dtype>& lhs, const Complex<Dtype>& rhs)
{
	Complex<Dtype> ret(lhs);
	ret *= rhs;

	return ret;
}

template <typename Dtype>
Complex<Dtype> operator / (const Complex<Dtype>& lhs, const Complex<Dtype>& rhs)
{
	Complex<Dtype> ret(lhs);
	ret /= rhs;

	return ret;
}

template <typename Dtype>
bool operator == (const Complex<Dtype>& lhs, const Complex<Dtype>& rhs)
{
	return lhs.re == rhs.re && lhs.im == rhs.im;
}

template <typename Dtype>
bool operator != (const Complex<Dtype>& lhs, const Complex<Dtype>& rhs)
{
	return !(lhs == rhs);
}

template <typename Dtype>
double abs(const Complex<Dtype> c)
{
	return std::sqrt((double)(c.re * c.re) + (double)(c.im * c.im));
}

template <typename Dtype>
double angle(const Complex<Dtype> c)
{
	return std::atan2((double)c.im, (double)c.re);
}

}	// namespace complex

#endif // !COMPLEX_HPP_