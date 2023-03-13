#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include <iostream>

class Channel
{
	public:

		Channel();
		Channel(Channel &other);
		Channel &operator=(Channel &other);
		~Channel();

	private:

		std::string	_name;
		std::string _topic;

};

#endif
