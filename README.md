# Engineering-Mathematics-Project

## Coding Style

Function 前要先做Check
example

```cpp
Matrix::Matrix(int rSize, int cSize) {
	// check
	if (rSize <= 0 || cSize <= 0)
		throw "Wrong Size!";
	//
	this->data_.resize(rSize*cSize);
	this->shape_[0] = rSize;
	this->shape_[1] = cSize;
}
```
