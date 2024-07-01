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

#define UNUSED 0//����ĳ��Ϣδʹ��wParam��lParam

typedef int STATE;//״̬����

class MassCalc : public ChemistryElements, public HighAccCalc {//�̳�ChemistryElements��
public:
    MassCalc() = default;

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

private:
    std::vector<int> eventualOrderList;//��¼����Ԫ�ض�Ӧԭ�������б����б�Ϊ����
    std::vector<std::vector<int>> eventualCountList;//��¼����Ԫ��ԭ�Ӹ����б����б�Ϊ����
    std::vector<int> eventualTotalMass;//��¼������Է�����������ֵΪ����
};
