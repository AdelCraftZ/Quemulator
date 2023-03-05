//
// Created by Adel on 11/02/2023.
//

#ifndef QUEMULATOR_QUANTUM_HPP
#define QUEMULATOR_QUANTUM_HPP

#include "config.hpp"
#include "traits.hpp"

#include "math.hpp"

#include <cmath>
#include <cstddef>
#include <cstdint>
#include <utility>
#include <complex>
#include <array>
#include <vector>
#include <tuple>
#include <memory>
#include <type_traits>
#include <iterator>

namespace qtm {
class NQubit {
	friend NQubit measure(NQubit const&);
	friend class Gate;
	/*
private:
	static std::size_t CONSTEVAL log2(std::size_t n) {
		return n == 1 ? 0 : 1 + log2(n >> 1);
	}
	*/
public:
	using size_type = std::vector<Complex>::size_type;

	template<typename T, typename ...Ts, std::enable_if_t<std::is_convertible_v<T, Complex>>* = nullptr>
	NQubit(T component, Ts &&...components)
			: /*_n(log2(1 + sizeof...(components))), */_components({std::forward<T>(component), std::forward<Ts>(components)...})
	{
		static_assert(QTM_IS_POWER_OF_2(1 + sizeof...(components)), "NQubit dimension must be a power of 2");
	}

	size_type getDim() const {
		return _components.size();
	}

	/*
	bool operator==(NQubit const &other) const {
		_normalize();
		other._normalize();

		return _components == other._components;
	}
	*/

	bool operator==(NQubit const &other) const = delete;

	// multiplication by a scalar
	NQubit &operator*=(scalar_t s) const;

	// Kronecker product
	NQubit operator*(NQubit const &q) const;
private:
	static scalar_t constexpr _norm_limit = 1 << 16;

	//std::size_t _n; // log base 2 of dimension;
	mutable std::vector<Complex> _components;

	explicit CONSTEXPR20 NQubit(size_type dim)
		: /*_n(0), */_components(dim)
	{}

	explicit CONSTEXPR20 NQubit(size_type dim, size_type oneIdx)
		: /*_n(0), */_components(dim, 0)
	{
		_components[oneIdx] = 1;
	}

	/*
	[[nodiscard]] scalar_t _calcNormSq() const;

	void _normalize() const {
		*this *= 1.0 / std::sqrt(_calcNormSq());
	}

	void _normalizeIfNeeded() const {
		if (_calcNormSq() > _norm_limit) {
			_normalize();
		}
	}
	 */

	auto CONSTEXPR20 begin() noexcept {
		return _components.begin();
	}

	auto CONSTEXPR20 end() noexcept {
		return _components.end();
	}

	[[nodiscard]] auto CONSTEXPR20 cbegin() const noexcept {
		return _components.cbegin();
	}

	[[nodiscard]] auto CONSTEXPR20 cend() const noexcept {
		return _components.cend();
	}

	std::vector<Complex>::reference CONSTEXPR20 operator[](size_type i) noexcept {
		return _components[i];
	}

	std::vector<Complex>::const_reference CONSTEXPR20 operator[](size_type i) const noexcept {
		return _components[i];
	}
};

class Gate {
public:
	using size_type = std::vector<Complex>::size_type;

	template<std::size_t n, std::size_t ...ns>
	constexpr Gate(Complex const (&row)[n], Complex const (&...rows)[ns])
		:  _size(n), _coeffs(_size * _size)
	{
		static_assert((... && (n == ns)), "all rows must have the same size");
		static_assert(n == 1 + sizeof...(ns), "number of columns must equal number of rows");
		static_assert(QTM_IS_POWER_OF_2(n), "both the number of columns and rows must be a power of 2");

		auto pos = std::copy(row, row + n, _coeffs.begin());
		((pos = std::copy(rows, rows + n, pos)), ...);
	}

	// Matrix product
	NQubit operator()(NQubit const&) const;

	// Matrix product
	Gate operator()(Gate const&) const;

	// Kronecker product
	Gate operator*(Gate const&) const;
private:
	size_type _size;
	std::vector<Complex> _coeffs;

	Gate(size_type size)
		: _size(size), _coeffs(_size * _size)
	{}
};

// Usual quantum gates //

extern Gate const gIdentity;    // identity
extern Gate const gX;   // Pauli's X (NOT)
extern Gate const gY;   // Pauli's Y
extern Gate const gZ;   // Pauli's Z
extern Gate const gS;   // phase gate S
extern Gate const gSqrtNot; // sqrt of X
extern Gate const gH;   // Hadamard
extern Gate const gCX;  // controlled X
extern Gate const gCXReverse;   // reverse controlled X
extern Gate const gAntiX;    // reverse controlled X
extern Gate const gCZ;   // controlled Z
extern Gate const gDX;  // double controlled X
extern Gate const gSwap;    // swap
extern Gate const gISwap;   // imaginary swap
extern Gate const gFSwap;   // fermionic swap

// phase shift
inline Gate makeGPhaseShift(Complex const &power) {
	return {
		{1, 0},
		{0, exp(power)}
	};
}

extern Gate const gT;   // phase gate T

// controlled shift
inline Gate makeGControlledShift(Complex const &power) {
	return {
		{1, 0, 0, 0},
		{0, 1, 0, 0},
		{0, 0, 1, 0},
		{0, 0, 0, exp(power)},
	};
}

extern Gate const gCS;   // controlled phase S

// rotation about x-axis
inline Gate makeGRX(scalar_t theta);

// rotation about x-axis
inline Gate makeGRY(scalar_t theta);

// rotation about x-axis
inline Gate makeGRZ(scalar_t theta);
} // qtm

#endif //QUEMULATOR_QUANTUM_HPP
