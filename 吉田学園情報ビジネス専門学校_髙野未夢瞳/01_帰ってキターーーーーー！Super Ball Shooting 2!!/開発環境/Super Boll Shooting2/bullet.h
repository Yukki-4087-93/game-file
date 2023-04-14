//--------------------------------------------------------------------------------------
//
// �e
// Author::TAKANO
//
//--------------------------------------------------------------------------------------
#ifndef _BULLET_H_
#define _BULLET_H_

//----------------------------------------
//�C���N���[�h�t�@�C��
//----------------------------------------
#include "object2d.h"

//----------------------------------------
//�N���X��`
//�e�֌W�ꎮ
//----------------------------------------
class CBullet : public CObject2D
{
public:
	/*�e�̎��*/
	enum BULLET_TYPE
	{
		TYPE_NOMAL = 0,					//�m�[�}���̒e
		TYPE_BURST,						//���͂ɍL����e
		TYPE_DIFFUSION,					//3�����U�e
		TYPE_GIJIMASUPAA,				//�^���}�X�p�[
		TYPE_MAX,						//�ő�
		TYPE_NOME,						//�e�̎�ނ��g�p���Ȃ����
	};
	/*�e�̃��[�U�[*/
	enum BULLET_USER
	{
		USER_PLAYER = 0,				//�v���C���[���[�U�[		
		USER_ENEMY,						//�G�l�~�[���[�U�[
		USER_MAX,						//���[�U�[�̍ő�
		USER_NOME,						//���[�U�[���g�p����Ă��Ȃ����
	};

	CBullet();																									//�R���X�g���N�^
	~CBullet() ;																								//�f�X�g���N�^
	HRESULT Init()override;																						//������
	static CBullet * Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, CTexture::TEXTURE tex,CBullet::BULLET_USER user);		//�N���G�C�g
	void Update()override;																						//�X�V
	void Draw()override;																						//�`��
	void Uninit()override;																						//�I��
	void Release();																								//�e�̊J��
	void SetMove(D3DXVECTOR3 move);																				//�ړ��ʂ̐ݒ�
	D3DXVECTOR3 GetMove();																						//�ړ��ʂ̏��擾
	CBullet::BULLET_USER GetUser();																				//���[�U�[���擾
	void SetTypeBullet(CBullet::BULLET_USER user);																//���[�U�[���̐ݒ�
	
private:
	void SubstructLife();											//���C�t��������
	void Collisison();												//�X�V�Ŏg�p���Ă��铖���蔻��

private:
	D3DXVECTOR3 m_nMove;											//�ړ���
	CBullet::BULLET_USER m_TypeUser;								//���[�U�[�̃|�C���^
	int m_nBLife;
	int m_nColorCount;
	int m_nPattarnCount;
};

#endif // !_BULLET_H_

/*2022/06/22	�t�B�[���h�m�[�g

�e�̃e�N�X�`���͂P�ɂ������B

//�o���b�h
ststic LPDIRECT3DTEXTURE9 m_Texture;	//���L�e�N�X�`���̃|�C���^

HRESULT CBullet::Load()
{
	�e�N�X�`���̐���
}

void CBullet::Unload
{
	�e�N�X�`���̔j��or���
}

object2dh

void BindTexture(LPDIRECT3DTEXTURE9 pTexture)

LPDIRECT3DTEXTURE9 m_Texture;
*/