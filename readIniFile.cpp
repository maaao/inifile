#include "readIniFile.hpp"
#include <cstdlib>

#define LINUX

atlnativeapi::Setting::Setting()
{
	values_[keyAnalyseModeName] = std::string(defaults.find(keyAnalyseModeName)->second);
	values_[keyBunkiriLengthName] = std::string(defaults.find(keyBunkiriLengthName)->second);
	values_[keyAnalyseLengthName] = std::string(defaults.find(keyAnalyseLengthName)->second);

	char *envPath = std::getenv("ATLAS_HOME");
	std::string iniFilePath;
	if (envPath != nullptr)
	{
#ifdef LINUX
		iniFilePath = std::string(envPath) + "/" + iniFileName;
#else
		iniFilePath = std::string(envPath) + "\\" + iniFileName;
#endif
		try
		{
			read_ini(iniFilePath, pt_);
			setValue(sectionName, std::string(keyAnalyseModeName));
			setValue(sectionName, std::string(keyBunkiriLengthName));
			setValue(sectionName, std::string(keyAnalyseLengthName));
		}
		catch (boost::property_tree::ini_parser::ini_parser_error &e)
		{
			// Todo エラー処理
			// ファイル未検出
			std::cout << "file not found" << std::endl;
		}
	}

	else
	{
		// Todo エラー出力
		// $ATLAS_HOMEが存在しない 
		std::cout << "path not found" << std::endl;
	}
}

void atlnativeapi::Setting::setValue(const std::string &section, const std::string &key)
{
	if (boost::optional<std::string> value = pt_.get_optional<std::string>(section + "." + key))
	{
		values_[key] = value.get();
	}
}

void atlnativeapi::Setting::getMapValues()
{
	std::cout << "== start check map kv ==" << std::endl;
	for (auto it = this->values_.begin(); it != values_.end(); it++)
	{
		std::cout << "key : " << it->first << " value : " << it->second << std::endl;
	}
	std::cout << "== end check map kv ==" << std::endl;
}

int atlnativeapi::Setting::getAnalyseMode() const
{
	int value = modes_.find(values_.find(keyAnalyseModeName)->second.c_str())->second;
	if(value == 0){
		value = modes_.find(defaults.find(keyAnalyseModeName)->second)->second;
	}
	return value;
}

int atlnativeapi::Setting::getBunkiriLength() const
{
	char *endp;

	int value = strtol(values_.find(keyBunkiriLengthName)->second.c_str(), &endp, 10);
	if(*endp != '\0'){
		value = strtol(defaults.find(keyBunkiriLengthName)->second.c_str(), &endp, 10);
	}
	return value;
}

int atlnativeapi::Setting::getAnalyseLength() const
{
	char *endp;
	int value = strtol(values_.find(keyAnalyseLengthName)->second.c_str(), &endp, 10);
	
	if(*endp != '\0'){
		value = strtol(defaults.find(keyAnalyseLengthName)->second.c_str(), &endp, 10);
	}
	return value;
}