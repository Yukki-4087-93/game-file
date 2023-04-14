//---------------------------------------------------------
//
//�X�R�A�\��
//Author::TAKANO
//
//---------------------------------------------------------
#ifndef _SCORE_H_
#define _SCORE_H_

//----------------------------------------
//�C���N���[�h�t�@�C��
//----------------------------------------
#include "object.h"
#include "object2d.h"
#include "renderer.h"
#include "texture.h"

//----------------------------------------
//�N���X�錾
//�X�R�A�A�I�u�W�F�N�g�̌p��
//----------------------------------------
class CScore : public CObject
{
public:
	CScore();													//�R���X�g���N�^
	~CScore()override;											//�f�X�g���N�^
	HRESULT Init()override;										//������
	static CScore * Create(D3DXVECTOR3 pos, int nScore);		//�N���G�C�g
	void Uninit()override;										//�I��
	void Update()override;										//�X�V
	void Draw()override;										//�`��

/*�X�R�A���v�Z����֐��܂Ƃ�*/
	void Set(int nScore);										//�X�R�A�̔z�u
	void Add(int nValue);										//�X�R�A�̉��Z
	void Sub(int nSub);											//�X�R�A�̌��Z
	static int Get() { return m_nScore; }						//�X�R�A�̎擾

/*�v���C���[�̃��C�t���v�Z����֐��܂Ƃ�*/
	void SetPlayerLife(int nLife);								//���C�t�̃Z�b�g�i�ڂɌ�����l�Ƃ��āj
	void AddLife(int nAdd);										//���C�t�̉��Z
	static void HitDamage(int nDamage);							//���C�t�̌��Z

/*�^�C�}�[�𐧌䂷��֐��܂Ƃ�*/
	void SetTime(int nTime);									//�^�C�}�[�̔z�u
	void MinusTime(int nMinus);									//�^�C�}�[�̌��Z
	void SetStartTimer(bool bTime) { m_bTimerStart = bTime; }

/*�R���{�𐧌䂷��֐��܂Ƃ�*/
	void SetCombo(int nCombo);									//�R���{�̔z�u
	void AddCombo(int nAddCombo);								//�R���{�̉��Z
	void SubCombo(int nSubCombo);								//�R���{�̌��Z

private:
	static CScore* m_pScore;									//�X�R�A�̃|�C���^�[
	static int m_nScore;										//�X�R�A�̒l
	int m_nTime;												//�^�C�}�[�̖ڂɌ�����e�N�X�`�����䂷�邽�߂̕ϐ�
	int m_nTimeCounter;											//�^�C�}�[��i�߂�ϐ�
	int m_nCountstartTime;										//�^�C�}�[�������܂ł̎��Ԃ𐔂���ϐ�
	static int m_nLife;											//���C�t����ϐ�
	D3DXVECTOR3 m_ScorePos;										//�X�R�A�̈ʒu
	CObject2D* m_pNumber[7];									//�X�R�A�i���o�[�̃|�C���^�[
	static CObject2D* m_pLife[2];								//���C�t�i���o�[�̃|�C���^�[
	CObject2D* m_pTime[3];										//�^�C���i���o�[�̃|�C���^�[
	static CObject2D* m_pCombo[4];								//�R���{�i���o�[�̃|�C���^�[
	static int m_nCombo;										//�R���{�𐔂���ϐ�
	bool m_bTimerStart;											//�^�C�}�[���J�n���邩�ۂ�
	bool m_bSount;
};

#endif // !_SCORE_H_
