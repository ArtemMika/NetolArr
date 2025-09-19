#include "figure.h"

Figure::Figure(const std::string& name) : name(name) {}

std::string Figure::get_name() const {  return name; }