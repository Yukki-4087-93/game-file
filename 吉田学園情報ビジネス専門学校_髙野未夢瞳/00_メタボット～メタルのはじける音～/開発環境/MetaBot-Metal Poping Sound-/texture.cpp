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
{// �e�N�X�`���̃p�X
	"Data/TEXTURE/Title_103.png",				// �^�C�g��
	"Data/TEXTURE/number001.png",				// �i���o�[
	"Data/TEXTURE/UI.png",						// ���[�U�[�C���^�[�t�F�[�X
	"Data/TEXTURE/UI2.png",						// ���[�U�[�C���^�[�t�F�[�X
	"Data/TEXTURE/reseut0099.png",				// ���U���g
	"Data/TEXTURE/reseut0999.png",				// ���U���g�i���S���j
	"Data/TEXTURE/Ranking_BG.png",				// �����L���O�̔w�i
	"Data/TEXTURE/ranking_rank.png",			// �����L���O
	"Data/TEXTURE/Ranking_Now.png",				// �����L���O
	"Data/TEXTURE/sky.jpg",						// ��
	"Data/TEXTURE/NewType.png",					// �G�t�F�N�g�p
	"Data/TEXTURE/damage_insignificant.png",	// �y���_���[�W�p
	"Data/TEXTURE/damage_medium_wave.png",		// ���j�_���[�W�p
	"Data/TEXTURE/damage_wave.png",				// ��j���O�_���[�W�p
	"Data/TEXTURE/tutorial.jpg",				// tutorial�p
	"Data/TEXTURE/EatMe.jpg",					// �H�ׂ���^���̎�
	"Data/TEXTURE/tutorial2.jpg",					// ����
	"Data/TEXTURE/arrow.jpg",					// �₶�邵
	"Data/TEXTURE/tutorial3.jpg",					// ����
	"Data/TEXTURE/TitleLogo.jpg",					// ����
	"Data/TEXTURE/ResultLogo.png",					// ����
};

//�ǂ��炩�̌č�������v���Ă��Ȃ���ԂȂ�G���[���o��(�f�o�b�N�����L��)
static_assert(sizeof(CTexture::s_FileName) / sizeof(CTexture::s_FileName[0]) == CTexture::TEXTURE_MAX, "Texture Check Error");

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
			continue;			//�ŏ��ɖ߂�
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
