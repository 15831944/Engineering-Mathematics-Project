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


Vector goldenSectionSearch(const Equation& eqt, const Vector& vecL, const Vector& vecU, int searchDim) {
	if (vecU.data_[searchDim] - vecL.data_[searchDim] < OptDlt)
		return vecU;
	NumType d = (vecU.data_[searchDim] - vecL.data_[searchDim]) * GoldenRatio;
	Vector vec1 = vecL, vec2 = vecU;
	vec1.data_[searchDim] += d;
	vec2.data_[searchDim] -= d;
	NumType fv1 = Equation::calcEquation(eqt, vec1), fv2 = Equation::calcEquation(eqt, vec2);
	if (fv1 > fv2) {
		return goldenSectionSearch(eqt, vecL, vec1, searchDim);
	}
	else {
		return goldenSectionSearch(eqt, vec2, vecU, searchDim);
	}


}

NumType goldenSectionSearch(const Equation& eqt, const Vector& vecL, const Vector& vecU, Vector p, Vector dir, NumType lowLim, NumType upLim) {
	if (upLim - lowLim < OptDlt)
		return upLim;
	NumType d = (upLim - lowLim) * GoldenRatio;
	NumType a1 = lowLim + d,a2 = upLim - d;
	NumType fv1 = Equation::calcEquation(eqt, p + dir.Scalar(a1)), fv2 = Equation::calcEquation(eqt, p + dir.Scalar(a2));
	if (fv1 > fv2) {
		return goldenSectionSearch(eqt, vecL, vecU, p,dir,lowLim,a1);
	}
	else {
		return goldenSectionSearch(eqt, vecL, vecU, p, dir, a2, upLim);
	}
}

void optimize(const Equation& eqt, Vector& vec, Vector& limX, Vector& limY, const string& method, string& info) {
	Vector direction,gradient;
	NumType val;
	gradient = getGradient(eqt, vec);
	info += "\n point = " + vec.ToString();
	val = Equation::calcEquation(eqt, vec);
	info += "\n val = " + std::to_string(val);
	Vector vecU(vec.dim_), vecL(vec.dim_);
	vecU.data_[0] = limX.data_[1];
	vecL.data_[0] = limX.data_[0];
	if (vec.dim_ == 2) {
		vecU.data_[1] = limY.data_[1];
		vecL.data_[1] = limY.data_[0];
	}

	if (method == "Gradient Decent") {
		direction = gradient.Scalar(-StepSize[Gradient]);
		vec = vec + direction;
		info += "\n h = " + direction.ToString();
	}
	else if (method == "Newton Method") {
		Matrix hessian = getHessian(eqt, vec); 
		info += "\n hessian = " + hessian.ToString();
		Matrix hessianInv = hessian.Inv();
		info += "\n hessian Inv = " + hessianInv.ToString();
		hessianInv = hessianInv * gradient;
		direction = Vector(hessianInv).Scalar(-1);
		vec = vec + direction;
		info += "\n h = " + direction.ToString();
	}
	else if (method == "Powell Method") {
		// one iteration
		Vector s(vec.dim_);
		for (int i = 0; i < vec.dim_; ++i) {
			Vector newL = vecL, newU = vecU;
			info += "\n i = " + std::to_string(i + 1);
			for (int j = 0; j < vec.dim_; ++j) {
				if (i == j)continue;
				newL.data_[j] = vec.data_[j];
				newU.data_[j] = vec.data_[j];
			}
			s.data_[i] = goldenSectionSearch(eqt, newL, newU,i).data_[i] - vec.data_[i];
			vec.data_[i] += s.data_[i];
			info += "\n X" + std::to_string(i + 1) + " = " + vec.ToString();
			s.data_[i] = s.data_[i];
		}
		info += "\n i = " + std::to_string(vec.dim_+1);
		NumType alpha = goldenSectionSearch(eqt, vecL, vecU, vec, s, 1e-9, 1e9);
		vec = vec + s.Scalar(alpha);
		info += "\n X" + std::to_string(vec.dim_ + 1) + " = " + vec.ToString();
	}
	
}
