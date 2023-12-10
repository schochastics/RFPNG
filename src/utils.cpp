#include <Rcpp.h>
using namespace Rcpp;
#include "fpng.h"

// [[Rcpp::export]]
std::vector<uint8_t> touint8(IntegerVector arr, Rcpp::Dimension dim) {
  // Ensure the input is a 3D array
  if (dim.size() != 3) {
    stop("Dimensions must be of size 3.");
  }

  int x = dim[0];
  int y = dim[1];
  int z = dim[2];
  int totalSize = x * y * z;

  // Initialize the result vector with the total size
  std::vector<uint8_t> result(totalSize);

  // Convert and copy the data
  for (int i = 0; i < totalSize; ++i) {
    result[i] = static_cast<uint8_t>(arr[i]);
  }

  return result;
}

// [[Rcpp::export]]
IntegerVector fromuint8(std::vector<uint8_t> arr, int x, int y, int z) {
  int totalSize = x * y * z;
  IntegerVector result(totalSize);

  for (int i = 0; i < totalSize; ++i) {
    result[i] = static_cast<int>(arr[i]);
  }

  // Set dimensions for the IntegerVector
  IntegerVector dim = IntegerVector::create(x, y, z);
  result.attr("dim") = dim;

  return result;
}

//' Encode to file
//' @param x integer matrix
//' @param file_path character. file to write to
//' @return bool
// [[Rcpp::export(writeFPNG)]]
bool writeFPNG(IntegerVector& x, const char* file_path) {
  fpng::fpng_init();
  Rcpp::Dimension d = x.attr("dim");
  int w = d[0];
  int h = d[1];
  int chan = d[2];
  std::vector<uint8_t> y = touint8(x, d);
  //   const void* ptr = static_cast<const void*>(y.begin());
  fpng::fpng_encode_image_to_file(file_path, static_cast<const void*>(y.data()),
                                  w, h, chan, 0);
  return true;
}

// [[Rcpp::export]]
IntegerVector decode_from_file(const char* file_path) {
  std::vector<uint8_t> out;
  uint32_t width, height, channels;
  unsigned int desired_channels = 3;
  int ret = fpng::fpng_decode_file(file_path, out, width, height, channels,
                                   desired_channels);
  IntegerVector img = fromuint8(out, width, height, channels);
  return img;
}