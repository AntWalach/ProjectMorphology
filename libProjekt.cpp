#include "libProjekt.h"
#include "libExceptions.h"

BitmapExt::BitmapExt(unsigned int sizeY, unsigned int sizeX) {
	lengthY = sizeY;
	lengthX = sizeX;
	if (lengthY <= 0 or lengthX <= 0)
		throw MyExceptionErrors::WrongArgument();

	// Creating a bitmap
	bitmap = new bool* [sizeY];
	for (int i = 0; i < sizeY; i++) {
		bitmap[i] = new bool[sizeX];
		for (int j = 0; j < sizeX; j++) {
			bitmap[i][j] = false;
		}
	}
}

// Length Y
unsigned int BitmapExt::length() const {
	return lengthY;
}

// Length X
unsigned int BitmapExt::width() const {
	return lengthX;
}

// Bitmap indexes
bool& BitmapExt::operator()(unsigned y, unsigned x) {
	if (lengthX < x or lengthY < y)
		throw MyExceptionErrors::WrongArgument();
	return bitmap[y][x];
}

// Bitmap cell value
bool BitmapExt::operator()(unsigned y, unsigned x) const {
	return bitmap[y][x];
}

// Dynamic array/bitmap destructor
BitmapExt::~BitmapExt() {
	for (unsigned int i = 0; i < length(); i++)
		delete bitmap[i];
	delete[] bitmap;
}

int f_SumOfNeighbors(BitmapExt& orginal, int y, int x, bool wanted, int neighbors) {
	// Upstairs neighbor
	if ((y - 1 >= 0)) {
		if (orginal(y - 1, x) == wanted)
			neighbors++;
	}
	// Downstairs neighbor
	if (y + 1 <= orginal.length() - 1) {
		if (orginal(y + 1, x) == wanted)
			neighbors++;
	}
	// Neighbor on the left
	if ((x - 1 >= 0)) {
		if (orginal(y, x - 1) == wanted)
			neighbors++;
	}
	// Neighbor on the right
	if (x + 1 <= orginal.width() - 1) {
		if (orginal(y, x + 1) == wanted)
			neighbors++;
	}
	return neighbors;
}

//Overloaded operator for displaying a bitmap
std::ostream& operator<<(std::ostream& result, const Bitmap& orginal) {
	for (unsigned int i = 0; i < orginal.length(); i++) {
		result << "  |";
		for (unsigned int j = 0; j < orginal.width(); j++) {
			result << std::setw(2) << orginal(i, j);
			
			if (j != orginal.width() - 1) result << "  ";
		}
		result << "| " << std::endl;
	}
	return result;
}


// Inversion
void Inversion::f_transform(Bitmap& orginal) {
	for (unsigned int i = 0; i < orginal.length(); i++) {
		for (unsigned int j = 0; j < orginal.width(); j++)
			orginal(i, j) = !orginal(i, j);
	}
}

// Erosion
void Erosion::f_transform(Bitmap& orginal) {
	int neighbors = 0;

	// Make a copy of the original bitmap to perform transformations
	BitmapExt temp(orginal.length(), orginal.width());
	for (int i = 0; i < orginal.length(); i++) {
		for (int j = 0; j < orginal.width(); j++)
			temp.bitmap[i][j] = orginal(i, j);
	}

	for (int i = 0; i < orginal.length(); i++) {
		for (int j = 0; j < orginal.width(); j++) {
			
			if (temp(i, j) == true) {
				neighbors = f_SumOfNeighbors(temp, i, j, false, neighbors);
				if (neighbors != 0)
					orginal(i, j) = false;
				neighbors = 0;
			}
		}
	}
}

// Dilatation
void Dilatation::f_transform(Bitmap& orginal) {
	int neighbors = 0;

	BitmapExt temp(orginal.length(), orginal.width());
	// Make a copy of the original bitmap to perform transformations
	for (int i = 0; i < orginal.length(); i++) {
		for (int j = 0; j < orginal.width(); j++)
			temp.bitmap[i][j] = orginal(i, j);
	}


	for (int i = 0; i < orginal.length(); i++) {
		for (int j = 0; j < orginal.width(); j++) {
			
			if (temp(i, j) == false) {
				neighbors = f_SumOfNeighbors(temp, i, j, true, neighbors);
				
				if (neighbors != 0)
					orginal(i, j) = true;
				neighbors = 0;
			}
		}
	}
}

// Averaging
void Averaging::f_transform(Bitmap& orginal) {

	int neighbors = 0;

	BitmapExt temp(orginal.length(), orginal.width());


	// Make a copy of the original bitmap to perform transformations
	for (int i = 0; i < orginal.length(); i++) {
		for (int j = 0; j < orginal.width(); j++)
			temp.bitmap[i][j] = orginal(i, j);
	}

	for (int i = 0; i < orginal.length(); i++) {
		for (int j = 0; j < orginal.width(); j++) {

			if (temp(i, j) == false) {
				neighbors = f_SumOfNeighbors(temp, i, j, true, neighbors);
				
				if (neighbors > 2)
					orginal(i, j) = true;
				neighbors = 0;
			}


			if (temp(i, j) == true) {
				neighbors = f_SumOfNeighbors(temp, i, j, false, neighbors);
				if (neighbors > 2)
					orginal(i, j) = false;
				neighbors = 0;
			}
		}
	}
}
// Reset
void Reset::f_transform(Bitmap& orginal) {
	for (unsigned int i = 0; i < orginal.length(); i++) {
		for (unsigned int j = 0; j < orginal.width(); j++)
			orginal(i, j) = false;
	}

}



string Inversion::name() {
	return "Inversion";
}
string Dilatation::name() {
	return "Dilatation";
}
string Averaging::name() {
	return "Averaging";
}
string Reset::name() {
	return "Reset";
}
string Erosion::name() {
	return "Erosion";
}
string ComplexTransformation::name() {
	return "Trasformations";
}


void ComplexTransformation::f_AddTransformation(Transformation* p) {
	tab.push_back(p);
}
void ComplexTransformation::f_madeTransformations() {
	std::cout << "Transformations made:\n";
	for (int i = 0; i < tab.size(); i++) {
		std::cout << "Transformations: " << tab[i]->name() << std::endl;
	}
}
void ComplexTransformation::f_transform(Bitmap& a) {
	for (int i = 0; i < tab.size(); i++)
		tab[i]->f_transform(a);
}


