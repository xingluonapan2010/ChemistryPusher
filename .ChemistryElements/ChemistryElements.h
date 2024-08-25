#pragma once
#ifndef CHEMISTRY_ELEMENTS_H
#define CHEMISTRY_ELEMENTS_H
#include<string>
#include<map>
#include<array>
#include<vector>

typedef int elenum;
typedef std::wstring elesymbol;
typedef int atmass;
typedef double accatmass;

typedef struct{
	elenum number;
	elesymbol symbol;
	atmass mass;
	accatmass acc_mass;
}CMELE;

typedef const CMELE cCMELE;

class ChemistryElements {
private:
	const static int ele_num = 68;/*now*/

	cCMELE H = { 1,L"H",1,1.008 };
	cCMELE He = { 2,L"He",4,4.003 };
	cCMELE Li = { 3,L"Li",7,6.941 };
	cCMELE Be = { 4,L"Be",9,9.012 };
	cCMELE B = { 5,L"B",11,10.81 };
	cCMELE C = { 6,L"C",12,12.01 };
	cCMELE N = { 7,L"N",14,14.01 };
	cCMELE O = { 8,L"O",16,16.00 };
	cCMELE F = { 9,L"F",19,19.00 };
	cCMELE Ne = { 10,L"Ne",20,20.18 };
	cCMELE Na = { 11,L"Na",23,22.99 };
	cCMELE Mg = { 12,L"Mg",24,24.31 };
	cCMELE Al = { 13,L"Al",27,26.98 };
	cCMELE Si = { 14,L"Si",28,28.09 };
	cCMELE P = { 15,L"P",31,30.97 };
	cCMELE S = { 16,L"S",32,32.06 };
	cCMELE Cl = { 17,L"Cl",35,35.45 };
	cCMELE Ar = { 18,L"Ar",40,39.95 };
	cCMELE K = { 19,L"K",39,39.10 };
	cCMELE Ca = { 20,L"Ca",40,40.08 };
	cCMELE Sc = { 21,L"Sc",45,44.96 };
	cCMELE Ti = { 22,L"Ti",48,47.87 };
	cCMELE V = { 23,L"V",51,50.94 };
	cCMELE Cr = { 24,L"Cr",52,52.00 };
	cCMELE Mn = { 25,L"Mn",55,54.94 };
	cCMELE Fe = { 26,L"Fe",56,55.85 };
	cCMELE Co = { 27,L"Co",59,58.93 };
	cCMELE Ni = { 28,L"Ni",59,58.69 };
	cCMELE Cu = { 29,L"Cu",64,63.55 };
	cCMELE Zn = { 30,L"Zn",65,65.38 };
	cCMELE Ga = { 31,L"Ga",70,69.72 };
	cCMELE Ge = { 32,L"Ge",73,72.63 };
	cCMELE As = { 33,L"As",75,74.92 };
	cCMELE Se = { 34,L"Se",79,78.96 };
	cCMELE Br = { 35,L"Br",80,79.90 };
	cCMELE Kr = { 36,L"Kr",84,83.80 };

	cCMELE Rb = { 37,L"Rb",85,85.47 };
	cCMELE Sr = { 38,L"Sr",88,87.62 };
	cCMELE Y = { 39,L"Y",89,88.91 };
	cCMELE Zr = { 40,L"Zr",91,91.22 };
	cCMELE Nb = { 41,L"Nb",93,92.91 };
	cCMELE Mo = { 42,L"Mo",96,95.96 };
	cCMELE Tc = { 43,L"Tc",98,98 };
	cCMELE Ru = { 44,L"Ru",101,101.1 };
	cCMELE Rh = { 45,L"Rh",103,102.9 };
	cCMELE Pd = { 46,L"Pd",106,106.4 };
	cCMELE Ag = { 47,L"Ag",108,107.9 };
	cCMELE Cd = { 48,L"Cd",112,112.4 };
	cCMELE In = { 49,L"In",115,114.8 };
	cCMELE Sn = { 50,L"Sn",119,118.7 };
	cCMELE Sb = { 51,L"Sb",122,121.8 };
	cCMELE Te = { 52,L"Te",128,127.6 };
	cCMELE I = { 53,L"I",127,126.9 };
	cCMELE Xe = { 54,L"Xe",131,131.3 };
	cCMELE Cs = { 55,L"Cs",133,132.9 };
	cCMELE Ba = { 56,L"Ba",137,137.3 };

	cCMELE Hf = { 72,L"Hf",179,178.5 };
	cCMELE Ta = { 73,L"Ta",181,180.9 };
	cCMELE W = { 74,L"W",184,183.8 };
	cCMELE Re = { 75,L"Re",186,186.2 };
	cCMELE Os = { 76,L"Os",190,190.2 };
	cCMELE Ir = { 77,L"Ir",192,192.2 };
	cCMELE Pt = { 78,L"Pt",195,195.1 };
	cCMELE Au = { 79,L"Au",197,197.0 };
	cCMELE Hg = { 80,L"Hg",201,200.6 };
	cCMELE Tl = { 81,L"Tl",204,204.4 };
	cCMELE Pb = { 82,L"Pb",207,207.2 };
	cCMELE Bi = { 83,L"Bi",209,209.0 };
	
public:
	std::array<cCMELE, ele_num> Eles = { H, He, Li, Be, B, C, N, O, F, Ne, Na, Mg, Al, Si, P, S, Cl, Ar, K, Ca, Sc, Ti, V, Cr, Mn, Fe, Co, Ni, Cu, Zn, Ga, Ge, As, Se, Br, Kr, 
		Rb, Sr, Y, Zr, Nb, Mo, Tc, Ru, Rh, Pd, Ag, Cd, In, Sn, Sb, Te, I, Xe, Cs, Ba, Hf, Ta, W, Re, Os, Ir, Pt, Au, Hg, Tl, Pb, Bi };

	ChemistryElements() = default;

};

#endif // !CHEMISTRY_ELEMENTS_H

