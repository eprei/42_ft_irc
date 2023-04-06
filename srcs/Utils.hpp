#ifndef UTILS_HPP
# define UTILS_HPP

template <typename T>
std::string to_string(T value)
{
    std::stringstream ss;
    ss << value;
    return ss.str();
}

#endif // UTILS_HPP

