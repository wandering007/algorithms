// Converting numbers to strings and strings to numbers

#include <sstream>  // for the use of stringstream
#include <string>

template <typename T>
std::string NumberToString(T Number) {
    std::stringstream ss;
    ss << Number;
    return ss.str();
}

template <typename T>
T StringToNumber(const std::string &Text)
{
    stringstream ss(Text);
    T result;
    return ss >> result ? result : 0;
}
