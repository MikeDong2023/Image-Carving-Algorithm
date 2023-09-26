#include "Matrix.hpp"
#include "Matrix_test_helpers.hpp"
#include "unit_test_framework.hpp"
#include <sstream>
using namespace std;


// Here's a free test for you! Model yours after this one.
// Test functions have no interface and thus no RMEs, but
// add a comment like the one here to say what it is testing.
// -----
// Fills a 3x5 Matrix with a value and checks
// that Matrix_at returns that value for each element.
TEST(test_init) {
  Matrix *mat = new Matrix; // create a Matrix in dynamic memory
  Matrix_init(mat, 4, 3);
  Matrix *mat2 = new Matrix;
  mat2->height = 3;
  mat2->width = 4;
  Matrix_equal(mat, mat2); 
  delete mat; 
  delete mat2;
}

TEST(test_print) {
  Matrix *mat = new Matrix;
  Matrix_init(mat, 1, 1);

  *Matrix_at(mat, 0, 0) = 42;
  ostringstream expected;
  expected << "1 1\n"
           << "42 \n";
  ostringstream actual;
  Matrix_print(mat, actual);
  ASSERT_EQUAL(expected.str(), actual.str());

  delete mat;
}

TEST(test_width) {
  Matrix *mat = new Matrix; 
  Matrix_init(mat, 4, 3);
  ASSERT_EQUAL(Matrix_width(mat), 4);
  delete mat; 
}

TEST(test_height) {
  Matrix *mat = new Matrix; 
  Matrix_init(mat, 4, 3);
  ASSERT_EQUAL(Matrix_height(mat), 3);
  delete mat;
}

TEST(test_row) {
  Matrix *mat = new Matrix;
  Matrix_init(mat, 4, 3);
  ASSERT_EQUAL(Matrix_row(mat, Matrix_at(mat, 2, 3)), 2);
  delete mat; 
}

TEST(test_column) {
  Matrix *mat = new Matrix; 
  Matrix_init(mat, 4, 3);
  ASSERT_EQUAL(Matrix_column(mat, Matrix_at(mat, 2, 3)), 3);
  delete mat; 
}

TEST(test_at) {
  Matrix *mat = new Matrix; 
  Matrix_init(mat, 4, 3);
  mat->data[1] = 3;
  ASSERT_EQUAL(*Matrix_at(mat, 0, 1), 3);
  delete mat; 
}

TEST(test_const_at) {
  Matrix *mat = new Matrix; 
  Matrix_init(mat, 4, 3);
  mat->data[1] = 3;
  ASSERT_EQUAL(*Matrix_at(mat, 0, 1), 3);
  delete mat; 
}

TEST(test_fill) {
  Matrix *mat = new Matrix;
  const int width = 3;
  const int height = 5;
  const int value = 42;
  Matrix_init(mat, 3, 5);
  Matrix_fill(mat, value);

  for(int r = 0; r < height; ++r) {
    for(int c = 0; c < width; ++c) {
      ASSERT_EQUAL(*Matrix_at(mat, r, c), value);
    }
  }

  delete mat;
}

TEST(Matrix_fillBorder) {
    Matrix *mat = new Matrix;
    Matrix_init(mat, 3, 3);
    Matrix_fill_border(mat, 8);
    for (int i = 0; i < Matrix_height(mat); ++i) {
        for (int j = 0; j < Matrix_width(mat); ++j) {
            if (i == 0 || i == 2 || j == 0 || j == 2) {
                ASSERT_EQUAL(*Matrix_at(mat, i, j), 8);
            } else {
                ASSERT_NOT_EQUAL(*Matrix_at(mat, i, j), 8);
            }
        }
    }
}

TEST(Matrix_maxTest) {
    Matrix *mat = new Matrix;
    Matrix_init(mat, 3, 3);
    int data[] = {4, 2, 9, 1, 7, 4, 8, 6, 2};
    for (int i = 0; i < 9; ++i) {
        *Matrix_at(mat, i / 3, i % 3) = data[i];
    }
    ASSERT_EQUAL(Matrix_max(mat), 9);
}

TEST(test_columnOfMinValueInRow) {
    Matrix *mat = new Matrix;
    Matrix_init(mat, 3, 3);
    int data[] = {9, 1, 1, 23, 5, 1, 3, 4, 5};
    for (int i = 0; i < 9; ++i) {
        *Matrix_at(mat, i / 3, i % 3) = data[i];
    }
    ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat, 1, 0, 3), 2);
}

TEST(test_minValueInRow) {
    Matrix *mat = new Matrix;
    Matrix_init(mat, 3, 3);
    int data[] = {9, 1, 1, 23, 5, 1, 3, 4, 5};
    for (int i = 0; i < 9; ++i) {
        *Matrix_at(mat, Matrix_row(mat, &mat->data[i]), Matrix_column(mat, &mat->data[i])) = data[i];
    }
    ASSERT_EQUAL(Matrix_min_value_in_row(mat, 1, 0, 3), 1);
}
// ADD YOUR TESTS HERE
// You are encouraged to use any functions from Matrix_test_helpers.hpp as needed.

// NOTE: The unit test framework tutorial in Lab 2 originally
// had a semicolon after TEST_MAIN(). Although including and
// excluding the semicolon are both correct according to the c++
// standard, the version of g++ we are using reports a warning
// when there is a semicolon. Therefore do NOT add a semicolon
// after TEST_MAIN()
TEST_MAIN() // Do NOT put a semicolon here
