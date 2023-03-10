# include "Includes.hpp"

// TO DO: write copilen's functions

Client::Client(){}

Client::Client(Client &other){ *this = other;}

Client &Client::operator=(Client &other){
	(void) other;
	return (*this);
}

Client::~Client(){}
