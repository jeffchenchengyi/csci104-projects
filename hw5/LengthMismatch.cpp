#include "LengthMismatch.h"
#include <string>
#include <stdexcept>

LengthMismatch::LengthMismatch(int x, int y) 
	: message("Input data structures have lengths " + std::to_string(x) + " and " + std::to_string(y)) {

}

const char* LengthMismatch::what() const noexcept {
    return message.c_str();
}