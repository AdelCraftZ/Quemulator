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
#include <memory>
#include <random>

#include <boost/nondet_random.hpp>

using q_scalar_t = double;
using QComplex = std::complex<q_scalar_t>;

class QRandomizer {
public:
	using rng_seed_t = decltype(boost::random_device()());

	explicit QRandomizer(rng_seed_t seed = boost::random_device()())
		: _rngRaw(seed), dist(0, 1)
	{}

	q_scalar_t operator()() {
		return dist(_rngRaw);
	}
private:
	std::mt19937 _rngRaw;
	std::uniform_real_distribution<q_scalar_t> dist;
};

class NQubit {
	friend class QGate;
public:
	explicit NQubit(std::size_t n = 1, std::shared_ptr<QRandomizer> p_rng = std::make_shared<QRandomizer>())
		: _p_rng(std::move(p_rng)), _components(1 << n)
	{}

	NQubit(std::initializer_list<QComplex> components, std::shared_ptr<QRandomizer> p_rng = std::make_shared<QRandomizer>())
		: _p_rng(std::move(p_rng)), _components(components)
	{}

	template<class InputIt>
	NQubit(InputIt first, InputIt last, std::shared_ptr<QRandomizer> p_rng = std::make_shared<QRandomizer>())
		: _p_rng(std::move(p_rng)), _components(first, last)
	{}

	// multiplication by a scalar
	NQubit &operator*=(q_scalar_t s);

	// Kronecker product
	NQubit operator*(NQubit const &q) const;

	NQubit measure();
private:
	std::shared_ptr<QRandomizer> _p_rng;
	std::vector<QComplex> _components;

	explicit NQubit(std::vector<QComplex> &&components)
		: _components(std::move(components))
	{}

	q_scalar_t _calcNormSq();

	void _normalize();

	void _normalizeIfNeeded();
};

class QGate {
public:
	QGate(std::initializer_list<std::initializer_list<QComplex>> coeffs);

	// matrix product
	NQubit operator*(NQubit const &q) const;

	// matrix product (alternative syntax)
	NQubit operator()(NQubit const &q) const {
		return *this * q;
	}
private:
	std::size_t _rowCnt;
	std::size_t _colCnt;
	std::vector<QComplex> _coeffs;
};

// Usual quantum gates //

extern QGate qgNot;

#endif //QUEMULATOR_QUANTUM_HPP
