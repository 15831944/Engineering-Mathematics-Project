# coding: utf-8
import numpy as np

def mat(a):
	result = "Matrix A("
	result += str(a.shape[0])
	result += ","
	result += str(a.shape[1])
	result += ",{"
	result += ','.join(str(e) for e in(a.flatten().tolist()))
	result +="});"
	return result

if __name__ == "__main__":
	s = int(input())
	a = np.random.randint(5, size=(s, s))
	print(mat(a))
	print(np.linalg.det(a))