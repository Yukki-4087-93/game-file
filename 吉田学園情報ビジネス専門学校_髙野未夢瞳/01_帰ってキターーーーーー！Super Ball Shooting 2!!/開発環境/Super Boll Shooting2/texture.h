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
		TEXTURE_PLAYER = 0,								// �v���C���[
		TEXTURE_PLAYER_VER2,							// �_���[�W�𕉂����v���C���[
		TEXTURE_PLAYER_VER3,							// ���_���[�W�𕉂����v���C���[
		TEXTURE_PLAYER_VER4,							// ����Ƀ_���[�W�𕉂����v���C���[
		TEXTURE_BULLET,									// �e�P
		TEXTURE_BULLET_E,								// �e�Q
		TEXTURE_EXPLOSION,								// ����
		TEXTERE_ENEMETYPE,								// �G�l�~�[�P
		TEXTERE_TUTORIAL_ZERO,							// �`���[�g���A���G�l�~�[0
		TEXTERE_TUTORIAL_ONE,							// �`���[�g���A���G�l�~�[1
		TEXTERE_TUTORIAL_TWO,							// �`���[�g���A���G�l�~�[2
		TEXTURE_AGE,									// �{�X
		TEXTERE_BG,										// �w�i
		TEXTURE_RANKING_BG,								// �����L���O�̔w�i
		TEXTURE_PROTECT,								// �X�̃e�N�X�`��
		TEXTURE_PROTECT_ALERT,							// �X�̃e�N�X�`���_���[�W
		TEXTURE_PROTECT_DEEPALERT,						// �X�̃e�N�X�`���_���[�W2
		TEXTURE_PROTECT_DEATHALERT,						// �X�̃e�N�X�`���_���[�W3
		TEXTURE_TITLE,									// �^�C�g���̃e�N�X�`��
		TEXTURE_RESULT,									// ���U���g�̃e�N�X�`��
		TEXTURE_RESULT_DEATH,							// ���U���g�̃e�N�X�`�� �f�X�o�[�W����
		TEXTURE_SCORE,									// �X�R�A�̃e�N�X�`��
		TEXTURE_UI,										// UI�̃e�N�X�`��
		TEXTURE_RANKING,								// �����L���O���S
		TEXTURE_MAX,									// �ő�
		TEXTURE_NONE,									// �g�p���Ȃ�
	};

	static const char* s_FileName[];					// �t�@�C���p�X

public:
	CTexture();											// �f�t�H���g�R���X�g���N�^
	~CTexture();										// �f�X�g���N�^

public: /* �����o�֐� */
	void LoadAll();										// �S�Ă̓ǂݍ���
	void Load(TEXTURE inTexture);						// �w��̓ǂݍ���
	void ReleaseAll();									// �S�Ă̔j��
	void Release(TEXTURE inTexture);					// �w��̔j��
	LPDIRECT3DTEXTURE9 GetTexture(TEXTURE inTexture);	// ���̎擾

private: /* �����o�ϐ� */
	LPDIRECT3DTEXTURE9 s_pTexture[TEXTURE_MAX];			// �e�N�X�`���̏��
};

#endif // !_TEXTURE_H_
