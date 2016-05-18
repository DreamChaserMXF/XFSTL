#ifndef XF_STRING_HPP
#define XF_STRING_HPP
#include "vector.hpp"
namespace xf
{
	class string
	{
	public:
		string();
		string(const string &_Right);
		string(const char *str);
		string(size_t _Count, char _Value);
		~string();
	private:
		xf::vector<unsigned char> str_;
	};

	string::string() : str_()
	{
	}

	string::~string()
	{
		;
	}
}

#endif