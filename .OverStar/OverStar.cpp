#include"OverStar.h"
std::map<wchar_t, wchar_t> smaller = {
    {L'1',L'₁'},
    {L'2',L'₂'},
    {L'3',L'₃'},
    {L'4',L'₄'},
    {L'5',L'₅'},
    {L'6',L'₆'},
    {L'7',L'₇'},
    {L'8',L'₈'},
    {L'9',L'₉'},
    {L'0',L'₀'}
};

std::map<wchar_t, wchar_t> bigger = {
    {L'₁',L'1'},
    {L'₂',L'2'},
    {L'₃',L'3'},
    {L'₄',L'4'},
    {L'₅',L'5'},
    {L'₆',L'6'},
    {L'₇',L'7'},
    {L'₈',L'8'},
    {L'₉',L'9'},
    {L'₀',L'0'}
};
namespace OverStar {
    bool isDigitWCHART(wchar_t wh) {
        if (wh == L'1' || wh == L'2' || wh == L'3' || wh == L'4' || wh == L'5' || wh == L'6' || wh == L'7' || wh == L'8' || wh == L'9' || wh == L'0')return true;
        return false;
    }
    bool isAlphaWCHART(wchar_t wh) {
        if (wh == L'A' || wh == L'B' || wh == L'C' || wh == L'D' || wh == L'E' || wh == L'F' || wh == L'G' || wh == L'H' || wh == L'I' || wh == L'J' || wh == L'K' || wh == L'L' || wh == L'M' || wh == L'N'
            || wh == L'O' || wh == L'P' || wh == L'Q' || wh == L'R' || wh == L'S' || wh == L'T' || wh == L'U' || wh == L'V' || wh == L'W' || wh == L'X' || wh == L'Y' || wh == L'Z'
            || wh == L'a' || wh == L'b' || wh == L'c' || wh == L'd' || wh == L'e' || wh == L'f' || wh == L'g' || wh == L'h' || wh == L'i' || wh == L'j' || wh == L'k' || wh == L'l' || wh == L'm' || wh == L'n'
            || wh == L'o' || wh == L'p' || wh == L'q' || wh == L'r' || wh == L's' || wh == L't' || wh == L'u' || wh == L'v' || wh == L'w' || wh == L'x' || wh == L'y' || wh == L'z') {
            return true;
        }
        return false;
    }
    bool isUpperWCHART(wchar_t wh) {
        if (wh == L'A' || wh == L'B' || wh == L'C' || wh == L'D' || wh == L'E' || wh == L'F' || wh == L'G' || wh == L'H' || wh == L'I' || wh == L'J' || wh == L'K' || wh == L'L' || wh == L'M' || wh == L'N'
            || wh == L'O' || wh == L'P' || wh == L'Q' || wh == L'R' || wh == L'S' || wh == L'T' || wh == L'U' || wh == L'V' || wh == L'W' || wh == L'X' || wh == L'Y' || wh == L'Z') {
            return true;
        }
        return false;
    }
    bool isLowerWCHART(wchar_t wh) {
        if (wh == L'a' || wh == L'b' || wh == L'c' || wh == L'd' || wh == L'e' || wh == L'f' || wh == L'g' || wh == L'h' || wh == L'i' || wh == L'j' || wh == L'k' || wh == L'l' || wh == L'm' || wh == L'n'
            || wh == L'o' || wh == L'p' || wh == L'q' || wh == L'r' || wh == L's' || wh == L't' || wh == L'u' || wh == L'v' || wh == L'w' || wh == L'x' || wh == L'y' || wh == L'z') {
            return true;
        }
        return false;
    }
    bool isSmallWCHART(wchar_t wh) {
        if (wh == L'₁' || wh == L'₂' || wh == L'₃' || wh == L'₄' || wh == L'₅' || wh == L'₆' || wh == L'₇' || wh == L'₈' || wh == L'₉' || wh == L'₀') {
            return true;
        }
        return false;
    }
    bool isAllDigitsPWCHART(wchar_t* wh, int len){
        for (int i = 0; i < len; i++) {
            if (!isDigitWCHART(wh[i]))return false;
        }
        return true;
    }
}
