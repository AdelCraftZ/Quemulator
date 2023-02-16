//
// Created by Adel on 11/02/2023.
//

#ifndef QUEMULATOR_QUANTUM_HPP
#define QUEMULATOR_QUANTUM_HPP

#include <cstddef>
#include <cstdint>
#include <utility>
#include <complex>
#include <vector>
#include <tuple>
#include <initializer_list>

using q_scalar_t = double;
using QComplex = std::complex<q_scalar_t>;

class NQubit {
	friend class QGate;
private:
	std::vector<QComplex> _components;

	explicit NQubit(std::vector<QComplex> &&components)
		: _components(std::move(components))
	{}

	q_scalar_t _calcNormSq();

	void _normalize();

	void _normalizeIfNeeded();
public:
	explicit NQubit(std::size_t n = 1)
		: _components(1 << n)
	{}

	NQubit(std::initializer_list<QComplex> components)
		: _components(components)
	{}

	template<class InputIt>
	NQubit(InputIt first, InputIt last)
		: _components(first, last)
	{}

	// multiplication by a scalar
	NQubit &operator*=(q_scalar_t s);

	// Kronecker product
	NQubit operator*(NQubit const &q) const;

	NQubit measure();
};

class QGate {
private:
	std::size_t _rowCnt;
	std::size_t _colCnt;
	std::vector<QComplex> _coeffs;
public:
	QGate(std::initializer_list<std::initializer_list<QComplex>> coeffs);

	// matrix product
	NQubit operator*(NQubit const &q) const;

	// matrix product (alternative syntax)
	NQubit operator()(NQubit const &q) const {
		return *this * q;
	}
};

// Usual quantum gates //

extern QGate qgNot;

#endif //QUEMULATOR_QUANTUM_HPP
