#pragma once
#include<string>
#include<map>

extern std::map<wchar_t, wchar_t> smaller;
extern std::map<wchar_t, wchar_t> bigger;

namespace OverStar {//自定义以代替微软提供，防未知错误
    
    bool isDigitWCHART(wchar_t wh);

    bool isAlphaWCHART(wchar_t wh);

    bool isUpperWCHART(wchar_t wh);

    bool isLowerWCHART(wchar_t wh);

    bool isSmallWCHART(wchar_t wh);

    bool isAllDigitsPWCHART(wchar_t* wh, int len);

}

