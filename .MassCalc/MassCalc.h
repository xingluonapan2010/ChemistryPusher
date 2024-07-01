#pragma once
#include<string>
#include<vector>
#include<tuple>
#include<map>
#include<Windows.h>
#include"../.ChemistryElements/ChemistryElements.h"
#include"../.HighAccCalc/HighAccCalc.h"
#include"../.OverStar/OverStar.h"


#define SUCCESS 100
#define MISMATCHED_BRACKETS 200
#define UNKNOWN_ELE 300
#define IS_DIGIT_AFTER_LEFT_BRACKET 400
#define RIGHT_BRACKET_RETURN 500
#define EMPTY_IN_BRACKET 600
#define UNNOWN_WRITING_GRAMMAR 700

#define UNUSED 0//表明某消息未使用wParam或lParam

typedef int STATE;//状态类型

class MassCalc : public ChemistryElements, public HighAccCalc {//继承ChemistryElements类
public:
    MassCalc() = default;

    //生成RLM列表并发送至回调函数接收并处理
    std::tuple < std::vector<int>/*元素对应原子序数列表*/, std::vector<std::vector<int>>/*元素原子个数列表*/,
        int/*状态（返回值）*/, std::wstring/*返回字符串信息*/ >
        ListGenerating(std::wstring rest/*剩余未读取字符串*/);

    //生成最终元素数据列表
    void eventualEleListGenerating(std::vector<int> orderList, std::vector<std::vector<int>> countList);

    //返回相对分子质量（倒序）
    std::vector<int> eventualTotalMassReturn() {
        return this->eventualTotalMass;
    }

private:
    std::vector<int> eventualOrderList;//记录最终元素对应原子序数列表，该列表为正序
    std::vector<std::vector<int>> eventualCountList;//记录最终元素原子个数列表，该列表为倒序
    std::vector<int> eventualTotalMass;//记录最终相对分子质量，该值为倒序
};
