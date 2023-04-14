//----------------------------------------------------------------------------------------
//
//�����L���O
//Author::TAKANO
//
//----------------------------------------------------------------------------------------

//--------------------------------------
//�C���N���[�h�t�@�C��
//--------------------------------------
#include "application.h"
#include "ranking.h"
#include "bg.h"
#include "score.h"
#include "input.h"
#include "sound.h"
#include "ui.h"
#include <stdio.h>

//--------------------------------------
//�}�N����`
//--------------------------------------
#define RANK_H				(80)					//�c��
#define RANK_WD				(50)					//����

//--------------------------------------
//�O���[�o���ϐ�
//--------------------------------------
//CBg *CRanking::m_pBg;
CScore *CRanking::m_pScore;
CTexture *CRanking::m_pTexture;
CUi *CRanking::m_pUi;
int CRanking::m_nBox;

//--------------------------------------
//�R���X�g���N�^
//--------------------------------------
CRanking::CRanking()
{
	for (int i = 0; i < MAX_RANKING; i++)
	{
		m_SortData[i] = {};
	}
}

//--------------------------------------
//�f�X�g���N�^
//--------------------------------------
CRanking::~CRanking()
{
}

//--------------------------------------
//������
//--------------------------------------
HRESULT CRanking::Init()
{
	Load();
	BubbleSort(m_nBox);
	Save();

	CBg* pBg = CApplication::GetBg()->Create(D3DXVECTOR3(1280.0f / 2, 720.0f / 2, 0.0f),
											1280.0f,
											720.0f,
											CTexture::TEXTURE::TEXTURE_RANKING_BG);

	m_pUi = CUi::Create(D3DXVECTOR3(360.0f, 383.0f, 0.0f), 80.0f, 600.0f, CTexture::TEXTURE::TEXTURE_RANKING);

	for (int i = 0; i < MAX_RANKING; i++)
	{
		m_pScore = CScore::Create(D3DXVECTOR3(620.0f + 40.0f * i, 137.0f + 123.0f * i, 0.0f), m_SortData[i]);
	}
	
	//�T�E���h�̍Đ�
	CApplication::GetSound()->Play(CSound::SOUND_BGM_RANKING);

	return S_OK;
}

//--------------------------------------
//�I��
//--------------------------------------
void CRanking::Uninit()
{
	//�T�E���h�̒�~
	CApplication::GetSound()->Stop(CSound::SOUND_BGM_RANKING);
}

//--------------------------------------
//�X�V
//--------------------------------------
void CRanking::Update()
{
	//����L�[(ENTER)�������ꂽ���ǂ���
	if (CApplication::GetKyeboard()->GetkeyboardTrigger(DIK_RETURN))
	{
		CApplication::SetMode(CApplication::MODE::MODE_TITLE);
	}
}

//--------------------------------------
//�`��
//--------------------------------------
void CRanking::Draw()
{
	
}

//--------------------------------------
//�����L���O�̒l�ݒ�
//--------------------------------------
void CRanking::Set(int nScore)
{
	m_nBox = nScore;
}

//--------------------------------------
//�����L���O�̏��擾
//--------------------------------------
int CRanking::Get()
{
	return m_nBox;
}

//--------------------------------------
//�o�u���\�[�g(�l����ւ�)
//--------------------------------------
void CRanking::BubbleSort(int nSort)
{
	if (nSort >= m_SortData[COMPARE_RANKING])
	{//�󂯎�����l�������L���O�̒l�̈�ԉ����傫��������
		m_SortData[COMPARE_RANKING] = nSort;										//��ԉ��̒l�ɑ������
	}
	for (int nInData = 0; nInData < COMPARE_RANKING; nInData++)						//��r�����
	{
		for (int nChange = nInData + 1; nChange < MAX_RANKING; nChange++)			//��r������
		{
			if (m_SortData[nInData] < m_SortData[nChange])
			{
				int nBox = m_SortData[nInData];
				m_SortData[nInData] = m_SortData[nChange];
				m_SortData[nChange] = nBox;
			}
		}
	}
}

//--------------------------------------
//�O���t�@�C���ɕۑ�
//--------------------------------------
void CRanking::Save()
{
	//�t�@�C���ɏ�������
	FILE *pFile;        //�t�@�C���|�C���^��錾

	//�t�@�C�����J��
	pFile = fopen(FILE_NAME, "w");

	if (pFile != nullptr)
	{//�t�@�C�����J�����Ƃ�
	 //�t�@�C���ɐ��l�������o��
		for (int i = 0; i < MAX_RANKING; i++)
		{
			fprintf(pFile, "%d\n", CRanking::m_SortData[i]);
		}

		//�t�@�C�������
		fclose(pFile);
	}
	//else
	//{//�t�@�C�����J���Ȃ������Ƃ�
	//	printf("~~~�t�@�C�����J���Ȃ������I~~~");
	//}
}

//--------------------------------------
//�O���t�@�C�����J��
//--------------------------------------
void CRanking::Load()
{
	FILE *pFile;        //�t�@�C���|�C���^��錾

	//�t�@�C�����J��
	pFile = fopen(FILE_NAME, "r");

	if (pFile != nullptr)
	{//�t�@�C�����J�����Ƃ�
	 //�t�@�C���ɐ��l�������o��
		for (int i = 0; i < MAX_RANKING; i++)
		{
			fscanf(pFile, "%d", &CRanking::m_SortData[i]);
		}

		//�t�@�C�������
		fclose(pFile);
	}
	//else
	//{//�t�@�C�����J���Ȃ������Ƃ�
	//	printf("~~~�t�@�C�����J���Ȃ������I~~~");
	//}
}

//--------------------------------------
//�w�i�̏��擾
//--------------------------------------
CScore * CRanking::GetScore()
{
	return m_pScore;
}

CUi * CRanking::GetUi()
{
	return m_pUi;
}

//--------------------------------------
//�e�N�X�`���̏��擾
//--------------------------------------
CTexture * CRanking::GetTexture()
{
	return m_pTexture;
}
