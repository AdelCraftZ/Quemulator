//
// Created by Adel on 2023-02-19.
//

#ifndef QUEMULATOR_MATH_HPP
#define QUEMULATOR_MATH_HPP

#include "config.hpp"

#include <complex>
#include <utility>

namespace qtm {
using scalar_t = double;

using Complex = std::complex<scalar_t>;

inline scalar_t modulusSq(Complex const &z) {
	return norm(z);
}

/*
class Complex {
public:
	constexpr Complex(scalar_t re = scalar_t(), scalar_t im = scalar_t())
		: _raw(re, im)
	{}

	friend bool constexpr operator==(Complex const &a, Complex const &b) {
		return _scalarCompare(a.real(), b.real()) && _scalarCompare(a.imag(), b.imag());
	}

	friend bool constexpr operator==(Complex const &z, scalar_t s) {
		return _scalarCompare(z.real(), s) && _scalarCompare(z.imag(), 0);
	}

	friend bool constexpr operator==(scalar_t s, Complex const &z) {
		return _scalarCompare(z.imag(), 0), _scalarCompare(z.real(), s);
	}

	Complex CONSTEXPR20 operator-() const {
		return -_raw;
	}

	friend Complex CONSTEXPR20 operator+(Complex const &a, Complex const &b) {
		return a._raw + b._raw;
	}

	friend Complex CONSTEXPR20 operator+(Complex const &z, scalar_t s) {
		return z._raw + s;
	}

	friend Complex CONSTEXPR20 operator+(scalar_t s, Complex const &z) {
		return s + z._raw;
	}

	friend Complex CONSTEXPR20 operator-(Complex const &a, Complex const &b) {
		return a._raw - b._raw;
	}

	friend Complex CONSTEXPR20 operator-(Complex const &z, scalar_t s) {
		return z._raw - s;
	}

	friend Complex CONSTEXPR20 operator-(scalar_t s, Complex const &z) {
		return s - z._raw;
	}

	friend Complex CONSTEXPR20 operator*(Complex const &a, Complex const &b) {
		return a._raw * b._raw;
	}

	friend Complex CONSTEXPR20 operator*(Complex const &z, scalar_t s) {
		return z._raw * s;
	}

	friend Complex CONSTEXPR20 operator*(scalar_t s, Complex const &z) {
		return s * z._raw;
	}

	Complex CONSTEXPR20 &operator+=(Complex other) {
		_raw += other._raw;
		return *this;
	}

	Complex CONSTEXPR20 &operator+=(scalar_t s) {
		_raw += s;
		return *this;
	}

	Complex CONSTEXPR20 &operator*=(Complex other) {
		_raw *= other._raw;
		return *this;
	}

	Complex CONSTEXPR20 &operator*=(scalar_t s) {
		_raw *= s;
		return *this;
	}

	[[nodiscard]] scalar_t constexpr real() const {
		return _raw.real();
	}

	[[nodiscard]] scalar_t constexpr imag() const {
		return _raw.imag();
	}

	friend CONSTEXPR20 scalar_t modulusSq(Complex const &z) {
		return std::norm(z._raw);
	}

	friend Complex exp(Complex const &z) {
		return std::exp(z._raw);
	}
private:
	std::complex<scalar_t> _raw;

	constexpr Complex(std::complex<scalar_t> const &raw)
		: _raw(raw)
	{}

	constexpr Complex(std::complex<scalar_t> &&raw)
		: _raw(std::move(raw))
	{}

	static bool constexpr _scalarCompare(scalar_t a, scalar_t b) {
		scalar_t constexpr EPSILON = 1e-7;
		return b - a < EPSILON && a - b < EPSILON;
	}
};
*/

namespace literals {
[[nodiscard]] Complex constexpr operator""_i(unsigned long long val) {
	return {0, static_cast<scalar_t>(val)};
}

[[nodiscard]] Complex constexpr operator""_i(long double val) {
	return {0, static_cast<scalar_t>(val)};
}
} // namespace literals
} // qtm

#endif //QUEMULATOR_MATH_HPP
