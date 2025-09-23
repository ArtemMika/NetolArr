#pragma once
#include <string>

class Figure {
public:
	virtual ~Figure() = default;

	virtual std::string getType() const = 0;
	virtual std::string getParams() const = 0;
	virtual bool validate() const = 0;
};