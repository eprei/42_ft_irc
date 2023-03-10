# include "Includes.hpp"

// TO DO: write copilen's functions

Channel::Channel(){}

Channel::Channel(Channel &other){ *this = other;}

Channel &Channel::operator=(Channel &other){
	(void) other;
	return (*this);
}

Channel::~Channel(){}
