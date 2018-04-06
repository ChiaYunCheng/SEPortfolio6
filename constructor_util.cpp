#include <fstream>

#include "constructor_util.h"
#include "xmlparser.h"

namespace Con_Util
{
	using std::string;
	using std::endl;

	/*
	*  Checks if file exists, logs result, then return the file contents
	*/
	bool Constructor_Util::canOpenFile(string & source)
	{
		string content, line;
		std::ifstream file(source);
		if (!file)
		{
			oss << endl << "error opening constructor source file " << source;
			constructorReport = oss.str();
			constructorSucceeded = false;
			return false;
		}
		oss << endl << "source file " << source << " opened okay";
		while (file.good())
		{
			getline(file, line);
			content += '\n';
			content += line;
		}
		oss << endl << "source file " << source << " read okay";

		source = content;
		
		return true;
	}

	/*  
	 *  Enhancement of XML_Parser::elementExists, automatically logs missing elements when checked.
	 */
	bool Constructor_Util::checkFor(const string & source, const string & elementName){
		if (XML_Parser::elementExists(source, elementName))
		{
			return true;
		}
		else
		{
			oss << endl << "no " << elementName << " tag";
			constructorReport = oss.str();
			constructorSucceeded = false;
			return false;
		}
	}
}