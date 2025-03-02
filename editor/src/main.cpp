#include "editor/utils.hpp"

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image.h"
#include "stb_image_write.h"
#undef STB_IMAGE_IMPLEMENTATION
#undef STB_IMAGE_WRITE_IMPLEMENTATION

#include "editor/main-window.hpp"
#include <QApplication>

int main(int argc, char* argv[]) {
  QApplication app(argc, argv);

  MainWindow window;
  window.show();

  return app.exec();
}

// const std::string ASCII_CHARS = "@%#*+=-:. ";
//
// char getAsciiChar(int value) {
//   int index = (value * (ASCII_CHARS.size() - 1)) / 255;
//   return ASCII_CHARS[index];
// }
//
// void convertToAscii(const unsigned char* image, int width, int height, std::ofstream& file) {
//   for (int y = 0; y < height; y++) {
//     for (int x = 0; x < width; x++) {
//       int index = y * width + x;
//       int gray = image[index];
//
//       char asciiChar = getAsciiChar(gray);
//       file << asciiChar;
//     }
//     file << '\n';
//   }
// }
//
// void resizeImage(std::vector<unsigned char>& resized, const unsigned char* image, int w, int h, int new_w, int new_h)
// {
//   for (int y = 0; y < new_h; ++y) {
//     for (int x = 0; x < new_w; ++x) {
//       int src_x = x * w / new_w;
//       int src_y = y * h / new_h;
//       resized[y * new_w + x] = image[src_y * w + src_x];
//     }
//   }
// }
//
// int main() {
//   int width, height, channels;
//   unsigned char* img = stbi_load("/Users/stasangoliuk/Desktop/image.png", &width, &height, &channels, 1);
//
//   auto image = std::make_shared<Image>("/Users/stasangoliuk/Desktop/image.png");
//
//   if (!img) {
//     std::cerr << "Error loading image!\n";
//     return 1;
//   }
//
//   int term_width = 200;
//   float aspect_ratio = static_cast<float>(height) / static_cast<float>(width);
//   int term_height = static_cast<int>(term_width * aspect_ratio * 0.5);
//
//   std::vector<unsigned char> resized(term_width * term_height);
//   resizeImage(resized, img, width, height, term_width, term_height);
//
//   std::ofstream outFile("output.txt");
//   if (!outFile) {
//     std::cerr << "Error opening file for writing!\n";
//     stbi_image_free(img);
//     return 1;
//   }
//
//   convertToAscii(resized.data(), term_width, term_height, outFile);
//   outFile.close();
//
//   std::cout << "ASCII art saved to output.txt\n";
//
//   stbi_image_free(img);
//   return 0;
// }
