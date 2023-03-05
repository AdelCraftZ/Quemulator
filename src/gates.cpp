//
// Created by Adel on 2023-02-19.
//

#include "quantum.hpp"
#include "math.hpp"

namespace qtm {
using namespace literals;

static scalar_t constexpr INV_SQRT_2 = 0.70710678118654752440084436210485;

Gate const gIdentity = {
	{1, 0},
	{0, 1}
};

Gate const gX = {
	{0, 1},
	{1, 0}
};

Gate const gY = Gate{
	{0, -1_i},
	{1_i, 0}
};

Gate const gZ = {
	{1, 0},
	{0, -1}
};

Gate const gS = {
	{1, 0},
	{0, 1_i}
};

Gate const gSqrtNot = {
	{0.5 + 0.5_i, 0.5 - 0.5_i},
	{0.5 - 0.5_i, 0.5 + 0.5_i}
};

Gate const gH = {
	{INV_SQRT_2, INV_SQRT_2},
	{INV_SQRT_2, -INV_SQRT_2}
};

Gate const gCX = {
	{1, 0, 0, 0},
	{0, 1, 0, 0},
	{0, 0, 0, 1},
	{0, 0, 1, 0},
};

Gate const gCXReverse = {
	{1, 0, 0, 0},
	{0, 0, 0, 1},
	{0, 0, 1, 0},
	{0, 1, 0, 0},
};

Gate const gAntiX = {
	{0, 1, 0, 0},
	{1, 0, 0, 0},
	{0, 0, 1, 0},
	{0, 0, 0, 1},

};

Gate const gCZ = {
	{1, 0, 0, 0},
	{0, 1, 0, 0},
	{0, 0, 1, 0},
	{0, 0, 0, -1}
};

Gate const gDX = {
	{1, 0, 0, 0},
	{0, 0, 1, 0},
	{0, 0, 0, 1},
	{0, 1, 0, 0},
};

Gate const gSwap = {
	{1, 0, 0, 0},
	{0, 0, 1, 0},
	{0, 1, 0, 0},
	{0, 0, 0, 1},
};

Gate const gISwap = {
	{1, 0, 0, 0},
	{0, 0, 1_i, 0},
	{0, 1_i, 0, 0},
	{0, 0, 0, 1},
};

Gate const gFSwap = {
	{1, 0, 0, 0},
	{0, 0, 1, 0},
	{0, 1, 0, 0},
	{0, 0, 0, -1},
};

Gate const gT = {
	{1, 0},
	{0, INV_SQRT_2 + INV_SQRT_2 * 1_i}
};

Gate const gCS = {
	{1, 0, 0, 0},
	{0, 1, 0, 0},
	{0, 0, 1, 0},
	{0, 0, 0, 1_i},
};

Gate makeGRX(scalar_t theta) {
	scalar_t halfTheta = theta / 2;
	Complex val1 = std::cos(halfTheta);
	Complex val2 = -1_i * std::sin(halfTheta);
	std::complex<double> val3 = 1;
	return {
		{val1, val2},
		{val2, val1}
	};
}

Gate makeGRY(scalar_t theta) {
	scalar_t halfTheta = theta / 2;
	Complex val1 = std::cos(halfTheta);
	Complex val2 = std::sin(halfTheta);
	std::complex<double> val3 = 1;
	return {
		{val1, -val2},
		{val2, val1}
	};
}

Gate makeGRZ(scalar_t theta) {
	scalar_t halfTheta = theta / 2;
	std::complex<double> val3 = 1;
	return {
		{exp(-1_i * halfTheta), 0},
		{0, exp(1_i * halfTheta)}
	};
}
} // namespace qtm
