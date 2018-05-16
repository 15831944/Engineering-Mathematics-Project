#include "Optimization.h"


Vector getGradient(const Equation& eqt, const Vector& vec) {
	// get gradient
	Vector gradient(vec.dim_);
	for (int i = 0; i < vec.dim_; ++i) {
		gradient.data_[i] = Equation::calcEquation(eqt.directionalDerivatives[i], vec);
	}
	return gradient;
}

Matrix getHessian(const Equation& eqt, const Vector& vec) {
	// get hessian
	Matrix hessian(vec.dim_, vec.dim_);
	for (int i = 0; i < hessian.data_.size(); ++i) {
		hessian.data_[i] = Equation::calcEquation(eqt.secondPartialDerivatives[i],vec);
	}

	// return inverse of hessian

	return hessian;

}

void optimize(const Equation& eqt, Vector& vec, const string& method, string& info) {
	Vector direction,gradient;
	NumType val;
	gradient = getGradient(eqt, vec);
	info += "\n point = " + vec.ToString();
	val = Equation::calcEquation(eqt, vec);
	info += "\n val = " + std::to_string(val);
	if (method == "Gradient Decent") {
		direction = gradient.Scalar(-StepSize[Gradient]);

	}
	else if (method == "Newton Method") {
		Matrix hessian = getHessian(eqt, vec); 
		info += "\n hessian = " + hessian.ToString();
		Matrix hessianInv = hessian.Inv();
		info += "\n hessian Inv = " + hessianInv.ToString();
		hessianInv = hessianInv * gradient;
		direction = Vector(hessianInv).Scalar(-1);
	}
	vec = vec + direction;
	info += "\n h = " + direction.ToString();
}
