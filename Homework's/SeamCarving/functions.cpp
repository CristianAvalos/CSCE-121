#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <cmath>
#include "functions.h"
using namespace std;

Pixel** createImage(int width, int height) {
  cout << "Start createImage... " << endl;
  
  // Create a one dimensional array on the heap of pointers to Pixels 
  //    that has width elements (i.e. the number of columns)
  Pixel** image = new Pixel*[width];
  
  bool fail = false;
  
  for (int i=0; i < width; ++i) { // loop through each column
    // assign that column to a one dimensional array on the heap of Pixels
    //  that has height elements (i.e. the number of rows)
    image[i] = new Pixel[height];
    
    if (image[i] == nullptr) { // failed to allocate
      fail = true;
    }
  }
  
  if (fail) { // if any allocation fails, clean up and avoid memory leak
    // deallocate any arrays created in for loop
    for (int i=0; i < width; ++i) {
      delete [] image[i]; // deleting nullptr is not a problem
    }
    delete [] image; // dlete array of pointers
    return nullptr;
  }
  
  // initialize cells
  cout << "Initializing cells..." << endl;
  for (int row=0; row<height; ++row) {
    for (int col=0; col<width; ++col) {
      //cout << "(" << col << ", " << row << ")" << endl;
      image[col][row] = { 0, 0, 0 };
    }
  }
  cout << "End createImage... " << endl;
  return image;
}

void deleteImage(Pixel** image, int width) {
  cout << "Start deleteImage..." << endl; 
  // avoid memory leak by deleting the array
  for (int i=0; i<width; ++i) {
    delete [] image[i]; // delete each individual array placed on the heap
  }
  delete [] image;
  image = nullptr;
}

// implement for part 1

int* createSeam(int length) {
	int* seam = new int[length];
	for (int i = 0; i < length; ++i) { ///////////////maybe start loop at 1?
		seam[i] = 0;
	}
	return seam;
}

void deleteSeam(int* seam) {
	delete [] seam;
	seam = nullptr;
}

bool loadImage(string filename, Pixel** image, int width, int height) {
	ifstream ifs (filename);
	if (!ifs.is_open()) {
		cout << "Error: failed to open input file - " << filename;
		return false;
	}
	char type[3];
	ifs >> type;
	if ((toupper(type[0]) != 'P') || (type[1] != '3')) {
		cout << "Error: type is " << type << " instead of P3";
		return false;
	}
	int w = 0, h = 0;
	ifs >> w;
	if (ifs.fail()) {
		cout << "Error: read non-integer value";
		return false;
	}
	ifs >> h;
	if (ifs.fail()) {
		cout << "Error: read non-integer value";
		return false;
	}
	if (w != width) {
		cout << "Error: input width (" << width << ") does not match value in file (" << w << ")";
		return false;
	}
	if (h != height) {
		cout << "Error: input height (" << height << ") does not match value in file (" << h << ")";
		return false;
	}
	int colorMax =0;
	ifs >> colorMax;
	if (colorMax < 0 || colorMax > 255) {
		cout << "Error: invalid color value " << colorMax;
		return false;
	}	
	for(int w = 0; w < height; w++ ) {
		for(int h = 0; h < width; h++) {
			if (ifs.eof()) {
				cout << "Error: not enough color values";
				return false;
			}
			
			ifs >> image[h][w].r;
			int r = image[h][w].r;
			if (ifs.eof() && ifs.fail()) {
				cout << "Error: not enough color values";
				return false;
			}
			if (ifs.fail()) {
				cout << "Error: read non-integer value";
				return false;
			}
			if ( r < 0 || r > 255) {
				cout << "Error: invalid color value " << r;
				return false;
			}
			
			ifs >> image[h][w].g;
			int g = image[h][w].g;
			if (ifs.eof() && ifs.fail()) {
				cout << "Error: not enough color values";
				return false;
			}
			if (ifs.fail()) {
				cout << "Error: read non-integer value";
				return false;
			}
			if (g < 0 || g > 255) {
				cout << "Error: invalid color value " << g;
				return false;
			}
			
			ifs >> image[h][w].b;
			int b = image[h][w].b;
			if (ifs.eof() && ifs.fail()) {
				cout << "Error: not enough color values";
				return false;
			}
			if (ifs.fail() && (w < width - 1 && h < height - 1)) {
				cout << "Error: read non-integer value";
				return false;
			}
			if ((b < 0 || b > 255) && (w < width - 1 && h < height - 1)) {
				cout << "Error: invalid color value " << b;
				return false;
			}
		}
	}
	int value;
	ifs >> value;
	if (!ifs.eof()) {
		cout << "Error: too many color values";
		return false;
	}
	else {
		ifs.close();
		return true;
	}
}

bool outputImage(string filename, Pixel** image, int width, int height) {
	ofstream ofs (filename);
	if (!ofs.is_open()) {
		cout << "Error: failed to open outputfile - " << filename;
		return false;
	}
	else {
		ofs << "P3" << endl;
		ofs << width << " " << height << endl;
		ofs << "255" << endl;
		for(int i = 0; i < height; ++i) 
			for(int j = 0; j < width; ++j) {
			ofs << image[j][i].r << " " << image[j][i].g << " " << image[j][i].b << " " << endl;
		}
		return true;
	}
}

int energy(Pixel** image, int x, int y, int width, int height) {
	int red = 0, green = 0, blue = 0, xsum = 0, ysum = 0, overallSum = 0;
	//top left
	if (x == 0 && y == 0) {
		red = fabs(image[x + 1][y].r - image[width - 1][y].r);
		green = fabs(image[x + 1][y].g - image[width - 1][y].g);
		blue = fabs(image[x + 1][y].b - image[width - 1][y].b);
		xsum = pow(red, 2) + pow(green, 2) + pow(blue, 2);
		
		red = fabs(image[x][y + 1].r - image[x][height - 1].r);
		green = fabs(image[x][y + 1].g - image[x][height - 1].g);
		blue = fabs(image[x][y + 1].b - image[x][height - 1].b);
		ysum = pow(red, 2) + pow(green, 2) + pow(blue, 2);
		
		overallSum = xsum + ysum;		
	}
	//bottom right
	else if (x == width - 1 && y == height - 1) {
		red = fabs(image[x - 1][y].r - image[0][y].r);
		green = fabs(image[x - 1][y].g - image[0][y].g);
		blue = fabs(image[x - 1][y].b - image[0][y].b);
		xsum = pow(red, 2) + pow(green, 2) + pow(blue, 2);

		red = fabs(image[x][y - 1].r - image[x][0].r);
		green = fabs(image[x][y - 1].g - image[x][0].g);
		blue = fabs(image[x][y - 1].b - image[x][0].b);
		ysum = pow(red, 2) + pow(green, 2) + pow(blue, 2);
		
		overallSum = xsum + ysum;		
	}
	//top right
	else if (x == width - 1 && y == 0) {
		red = fabs(image[x - 1][y].r - image[0][0].r);
		green = fabs(image[x - 1][y].g - image[0][0].g);
		blue = fabs(image[x - 1][y].b - image[0][0].b);
		xsum = pow(red, 2) + pow(green, 2) + pow(blue, 2);

		red = fabs(image[x][y + 1].r - image[x][height - 1].r); 
		green = fabs(image[x][y + 1].g - image[x][height - 1].g);
		blue = fabs(image[x][y + 1].b - image[x][height - 1].b);
		ysum = pow(red, 2) + pow(green, 2) + pow(blue, 2);
		
		overallSum = xsum + ysum;		
	}
	//bottom left
	else if (x == 0 && y == height - 1) {
		red = fabs(image[x + 1][height - 1].r - image[width - 1][height - 1].r); 
		green = fabs(image[x + 1][height - 1].g - image[width - 1][height - 1].g);
		blue = fabs(image[x + 1][height - 1].b - image[width - 1][height - 1].b);
		xsum = pow(red, 2) + pow(green, 2) + pow(blue, 2);

		red = fabs(image[0][y - 1].r - image[0][0].r);
		green = fabs(image[0][y - 1].g - image[0][0].g);
		blue = fabs(image[0][y - 1].b - image[0][0].b);
		ysum = pow(red, 2) + pow(green, 2) + pow(blue, 2);
		
		overallSum = xsum + ysum;		
	}
	// top
	else if (y == 0) {
		red = fabs(image[x + 1][0].r - image[x - 1][0].r);
		green = fabs(image[x + 1][0].g - image[x - 1][0].g);
		blue = fabs(image[x + 1][0].b - image[x - 1][0].b);
		xsum = pow(red, 2) + pow(green, 2) + pow(blue, 2);
		
		red = fabs(image[x][y + 1].r - image[x][height - 1].r);
		green = fabs(image[x][y + 1].g - image[x][height - 1].g);
		blue = fabs(image[x][y + 1].b - image[x][height - 1].b);
		ysum = pow(red, 2) + pow(green, 2) + pow(blue, 2);
		
		overallSum = xsum + ysum;
	}
	//bottom
	else if (y == height - 1) {
		red = fabs(image[x + 1][y].r - image[x - 1][y].r);
		green = fabs(image[x + 1][y].g - image[x - 1][y].g);
		blue = fabs(image[x + 1][y].b - image[x - 1][y].b);
		xsum = pow(red, 2) + pow(green, 2) + pow(blue, 2);
		
		red = fabs(image[x][y - 1].r - image[x][0].r);
		green = fabs(image[x][y - 1].g - image[x][0].g);
		blue = fabs(image[x][y - 1].b - image[x][0].b);
		ysum = pow(red, 2) + pow(green, 2) + pow(blue, 2);
		
		overallSum = xsum + ysum;
	}
	//left
	else if (x == 0) {
		red = fabs(image[x + 1][y].r - image[width - 1][y].r);
		green = fabs(image[x + 1][y].g - image[width - 1][y].g);
		blue = fabs(image[x + 1][y].b - image[width - 1][y].b);
		xsum = pow(red, 2) + pow(green, 2) + pow(blue, 2);
		
		red = fabs(image[x][y - 1].r - image[x][y + 1].r);
		green = fabs(image[x][y - 1].g - image[x][y + 1].g);
		blue = fabs(image[x][y - 1].b - image[x][y + 1].b);
		ysum = pow(red, 2) + pow(green, 2) + pow(blue, 2);
		
		overallSum = xsum + ysum;
	}
	//right
	else if (x == width - 1) {
		red = fabs(image[x - 1][y].r - image[0][y].r);
		green = fabs(image[x - 1][y].g - image[0][y].g);
		blue = fabs(image[x - 1][y].b - image[0][y].b);
		xsum = pow(red, 2) + pow(green, 2) + pow(blue, 2);
		
		red = fabs(image[x][y - 1].r - image[x][y + 1].r);
		green = fabs(image[x][y - 1].g - image[x][y + 1].g);
		blue = fabs(image[x][y - 1].b - image[x][y + 1].b);
		ysum = pow(red, 2) + pow(green, 2) + pow(blue, 2);
		
		overallSum = xsum + ysum;
	}
	//middle
	else {
		red = fabs(image[x + 1][y].r - image[x - 1][y].r);
		green = fabs(image[x + 1][y].g - image[x - 1][y].g);
		blue = fabs(image[x + 1][y].b - image[x - 1][y].b);
		xsum = pow(red, 2) + pow(green, 2) + pow(blue, 2);
		
		red = fabs(image[x][y - 1].r - image[x][y + 1].r);
		green = fabs(image[x][y - 1].g - image[x][y + 1].g);
		blue = fabs(image[x][y - 1].b - image[x][y + 1].b);
		ysum = pow(red, 2) + pow(green, 2) + pow(blue, 2);

		overallSum = xsum + ysum;
	}
	return overallSum;
}

//implement for part 2

 int loadVerticalSeam(Pixel** image, int start_col, int width, int height, int* seam) {
	int val = 0, val1 = 0, val2 = 0, val3 = 0, position = 0, sum = 0;
	val = energy(image, start_col, position, width, height);
	sum += val;
	seam[position] = start_col;
	for (int position = 1; position < height; ++position) {
		val = 0;
		if (start_col == 0) {
			val1 = energy(image, start_col, position, width, height);
			val2 = energy(image, start_col + 1, position, width, height);
			if (val1 == val2) {
				val = val1;
				seam[position] = val1;
			}
			else if (val2 < val1) {
				val = val2;
				start_col += 1;
				seam[position] = start_col;
			}
			else {
				val = val1;
				seam[position] = start_col;
			}
		}
		else if (start_col == width - 1) {
			val1 = energy(image, start_col - 1, position, width, height);
			val2 = energy(image, start_col, position, width, height);
			if (val1 == val2) {
				val = val2; 
				seam[position] = start_col;
			}
			else if (val2 < val1) {
				val = val2;
				seam[position] = start_col;
			}
			else {
				val = val1;
				start_col -= 1;
				seam[position] = start_col;
			}
		}
		else {
			val1 = energy(image, start_col - 1, position, width, height);
			val2 = energy(image, start_col, position, width, height);
			val3 = energy(image, start_col + 1, position, width, height);
			if (val1 == val2 && val2 == val3) {
				val = val2;
				seam[position] = start_col;
			}
			else if (val1 < val2 && val1 < val3) {
				val = val1;
				start_col -= 1; 
				seam[position] = start_col;
			}
			else if (val3 < val2 && val3 < val1) {
				val = val3;
				start_col += 1;
				seam[position] = start_col;
			}
			else if (val2 < val1 && val2  < val3) {
				val = val2;
				seam[position] = start_col;
			}
			else if (val2 < val1 && val2 == val3) {
				val = val2;
				seam[position] = start_col;
			}
			else if (val2 < val3 && val2 == val1) {
				val = val2;
				seam[position] = start_col;
			}
			else if (val1 < val2 && val1 == val3) {
				val = val3;
				start_col += 1;
				seam[position] = start_col;
			}
		}
		sum += val;
	}
	return sum;
 }

int loadHorizontalSeam(Pixel** image, int start_row, int width, int height, int* seam) {
  int val = 0, val1 = 0, val2 = 0, val3 = 0, position = 0, sum = 0;
	val = energy(image, position, start_row, width, height);
	sum += val;
	seam[position] = start_row;
	for (int position = 1; position < width; ++position) {
		val = 0;
		if (start_row == 0) {
			val1 = energy(image, position, start_row + 1, width, height);
			val2 = energy(image, position, start_row, width, height);
			if (val1 == val2) {
				val = val2;
				seam[position] = start_row;
			}
			else if (val1 < val2) {
				val = val1;
				start_row =+ 1;
				seam[position] = start_row;
			}
			else {
				val = val2;
				seam[position] = start_row;
			}
		}
		else if (start_row == height - 1) {
			val1 = energy(image, position, start_row, width, height);
			val2 = energy(image, position, start_row - 1, width, height);
			if (val1 == val2) {
				val = val1;
				seam[position] = start_row;
			}
			else if (val2 < val1) {
				val = val2;
				start_row -= 1;
				seam[position] = start_row;
			}
			else {
				val = val1;
				seam[position] = start_row;
			}
		}
		else {
			val1 = energy(image, position, start_row + 1, width, height);
			val2 = energy(image, position, start_row, width, height);
			val3 = energy(image, position, start_row - 1, width, height);
			if (val1 == val2 && val2 == val3) {
				val = val2;
				seam[position] = start_row;
			}
			else if (val1 < val2 && val1 < val3) {
				val = val1;
				start_row += 1;
				seam[position] = start_row;
			}
			else if (val3 < val2 && val3 < val1) {
				val = val3;
				start_row -= 1;
				seam[position] = start_row;
			}
			else if (val2 < val1 && val2  < val3) {
				val = val2;
				seam[position] = start_row;
			}
			else if (val2 < val1 && val2 == val3) {
				val = val2;
				seam[position] = start_row;
			}
			else if (val2 < val3 && val2 == val1) {
				val = val2;
				seam[position] = start_row;
			}
			else if (val1 < val2 && val1 == val3) {
				val = val3;
				start_row -= 1;
				seam[position] = start_row;
			}
		}
		sum += val;
	}
	return sum;
}

int* findMinVerticalSeam(Pixel** image, int width, int height) {
	int min_energy = 0, val = 0;
	int* seam = createSeam(height);
	min_energy = loadVerticalSeam(image, 0, width, height, seam);
	for (int col = 1; col < width; ++col) {
		int* seam2 = createSeam(height);
		val = loadVerticalSeam(image, col, width, height, seam2);
		if (val < min_energy) {
			min_energy = val;
			deleteSeam(seam);
			seam = seam2;
		}
		else {
			deleteSeam(seam2);
		}
	}
	return seam;
}

int* findMinHorizontalSeam(Pixel** image, int width, int height) {
	int min_energy = 0, val = 0;
	int* seam = createSeam(width);
	min_energy = loadHorizontalSeam(image, 0, width, height, seam);
	for (int row = 1; row < height; ++row) {
		int* seam2 = createSeam(width);
		val = loadHorizontalSeam(image, row, width, height, seam2);
		if (val < min_energy) {
			min_energy = val;
			deleteSeam(seam);
			seam = seam2;
		}
		else {
			deleteSeam(seam2);
		}
	}
	return seam;
}

void removeVerticalSeam(Pixel** image, int width, int height, int* verticalSeam) {
	for (int y = 0; y < height; ++y) {
		for (int x = verticalSeam[y]; x < width - 1; ++x) {
			image[x][y] = image[x + 1][y];
		}
	}
}

void removeHorizontalSeam(Pixel** image, int width, int height, int* horizontalSeam) {
	for (int x = 0; x < width; ++x) {
		for (int y = horizontalSeam[x]; y < height - 1; ++y) {
			image[x][y] = image[x][y + 1];
		}
	}
}
