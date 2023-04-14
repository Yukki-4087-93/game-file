//--------------------------------------------------------------------------------------
//
//�����L���O����
//Author::TAKANO
//
//--------------------------------------------------------------------------------------
#ifndef _RANKING_H_
#define _RANKING_H_

#include <d3dx9.h>

//----------------------------------------
//�O���錾
//----------------------------------------
//class CBg;
class CScore;
class CObject2D;
class CTexture;
class CSoundManager;
class CUi;

//---------------------------------------------------
//�}�N����`
//---------------------------------------------------
#define MAX_RANKING			(5)
#define COMPARE_RANKING		(4)
#define FILE_NAME			"Data/Text/Ranking.txt"				//�ǂݍ��ރt�@�C��

//----------------------------------------
//�N���X�錾
//�����L���O
//----------------------------------------
class CRanking
{
public:
	CRanking();
	~CRanking();
	HRESULT Init();
	void Uninit();
	void Update();
	void Draw();
	static void Set(int nScore);
	int Get();
	void BubbleSort(int nSort);		//�\�[�g����
	void Save();											//�t�@�C���ۑ�
	void Load();											//�t�@�C���Ăяo��
	//static CBg* GetBg();									//�w�i�̏��擾
	static CScore* GetScore();								//�X�R�A�̏��擾
	static CUi* GetUi();
	static CTexture* GetTexture();							//�e�N�X�`�����̎擾

private:
	static int m_nBox;
	int m_nRankUpdate;										//�X�V�����NNo.
	int m_nCountState;										//�����L���O�X�R�A�̏�ԃJ�E���^�[
	int m_nScoreState;										//�����L���O�X�R�A�̏�ԏ��
	int m_SortData[MAX_RANKING] = {};
	//static CBg* m_pBg;										//�w�i�̃|�C���^�[
	static CScore* m_pScore;								//�X�R�A�̃|�C���^�[
	static CUi* m_pUi;
	static CTexture* m_pTexture;							//�e�N�X�`���̃|�C���^�[
};

#endif // !_RANKING_H_
