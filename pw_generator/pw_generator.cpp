#include <Windows.h>
#include <iostream>
#include <random>
#include <string>

std::string random_string(std::string::size_type length)
{
    static auto& chrs = 
        "0123456789"
        "!?;,:._-"
        "abcdefghijklmnopqrstuvwxyz"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    thread_local static std::mt19937 rg{ std::random_device{}() };
    thread_local static std::uniform_int_distribution<std::string::size_type> pick(0, sizeof(chrs) - 2);

    std::string random;

    random.reserve(length);

    while (length--)
        random += chrs[pick(rg)];

    return random;
}

using namespace std;

int main()
{
    // initializing
    system("@echo off");
	system("color a");
    SetConsoleTitleA("PW Generator");
    HWND hwnd = GetDesktopWindow();
    int custom_size = 1;

    std::string strenght;
    cout << "Password lenght: ";
    cin >> custom_size;
    cout << endl;

    // checking password
    if (custom_size <= 5) {
        printf("Too short.");
        Sleep(5000);
        exit(0);
    }
    else if (custom_size >= 255) {
        printf("Too long.");
        Sleep(5000);
        exit(0);
    }

    if (custom_size < 10) {
        strenght = "Weak.";
    }
    else if (custom_size >= 10 && custom_size <= 15) {
        strenght = "Medium.";
    }
    else if (custom_size > 15) {
        strenght = "Strong.";
    }

    std::string bitch = random_string(custom_size);

    SetConsoleTitleA(bitch.c_str());

    // copy to clipbboard
    OpenClipboard(hwnd);
    EmptyClipboard();
    HGLOBAL hg = GlobalAlloc(GMEM_MOVEABLE, bitch.size() + 1);
    memcpy(GlobalLock(hg), bitch.c_str(), bitch.size() + 1);
    GlobalUnlock(hg);
    SetClipboardData(CF_TEXT, hg);
    CloseClipboard();
    GlobalFree(hg);

    // text shit
    cout << "Random password: " << bitch << endl;
    cout << "Copied password to clipboard" << endl;
    cout << "Your password is ranked as: " << strenght << endl;

    Sleep(5000);
}
