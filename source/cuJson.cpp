#include "cuJson.h"

cuJson::cuJson() { }
cuJson::~cuJson() { }

cuJson::Json cuJson::ParseJson(const std::string &text)
{
	Json json = jsonList.size();
	if (json == INT_MAX) {
		return JSON_ERROR;
	}
	jsonList.emplace_back(FormatString(text));
	return json;
}

std::string cuJson::GetItemString(const Json &json, const std::string &itemName)
{
	if (json >= jsonList.size() || json < 0) {
		return "";
	}

	std::string item = GetNotNestedItem(jsonList[json], itemName);
	if (!item.empty()) {
		item = GetRePrevString(GetPostString(item, ':'), ',');
	} else {
		return "";
	}

	std::string itemString = GetRePrevString(GetPostString(item, '\"'), '\"');

	return itemString;
}

int cuJson::GetItemInt(const Json &json, const std::string &itemName)
{
	if (json >= jsonList.size() || json < 0) {
		return 0;
	}

	std::string item = GetNotNestedItem(jsonList[json], itemName);
	if (!item.empty()) {
		item = GetRePrevString(GetPostString(item, ':'), ',');
	} else {
		return 0;
	}

	int itemInt = atoi(item.c_str());

	return itemInt;
}

bool cuJson::GetItemBool(const Json &json, const std::string &itemName)
{
	if (json >= jsonList.size() || json < 0) {
		return false;
	}

	std::string item = GetNotNestedItem(jsonList[json], itemName);
	if (!item.empty()) {
		item = GetRePrevString(GetPostString(item, ':'), ',');
	} else {
		return false;
	}

	bool itemBool;
	if (item == "true") {
		itemBool = true;
	} else {
		itemBool = false;
	}

	return itemBool;
}

cuJson::Json cuJson::GetItemJson(const Json &json, const std::string &itemName)
{
	if (json >= jsonList.size() || json < 0) {
		return JSON_ERROR;
	}

	std::string itemJsonText = "";
	std::string item = GetNotNestedItem(jsonList[json], itemName);
	if (!item.empty()) {
		itemJsonText = GetSingleJson(GetPostString(item, ':'));
	} else {
		return JSON_ERROR;
	}

	Json itemJson = ParseJson(itemJsonText);

	return itemJson;
}

std::string cuJson::PrintJson(const Json &json)
{
	std::string jsonText = "";
	if (json >= jsonList.size() || json < 0) {
		return jsonText;
	}

	jsonText = jsonList[json];

	return jsonText;
}

std::string cuJson::FormatString(const std::string &str)
{
	char* buffer = (char*)str.c_str();

	std::string fstring = "";
	while (*buffer != '\0') {
		if (*buffer != ' ' && *buffer != '	' && *buffer != '\r' && *buffer != '\n') {
			fstring += *buffer;
		}
		buffer++;
	}

	return fstring;
}

std::string cuJson::GetPrevString(const std::string &str, const char &chr)
{
	char* buffer = (char*)str.c_str();

	int i;
	for (i = (strlen(buffer) - 1); i >= 0; i--) {
		char* buffer_ptr = buffer + i;
		if (*buffer_ptr == chr) {
			*buffer_ptr = '\0';
			break;
		}
	}

	std::string prevString = buffer;

	return prevString;
}

std::string cuJson::GetPostString(const std::string &str, const char &chr)
{
	char* buffer = (char*)str.c_str();
	while (*buffer != '\0') {
		if (*buffer == chr) {
			buffer++;
			break;
		}
		buffer++;
	}

	std::string postString = buffer;

	return postString;
}

std::string cuJson::GetRePrevString(const std::string &str, const char &chr)
{
	char* buffer = (char*)str.c_str();
	int i;
	for (i = 0; i < strlen(buffer); i++) {
		char* buffer_ptr = buffer + i;
		if (*buffer_ptr == chr) {
			*buffer_ptr = '\0';
			break;
		}
	}

	std::string prevString = buffer;

	return prevString;
}

std::string cuJson::GetSingleJson(const std::string &str)
{
	char* buffer = (char*)str.c_str();

	std::string jsonText = "";
	int braceNum = 0;
	while (*buffer != '\0') {
		jsonText += *buffer;
		if (*buffer == '{') {
			braceNum++;
		} else if (*buffer == '}') {
			braceNum--;
			if (braceNum == 0) {
				break;
			}
		}
		buffer++;
	}

	return jsonText;
}

bool cuJson::IsInNestJson(const std::string &str)
{
	bool inNestJson = false;

	char* buffer = (char*)str.c_str();
	int braceNum = 0;
	while (*buffer != '\0') {
		if (*buffer == '{') {
			braceNum++;
		} else if (*buffer == '}') {
			braceNum--;
		}
		buffer++;
	}

	if (braceNum < 0) {
		inNestJson = true;
	}

	return inNestJson;
}

std::string cuJson::GetNotNestedItem(const std::string &str, const std::string &itemName)
{
	std::string itemText = GetPrevString(GetPostString(str, '{'), '}');

	char itemNameBuf[128];
	sprintf(itemNameBuf, "\"%s\"", itemName.c_str());
	char* item_ptr = (char*)itemText.c_str();
	int inNestJson = 1;
	while (inNestJson) {
		const char* new_item_ptr = strstr(item_ptr, itemNameBuf);
		if (new_item_ptr == NULL) {
			return "";
		} else if (new_item_ptr != item_ptr) {
			itemText = new_item_ptr;
			item_ptr = (char*)new_item_ptr + strlen(itemNameBuf);
		} else {
			itemText = new_item_ptr;
			break;
		}
		inNestJson = (int)IsInNestJson(itemText);
	}

	return itemText;
}
