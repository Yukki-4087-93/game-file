//**************************************************
// 
// texture.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// �C���N���[�h
//==================================================
#include "application.h"
#include "renderer.h"
#include "texture.h"

#include <assert.h>

//==================================================
// ��`
//==================================================
const char* CTexture::s_FileName[] =
{// �e�N�X�`���̃p�Xrunningman000
	"Data/TEXTURE/NewType.png",					// �v���C���[
	"Data/TEXTURE/Brokon_S.png",				// �v���C���[Ver2
	"Data/TEXTURE/Brokon_T.png",				// �v���C���[Ver3
	"Data/TEXTURE/Brokon_F.png",				// �v���C���[Ver4
	"Data/TEXTURE/Bullet.png",					// �e�P
	"Data/TEXTURE/Bullet_E.png",				// �e�Q
	"Data/TEXTURE/explosion000.png",			// ����
	"Data/TEXTURE/enemy000.png",				// �G�l�~�[
	"Data/TEXTURE/TutorialEnemy0.png",			// �`���[�g���A���G�l�~�[1
	"Data/TEXTURE/TutorialEnemy1.png",			// �`���[�g���A���G�l�~�[2
	"Data/TEXTURE/TutorialEnemy2.png",			// �`���[�g���A���G�l�~�[3
	"Data/TEXTURE/open_my_hart.png",			// �{�X
	"Data/TEXTURE/RGBA2.png",					// �w�i
	"Data/TEXTURE/Ranking_BG.png",				// �w�i
	"Data/TEXTURE/joheki_2.png",				// �X
	"Data/TEXTURE/RED1.png",					// �X�A�_���[�W���
	"Data/TEXTURE/RED2.png",					// �X�A���_���[�W���
	"Data/TEXTURE/RED3.png",					// �X�A����Ƀ_���[�W���
	"Data/TEXTURE/Taitoru_102.png",				// �^�C�g��
	"Data/TEXTURE/reseut0099.png",				// ���U���g
	"Data/TEXTURE/reseut0999.png",				// ���U���g�i���S���j
	"Data/TEXTURE/number000.png",				// �i���o�[
	"Data/TEXTURE/UI.png",						// ���[�U�[�C���^�[�t�F�[�X
	"Data/TEXTURE/ranking_rank.png",			// �����L���O
};

//�ǂ��炩�̌č�������v���Ă��Ȃ���ԂȂ�G���[���o��(�f�o�b�N�����L��)
static_assert(sizeof(CTexture::s_FileName) / sizeof(CTexture::s_FileName[0]) == CTexture::TEXTURE_MAX, "���������Ă��܂���B");

//--------------------------------------------------
// �f�t�H���g�R���X�g���N�^
//--------------------------------------------------
CTexture::CTexture()
{
	memset(s_pTexture, 0, sizeof(s_pTexture));
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
CTexture::~CTexture()
{
}

//--------------------------------------------------
// �S�Ă̓ǂݍ���
//--------------------------------------------------
void CTexture::LoadAll()
{
	for (int nCountTex = 0; nCountTex < TEXTURE_MAX; nCountTex++)
	{
		if (s_pTexture[nCountTex] != nullptr)
		{// �e�N�X�`���̓ǂݍ��݂�����Ă���
			continue;			//for�̍ŏ��ɖ߂�
		}

		Load((TEXTURE)nCountTex);
	}
}

//--------------------------------------------------
// �ǂݍ���
//--------------------------------------------------
void CTexture::Load(TEXTURE inTexture)
{
	assert(inTexture >= 0 && inTexture < TEXTURE_MAX);

	if (s_pTexture[inTexture] != nullptr)
	{// �e�N�X�`���̓ǂݍ��݂�����Ă���
		return;
	}

	// �f�o�C�X�ւ̃|�C���^�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		s_FileName[inTexture],
		&s_pTexture[inTexture]);
}

//--------------------------------------------------
// �S�Ẳ��
//--------------------------------------------------
void CTexture::ReleaseAll(void)
{
	for (int nCntTex = 0; nCntTex < TEXTURE_MAX; nCntTex++)
	{
		if (s_pTexture[nCntTex] != nullptr)
		{// �e�N�X�`���̉��
			s_pTexture[nCntTex]->Release();
			s_pTexture[nCntTex] = nullptr;
		}
	}
}

//--------------------------------------------------
// ���
//--------------------------------------------------
void CTexture::Release(TEXTURE inTexture)
{
	assert(inTexture >= 0 && inTexture < TEXTURE_MAX);

	if (s_pTexture[inTexture] != nullptr)
	{// �e�N�X�`���̉��
		s_pTexture[inTexture]->Release();
		s_pTexture[inTexture] = nullptr;
	}
}

//--------------------------------------------------
// �擾
//--------------------------------------------------
LPDIRECT3DTEXTURE9 CTexture::GetTexture(TEXTURE inTexture)
{
	if (inTexture == TEXTURE_NONE)
	{// �e�N�X�`�����g�p���Ȃ�
		return nullptr;
	}

	assert(inTexture >= 0 && inTexture < TEXTURE_MAX);

	// �ǂݍ���
	Load(inTexture);

	return s_pTexture[inTexture];
}
