#include "Optimization.h"


Vector getGradient(Equation eqt, Vector vec) {
	// get directional derivation
	vector<Equation> directionalDerivatives(vec.dim_);
	for (int i = 0; i < vec.dim_; ++i) {
		directionalDerivatives[i] = eqt.PartialDerivative('x' + i);
	}
	// get gradient
	Vector gradient(vec.dim_);
	for (int i = 0; i < vec.dim_; ++i) {
		gradient.data_[i] = Equation::calcEquation(eqt, vec);
	}
	return gradient;
}

Vector getDirection(Equation eqt, Vector vec, string method) {
	Vector direction;
	if (method == "Powell Method") {

	}
	else if (method == "Gradient Decent") {
		direction = getGradient(eqt, vec).Scalar(-1);
	}

	return direction;
}