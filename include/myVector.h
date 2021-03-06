////////////////////////////////////////////////////////////
//
// myVector.h
//
// Uses myVector.cpp
//
////////////////////////////////////////////////////////////

#ifndef MYVECTOR_H
#define MYVECTOR_H
////////////////////////////////////////////////////////////
/// \brief Utility class for storing and altering data,
///        myVecotor is a set of functions to allow 
///		   the use of vectors with dot product and other function.
///			
///			Used for positions, size, acceleration , velocity etc..
///
////////////////////////////////////////////////////////////


class myVector
{

protected:
	////////////////////////////////////////////////////////////
	/// \brief Array of floats
	///
	///			Size of 2
	///
	////////////////////////////////////////////////////////////
	float m_afData[2];

public:
	////////////////////////////////////////////////////////////
	/// \brief Default constructor
	///
	/// Creates a myVector().
	///
	////////////////////////////////////////////////////////////
	myVector();

	////////////////////////////////////////////////////////////
	/// \brief Overlaoded constructor
	///
	/// \param float all values
	///
	/// sets both values in vector to the param
	///
	////////////////////////////////////////////////////////////
	myVector(float allValues);

	////////////////////////////////////////////////////////////
	/// \brief Overlaoded constructor
	///
	/// \param float x coord
	/// \param float y coord
	///
	/// sets the x y coord of the vector
	///
	////////////////////////////////////////////////////////////
	myVector(float i, float j);
	
	////////////////////////////////////////////////////////////
	/// \brief Finds maginitude
	///
	/// \param vector
	///	returns a float equal to the maginitude of the passed vector
	///
	////////////////////////////////////////////////////////////
	float magnitude(const myVector& other) const;

	////////////////////////////////////////////////////////////
	/// \brief Finds Angle
	///
	/// \param vector
	///	returns a float equal to the angle between the two values
	///
	////////////////////////////////////////////////////////////
	float angle(const myVector& other) const;

	////////////////////////////////////////////////////////////
	/// \brief Finds Angle
	///
	/// \param vector
	///	returns a float equal to the angle between the two values
	///
	////////////////////////////////////////////////////////////
	float dotProduct(const myVector& other) const;
	
	////////////////////////////////////////////////////////////
	/// \brief Finds unit vector
	///
	///	calculates and returns the unit vector
	///
	////////////////////////////////////////////////////////////
	myVector unitVector() const;

	////////////////////////////////////////////////////////////
	/// \brief subtracts one vector from another
	///
	///	calculates and returns the subtracted vector
	///
	////////////////////////////////////////////////////////////
	myVector subtract(const myVector& other) const;


	////////////////////////////////////////////////////////////
	/// \brief X coord
	///
	///	float xcoord of the vector
	///
	////////////////////////////////////////////////////////////
	float i() const;

	////////////////////////////////////////////////////////////
	/// \brief Y coord
	///
	///	float ycoord of the vector
	///
	////////////////////////////////////////////////////////////
	float j() const;



};

#endif

////////////////////////////////////////////////////////////
/// \class myVector.h
///
/// myVector.h is a 2d vector class that contains some mathmatical functions
///
/// Myvector can be constructed with its values specified or with out
///
/// Usage example:
/// \code
/// 
/// myVector Vectora(2, 10);
/// myVector Vectorb(5, 3);
/// float dot =  Vectora.dotProduct(Vectorb);
///
/// \endcode
///
////////////////////////////////////////////////////////////
