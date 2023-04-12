#ifndef UTILS_HPP
# define UTILS_HPP

template <typename T>
std::string to_string(T value)
{
    std::stringstream ss;
    ss << value;
    return ss.str();
}

template <typename T>
void    PrintVector(const std::vector<T> &v)
{
		std::cout << FC(GREEN, "VECTOR") << std::endl;
		for(typename std::vector<T>::const_iterator it(v.begin()); it != v.end(); it++)
		{
				std::cout << *it << std::endl;
		}
}

template <typename T>
void    PrintVectorPointer(const std::vector<T> &v)
{
		std::cout << FC(GREEN, "VECTOR") << std::endl;
		for(typename std::vector<T>::const_iterator it(v.begin()); it != v.end(); it++)
		{
				std::cout << *(*it) << std::endl;
		}
}

#endif // UTILS_HPP

