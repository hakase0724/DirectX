#pragma once
#pragma comment(lib, "winmm.lib")

#include <windows.h>
#include <mmsystem.h>
#include <list>

using namespace std;

//�����擾�Ɏg�p����API
#define FPSCOUNTER_QUERYPER_COUNTER        1
#define FPSCOUNTER_TIMEGETTIME             2
namespace MyDirectX
{
	class FPSCountor
	{
	public:
		FPSCountor(unsigned int smp = 10);
		~FPSCountor();
		// FPS�l���擾
		double GetFPS();
		// �T���v������ύX
		void SetSampleNum(unsigned int smp);
		// ���݂̎������擾
		double GetCurDefTime();
		// FPS���X�V
		double UpdateFPS(double Def);
	private:
		int m_iCounterFlag;                // �g�p����v���֐��̔���t���O
		LARGE_INTEGER m_Counter;           // �N���b�N�J�E���g��
		double m_dFreq;                    // 1�b������N���b�N�J�E���g���i���g���j
		LONGLONG m_OldLongCount;           // �ȑO�̃N���b�N�J�E���g��
		DWORD m_dwTGTOldCount;             // �ȑO�̎����i�~���b�j
		list<double> m_dwDefTimeLst;       // ���ԃ��X�g
		UINT m_uiNum;                      // �ړ����όv�Z���̃f�[�^��
		double m_dwSumTimes;               // ���ʕ����̍��v�l
	};

}

