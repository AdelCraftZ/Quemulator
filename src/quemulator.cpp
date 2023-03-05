#include <cstdlib>

#include "quantum.hpp"

int main() {
	using namespace qtm;

	NQubit q0 = {
		1,
		0
	};
	NQubit q1 = {
		0,
		1
	};

	NQubit out = (gH * gH)(gCZ)(gZ * gZ)(gH * gH)(gX * gX)(gCZ)(gX * gX)(gH * gH)(q0 * q0);
	NQubit meas = measure(out);

	return EXIT_SUCCESS;
}
