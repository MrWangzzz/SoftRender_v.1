
#pragma once
#include <vector>
#include <string>
#include <fstream>
#include"Mesh.h"
using namespace std;


void StringSplit(string s, char splitchar, vector<string>& vec);


void ReadObjFile(string path, Mesh* obj);