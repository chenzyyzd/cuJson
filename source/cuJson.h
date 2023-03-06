#pragma once

#include <iostream>
#include <string>
#include <vector>

#define JSON_ERROR -1

class cuJson
{
	public:
		using Json = int;

		cuJson();
		~cuJson();

		Json ParseJson(const std::string &text);
		std::string GetItemString(const Json &json, const std::string &itemName);
		int GetItemInt(const Json &json, const std::string &itemName);
		double GetItemDouble(const Json &json, const std::string &itemName);
		bool GetItemBool(const Json &json, const std::string &itemName);
		Json GetItemJson(const Json &json, const std::string &itemName);
		std::string PrintJson(const Json &json);

	private:
		std::vector<std::string> jsonList;

		std::string FormatString(const std::string &str);
		std::string GetPrevString(const std::string &str, const char &chr);
		std::string GetPostString(const std::string &str, const char &chr);
		std::string GetRePrevString(const std::string &str, const char &chr);
		std::string GetSingleJson(const std::string &str);
		bool IsInNestJson(const std::string &str);
		std::string GetNotNestedItem(const std::string &str, const std::string &itemName);
};
