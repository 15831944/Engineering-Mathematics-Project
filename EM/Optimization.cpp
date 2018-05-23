#include "Optimization.h"


Vector getGradient(const Equation& eqt, const Vector& vec, bool numWay) {
	if (numWay)
		return numericalGetGradient(eqt, vec);
	else
		return DeriGetGradient(eqt, vec);

}

Matrix getHessian(const Equation& eqt,const Vector& vec, bool numWay) {
	if (numWay)
		return numericalGetHessian(eqt, vec);
	else
		return DeriGetHessian(eqt, vec);
}

Vector DeriGetGradient(const Equation& eqt, const Vector& vec) {
	// get gradient
	Vector gradient(vec.dim_);
	for (int i = 0; i < vec.dim_; ++i) {
		gradient.data_[i] = Equation::calcEquation(eqt.directionalDerivatives[i], vec);
	}
	return gradient;
}

Matrix DeriGetHessian(const Equation& eqt, const Vector& vec) {
	// get hessian
	Matrix hessian(vec.dim_, vec.dim_);
	for (int i = 0; i < hessian.data_.size(); ++i) {
		hessian.data_[i] = Equation::calcEquation(eqt.secondPartialDerivatives[i],vec);
	}

	// return inverse of hessian

	return hessian;

}

Vector calcBound(const Vector& vecL, const Vector& vecU, Vector p, Vector dir) {
	Vector bound({BIGNUM,-BIGNUM});
	for (int i = 0; i < p.dim_; ++i) {
		NumType extrem1, extrem2;
		extrem1 = (vecU.data_[i] - p.data_[i]) / dir.data_[i];
		extrem2 = (vecL.data_[i] - p.data_[i]) / dir.data_[i];
		bound.data_[0] = std::fmin(bound.data_[0], std::fmin(extrem1, extrem2));
		bound.data_[1] = std::fmax(bound.data_[1], std::fmax(extrem1, extrem2));
	}
	return bound;
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
		return (upLim+lowLim)/2;
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

void optimize(const Equation& eqt, Vector& vec, Vector& limX, Vector& limY, const string& method, string& info, bool numWay,int iter) {
	
	Vector direction,gradient;
	NumType val;
	gradient = getGradient(eqt, vec,numWay);
	val = Equation::calcEquation(eqt, vec);
	Vector vecU(vec.dim_), vecL(vec.dim_),bound;
	vecU.data_[0] = limX.data_[1];
	vecL.data_[0] = limX.data_[0];
	if (vec.dim_ == 2) {
		vecU.data_[1] = limY.data_[1];
		vecL.data_[1] = limY.data_[0];
	}

	if (method == "Steep Decent") {
		direction = gradient.Scalar(-1);
		bound = calcBound(vecL, vecU, vec, direction);
		NumType alpha = goldenSectionSearch(eqt, vecL, vecU, vec, direction, bound.data_[0], bound.data_[1]);
		vec = vec + direction.Scalar(alpha);
		info += "\n h = " + direction.ToString();
		info += "\n alpha = " + std::to_string(alpha);
		info += "\n x = " + vec.ToString();
	}
	else if (method == "Newton Method") {
		Matrix hessian = getHessian(eqt, vec,numWay); 
		info += "\n Hessian = \n" + hessian.ToString();
		Matrix hessianInv = hessian.Inv();
		info += "Hessian Inverse = \n" + hessianInv.ToString();
		hessianInv = hessianInv * gradient;
		direction = Vector(hessianInv).Scalar(-1);
		vec = vec + direction;
		info += "h = " + direction.ToString();
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
		bound = calcBound(vecL, vecU, vec, s);
		NumType alpha = goldenSectionSearch(eqt, vecL, vecU, vec, s, bound.data_[0], bound.data_[1]);
		info += "\n S = " + s.ToString();
		vec = vec + s.Scalar(alpha);
		info += "\n X" + std::to_string(vec.dim_ + 1) + " = " + vec.ToString();
	}
	else if (method == "Conjugate Gradient") {
		static string func;
		static Vector lastGradient;
		static Vector lastDirection;

		if (eqt.ToString() != func || iter==1) {
			func = eqt.ToString();
			lastGradient = gradient;
			direction = lastGradient.Scalar(-1);
			lastDirection = direction;
		}
		else {
			NumType beta = gradient.Dot(gradient) / lastGradient.Dot(lastGradient);
			direction = gradient.Scalar(-1) + lastDirection.Scalar(beta);
			lastGradient = gradient;
			lastDirection = direction;

		}
		bound = calcBound(vecL, vecU, vec, direction);
		NumType alpha = goldenSectionSearch(eqt, vecL, vecU, vec, direction, bound.data_[0], bound.data_[1]);
		vec = vec + direction.Scalar(alpha);
		info += "\n S= " + direction.ToString();
		info += "\n alpha= " + std::to_string(alpha);
		info += "\n X= " + vec.ToString();
	}
	else if (method == "Quasi Newton") {
		static string func;
		static Matrix lastHInv;
		static Vector lastGradient;
		static Vector lastVec;
		Matrix HInv;
		if (func != eqt.ToString() || iter==1) {
			func = eqt.ToString();
			lastHInv = Matrix(vec.dim_, vec.dim_);
			// Set H to I
			//for (int i = 0; i < vec.dim_; ++i)
			//	lastHInv.data_[i*vec.dim_ + i] = 1;
			lastHInv = getHessian(eqt, vec, numWay);
			info += "H init = \n" + lastHInv.ToString();
			lastHInv = lastHInv.Inv();
			info += "H init Inv = \n" + lastHInv.ToString();
			lastGradient = gradient;
			lastVec = vec;
			direction = lastHInv * gradient;
			vec = vec + direction;
			info += "\n X= " + vec.ToString();
		}
		else {
			//DFP
			Vector dgradient = gradient - lastGradient, dvec = vec - lastVec;
			HInv = lastHInv + Matrix::vecMulMat(dvec, dvec).Scale(1 / (dvec.Dot(dgradient))) - ((lastHInv*dgradient)*((Matrix(dgradient).Trans())*lastHInv)).Scale(1 / (Matrix(dgradient).Trans() * (lastHInv*dgradient)).data_[0]);
			lastHInv = HInv;
			direction = (HInv * gradient);
			bound = calcBound(vecL, vecU, vec, direction);
			NumType alpha = goldenSectionSearch(eqt, vecL, vecU, vec, direction, bound.data_[0], bound.data_[1]);
			vec = vec + direction.Scalar(alpha);
			info += "\n h inv= \n" + HInv.ToString();
			info += "\n alpha= " + std::to_string(alpha);
			info += "\n X= " + vec.ToString();
			lastGradient = gradient;
			lastVec = vec;
		}
	}
	
}

Vector numericalGetGradient(const Equation& eqt, const Vector& vec) {
	Vector gradient(vec.dim_), vecp;
	NumType val1 = Equation::calcEquation(eqt,vec), val2;
	for (int i = 0; i < vec.dim_; ++i) {
		vecp = vec;
		vecp.data_[i] += NumDlt;
		val2 = Equation::calcEquation(eqt, vecp);
		gradient.data_[i] = (val2 - val1) / NumDlt;
	}
	return gradient;
}


Matrix numericalGetHessian(const Equation& eqt, const Vector& vec) {
	Matrix hessian(vec.dim_, vec.dim_);
	Vector grad1 = numericalGetGradient(eqt, vec), grad2,vecp;
	for (int i = 0; i < vec.dim_; ++i) {
		vecp = vec;
		vecp.data_[i] += NumDlt;
		grad2 = numericalGetGradient(eqt, vecp);
		for (int j = 0; j < vec.dim_; ++j) {
			int loca = i * vec.dim_ + j;
			hessian.data_[loca] = (grad2.data_[j] - grad1.data_[j]) / NumDlt;
		}
	}
	return hessian;
}
