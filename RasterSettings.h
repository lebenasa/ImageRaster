#pragma once
#include "qexception.h"

namespace tinyxml2 {
	class XMLDocument;
};

//Profile structure:
class CalibrationProfile {
	QString qName;
	std::string myName;
	int m_x;
	int m_y;
public:
	CalibrationProfile(const std::string& name = "", const int& x = 1, const int& y = 1);
	~CalibrationProfile() { }
	int x() const { return m_x; }
	void setX(const int& x) { m_x = x; }
	int y() const { return m_y; }
	void setY(const int& y) { m_y = y; }
	std::string name() const { return myName; }
	QString qname() const { return qName; }
	void setName(const QString& name) {
		qName = name;
		myName = name.toStdString();
	}
};

//Global settings reader:
class GlobalSettings
{
	tinyxml2::XMLDocument *doc;
	std::vector<CalibrationProfile> profiles;
	QString fileName;
	QFile settings;
	//Return true if found, false otherwise:
	QString searchSettings(const QString& name);
public:
	GlobalSettings(const QString& filename = "RasterSettings.cfg", int fallback = AppData);
	~GlobalSettings();
	void LoadSettings();
	void WriteSettings(const std::vector<CalibrationProfile>& p);

	//Fallback mechanism:
	enum Fallback {
		Exe, User, AppData
	} fallback;

	//Profile accessors:
	std::vector<CalibrationProfile> getProfiles() const {
		return profiles;
	}
	CalibrationProfile at(int i) const {
		return profiles.at(i);
	}
	void removeProfile(int i);
	void appendProfile(CalibrationProfile& p);
};

class SettingsNotFound :
	public QException 
{
public:
    void raise() const { throw *this; }
    SettingsNotFound *clone() const { return new SettingsNotFound(*this); }
};