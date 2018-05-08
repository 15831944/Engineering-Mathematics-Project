#include "Optimization.h"


Vector getGradient(const Equation& eqt, const Vector& vec) {
	// get gradient
	Vector gradient(vec.dim_);
	for (int i = 0; i < vec.dim_; ++i) {
		gradient.data_[i] = Equation::calcEquation(eqt.directionalDerivatives[i], vec);
	}
	return gradient;
}

void optimize(const Equation& eqt, Vector& vec, const string& method, string& info) {
	Vector direction;
	NumType val;
	if (method == "Gradient Decent") {
		direction = getGradient(eqt, vec).Scalar(-StepSize[Gradient]);
		info += "\n point = " + vec.ToString();
		val = Equation::calcEquation(eqt, vec);
		info += "\n val = " + std::to_string(val);
		info += "\n direction = " + direction.ToString();
		vec = vec + direction;
		val = Equation::calcEquation(eqt, vec);
		info += "\n point = " + vec.ToString();
		info += "\n val = " + std::to_string(val);
		
	}

}
