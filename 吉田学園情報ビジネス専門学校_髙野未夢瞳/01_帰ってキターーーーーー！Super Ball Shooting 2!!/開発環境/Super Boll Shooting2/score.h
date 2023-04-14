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
//�萔��`
//----------------------------------------
const int SCORE_NUMBER = 5;
const int LIFE_NUMBER = 2;
const int TIME_NUMBER = 3;

//----------------------------------------
//�N���X�錾
//�X�R�A
//----------------------------------------
class CScore : public CObject
{
public:
	CScore();
	~CScore()override;
	HRESULT Init()override;
	static CScore * Create(D3DXVECTOR3 pos, int nScore);					//�N���G�C�g
	void Uninit()override;
	void Update()override;
	void Draw()override;
	void Setpos(D3DXVECTOR3 pos) override {}			//�ʒu�̐ݒ�

	void Set(int nScore);
	void Add(int nValue);

	void SetWallLife(int nLife);
	static void HitDamage(int nDamage);

	void SetTime(int nTime);
	void MinusTime(int nMinus);

	static int Get();

private:
	static int m_nScore;														//�X�R�A�̒l
	int m_nTime;
	int m_nTimeCounter;
	int m_nTimeStartCounter;
	static int m_nWallLife;
	D3DXVECTOR3 m_ScorePos;
	CObject2D* m_pNumber[SCORE_NUMBER];
	static CObject2D* m_pWoll_Life[LIFE_NUMBER];
	CObject2D* m_pTime[TIME_NUMBER];
};

#endif // !_SCORE_H_
