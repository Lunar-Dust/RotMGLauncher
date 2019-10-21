#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <Windows.h>
#include <process.h>
#include <stdio.h>
#include <fstream>
#include <string>


using namespace std;

string projector_path;
int settings[4];
string default_settings[5] { "Projector=", "XPosition=250", "YPosition=10", "Width=1336", "Height=" };
const char *filename = "settings.ini";

void createSettings() {
    FILE *file;
    file = fopen(filename, "w+b");
    for (int x = 0; x < 5; ++x) {
        fprintf(file, "%s\n", default_settings[x].c_str());
    }
    fclose(file);
}

void loadSettings() {
    FILE *file;
    file = fopen(filename, "r");
    if (file == NULL) createSettings();
    else fclose(file);

    ifstream f(filename);
    string line;

    // I'm lazy and tired so I'm not gonna find some clever way to do this
    getline(f, line);
    projector_path = line.substr(10);

    getline(f, line);
    settings[0] = atoi(line.substr(10).c_str());

    getline(f, line);
    settings[1] = atoi(line.substr(10).c_str());

    getline(f, line);
    settings[2] = atoi(line.substr(6).c_str());

    getline(f, line);
    settings[3] = atoi(line.substr(7).c_str());

    f.close();
}

int main(int argc, char* argv[]) {
    loadSettings();
    _spawnl(P_NOWAITO, projector_path.c_str(), " ", "https://www.realmofthemadgod.com/client", NULL);
    Sleep(5000);
    HWND Find = ::FindWindowEx(0, 0, "ShockwaveFlash", 0);
    ::SetFocus(Find);
    int x = settings[0];
    int y = settings[1];
    int width = settings[2];
    int height = settings[3] ? settings[3] : ((int)(width / 4)) * 3;
    ::SetWindowPos(Find, HWND_TOP, x, y, width, height, NULL);
}
