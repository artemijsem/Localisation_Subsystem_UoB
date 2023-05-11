#ifndef __MY_ENGINE_H__
#define __MY_ENGINE_H__

#include "../EngineCommon.h"
#include <map>
#include <list>


class MyEngineSystem {
	friend class XCube2Engine;
private:
	MyEngineSystem();
	
	std::map<std::string, std::map<std::string, std::string>> languages;
	std::map<std::string, std::map<std::string, std::string>> langSounds;

	std::map<std::string, std::string> langData;
	std::map<std::string, std::string> langSoundRaw;

	std::string selectedLanguage = "en-US";
	std::string langSoundsPath = {};

	bool useSound;
public:
	~MyEngineSystem();

	void init(); // Initialize values
	void initSounds();

	void setLanguage(std::string pLanguage);

	std::map<std::string, std::string> readJSON(std::string lang_json_path);

	std::string getLanguage() { return selectedLanguage; }
	std::map<std::string, std::map<std::string, std::string>> getAllLangSounds() { return langSounds; }
	std::map<std::string, std::map<std::string, std::string>> getAllLanguages() { return languages; }

	std::string getLocalisedString(std::string pKey);
	std::string getLocalisedSoundString(std::string pKey);
};

#endif