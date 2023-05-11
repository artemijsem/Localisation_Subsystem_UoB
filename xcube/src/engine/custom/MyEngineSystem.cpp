#include "MyEngineSystem.h"
#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>
#include <fcntl.h>
#include <io.h>
#include <stdio.h>
#include <Windows.h>
using json = nlohmann::json;

/*
	Localization subsystem developed by Artemi Sementsenko, 2023
*/

MyEngineSystem::MyEngineSystem() : useSound(true) {
	init();
	if (useSound)
	{
		initSounds();
	}
}

MyEngineSystem::~MyEngineSystem() {}

void MyEngineSystem::init()
{

	/*
	* Initilieze paths for localisation objects
	*/
	std::string english_json = "res/lang/en-US.json";
	std::string russian_json = "res/lang/ru-RU.json";
	std::string example_json = "res/lang/example.json";


	/*
	*  Populate languages map
	*/
	languages["en-US"] = readJSON(english_json);
	languages["ru-RU"] = readJSON(russian_json);
	languages["example"] = readJSON(example_json);

}

void MyEngineSystem::setLanguage(std::string pLanguage)
{
	selectedLanguage = pLanguage;
}

/*
* Read JSON file and retrieve language data from it
*/
std::map<std::string, std::string> MyEngineSystem::readJSON(std::string lang_json_path)
{
	std::ifstream f(lang_json_path);

	json data = json::parse(f);
	std::map<std::string, std::string> languageData;
	try {
		if (data["data"] != NULL)
		{
			for (json& obj : data["data"])
			{
				/*
				* Weird conversion required from JSON object to string object
				*/
				std::string str_key = obj["key"];
				std::string str_value = obj["value"];
				languageData.insert({ str_key, str_value });

			}

		}
		else { std::cout << "Data is null" << std::endl; }
	}
	catch (std::exception& ex)
	{
		std::string errMsg = "!!!Error: ";
		errMsg += ex.what();
		std::cout << errMsg << std::endl;
	}

	return languageData;

}

/*
*  Initialise all sounds that the sound folder has
*/
void MyEngineSystem::initSounds()
{
	std::map<std::string, std::string> soundData;
	std::string soundPath = "res/lang/sfx/";

	for (auto it : languages)
	{
		if (std::filesystem::is_directory(soundPath + it.first))
		{
			for (const auto& dirEntry : std::filesystem::directory_iterator::directory_iterator(soundPath + it.first))
			{
				langSounds[it.first].insert({ dirEntry.path().filename().string(), dirEntry.path().string() });
			}
		}
	}
}

std::string MyEngineSystem::getLocalisedString(std::string pKey)
{
	// Create temporary map
	std::map<std::string, std::string> selectedLangData;


	// Populate temp map with currently selected language data
	for (auto it : languages)
	{
		if (it.first == selectedLanguage)
		{
			selectedLangData = it.second;
		}
	}

	// Return localised string
	for (auto const& it : selectedLangData)
	{
		if (it.first == pKey)
		{
			return it.second;

		}

	}

	// If localised string is not found, return Key instead to indicate missing string
	if (selectedLangData.find(pKey) == selectedLangData.end())
	{
		return pKey;
	}


}


std::string MyEngineSystem::getLocalisedSoundString(std::string pKey)
{
	// Create temporary map
	std::map<std::string, std::string> selectedSoundData;


	// Populate temp map with currently selected language data
	for (auto it : langSounds)
	{
		if (it.first == selectedLanguage)
		{
			selectedSoundData = it.second;
		}
	}

	// Return localised string
	for (auto const& it : selectedSoundData)
	{
		if (it.first == pKey)
		{
			return it.second;

		}

	}

	// If localised string is not found, return empty string
	if (selectedSoundData.find(pKey) == selectedSoundData.end())
	{
		return "";
	}
}

