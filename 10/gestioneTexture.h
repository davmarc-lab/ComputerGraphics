#pragma once

#include <iostream>
#include <vector>

using namespace std;

unsigned int loadTexture(char const* path, int flip);
unsigned int loadCubemap(vector<string> faces, int flip);
