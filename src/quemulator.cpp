#include <cstdlib>
#include <memory>

#include "quantum.hpp"

int main() {
	std::shared_ptr<QRandomizer> p_rng = std::make_shared<QRandomizer>();

	NQubit q0 = {
		1,
		0
	};
	NQubit q1 = {
		0,
		1
	};

	NQubit q11 = q1 * q1;

	NQubit r = qgNot(q1);

	q0.measure();
	q0.measure();
	q0.measure();
	q0.measure();

	return EXIT_SUCCESS;
}
