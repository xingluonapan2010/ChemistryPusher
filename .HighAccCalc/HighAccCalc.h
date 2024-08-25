#pragma once

#include<vector>
#include<string>
class HighAccCalc {
public:
	HighAccCalc() = default;
	std::vector<int> HighAccCalcPlus(std::vector<int> a, std::vector<int> b);
	std::vector<int> HighAccCalcTimes(std::vector<int> a, std::vector<int> b);
};


