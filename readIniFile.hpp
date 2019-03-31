#include <iostream>
#include <string>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <boost/optional.hpp>
#include <map>

using namespace boost::property_tree;

namespace atlnativeapi{

static const char* iniFileName = "atlnativeapi.ini";
static const char* sectionName = "settings";
static const char* keyAnalyseModeName = "analyse_mode";
static const char* keyBunkiriLengthName = "bunkiri_len";
static const char* keyAnalyseLengthName = "analyse_len";

const std::map<const std::string, const std::string> defaults{
    {keyAnalyseModeName, "all"}, 
	{keyBunkiriLengthName, "1024"},
	{keyAnalyseLengthName, "1024"}
};
const std::map<const std::string, const int> modes_{
	{"seg", 0x10},
	{"cs", 0x20}, 
	{"cs2", 0x40}, 
	{"all", 0x70}
};

class Setting{
    public:
    Setting();
    int getAnalyseMode() const;
    int getBunkiriLength() const;
    int getAnalyseLength() const;

    // temporary
    // for print debug
	void getMapValues();

    private:
    std::map<std::string, std::string> values_;
	boost::property_tree::ptree pt_;
    void setValue(const std::string &section, const std::string &key);

};
}
