#include "Fixed.hpp"
#include <cmath>
#include <iostream>

//Construtores, destrutor e operador '='
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
		_rawBits = other.getRawBits();
	return *this;
}

Fixed::~Fixed() {
	std::cout << "Destructor called" << std::endl;
}


//Getters e Setters
int Fixed::getRawBits(void) const {
	return _rawBits;
}

void Fixed::setRawBits(int const raw) {
	_rawBits = raw;
}

//Operadores Aritméticos
Fixed Fixed::operator+(const Fixed &other) const {
	return Fixed(this->toFloat() + other.toFloat());
}

Fixed Fixed::operator-(const Fixed &other) const {
	return Fixed(this->toFloat() - other.toFloat());
}

Fixed Fixed::operator*(const Fixed &other) const {
	return Fixed(this->toFloat() * other.toFloat());
}

Fixed Fixed::operator/(const Fixed &other) const {
	if (other.getRawBits() == 0) {
		std::cerr << "Error: division by zero" << std::endl;
		return Fixed();
	}
	return Fixed(this->toFloat() / other.toFloat());
}

//Operadores incremento e decremento
Fixed Fixed::operator++() {
	++_rawBits;
	return *this;
}

Fixed Fixed::operator++(int) {
	Fixed temp(*this);
	_rawBits++;
	return temp;
}

Fixed Fixed::operator--() {
	--_rawBits;
	return *this;
}

Fixed Fixed::operator--(int) {
	Fixed temp(*this);
	_rawBits--;
	return temp;
}

//Conversores
float Fixed::toFloat(void) const {
	return (float)_rawBits / (1 << _fracBits);
}

int Fixed::toInt(void) const {
	return _rawBits >> _fracBits;
}

//Operadores de comparação
bool Fixed::operator>(const Fixed &other) const {
       return this->_rawBits > other._rawBits;
}

bool Fixed::operator<(const Fixed &other) const {
       return this->_rawBits < other._rawBits;
}

bool Fixed::operator>=(const Fixed &other) const {
       return this->_rawBits >= other._rawBits;
}

bool Fixed::operator<=(const Fixed &other) const {
       return this->_rawBits <= other._rawBits;
}

bool Fixed::operator==(const Fixed &other) const {
       return this->_rawBits == other._rawBits;
}

bool Fixed::operator!=(const Fixed &other) const {
       return this->_rawBits != other._rawBits;
}

//Funções min e max
Fixed &Fixed::min(Fixed &a, Fixed &b) {
	return (a < b) ? a : b;
}

const Fixed &Fixed::min(const Fixed &a, const Fixed &b) {
	return (a < b) ? a : b;
}

Fixed &Fixed::max(Fixed &a, Fixed &b) {
	return (a > b) ? a : b;
}

const Fixed &Fixed::max(const Fixed &a, const Fixed &b) {
	return (a > b) ? a : b;
}

//Operador output
std::ostream &operator<<(std::ostream &os, const Fixed &fixed) {
	os << fixed.toFloat();
	return os;
}
