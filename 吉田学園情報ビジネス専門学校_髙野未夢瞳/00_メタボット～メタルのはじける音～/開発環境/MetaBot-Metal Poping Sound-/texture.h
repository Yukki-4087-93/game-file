//**************************************************
// 
// texture.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _TEXTURE_H_	//���̃}�N����`������ĂȂ�������
#define _TEXTURE_H_	//�Q�d�C���N���[�h�h�~�̃}�N����`

//==================================================
// �C���N���[�h
//==================================================
#include <d3dx9.h>

//==================================================
// ��`
//==================================================
class CTexture
{
public: /* ��` */
	enum TEXTURE
	{
		TEXTURE_NONE = -1,					// �g�p���Ȃ�
		TEXTURE_TITLE = 0,					// �^�C�g��
		TEXTURE_SCORE,						// �i���o�[
		TEXTURE_UI,							// ���[�U�[�C���^�[�t�F�[�X
		TEXTURE_UI_PLAYERDATA,				// ���[�U�[�f�[�^�C���^�[�t�F�[�X
		TEXTURE_RESULT,						// ���U���g
		TEXTURE_RESULT_DEATH,				// ���S���̃��U���g
		TEXTYRE_RANKING_BG,					// �����L���O�̔w�i
		TEXTURE_RANKING_BUMMBER,			// �����L���O�̈�
		TEXTURE_RANKING_NOW_UI,
		TEXTURE_SKY,						// �X�J�C�{�b�N�X�ɓ\��
		TRXTURE_EFFECT,						// �G�t�F�N�g�p
		TEXTURE_DAMAGE_INSIGNIFICANT,		// �_���[�W(�y��)
		TEXTURE_HALF_DAMAGE,				// �_���[�W(���j)
		TEXTURE_SERIOUS_DAMAGE,				// �_���[�W(��j���O)
		TEXTURE_TUTORIAL,					// �`���[�g���A��
		TEXTURE_EAT_ME,						// �`���[�g���A��
		TEXTURE_DISCRIPTION,				// �`���[�g���A��
		TEXTURE_ARROW,						// �`���[�g���A��
		TEXTURE_DISCRIPTION2,				// �`���[�g���A��
		TEXTURE_TITLE_LOGO,					// �`���[�g���A��
		TEXTURE_RESULT_LOGO,				// �`���[�g���A��
		TEXTURE_MAX,						// �ő�
	};

	static const char* s_FileName[];	// �t�@�C���p�X

public:
	CTexture();		// �f�t�H���g�R���X�g���N�^
	~CTexture();	// �f�X�g���N�^

public: /* �����o�֐� */
	void LoadAll();										// �S�Ă̓ǂݍ���
	void Load(TEXTURE inTexture);						// �w��̓ǂݍ���
	void ReleaseAll();									// �S�Ă̔j��
	void Release(TEXTURE inTexture);					// �w��̔j��
	LPDIRECT3DTEXTURE9 GetTexture(TEXTURE inTexture);	// ���̎擾

private: /* �����o�ϐ� */
	LPDIRECT3DTEXTURE9 s_pTexture[TEXTURE_MAX];	// �e�N�X�`���̏��
};

#endif // !_TEXTURE_H_
