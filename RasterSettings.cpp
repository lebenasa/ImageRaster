#include "stdafx.h"
#include "RasterSettings.h"
#include "tinyxml2.h"
#include "Collection.h"

CalibrationProfile::CalibrationProfile(const std::string& name, const int& x, const int& y)
	: m_x(x), m_y(y), myName(name)
{
	qName = QString(name.c_str());
}

GlobalSettings::GlobalSettings(const QString& filename, int fallback)
{
	this->fallback = (Fallback)fallback;
	QString s = searchSettings(filename);
	if ("" == s) {
		fileName = QDir::homePath() + "/AppData/Local/Miconos/" + filename;
	}
	else
		fileName = s;
	LoadSettings();
}

GlobalSettings::~GlobalSettings()
{
	if (doc != nullptr)
		delete doc;
}

QString GlobalSettings::searchSettings(const QString& name) {
	if (fallback >= Fallback::AppData) {
		if (QFile(QDir::homePath() + "/AppData/Local/Miconos/" + name).exists())
			return QDir::homePath() + "/AppData/Local/Miconos/" + name;
	}
	if (fallback >= Fallback::User) {
		if (QFile(QDir::homePath() + "/My Documents/Miconos/" + name).exists())
			return QDir::homePath() + "/My Documents/Miconos/" + name;
	}
	if (fallback >= Fallback::Exe) {
		if (QFile(QCoreApplication::applicationDirPath() + "/" + name).exists())
			return QCoreApplication::applicationDirPath() + "/" + name;
	}
	return "";
}

void GlobalSettings::LoadSettings() {
	using namespace tinyxml2;
	using namespace Converter;
	doc = new tinyxml2::XMLDocument();
	XMLError err = doc->LoadFile(fileName.toStdString().c_str());
	if (err != XMLError::XML_NO_ERROR) 
		return;
	//Load calibration profiles:
	XMLElement* base = doc->FirstChildElement("app")->FirstChildElement("calibration")
		->FirstChildElement("profile");
	while (true) {
		CalibrationProfile profile = CalibrationProfile();
		//Get name:
		profile.setName(base->Attribute("name"));
		//Get x:
		XMLText* dataX = base->FirstChildElement("x")->FirstChild()->ToText();
		profile.setX(ToInt(dataX->Value()));
		//Get y:
		XMLText* dataY = base->FirstChildElement("y")->FirstChild()->ToText();
		profile.setY(ToInt(dataY->Value()));
		//Append:
		profiles.push_back(profile);
		//Next:
		base = base->NextSiblingElement("profile");
		if (base == nullptr)
			break;
	}
}

void GlobalSettings::WriteSettings(const std::vector<CalibrationProfile> &p) {
	using namespace tinyxml2;
	using namespace Converter;
	tinyxml2::XMLDocument save;
	save.LinkEndChild(save.NewDeclaration());
	save.LinkEndChild(save.NewComment("@author=Leben Asa"));
	save.LinkEndChild(save.NewComment("Application settings for ImageRaster.exe"));
	save.LinkEndChild(save.NewComment("Manual editting is not recommended"));
	XMLElement* app = save.NewElement("app");
	//Write calibration element:
	XMLElement* calibration = save.NewElement("calibration");
	for (auto profile : p) {
		XMLElement* p_elem = save.NewElement("profile");
		p_elem->SetAttribute("name", profile.name().c_str());

		XMLElement* c_elem = save.NewElement("x");
		XMLText* t_elem = save.NewText(ToString(profile.x()).c_str());
		c_elem->LinkEndChild(t_elem);
		p_elem->LinkEndChild(c_elem);

		c_elem = save.NewElement("y");
		t_elem = save.NewText(ToString(profile.y()).c_str());
		c_elem->LinkEndChild(t_elem);
		p_elem->LinkEndChild(c_elem);

		calibration->LinkEndChild(p_elem);
	}
	//Link them all:
	app->LinkEndChild(calibration);
	save.LinkEndChild(app);
	save.SaveFile(fileName.toStdString().c_str());
}

void GlobalSettings::removeProfile(int i) {
	auto p = profiles.begin() + i;
	profiles.erase(p);
}

void GlobalSettings::appendProfile(CalibrationProfile& p) {
	profiles.push_back(p);
}

