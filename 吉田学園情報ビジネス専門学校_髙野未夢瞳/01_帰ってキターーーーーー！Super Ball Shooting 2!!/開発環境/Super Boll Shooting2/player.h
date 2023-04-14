//--------------------------------------------------------------------------------------
//
// �I�u�W�F�N�g
// Author::TAKANO
//
//--------------------------------------------------------------------------------------
#ifndef _CPLAYER_H_
#define _CPLAYER_H_

//----------------------------------------
//�C���N���[�h�t�@�C��
//----------------------------------------
#include "object2d.h"
#include "renderer.h"
#include "texture.h"

//----------------------------------------
//�N���X��`
//�I�u�W�F�N�g
//----------------------------------------
class CPlayer : public CObject2D
{
public:

	/*�v���C���[�̏�ԊǗ�*/
	enum PLAYER_STATE
	{
		STARE_NOMAL = 0,
		STARE_DAMAGE,
		STATE_MAX
	};

	CPlayer();																//�R���X�g���N�^
	~CPlayer();																//�f�X�g���N�^
	HRESULT Init()override;													//������
	static CPlayer * Create(D3DXVECTOR3 pos, float ObfHi, float ObfWd);		//�N���G�C�g
	void Update()override;													//�X�V
	void Draw()override;													//�`��
	void Uninit()override;													//�I��
	void HitDamage(int nDamage);											//�_���[�W����
	void SetState(CPlayer::PLAYER_STATE state);

private:
	void Command();							//�X�V�ōs���v���C���[�̓���(�ړ���e�̔��˂Ȃ�)����
	void CommandBullet();							//�X�V�ōs���e�֘A�̏���
	void Move();								//�ړ��ʂȂǂ̐ݒ�
	void Collision();							//��ʒ[�Ȃǂ̓����蔻�菈��
	void State();

private:
	D3DXVECTOR3 m_move;								//�v���C���[�̈ړ���
	int m_nCount;									//�e�̔��˃J�E���g�p�̕ϐ�
	int m_nPi;										//�e�̊p�x�ύX�p�̕ϐ�
	int m_nRand;									//�����_���p�̕ϐ�
	int m_Damage;									//�_���[�W���擾����ϐ�
	int m_nLife;									//����
	int m_nPressCount;								//�{�^�����������^�C�~���O�Ŏg�p����J�E���g�p�ϐ�
	int m_nColorCount;
	bool m_bSetTexture;	
	D3DXCOLOR m_col;
	CPlayer::PLAYER_STATE m_State;

};

#endif // !_CPLAYER_H_
