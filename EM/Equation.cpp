#include "Equation.h"
#include <algorithm>

vector<Equation> equations;

inline bool is_numChar(char c) {
	if (c == '.')
		return true;
	if (c >= '0' && c <= '9')
		return true;
	return false;
}

inline NumType getNum(const string& equation, size_t& nowPosi) {
	if (!is_numChar(equation[nowPosi]))
		return 1;
	NumType result = 0;
	bool is_offset = false;
	int offset = 0;
	while (nowPosi < equation.length() && is_numChar(equation[nowPosi])) {
		if (equation[nowPosi] == '.') {
			is_offset = true;
			++nowPosi;
			continue;
		}
		result = result * 10 + equation[nowPosi] - '0';
		if (is_offset)
			++offset;
		++nowPosi;
	}
	result = result / pow(10, offset);
	return result;
}

Equation::Equation(string equation) {
	// 0 nomial will have bug 
	this->str = equation;
	dim_ = 1;
	equation.erase(std::remove(equation.begin(), equation.end(), '*'), equation.end());
	equation.erase(std::remove(equation.begin(), equation.end(), ' '), equation.end());
	equation.erase(std::remove(equation.begin(), equation.end(), '('), equation.end());
	equation.erase(std::remove(equation.begin(), equation.end(), ')'), equation.end());
	Nomial nowNomial;
	bool neg;
	
	size_t nowPosi = 0, opPosi = equation.find('+', nowPosi);

	while (nowPosi < equation.length()) {
		nowNomial.coef = 0;
		nowNomial.powX = 0;
		nowNomial.powY = 0;

		// check sign
		if (equation[nowPosi] == '-') {
			neg = true;
			++nowPosi;
		}
		else if (equation[nowPosi] == '+') {
			neg = false;
			++nowPosi;
		}
		else {
			neg = false;
		}

		// get coef
		nowNomial.coef = getNum(equation, nowPosi);
		if (neg)
			nowNomial.coef *= -1;

		// check end

		if (nowPosi >= equation.length()) {
			this->polynomial_.push_back(nowNomial);
			break;
		}
		// check x
		if (equation[nowPosi] == 'x') {
			nowNomial.powX = 1;
			if (nowPosi + 1 >= equation.length()) {
				this->polynomial_.push_back(nowNomial);
				break;
			}
			if (equation[++nowPosi] == '^') {
				if (equation[nowPosi + 1] == '-') {
					neg = true;
					nowPosi += 1;
				}
				else
					neg = false;
				++nowPosi;
				nowNomial.powX = getNum(equation, nowPosi);
				if (neg)
					nowNomial.powX *= -1;
			}
		}
		
		// check y
		if (equation[nowPosi] == 'y') {
			dim_ = 2;
			nowNomial.powY = 1;
			if (nowPosi + 1 >= equation.length()) {
				this->polynomial_.push_back(nowNomial);
				break;
			}
			if (equation[++nowPosi] == '^') {
				if (equation[nowPosi + 1] == '-') {
					neg = true;
					nowPosi += 1;
				}
				else
					neg = false;
				++nowPosi;
				nowNomial.powY = getNum(equation, nowPosi);
				if (neg)
					nowNomial.powY *= -1;
			}
		}

		// push to polynomial
		this->polynomial_.push_back(nowNomial);
	}

	// set directional derivative
	this->directionalDerivatives.resize(this->dim_);
	for (int i = 0; i < this->dim_; ++i) {
		directionalDerivatives[i] = this->PartialDerivative('x' + i);
	}

	// set second partial Derivatives

	this->secondPartialDerivatives.resize(this->dim_ * this->dim_);
	for (int i = 0; i < this->dim_; ++i) {
		for (int j = 0; j < this->dim_; ++j) {
			int ith = i * this->dim_ + j;
			this->secondPartialDerivatives[ith] = this->directionalDerivatives[i].PartialDerivative('x' + j);
		}
	}

}

vector<string> loadEquations(string path) {
	std::ifstream fin(path);
	vector<string> display;
	string line;
	while (fin >> line) {
		display.push_back(line);
		equations.push_back(Equation(line));
	}
	return display;
}

NumType Equation::calcEquation(Equation eqt,Vector vec) {
	NumType result = 0,X=vec.data_[0],Y= calcDlt;
	if (vec.dim_ == 2)
		Y = vec.data_[1];

	if (std::abs(X) < calcDlt)
		X = calcDlt;
	else if (std::abs(Y) < calcDlt)
		Y = calcDlt;
	for (int i = 0; i < eqt.polynomial_.size(); ++i) {
		result += eqt.polynomial_[i].coef *( (X==0.0 || eqt.polynomial_[i].powX==0.0)? 1:pow(X, eqt.polynomial_[i].powX)) * ((Y == 0.0 || eqt.polynomial_[i].powY == 0.0) ? 1:pow(Y, eqt.polynomial_[i].powY));
	}
	return result;
}

Equation Equation::operator=(const Equation& rhs) {
	this->polynomial_ = rhs.polynomial_;
	this->dim_ = rhs.dim_;
	this->str = rhs.str;
	return *this;
}

Equation Equation::operator=(const string& rhs) {
	*this = Equation(rhs);
	return *this;
}

Equation Equation::PartialDerivative(char respectTo) {
	Equation result = *this;
	if (respectTo == 'x') {
		for (int i = 0; i < result.polynomial_.size(); ++i) {
			// no x term
			if (result.polynomial_[i].powX == 0.0) {
				result.polynomial_.erase(result.polynomial_.begin() + i);
				--i;
			}
			else {
				// partial derivative
				result.polynomial_[i].coef *= result.polynomial_[i].powX;
				result.polynomial_[i].powX -= 1;
			}
		}
	}
	else if (respectTo == 'y') {
		for (int i = 0; i < result.polynomial_.size(); ++i) {
			// no y term
			if (result.polynomial_[i].powY == 0.0) {
				result.polynomial_.erase(result.polynomial_.begin() + i);
				--i;
			}
			else {
				// partial derivative
				result.polynomial_[i].coef *= result.polynomial_[i].powY;
				result.polynomial_[i].powY -= 1;
			}
		}
	}
	return result;
}

int Equation::getDim() {
	return this->dim_;
}

string Equation::ToString() const{
	return this->str;
}