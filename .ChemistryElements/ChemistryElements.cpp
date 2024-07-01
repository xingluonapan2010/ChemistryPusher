#include"ChemistryElements.h"

std::vector<int> fromIntToDigitArr(int wh) {
	std::vector<int> tmpint;
	std::string tmpstring = std::to_string(wh);
	for (int i = 0; i < tmpstring.size(); i++) {
		tmpint.push_back(tmpstring[i] - '0');
	}
	return tmpint;
}

std::vector<int> fromIntToOppoDigitArr(int wh){
	std::vector<int> tmpint;
	std::string tmpstring = std::to_string(wh);
	for (int i = tmpstring.size() - 1; i >= 0; i--) {
		tmpint.push_back(tmpstring[i] - '0');
	}
	return tmpint;
}


ChemistryElements::ChemistryElements() {
	for (int i = 0; i < 44; i++) {
		order_map[Eles.at(i).symbol] = Eles.at(i).number;
		ele_map[Eles.at(i).number] = Eles.at(i).symbol;
		mass_map[Eles.at(i).number] = fromIntToDigitArr(Eles.at(i).mass);
		oppo_mass_map[Eles.at(i).number] = fromIntToOppoDigitArr(Eles.at(i).mass);
	}
}
