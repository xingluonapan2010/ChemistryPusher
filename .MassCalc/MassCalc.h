#pragma once

#include"../.ChemistryElements/ChemistryElements.h"
#include"../.HighAccCalc/HighAccCalc.h"
#include"../.OverStar/OverStar.h"
#include"../.TypeConversion/TypeConversion.h"

#include<map>
#include<string>
#include<tuple>
#include<vector>
#include<Windows.h>

#define SUCCESS 100
#define MISMATCHED_BRACKETS 200
#define UNKNOWN_ELE 300
#define IS_DIGIT_AFTER_LEFT_BRACKET 400
#define RIGHT_BRACKET_RETURN 500
#define EMPTY_IN_BRACKET 600
#define UNNOWN_WRITING_GRAMMAR 700

#define UNUSED 0//表明某消息未使用wParam或lParam

typedef int STATE;//状态类型

class MassCalc : public ChemistryElements, public HighAccCalc, public TypeConversion {
public:
    MassCalc();

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

    //返回暂存列表数据
    std::pair<std::vector<int>, std::vector<std::vector<int>>> listDataReturn() {
        return std::make_pair(eventualOrderList, eventualCountList);
    }

    //清空列表
    void clear() {
        eventualOrderList.clear();
        eventualCountList.clear();
        eventualTotalMass.clear();
    }

    std::map<std::wstring, int> order_map;//元素对应原子序数
    std::map<int, std::wstring> ele_map;//原子序数对应元素
    std::map<int, std::vector<int>> mass_map;//原子序数对应正序相对原子质量
    std::map<int, std::vector<int>> oppo_mass_map;//原子序数对应倒序相对原子质量

private:
    std::vector<int> eventualOrderList;//记录最终元素对应原子序数列表，该列表为正序
    std::vector<std::vector<int>> eventualCountList;//记录最终元素原子个数列表，该列表为倒序
    std::vector<int> eventualTotalMass;//记录最终相对分子质量，该值为倒序
};
