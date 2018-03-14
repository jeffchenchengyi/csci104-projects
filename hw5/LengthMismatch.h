#ifndef LENGTHMISMATCH_H
#define LENGTHMISMATCH_H
#include <string>
#include <stdexcept>

class LengthMismatch : public std::exception {
  public:
    LengthMismatch(int x, int y);
    virtual const char* what() const noexcept;
  private:
    std::string message;
};

#endif
