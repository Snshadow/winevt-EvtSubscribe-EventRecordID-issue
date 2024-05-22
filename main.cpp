#define _CRT_SECURE_NO_WARNINGS

#include "main.hpp"

// get channel path as first parameter, query string as second parameter
int wmain(int argc, wchar_t* argv[]) {
	if (argc < 3) {
		printf("requires channel path and query string\n");
		return 1;
	}

	int choice;

	wprintf(L"choose event subscription type(1 for push, 2 for pull): ");
	
	wscanf(L"%d", &choice);

	switch (choice) {
	case 1:
		GetPushEvent(argv[1], argv[2]);
		break;
	case 2:
		GetPullEvent(argv[1], argv[2]);
		break;
	}

	return 0;
}
