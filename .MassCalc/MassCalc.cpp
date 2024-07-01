﻿#include"MassCalc.h"

std::tuple < std::vector<int>/*元素对应原子序数列表*/, std::vector<std::vector<int>>/*元素原子个数列表*/,
    int/*状态（返回值）*/, std::wstring/*返回字符串信息（目前仅有函数内部需使用）*/ >
    MassCalc::ListGenerating(std::wstring rest/*剩余未读取字符串*/) {
    std::vector<int> orderList;//元素对应原子序数列表
    std::vector<std::vector<int>> countList;//元素原子个数列表
    std::vector<int> num;//元素总个数
    std::wstring tmpEle;//临时储存元素
    std::vector<int> tmpOrderListReturn;//临时储存递归所得元素对应原子序数列表
    std::vector<int> tmpCount;//临时储存元素原子个数
    std::vector<std::vector<int>> tmpCountListReturn;//临时储存递归所得元素原子个数列表
    int openLetter = 0;//假定字母开始位置
    int sepIndex = 0;//出现·时，记录列表在·后的第一个成员索引
    for (int i = 0; i < rest.size(); i++) {
        wchar_t r = rest[i];//读取字符
        if (OverStar::isDigitWCHART(r)) {
            //转入num暂存
            num.push_back(r - L'0');
            openLetter++;
        }
        else if (OverStar::isUpperWCHART(r) || r == L'(' || r == L')' || r == L'·') {
            //字符为'('的开头处理
            if (r == L'(')
                //如果该字符为字符串末尾，返回括号不匹配
                if (i == rest.size() - 1)return std::make_tuple(orderList, countList, MISMATCHED_BRACKETS, L"");

            //字符为'·'的开头处理
            else if (r == L'·')
                //如果在字符串开头或末尾，返回未知书写语法
                if (i == openLetter || i == rest.size() - 1)return std::make_tuple(orderList, countList, UNNOWN_WRITING_GRAMMAR, L"");

            //四者公用清空暂存区部分：
            //如果tmpEle暂存区非空
            if (tmpEle.size()) {
                int order = order_map[tmpEle];
                if (order == 0)return std::make_tuple(orderList, countList, UNKNOWN_ELE, L"");
                orderList.push_back(order);
                tmpEle.clear();
                if (tmpCount.size()) {
                    countList.push_back(tmpCount);
                    tmpCount.clear();
                }
                else {
                    std::vector<int> tmpPushOne;
                    tmpPushOne.push_back(1);
                    countList.push_back(tmpPushOne);
                }
            }
            //如果递归暂存区非空
            else if (tmpOrderListReturn.size()) {
                for (int x = 0; x < tmpOrderListReturn.size(); x++) {
                    orderList.push_back(tmpOrderListReturn[x]);
                    tmpCount.size() ? countList.push_back(oppoDigitArr(HighAccCalcTimes(oppoDigitArr(tmpCountListReturn[x]), oppoDigitArr(tmpCount))))
                        : countList.push_back(oppoDigitArr(tmpCountListReturn[x]));
                }
                tmpOrderListReturn.clear();
                tmpCountListReturn.clear();
                tmpCount.clear();
            }

            //对于isUpper，否则为字母开始
            //对于'('，否则为字母开始向前标志
            //对于'·'，否则位于非法位置
            //对于')'，永远返回下一级，其中EMPTY_IN_BRACKET已经在'('中处理
            else
                if (r == L'·')return std::make_tuple(orderList, countList, UNNOWN_WRITING_GRAMMAR, L"");

            if (OverStar::isUpperWCHART(r))tmpEle.push_back(r);//对于isUpper，无论字母是否为开始，都要将此字符转入tmpEle暂存
            else if (r == L'(') {//有关'('的后续处理
                //递归（上级）
                auto ReturnRet = ListGenerating(rest.substr(i + 1, rest.size() - i - 1));

                /*
                状态结果处理：
                如果为SUCCESS，则未找到上一级的有括号但遍历已即将结束，返回括号不匹配
                如果为RIGHT_BRACKET_RETURN，则递归成功，继续处理
                否则返回上一级返回的错误值以传递到下一级
                */
                int ReturnState = std::get<2>(ReturnRet);
                if (ReturnState == SUCCESS)return std::make_tuple(orderList, countList, MISMATCHED_BRACKETS, L"");
                if (ReturnState != RIGHT_BRACKET_RETURN)return std::make_tuple(orderList, countList, ReturnState, L"");
                i += (_wtoi(std::get<3>(ReturnRet).c_str()) + 1);//迭代器后移

                //将递归所得列表转入递归暂存区
                tmpOrderListReturn = std::get<0>(ReturnRet);
                if (tmpOrderListReturn.empty())return std::make_tuple(orderList, countList, EMPTY_IN_BRACKET, L"");
                tmpCountListReturn = std::get<1>(ReturnRet);
            }
            //对于')'，递归结束，降到下一级
            else if (r == L')')return std::make_tuple(orderList, countList, RIGHT_BRACKET_RETURN, std::to_wstring(i));
            else {//有关'·'的后续处理
                //递归（平级）
                auto ReturnRet = ListGenerating(rest.substr(i + 1, rest.size() - i - 1));

                /*
                状态结果处理：
                如果为RIGHT_BRACKET_RETURN，则由于右括号过多而提前返回，返回括号不匹配
                如果为SUCCESS，则递归成功，继续处理
                否则将后一块平级返回给这一块
                */
                int ReturnState = std::get<2>(ReturnRet);
                if (ReturnState == RIGHT_BRACKET_RETURN)return std::make_tuple(orderList, countList, MISMATCHED_BRACKETS, L"");
                if (ReturnState != SUCCESS)return std::make_tuple(orderList, countList, ReturnState, L"");

                //记录·后第一个列表成员索引
                sepIndex = orderList.size();
                //将递归所得列表转入此块
                std::vector<int> GetOrderList = std::get<0>(ReturnRet);
                orderList.insert(orderList.end(), GetOrderList.begin(), GetOrderList.end());
                std::vector<std::vector<int>> GetCountList = std::get<1>(ReturnRet);
                countList.insert(countList.end(), GetCountList.begin(), GetCountList.end());

                break;//跳转至末处理
            }
        }
        else if (OverStar::isLowerWCHART(r)) {
            //当tmpCount非空，或递归count非空，或为起始字母时，均非法
            if (tmpCount.size() || tmpCountListReturn.size() || i == openLetter)return std::make_tuple(orderList, countList, UNKNOWN_ELE, std::to_wstring(r));
            tmpEle.push_back(r);
        }
        else if (OverStar::isSmallWCHART(r)) {
            //防止递归时形如"(₂"的情况发生
            if (i == 0)return std::make_tuple(orderList, countList, IS_DIGIT_AFTER_LEFT_BRACKET, L"");
            tmpCount.push_back(bigger[r] - L'0');
        }
        else {
            return std::make_tuple(orderList, countList, UNKNOWN_ELE, std::to_wstring(r));
        }
    }
    //清空tmpEle暂存区
    if (tmpEle.size()) {
        int order = order_map[tmpEle];
        if (order == 0)return std::make_tuple(orderList, countList, UNKNOWN_ELE, tmpEle);
        orderList.push_back(order);
        if (tmpCount.size())countList.push_back(tmpCount);
        else {
            std::vector<int> tmpPushOne;
            tmpPushOne.push_back(1);
            countList.push_back(tmpPushOne);
        }
    }
    //清空递归暂存区
    else if (tmpOrderListReturn.size()) {
        for (int x = 0; x < tmpOrderListReturn.size(); x++) {
            orderList.push_back(tmpOrderListReturn[x]);
            tmpCount.size() ? countList.push_back(oppoDigitArr(HighAccCalcTimes(oppoDigitArr(tmpCountListReturn[x]), oppoDigitArr(tmpCount))))
                : countList.push_back(oppoDigitArr(tmpCountListReturn[x]));
        }
        tmpOrderListReturn.clear();
    }
    //若两者皆不存在，且非·，则报错未知书写语法
    else if (!sepIndex) return std::make_tuple(orderList, countList, UNNOWN_WRITING_GRAMMAR, L"");

    //遍历与元素总个数(num)相乘
    if (num.size()) {
        /*
        对于三目运算表达式：!sepIndex ? orderList.size() : sepIndex
        若sepIndex为空，则未出现·，应对列表每个成员逐一相乘
        否则，已标记·后第一个列表成员相应索引，应对该成员之前的每个成员逐一相乘
        */
        for (int x = 0; x < (!sepIndex ? orderList.size() : sepIndex); x++)countList[x] = oppoDigitArr(HighAccCalcTimes(oppoDigitArr(countList[x]), oppoDigitArr(num)));
    }

    return std::make_tuple(orderList, countList, SUCCESS, L"");
}

void MassCalc::eventualEleListGenerating(std::vector<int> orderList, std::vector<std::vector<int>> countList){
    std::vector<int> table[120];//创建哈希表，该哈希表各成员对应最终值为倒序
    for (int i = 0; i < orderList.size(); i++) {
        //以倒序形式进行哈希
        if (table[orderList[i]].size())table[orderList[i]] = HighAccCalcPlus(table[orderList[i]], oppoDigitArr(countList[i]));
        else table[orderList[i]] = oppoDigitArr(countList[i]);
    }
    std::vector<int> total;//记录相对分子质量（倒序）
    //赋值于：this->eventualTotalMass（倒序运算，正序push）
    //赋值于：this->eventualOrderList（正序push）以及this->eventualCountList（倒序push）
    for (int i = 0; i < 120; i++) {
        int tmp = table[i].size();
        if (tmp) {
            total = HighAccCalcPlus(total, HighAccCalcTimes(oppo_mass_map[i], table[i]));
            this->eventualOrderList.push_back(i);
            this->eventualCountList.push_back(table[i]);
        }
    }
    this->eventualTotalMass = total;
}
