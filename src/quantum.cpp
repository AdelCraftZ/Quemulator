//
// Created by Adel on 11/02/2023.
//

#include "quantum.hpp"

#include <cstddef>
#include <complex>
#include <utility>
#include <functional>

using namespace std;

static constexpr q_scalar_t NORM_LIMIT = 1 << 16; // Set the threshold from which to normalize the qubit.

// Usual quantum gates //

QGate qgNot({
	{0, 1},
	{1, 0}
});

// NQubit class //

q_scalar_t NQubit::_calcNormSq() {
	q_scalar_t normSq = 0;
	for (auto const &comp : _components) {
		normSq += norm(comp);   // What the standard calls "norm" is actually the squared norm.
	}
	return normSq;
}

void NQubit::_normalize() {
	*this *= 1.0 / sqrt(_calcNormSq());
}

void NQubit::_normalizeIfNeeded() {
	if (_calcNormSq() > NORM_LIMIT) {
		_normalize();
	}
}

NQubit &NQubit::operator*=(q_scalar_t s) {
	for (auto &comp : _components) {
		comp *= s;
	}

	return *this;
}

NQubit NQubit::operator*(NQubit const &q) const {
	std::vector<QComplex> newComponents(_components.size() * q._components.size());

	// algorithm for Kronecker product
	auto it = newComponents.begin();
	for (auto const &compThis : _components) {
		for (auto const &compOther : q._components) {
			*it++ = compThis * compOther;
		}
	}

	return NQubit(std::move(newComponents));
}

NQubit NQubit::measure() {
	q_scalar_t x;
	for (size_t i = 0; i < 50; i++) {
		x = (*_p_rng)();
	}

	return NQubit();
}

// QGate class //

QGate::QGate(std::initializer_list<std::initializer_list<QComplex>> coeffs)
	: _rowCnt(coeffs.size()), _colCnt((empty(coeffs) ? 0 : coeffs.begin()->size())), _coeffs(_rowCnt * _colCnt)
{

	auto it = _coeffs.begin();
	for (auto const row : coeffs) {
		for (auto const &coeff : row) {
			*it++ = coeff;
		}
	}
}

NQubit QGate::operator*(NQubit const &q) const {
	std::vector<QComplex> newComponents(q._components.size(), 0);

	// algorithm for matrix product
	for (size_t i = 0; i < _rowCnt; i++) {
		size_t start = _colCnt * i;
		for (size_t j = 0; j < _colCnt; j++) {
			newComponents[i] += _coeffs[start + j] * q._components[j];
		}
	}

	return NQubit(std::move(newComponents));
}
