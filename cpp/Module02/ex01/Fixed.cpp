#include "Fixed.hpp"
#include <cmath>
#include <iostream>

Fixed::Fixed() : _rawBits(0) {
	std::cout << "Default constructor called" << std::endl;
}

Fixed::Fixed(const int n){
	std::cout << "Int constructor called" << std::endl;
	_rawBits = n << _fracBits;
}

Fixed::Fixed(const float f) {
	std::cout << "Float constructor called" << std::endl;
	_rawBits = roundf(f * (1 << _fracBits));
}

Fixed::Fixed (const Fixed &other) : _rawBits(other._rawBits) {
	std::cout << "Copy constructor called" << std::endl;
	//*this = other;
}

Fixed &Fixed::operator=(const Fixed &other) {
	std::cout << "Copy assignment operator called" << std::endl;
	if (this != &other)
		this->_rawBits = other.getRawBits();
	return *this;
}

Fixed::~Fixed() {
	std::cout << "Destructor called" << std::endl;
}

int Fixed::getRawBits(void) const {
	return _rawBits;
}

void Fixed::setRawBits(int const raw) {
	_rawBits = raw;
}

float Fixed::toFloat(void) const {
	return (float)_rawBits / (1 << _fracBits);
}

int Fixed::toInt(void) const {
	return _rawBits >> _fracBits;
}

std::ostream &operator<<(std::ostream &os, const Fixed &fixed) {
	os << fixed.toFloat();
	return os;
}
