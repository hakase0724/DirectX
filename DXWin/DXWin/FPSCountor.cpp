#include "stdafx.h"
#include "FPSCountor.h"

using namespace MyDirectX;

FPSCountor::FPSCountor(unsigned int smp)
{
	//サンプル数の設定
	SetSampleNum(smp);
	//計測する時計の選択
	if (QueryPerformanceCounter(&m_Counter) != 0)
	{
		//QueryPerformanceCounter関数を使うフラグ
		m_iCounterFlag = FPSCOUNTER_QUERYPER_COUNTER;
		//生成時の時刻（クロック数）を取得
		m_OldLongCount = m_Counter.QuadPart;        
		LARGE_INTEGER Freq;
		//1秒当たりクロック数を取得
		QueryPerformanceFrequency(&Freq);            
		m_dFreq = (double)Freq.QuadPart;
	}
	else
	{
		//timeGetTime関数を使うフラグ
		m_iCounterFlag = FPSCOUNTER_TIMEGETTIME;
		//精度を上げる
		timeBeginPeriod(1);
		//生成時の時刻（ミリ秒）を取得
		m_dwTGTOldCount = timeGetTime();
	}
}


FPSCountor::~FPSCountor()
{
	//タイマーの精度を戻す
	if (m_iCounterFlag == FPSCOUNTER_TIMEGETTIME)
		timeEndPeriod(1);    
}

double FPSCountor::GetFPS()
{
	double Def = GetCurDefTime();
	//計算できないのでを返す
	if (Def == 0) return 0;
	return UpdateFPS(Def);
}

void FPSCountor::SetSampleNum(unsigned int smp)
{
	//平均を計算する個数
	m_uiNum = smp; 
	//リスト初期化
	m_dwDefTimeLst.resize(m_uiNum, 0.0);    
	m_dwSumTimes = 0;
}

double FPSCountor::GetCurDefTime()
{
	//差分時間を計測
	if (m_iCounterFlag == FPSCOUNTER_QUERYPER_COUNTER)
	{
		//QueryPerformanceCounter関数による計測
		QueryPerformanceCounter(&m_Counter);
		LONGLONG LongDef = m_Counter.QuadPart - m_OldLongCount;
		double dDef = (double)LongDef;
		m_OldLongCount = m_Counter.QuadPart;
		return dDef * 1000 / m_dFreq;
	}
	//timeGetTime関数による計測
	DWORD CurTime = timeGetTime();
	DWORD CurDef = CurTime - m_dwTGTOldCount;
	m_dwTGTOldCount = CurTime;
	return CurDef;
}

double FPSCountor::UpdateFPS(double Def)
{
	//最も古いデータを消去
	m_dwDefTimeLst.pop_front();
	//新しいデータを追加
	m_dwDefTimeLst.push_back(Def);
	//FPS算出
	double FPS;
	double AveDef = (m_dwSumTimes + Def) / m_uiNum;
	if (AveDef != 0) FPS = 1000.0 / AveDef;
	//共通加算部分の更新
	m_dwSumTimes += Def - *m_dwDefTimeLst.begin();
	return FPS;
}
