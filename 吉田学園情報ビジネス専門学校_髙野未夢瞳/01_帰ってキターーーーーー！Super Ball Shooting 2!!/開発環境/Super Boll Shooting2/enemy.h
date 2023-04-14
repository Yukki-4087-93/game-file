//--------------------------------------------------------------------------------------
//
// �I�u�W�F�N�g
// Author::TAKANO
//
//--------------------------------------------------------------------------------------
#ifndef _CENEMY_H_
#define _CENEMY_H_

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
class CEnemy : public CObject2D
{
public:
	/*�G�l�~�[�̃^�C�v*/
	enum ENEMY_TYPE
	{
		TYPE_NOME = 0,					//�G�l�~�[���g�p���Ȃ����
		TYPE_TUTORIAL,					//�`���[�g���A���G�l�~�[
		TYPE_TUTORIAL_BACK,
		TYPE_STRAIGHT,					//�^�������i�ރG�l�~�[
		TYPE_COLLISION_DOWN,			//���ǂɔ��˂���G�l�~�[	
		TYPE_COLLISION_UP,				//��ǂɔ��˂���G�l�~�[
		TYPE_STRANGER_DOWN,				//�ςȓ�������G�l�~�[�̏���
		TYPE_STRANGER_UP,				//�ςȓ�������G�l�~�[�̏���
		TYPE_STRENGER_GO,				//�ςȓ�������G�l�~�[�̎���
		TYPE_STRENGER_CHANGE,			//�ςȓ�������G�l�~�[�̎���
		TYPE_MIDBOSS,					//���{�X�N���X�̃G�l�~�[
		TYPE_BOSS,
		TYPE_BOSS_DOWN,
		TYPE_BOSS_UP,
		TYPE_BOSS_TWO,
		TYPE_BOSS_TWO_DOWN,
		TYPE_BOSS_TWO_UP,
		TYPE_BOSS_TREE,
		TYPE_BOSS_TREE_DOWN,
		TYPE_BOSS_TREE_UP,
		TYPE_MAX,						//�ő�G�l�~�[
	};

	/*�G�l�~�[�̏�ԊǗ�*/
	enum ENEMY_STATE
	{
		STARE_NOMAL = 0,
		STARE_DAMAGE,
		STATE_MAX
	};

	CEnemy();																								//�R���X�g���N�^
	~CEnemy();																								//�f�X�g���N�^
	HRESULT Init()override;																					//������
	static CEnemy * Create(D3DXVECTOR3 pos,int nlife,float ObfHi, float ObfWd,CTexture::TEXTURE tex, CObject::ObjType typ, CEnemy::ENEMY_TYPE type, float sin, float cos);				//�N���G�C�g
	void Update()override;																					//�X�V
	void Draw()override;																					//�`��
	void Uninit()override;																					//�I��
	void NumTypeEnemy(CEnemy::ENEMY_TYPE type,float fsin,float fcos);																//�G�l�~�[���̐ݒ�
	void HitLife(int nDamage);
	void SetColor(D3DXCOLOR col);
	void SetState(CEnemy::ENEMY_STATE state);

private:
	void ShotBullet();
	void Updatepos();
	void State();
	void Relesepos();

private:
	D3DXVECTOR3 m_move;						//�G�l�~�[�̈ړ���
	int m_nECount;							//�J�E���g�p�ϐ�
	int m_nELife;							//�G�l�~�[�p�̗�
	float m_fSpeed_sin;				
	float m_fSpeed_cos;
	int m_nSwitch;
	int m_nOpen_Fire;
	int m_nColorCount;
	D3DXCOLOR m_col;
	CEnemy::ENEMY_TYPE m_nType;				
	CEnemy::ENEMY_STATE m_nState;
};

#endif // !_CENEMY_H_
