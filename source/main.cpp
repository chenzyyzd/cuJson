#include <stdio.h>
#include "cuJson.h"

constexpr char demo_json[] = 
"{                                \r\n"
"\"jsonName\": \"demoJson\",      \r\n"
"\"jsonVersion\": 100,            \r\n"
"\"json\": {                      \r\n"
"   \"boolean\": true,            \r\n"
"   \"number\": 1234567,          \r\n"
"   \"json\": {                   \r\n"
"       \"text\": \"testWords\",  \r\n"
"       \"num\": 11451419         \r\n"
"		}                         \r\n"
"   }                             \r\n"
"}                                \r\n";

int main()
{
	cuJson cj;
	cuJson::Json json = cj.ParseJson(demo_json);

	std::string jsonName = cj.GetItemString(json, "jsonName");
	printf("jsonName=%s\n", jsonName.c_str());

	int jsonVersion = cj.GetItemInt(json, "jsonVersion");
	printf("jsonVersion=%d\n", jsonVersion);

	cuJson::Json itemJson = cj.GetItemJson(json, "json");

	bool boolean = cj.GetItemBool(itemJson, "boolean");
	if (boolean) {
		printf("boolean=true\n");
	} else {
		printf("boolean=false\n");
	}

	int number = cj.GetItemInt(itemJson, "number");
	printf("number=%d\n", number);

	std::string printJson = cj.PrintJson(itemJson);
	printf("print=%s\n", printJson.c_str());

	cuJson::Json secItemJson = cj.GetItemJson(itemJson, "json");

	std::string text = cj.GetItemString(secItemJson, "text");
	printf("text=%s\n", text.c_str());

	int num = cj.GetItemInt(secItemJson, "num");
	printf("num=%d\n", num);

	std::string printSecJson = cj.PrintJson(secItemJson);
	printf("print=%s\n", printSecJson.c_str());

	return 0;
}
