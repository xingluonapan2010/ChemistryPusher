#pragma once

#include<vector>
#include<string>
class HighAccCalc {
public:
	HighAccCalc() = default;
	std::vector<int> fromWstringtoOppoDigitArr(std::wstring wh);
	std::vector<int> oppoDigitArr(std::vector<int> wh);
	std::wstring fromDigitArrtoOppoWstring(std::vector<int> wh);
	std::vector<int> HighAccCalcPlus(std::vector<int> a, std::vector<int> b);
	std::vector<int> HighAccCalcTimes(std::vector<int> a, std::vector<int> b);
};


