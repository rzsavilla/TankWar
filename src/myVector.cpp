#include "myVector.h"
#include "math.h"

myVector::myVector()
{

}
myVector::myVector(float allValues)
{
	// make both values equal to the passed vlaue
	m_afData[0] = allValues;
	m_afData[1] = allValues;
}

myVector::myVector(float i, float j)
{
	// assign to passed values
	m_afData[0] = i;
	m_afData[1] = j;

}

float myVector::magnitude(const myVector& other) const
{
	// use pythagorus theorm to find magnitude
	float a,b,c;
	a = other.m_afData[0] * other.m_afData[0];
	b = other.m_afData[1] * other.m_afData[1];
	c = sqrt(a + b);
	return c;
}

float myVector::angle(const myVector& other)const
{
	//cos() = E/magA*magB

	// find the magnitude
	myVector A(m_afData[0], m_afData[1]);
	myVector B(other.m_afData[1], other.m_afData[1]);
	float magA;
	float magB;
	magA = A.magnitude(A);
	magB = other.magnitude(other);

	// dot product
	myVector C(m_afData[0], m_afData[1]);
	myVector D(other.m_afData[0], other.m_afData[1]);
	float E = C.dotProduct(D);

	float result = E / (magA * magB);
	// cos () = result
	// radians
	return acos(result);
}

float myVector::dotProduct(const myVector& other) const
{

	float i;
	float j;
	// multiply values
	i = m_afData[0] * other.m_afData[0];
	j = m_afData[1] * other.m_afData[1];
	// add values
	float fResult = i + j;
	return fResult;
}

myVector myVector::unitVector() const
{
	myVector A(m_afData[0], m_afData[1]);
	float magA;
	magA = A.magnitude(A);
	// divide values by the magnitude
	float x = m_afData[0] / magA;
	float y = m_afData[1] / magA;
	// set the vlaues of the vector
	A.m_afData[0] = x;
	A.m_afData[1] = y;
	return A;

}

float myVector::i() const
{
	return m_afData[0];
}
float myVector::j() const
{
	return m_afData[1];
}

myVector myVector::subtract(const myVector& other) const
{
	myVector result(other.i() - m_afData[0], other.j() - m_afData[1]);
	return result;
	
}
