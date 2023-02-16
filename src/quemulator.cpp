#include <cstdlib>
#include <iostream>

#include "quantum.hpp"

int main() {
	NQubit q0({
		1,
		0
	});
	NQubit q1({
		0,
		1
	});

	NQubit q11 = q1 * q1;

	NQubit r = qgNot(q1);

	return EXIT_SUCCESS;
}
