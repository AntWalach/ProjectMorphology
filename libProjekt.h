#ifndef LIBPROJEKT_H
#define LIBPROJEKT_H
#include <vector>
#include <iostream>
#include <string>
#include <exception>
#include <iomanip>
#include "libExceptions.h"

class Bitmap {
public:
	virtual unsigned int length() const = 0;
	virtual unsigned int width() const = 0;
	virtual bool& operator() (unsigned y, unsigned x) = 0;
	virtual bool operator()(unsigned y, unsigned x) const = 0;
	virtual ~Bitmap() {}
};

template <typename T, typename G>
class Transformation {
public:
	virtual G f_transform(Bitmap&) = 0;
	virtual T name() = 0;
	virtual ~Transformation() {}
};


class BitmapExt : public Bitmap {
public:
	unsigned int lengthY, lengthX;
	bool** bitmap;

	BitmapExt(unsigned int sizeY, unsigned int sizeX);

	unsigned int length() const;
	unsigned int width() const;
	bool& operator()(unsigned y, unsigned x);
	bool operator()(unsigned y, unsigned x) const;

	~BitmapExt();
};
/*
A function that sums neighbors with a specified value "true" or "false"

@param Orginal - bitmap
@param Y 
@param X
@param Wanted - what neighbors (with what value) we want to sum 
@param Neighbors

@result Neighbours - sum of neighbor wit a specified value for single bit

*/
int f_SumOfNeighbors(BitmapExt& orginal, int y, int x, bool wanted, int neighbors);

std::ostream& operator<<(std::ostream& out, const Bitmap& a);


/*
Inversion - negation, changing the pixels from true to false and false to true
*/
class Inversion : public Transformation<string, void> {
public:
	string name();
	void f_transform(Bitmap& orginal);
};

/*
By the edge bit of the image we mean the bit "true", which one of the neighbors is
bit "false". The erosion operation is to locate all edge bits of the image and then transform them into "false" value.
*/
class Erosion : public Transformation<string, void> {
public:
	string name();
	void f_transform(Bitmap& orginal);
};

/*
Reverse operation to erosion. All false bits in dilatation that are
 adjacent to true bits are set to true.
*/
class Dilatation : public Transformation<string, void> {
public:
	string name();
	void f_transform(Bitmap& orginal);
};

/*
 For each pixel p of the image we check the number of bits false and true  adjacent to it
 If it has more than 2 neighbors with true value, the new pixel value of pixel is true. 
 I would like to draw your attention to the fact that we consider the neighbors in the original painting,
not in the partially averaged image
*/
class Averaging : public Transformation<string, void> {
public:
	string name();
	void f_transform(Bitmap& orginal);
};

/*
Reset - convert all bits to false
*/
class Reset : public Transformation<string, void> {
public:
	string name();
	void f_transform(Bitmap& orginal);
};

/*
A class with 2 methods for adding and performing transformations on a bitmap
*/
class ComplexTransformation : public Transformation<string, void> {
public:
	std::vector <Transformation*> tab;
	string name();
	void f_AddTransformation(Transformation* p);
	void f_madeTransformations();
	void f_transform(Bitmap& orginal);
};
#endif 


