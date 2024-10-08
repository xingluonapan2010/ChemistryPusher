#pragma once

#include".ChemistryElements/ChemistryElements.h"
#include".HighAccCalc/HighAccCalc.h"
#include".MassCalc/MassCalc.h"
#include "resource.h"
#include<CommCtrl.h>
#include<iostream>

#define MAX_LOADSTRING 100

#define MAX_READSTRING 1100

#define ITERID_OUTPUT_END 1003//记录static结束ID的后一个空ID，以便批量操作
#define ITERID_INPUT_END 2003//记录edit结束ID的后一个空ID，以便批量操作
#define ITERID_CLICK_END 3003//记录MassCalc主界面button结束ID的后一个ID，以便批量操作
#define ITERID_OUTPUT_BEGIN 1000//记录static起始ID，以便批量操作
#define ITERID_INPUT_BEGIN 2000//记录edit起始ID，以便批量操作
#define ITERID_CLICK_BEGIN 3000//记录MassCalc主界面button起始ID，以便批量操作

//控件ID

//static
#define ID_OUTPUT_EQUATION 1000
#define ID_OUTPUT_NUM 1001
#define ID_OUTPUT_RESULT 1002

//edit
#define ID_INPUT_EQUATION 2000
#define ID_INPUT_NUM 2001
#define ID_OUTPUT_RESULTVAL 2002//readonly

//button
#define ID_CLICKBUTTON 3000
#define ID_MCCLEAR 3001
#define ID_INGREDIENTS_LIST_BUTTON 3002
#define ID_INGREDIENTS_LIST_FRACTION_OK 3003

//combobox
#define ID_INGREDIENTS_LIST_COMBOBOX 4000

//listview
#define ID_INGREDIENTS_LISTVIEW 5000
