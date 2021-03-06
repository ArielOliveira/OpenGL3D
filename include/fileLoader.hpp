#pragma once
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <set>

using std::cout;
using std::endl;
using std::string;

#include <Importer.hpp>
#include <scene.h>
#include <postprocess.h>

const std::string meshPath = "..\\..\\data\\msh\\";
const std::string texturePath = "..\\..\\data\\textures\\";
const std::string shaderPath = "..\\..\\data\\shaders\\";

template <typename T>
class FileLoader {
	public:
		static string extractPath(string filename) {
			while (filename.find('\\') != string::npos)
				filename.replace(filename.find('\\'), 1, 1, '/');

			size_t pos = filename.rfind('/');
			if (pos == string::npos) return "";
			filename = filename.substr(0, pos);
			if (filename.size() > 0) filename += '/';
			return filename;
		}

		static string extractFileName(string filename) {
			if (extractPath(filename) != "") {
				size_t pos = filename.rfind('\\');
				return filename.substr(pos+1, filename.length());
			} else {
				return "";
			}
		}

		static string extractFileNameNoExtension(string filename) {
			filename = extractFileName(filename);
			size_t pos = filename.rfind('.');
			return filename.substr(0, pos);
		}

		static std::vector<T> splitString(const std::string& str, char delim);

		static T numberFromString(const std::string& str);
};

template <typename T>
std::vector<T> FileLoader<T>::splitString(const std::string& str, char delim) {
	std::vector<T> elems;
	if (str != "") {
		std::stringstream ss(str);
		std::string item;
		while (std::getline(ss, item, delim)) {
			T value;
			std::stringstream ss2(item);
			ss2 >> value;
			elems.push_back(value);
		}
	}
	return elems;
}

template <typename T>
T FileLoader<T>::numberFromString(const std::string& str)
{
	T number;
	std::istringstream stream(str);
	stream >> number;
	return number;
}