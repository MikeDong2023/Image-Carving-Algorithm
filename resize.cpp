#include <iostream>
#include <fstream>      // Include the required headers
#include "processing.hpp"  // Include the required headers

using namespace std;

int main(int argc, char* argv[]) {
    if (argc < 4 || argc > 5) {
        cout << "Usage: resize.exe IN_FILENAME OUT_FILENAME WIDTH [HEIGHT]\n"
             << "WIDTH and HEIGHT must be less than or equal to the original" << endl;
        return 1; 
    }

    std::string inputFilename = argv[1];
    std::ifstream input(inputFilename);

    std::string outputFilename = argv[2];
    std::ofstream output(outputFilename);

    if (!input.is_open()) {
        cout << "Error opening file: " << inputFilename << endl;
        return 2; 
    }

    if (!output.is_open()) {
        cout << "Error opening file: " << outputFilename << endl;
        return 3; 
    }

    Image* img = new Image;
    Image_init(img, input);

    int newWidth = std::stoi(argv[3]);
    int newHeight = (argc == 5) ? std::stoi(argv[4]) : -1;

    if ((newWidth > 0) && (newWidth <= Image_width(img)) && ((newHeight == -1) || (newHeight > 0 && newHeight <= Image_height(img)))) {
        if (argc == 5) {
            seam_carve(img, newWidth, newHeight);
        } else {
            seam_carve_width(img, newWidth);
        }
    } else {
      cout << "Usage: resize.exe IN_FILENAME OUT_FILENAME WIDTH [HEIGHT]\n"
          << "WIDTH and HEIGHT must be less than or equal to original" << endl;
      return 4; 
    }

    delete img;

    return 0;
}
