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
#include <assert.h>

//--------------------------------------
//�}�N����`
//--------------------------------------
#define RANK_H				(80)					//�c��
#define RANK_WD				(50)					//����

//--------------------------------------
//�O���[�o���ϐ�
//--------------------------------------
CBg *CRanking::m_pBg;
CScore *CRanking::m_pScore;
CUi *CRanking::m_pUi;
int CRanking::m_nBox;

//--------------------------------------
//�R���X�g���N�^
//--------------------------------------
CRanking::CRanking()
{
	for (int i = 0; i < MAX_RANKING; i++)
	{//�f�[�^���N���A����
		m_SortData[i] = {};
		m_pScore = {};
	}

	m_nRankUpdate = 0;		//�����L���O���X�V���邽�߂̕ϐ��̃N���A
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
	Load();					//�ǂݍ���
	BubbleSort(m_nBox);		//�\�[�g�f�[�^
	Save();					//�ۑ�

	//�w�i�̐���
	m_pBg = CBg::Create(D3DXVECTOR3(1280.0f / 2, 720.0f / 2, 0.0f), 1280.0f, 720.0f, CTexture::TEXTURE::TEXTYRE_RANKING_BG);

	//UI�̐���
	m_pUi = CUi::Create(D3DXVECTOR3(360.0f, 383.0f, 0.0f), 80.0f, 600.0f, CTexture::TEXTURE::TEXTURE_RANKING_BUMMBER);

	for (int i = 0; i < MAX_RANKING; i++)
	{//�����L���O��\������
		m_pScore = CScore::Create(D3DXVECTOR3(520.0f + 40.0f * i, 137.0f + 123.0f * i, 0.0f), m_SortData[i]);
	}

	//UI�̐���
	m_pUi = CUi::Create(D3DXVECTOR3(980.0f, 107.0f, 0.0f), 200.0f, 400.0f, CTexture::TEXTURE::TEXTURE_RANKING_NOW_UI);

	//�擾�����X�R�A��\������
	m_pScore = CScore::Create(D3DXVECTOR3(920.0f, 157.0f, 0.0f), m_nBox);

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

	if (m_pBg != nullptr)
	{
		m_pBg = nullptr;
	}

	if (m_pUi != nullptr)
	{
		m_pUi = nullptr;
	}

	if (m_pScore != nullptr)
	{
		for (int i = 0; i < MAX_RANKING; i++)
		{
			m_pScore = nullptr;
		}
	}

	//�I�u�W�F�N�g�̉��
	CObject::ReleaseAll();
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
	m_nRankUpdate = -1;		//�\�[�g�ԍ���������

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
				int nBox = m_SortData[nInData];					//�ϐ��ɓ����Ă����l����
				m_SortData[nInData] = m_SortData[nChange];		//�����Ă����l��ύX����ϐ��ɑ��
				m_SortData[nChange] = nBox;						//�ύX�����l�𔠂̕ϐ��ɑ��
			}
		}
	}

	for (int nComparisonData = 0; nComparisonData < MAX_RANKING; nComparisonData++)
	{//�l���r����
		if (m_SortData[nComparisonData] == nSort)
		{//����ւ����f�[�^���������l�Ɠ����Ȃ�
			m_nRankUpdate = nComparisonData;	//�X�V�f�[�^�ɊY������ԍ��ɑ������
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

	else
	{//�t�@�C�����J���Ȃ������Ƃ�
		assert(false);				//�v���O�������~�߂�
	}
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
			fscanf(pFile, "%d", &m_SortData[i]);
		}

		//�t�@�C�������
		fclose(pFile);
	}

	else
	{//�t�@�C�����J���Ȃ������Ƃ�
		assert(false);				//�v���O�������~�߂�
	}
}
