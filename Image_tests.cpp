#include "Matrix.hpp"
#include "Image_test_helpers.hpp"
#include "unit_test_framework.hpp"
#include <iostream>
#include <string>
#include <sstream>
#include <cassert>
#include <fstream>

using namespace std;


// Here's a free test for you! Model yours after this one.
// Test functions have no interface and thus no RMEs, but
// add a comment like the one here to say what it is testing.
// -----
// Sets various pixels in a 2x2 Image and checks
// that Image_print produces the correct output.
TEST(test_print) {
  Image *img = new Image; // create an Image in dynamic memory

  const Pixel red = {255, 0, 0};
  const Pixel green = {0, 255, 0};
  const Pixel blue = {0, 0, 255};
  const Pixel white = {255, 255, 255};

  Image_init(img, 2, 2);
  Image_set_pixel(img, 0, 0, red);
  Image_set_pixel(img, 0, 1, green);
  Image_set_pixel(img, 1, 0, blue);
  Image_set_pixel(img, 1, 1, white);

  // Capture our output
  ostringstream s;
  Image_print(img, s);

  // Correct output
  ostringstream correct;
  correct << "P3\n2 2\n255\n";
  correct << "255 0 0 0 255 0 \n";
  correct << "0 0 255 255 255 255 \n";
  ASSERT_EQUAL(s.str(), correct.str());

  delete img; 
}

TEST(test_Image_init) {
    Image* img = new Image;
    Image_init(img, 100, 100);

    ASSERT_EQUAL(Image_width(img), 100);
    ASSERT_EQUAL(Image_height(img), 100);
    ASSERT_EQUAL(Matrix_width(&img->red_channel), 100);
    delete img;
}

TEST(test_Image_init_stream) {
    std::ifstream input("dog.ppm");
    Image* img = new Image;
    Image_init(img, input);

    ASSERT_EQUAL(Image_width(img), 5);
    ASSERT_EQUAL(Image_height(img), 5);
    ASSERT_EQUAL(*Matrix_at(&img->blue_channel, 0, 2), 250);
    delete img;
}

TEST(test_Image_width) {
    Image* img = new Image;
    Image_init(img, 100, 100);

    ASSERT_EQUAL(Image_width(img), 100);

    delete img;
}

TEST(test_Image_height) {
    Image* img = new Image;
    Image_init(img, 100, 100);

    ASSERT_EQUAL(Image_height(img), 100);

    delete img;
}

TEST(test_Image_get_pixel) {
    std::ifstream input("dog.ppm");
    Image* img = new Image;
    Image_init(img, input);

    // Get the pixel color and assert that it matches the expected color
    Pixel pixel = Image_get_pixel(img, 0, 2);
    ASSERT_EQUAL(pixel.r, 255);
    ASSERT_EQUAL(pixel.g, 255);
    ASSERT_EQUAL(pixel.b, 250);

    delete img;
}

TEST(test_Image_fill) {
    Image* img = new Image;
    Image_init(img, 5, 5);

    Pixel set_color = {255, 0, 0};
    Image_fill(img, set_color);

    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            Pixel pixel = Image_get_pixel(img, i, j);
            ASSERT_EQUAL(pixel.r, set_color.r);
            ASSERT_EQUAL(pixel.g, set_color.g);
            ASSERT_EQUAL(pixel.b, set_color.b);
        }
    }

    delete img;
}


TEST(test_Image_set_pixel) {
    Image* img = new Image;
    Image_init(img, 5, 5);

    Pixel expected_color = {255, 0, 0};
    int r = 4;
    int c = 4;
    Image_set_pixel(img, r, c, expected_color);

    Pixel pixel = Image_get_pixel(img, r, c);
    ASSERT_EQUAL(pixel.r, expected_color.r);
    ASSERT_EQUAL(pixel.g, expected_color.g);
    ASSERT_EQUAL(pixel.b, expected_color.b);

    delete img;
}



// Add more test cases for other functions here

// IMPLEMENT YOUR TEST FUNCTIONS HERE
// You are encouraged to use any functions from Image_test_helpers.hpp as needed.

// NOTE: The unit test framework tutorial in Lab 2 originally
// had a semicolon after TEST_MAIN(). Although including and
// excluding the semicolon are both correct according to the c++
// standard, the version of g++ we are using reports a warning
// when there is a semicolon. Therefore do NOT add a semicolon
// after TEST_MAIN()
TEST_MAIN() // Do NOT put a semicolon here
