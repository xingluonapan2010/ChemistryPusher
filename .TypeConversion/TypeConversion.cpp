#include"TypeConversion.h"


std::vector<int> TypeConversion::fromIntToDigitArr(int wh) {
	std::vector<int> tmpint;
	std::string tmpstring = std::to_string(wh);
	for (int i = 0; i < tmpstring.size(); i++) {
		tmpint.push_back(tmpstring[i] - '0');
	}
	return tmpint;
}


std::vector<int> TypeConversion::fromIntToOppoDigitArr(int wh) {
	std::vector<int> tmpint;
	std::string tmpstring = std::to_string(wh);
	for (int i = tmpstring.size() - 1; i >= 0; i--) {
		tmpint.push_back(tmpstring[i] - '0');
	}
	return tmpint;
}

std::vector<int> TypeConversion::fromWstringtoOppoDigitArr(std::wstring wh) {//(µ¹Ðò)
	std::vector<int> DigitArr;
	for (int i = wh.size() - 1; i >= 0; i--) {
		DigitArr.push_back(wh[i] - L'0');
	}
	return DigitArr;
}

std::vector<int> TypeConversion::oppoDigitArr(std::vector<int> wh) {
	std::vector<int> oppo;
	for (int i = wh.size() - 1; i >= 0; i--) {
		oppo.push_back(wh[i]);
	}
	return oppo;
}



std::wstring TypeConversion::fromDigitArrtoOppoWstring(std::vector<int> wh) {//(»ØÕý)
	std::wstring Wstr;
	for (int i = wh.size() - 1; i >= 0; i--) {
		Wstr.push_back(wh[i] + L'0');
	}
	return Wstr;
}


std::wstring TypeConversion::toPercentStr(double oriNum, int fracLen)
{
	std::wstring percentForm = std::to_wstring(round(oriNum * pow(10, fracLen + 2)) / pow(10, fracLen));
	return  percentForm.substr(0, percentForm.find(L'.') + fracLen + 1) + L"%";
}