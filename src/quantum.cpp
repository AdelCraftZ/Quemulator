//
// Created by Adel on 11/02/2023.
//

#include "quantum.hpp"

#include <cstddef>
#include <complex>
#include <utility>
#include <functional>
#include <limits>
#include <iterator>
#include <random>
#include <stdexcept>

#include <boost/nondet_random.hpp>

using namespace std;

namespace qtm {
// Input iterator helper class for measuring an n-qubit.

class ProbIterator {
public:
	using iterator_category = input_iterator_tag;
	using difference_type = ptrdiff_t;
	using value_type = double;
	using pointer = vector<Complex>::iterator;
	using reference = pointer::value_type&;

	explicit ProbIterator(pointer p_weight)
		: _p_weight(std::move(p_weight))
	{}

	value_type operator*() const {
		return modulusSq(*_p_weight);
	}

	value_type operator->() const {
		return **this;
	}

	ProbIterator &operator++() {
		_p_weight++;
		return *this;
	}

	ProbIterator operator++(int) & { // NOLINT(cert-dcl21-cpp)
		ProbIterator bak = *this;
		++(*this);
		return bak;
	}

	friend bool operator==(ProbIterator const &a, ProbIterator const &b) {
		return a._p_weight == b._p_weight;
	}

	friend bool operator!=(ProbIterator const &a, ProbIterator const &b) {
		return !(a == b);
	}
private:
	pointer _p_weight;
};

// NQubit class //

NQubit &NQubit::operator*=(scalar_t s) const {
	for (auto &comp : _components) {
		comp *= s;
	}

	return const_cast<NQubit&>(*this);
}

NQubit NQubit::operator*(NQubit const &q) const {
	NQubit ret(_components.size() * q._components.size());

	// algorithm for Kronecker product
	auto it = ret._components.begin();
	for (auto const &compThis : _components) {
		for (auto const &compOther : q._components) {
			*it++ = compThis * compOther;
		}
	}

	return ret;
}

NQubit measure(NQubit const &q) {
	// TODO: Provide a way to specify the RNG seed.
	thread_local mt19937 rng((boost::random_device())());

	NQubit::size_type oneIdx = 0;
	for (
		auto pick = generate_canonical<scalar_t, numeric_limits<scalar_t>::digits>(rng);
		oneIdx < q._components.size();
		oneIdx++
	) {
		scalar_t modulusSqCur = modulusSq(q._components[oneIdx]);
		if (pick < modulusSqCur) { break; }
		pick -= modulusSqCur;
	}

	return NQubit(q._components.size(), oneIdx);
}

// Gate class //

NQubit Gate::operator()(NQubit const &q) const {
	if (_size != q.getDim()) {
		throw logic_error(string("gate matrix column count is not equal to n-qubit dimension (") + to_string(_size) + " != " + to_string(q.getDim()) + ")");
	}

	NQubit ret(q._components.size());

	// algorithm for matrix product
	for (size_type i = 0; i < _size; i++) {
		size_type start = _size * i;
		ret._components[i] = 0;
		for (size_type j = 0; j < _size; j++) {
			ret._components[i] += _coeffs[start + j] * q._components[j];
		}
	}

	return ret;
}

Gate Gate::operator()(Gate const &g) const {
	if (_size != g._size) {
		throw logic_error(string("gate matrix column count is not equal to n-qubit dimension (") + to_string(_size) + " != " + to_string(g._size) + ")");
	}

	Gate ret(g._size);

	// algorithm for matrix product
	for (size_type i = 0; i < _size; i++) {
		size_type start = _size * i;
		for (size_type j = 0; j < _size; j++) {
			size_type dest = start + j;
			ret._coeffs[dest] = 0;
			for (size_type k = 0; k < _size; k++) {
				ret._coeffs[dest] += _coeffs[start + k] * g._coeffs[j + _size * k];
			}
		}
	}

	return ret;
}

Gate Gate::operator*(const Gate &g) const {
	// Create a new Gate object with the correct dimensions
	Gate ret(_size * g._size);

	// loop through each row in the current object
	for (size_type i = 0; i < _size; i++) {
		// loop through each row in the other object
		for (size_type j = 0; j < g._size; j++) {
			// loop through each column in the current object
			for (size_type k = 0; k < _size; k++) {
				// loop through each column in the other object
				for (size_type l = 0; l < g._size; l++) {
					// compute the index in the result vector
					size_t index = (i * g._size + j) * ret._size + k * g._size + l;

					// compute the product of the corresponding elements in the two matrices
					ret._coeffs[index] = _coeffs[_size * i + k] * g._coeffs[g._size * j + l];
				}
			}
		}
	}

	return ret;
}
} // qtm
