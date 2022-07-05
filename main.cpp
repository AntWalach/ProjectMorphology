#include "libProjekt.h"
#include "libExceptions.h"
#include <iostream>
#include <iostream>
#include <vector>

int main() {

	try {
		BitmapExt bitMap(5, 5);

		//bitmapA(1, 3) = bitmapA(2, 2) = bitmapA(2, 3) = bitmapA(2, 4) = bitmapA(3,1) = bitmapA(3,2) = bitmapA(3, 3) = bitmapA(3,4) = bitmapA(3, 5) = bitmapA(4, 2) = bitmapA(4, 3) = bitmapA(4, 4) = bitmapA(5, 3) = true;
		bitMap(1, 1) = bitMap(2, 1) = bitMap(3, 1) = bitMap(2, 2) = bitMap(1, 3) = bitMap(2, 3) = bitMap(3, 3) = true;
		std::cout << "\nOryginal bitmapy:\n\n" << bitMap << std::endl;

		Averaging U;
		Dilatation D;
		Erosion E;
		Reset Z;
		Inversion I;

		ComplexTransformation z;
		z.f_AddTransformation(&U);
		z.f_AddTransformation(&D);
		z.f_transform(bitMap);
		z.f_madeTransformations();
		std::cout << "\nPrzeksztalcona bitmapa:\n\n" << bitMap << "\n";
	}
	catch (std::exception& error) {
		std::cout << error.what();
		exit(0);
	}

}
