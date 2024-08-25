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

#define UNUSED 0//����ĳ��Ϣδʹ��wParam��lParam

typedef int STATE;//״̬����

class MassCalc : public ChemistryElements, public HighAccCalc, public TypeConversion {
public:
    MassCalc();

    //����RLM�б��������ص��������ղ�����
    std::tuple < std::vector<int>/*Ԫ�ض�Ӧԭ�������б�*/, std::vector<std::vector<int>>/*Ԫ��ԭ�Ӹ����б�*/,
        int/*״̬������ֵ��*/, std::wstring/*�����ַ�����Ϣ*/ >
        ListGenerating(std::wstring rest/*ʣ��δ��ȡ�ַ���*/);

    //��������Ԫ�������б�
    void eventualEleListGenerating(std::vector<int> orderList, std::vector<std::vector<int>> countList);

    //������Է�������������
    std::vector<int> eventualTotalMassReturn() {
        return this->eventualTotalMass;
    }

    //�����ݴ��б�����
    std::pair<std::vector<int>, std::vector<std::vector<int>>> listDataReturn() {
        return std::make_pair(eventualOrderList, eventualCountList);
    }

    //����б�
    void clear() {
        eventualOrderList.clear();
        eventualCountList.clear();
        eventualTotalMass.clear();
    }

    std::map<std::wstring, int> order_map;//Ԫ�ض�Ӧԭ������
    std::map<int, std::wstring> ele_map;//ԭ��������ӦԪ��
    std::map<int, std::vector<int>> mass_map;//ԭ��������Ӧ�������ԭ������
    std::map<int, std::vector<int>> oppo_mass_map;//ԭ��������Ӧ�������ԭ������

private:
    std::vector<int> eventualOrderList;//��¼����Ԫ�ض�Ӧԭ�������б����б�Ϊ����
    std::vector<std::vector<int>> eventualCountList;//��¼����Ԫ��ԭ�Ӹ����б����б�Ϊ����
    std::vector<int> eventualTotalMass;//��¼������Է�����������ֵΪ����
};
