#pragma once

#include<vector>
#include<string>
#include<Windows.h>

class TypeConversion {
public:

	TypeConversion() = default;

	std::vector<int> fromIntToDigitArr(int wh);
	std::vector<int> fromIntToOppoDigitArr(int wh);
	std::vector<int> fromWstringtoOppoDigitArr(std::wstring wh);
	std::vector<int> oppoDigitArr(std::vector<int> wh);
	std::wstring fromDigitArrtoOppoWstring(std::vector<int> wh);
	std::wstring toPercentStr(double oriNum, int fracLen);
};