#include "stdafx.h"
#include "FPSCountor.h"

using namespace MyDirectX;

FPSCountor::FPSCountor(unsigned int smp)
{
	//�T���v�����̐ݒ�
	SetSampleNum(smp);
	//�v�����鎞�v�̑I��
	if (QueryPerformanceCounter(&m_Counter) != 0)
	{
		//QueryPerformanceCounter�֐����g���t���O
		m_iCounterFlag = FPSCOUNTER_QUERYPER_COUNTER;
		//�������̎����i�N���b�N���j���擾
		m_OldLongCount = m_Counter.QuadPart;        
		LARGE_INTEGER Freq;
		//1�b������N���b�N�����擾
		QueryPerformanceFrequency(&Freq);            
		m_dFreq = (double)Freq.QuadPart;
	}
	else
	{
		//timeGetTime�֐����g���t���O
		m_iCounterFlag = FPSCOUNTER_TIMEGETTIME;
		//���x���グ��
		timeBeginPeriod(1);
		//�������̎����i�~���b�j���擾
		m_dwTGTOldCount = timeGetTime();
	}
}


FPSCountor::~FPSCountor()
{
	//�^�C�}�[�̐��x��߂�
	if (m_iCounterFlag == FPSCOUNTER_TIMEGETTIME)
		timeEndPeriod(1);    
}

double FPSCountor::GetFPS()
{
	double Def = GetCurDefTime();
	//�v�Z�ł��Ȃ��̂ł�Ԃ�
	if (Def == 0) return 0;
	return UpdateFPS(Def);
}

void FPSCountor::SetSampleNum(unsigned int smp)
{
	//���ς��v�Z�����
	m_uiNum = smp; 
	//���X�g������
	m_dwDefTimeLst.resize(m_uiNum, 0.0);    
	m_dwSumTimes = 0;
}

double FPSCountor::GetCurDefTime()
{
	//�������Ԃ��v��
	if (m_iCounterFlag == FPSCOUNTER_QUERYPER_COUNTER)
	{
		//QueryPerformanceCounter�֐��ɂ��v��
		QueryPerformanceCounter(&m_Counter);
		LONGLONG LongDef = m_Counter.QuadPart - m_OldLongCount;
		double dDef = (double)LongDef;
		m_OldLongCount = m_Counter.QuadPart;
		return dDef * 1000 / m_dFreq;
	}
	//timeGetTime�֐��ɂ��v��
	DWORD CurTime = timeGetTime();
	DWORD CurDef = CurTime - m_dwTGTOldCount;
	m_dwTGTOldCount = CurTime;
	return CurDef;
}

double FPSCountor::UpdateFPS(double Def)
{
	//�ł��Â��f�[�^������
	m_dwDefTimeLst.pop_front();
	//�V�����f�[�^��ǉ�
	m_dwDefTimeLst.push_back(Def);
	//FPS�Z�o
	double FPS;
	double AveDef = (m_dwSumTimes + Def) / m_uiNum;
	if (AveDef != 0) FPS = 1000.0 / AveDef;
	//���ʉ��Z�����̍X�V
	m_dwSumTimes += Def - *m_dwDefTimeLst.begin();
	return FPS;
}
