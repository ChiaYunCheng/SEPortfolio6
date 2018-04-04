#ifndef CONSTRUCTOR_UTIL_H
#define CONSTRUCTOR_UTIL_H

#include <sstream>

using std::string;

namespace Con_Util
{
	class Constructor_Util
	{
	public:
		//temporarily public for testing
		std::ostringstream oss;
		bool canOpenFile(string & source);
	protected:
		//std::ostringstream oss; TEMPORARILY MADE PUBLIC FOR TESTING
		bool constructorSucceeded;
		string constructorReport;

		//bool canOpenFile(string & source); TEMPORARILY MADE PUBLIC FOR TESTING
		bool checkFor(const string & source, const string & elementName);
	};
}

#endif