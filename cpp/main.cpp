#include <windows.h>
#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>
#include <ctype.h>

void shift() {
	INPUT input; // INPUT structure
	memset(&input, 0, sizeof(input));

	// fill it out for keyboard key presses...
	input.type = INPUT_KEYBOARD;
	input.ki.wVk = VK_SHIFT;

	SendInput(1, &input, sizeof(INPUT));
}

void unshift() {
	INPUT input; // INPUT structure
	memset(&input, 0, sizeof(input));

	// fill it out for keyboard key presses...
	input.type = INPUT_KEYBOARD;
	input.ki.wVk = VK_SHIFT;

	input.ki.dwFlags = KEYEVENTF_KEYUP;
	SendInput(1, &input, sizeof(INPUT));
}

std::string symbols = "!?';:\"";

bool needsShift(char key) {
	if (isupper(key)) {
		return true;
	}
	for (unsigned i = 0; i < symbols.length(); i++) {
		if (symbols[i] == key) {
			return true;
		}
	}
	return false;
}

void sim(char key) {
	bool shifted = false;
	if (needsShift(key)) {
		shift();
		shifted = true;
	}
	INPUT input; // INPUT structure
	memset(&input, 0, sizeof(input));

	// fill it out for keyboard key presses...
	input.type = INPUT_KEYBOARD;
	input.ki.wVk = VkKeyScanA(key);

	SendInput(1, &input, sizeof(INPUT)); // 3rd param is size of an INPUT structure
										 // 2nd is LP to INPUT
										 // 1st is number of structures..

										 //modify the structure to do key up, a zero will indicate key down, as used above
	input.ki.dwFlags = KEYEVENTF_KEYUP;
	SendInput(1, &input, sizeof(INPUT));
	if (shifted) {
		unshift();
	}
}


int main(int argc, char *argv[]) // Don't forget first integral argument 'argc'
{
	std::string current_exec_name = argv[0]; // Name of the current exec program
	std::string text;

	//Sleep(2000);

	for (int i = 1; i < argc; i++) {
		std::string word = argv[i];
		std::cout << word << std::endl;
		for (int j = 0; j < word.length(); j++) {
			char letter = word[j];
			std::cout << letter << " ";
			Sleep(1);
			if (letter == *" ") {
				Sleep(200);
			}
			sim(letter);
		}
		sim(VK_SPACE);
	}

	std::cout << text;
}
