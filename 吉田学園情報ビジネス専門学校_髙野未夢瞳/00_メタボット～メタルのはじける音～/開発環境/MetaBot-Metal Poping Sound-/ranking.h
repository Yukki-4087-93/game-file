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
class CBg;
class CScore;
class CObject2D;
class CTexture;
class CUi;

//---------------------------------------------------
//�}�N����`
//---------------------------------------------------
#define MAX_RANKING			(5)
#define COMPARE_RANKING		(4)
#define FILE_NAME			"Data/Text/Ranking.txt"			//�ǂݍ��ރt�@�C��

//----------------------------------------
//�N���X�錾
//�����L���O
//----------------------------------------
class CRanking
{
public:
	CRanking();												//�R���X�g���N�^
	~CRanking();											//�f�X�g���N�^
	HRESULT Init();											//������
	void Uninit();											//�I��
	void Update();											//�X�V
	void Draw();											//�`��
	static void Set(int nScore);							//�����L���O�̐ݒ�
	int Get();												//�����L���O�̎擾
	void BubbleSort(int nSort);								//�\�[�g����
	void Save();											//�t�@�C���ۑ�
	void Load();											//�t�@�C���Ăяo��

private:
	static CBg* m_pBg;										//�w�i�̃|�C���^�[
	static CScore* m_pScore;								//�X�R�A�̃|�C���^�[
	static CUi* m_pUi;										//���[�U�[�C���^�[�t�F�[�X�̃|�C���^�[
	static int m_nBox;										//�����L���O�̒l���󂯎��ϐ�
	int m_nRankUpdate;										//�X�V�����NNo.
	int m_nCountState;										//�����L���O�X�R�A�̏�ԃJ�E���^�[
	int m_nScoreState;										//�����L���O�X�R�A�̏�ԏ��
	int m_SortData[MAX_RANKING];							//�\�[�g�������̂��󂯎��ϐ�
};

#endif // !_RANKING_H_
