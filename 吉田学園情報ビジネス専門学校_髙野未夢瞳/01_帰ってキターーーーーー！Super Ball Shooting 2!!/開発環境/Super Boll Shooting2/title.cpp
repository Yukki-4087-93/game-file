//--------------------------------------------------------------------------------------
//
// �^�C�g��
// Author::TAKANO
//
//--------------------------------------------------------------------------------------

//--------------------------------------
//�C���N���[�h�t�@�C��
//--------------------------------------
#include "application.h"
#include "title.h"
#include "object2d.h"
#include "input.h"
#include "bg.h"
#include "sound.h"

//--------------------------------------
//�O���[�o���ϐ�
//--------------------------------------
//CBg *CTitle::m_pBg;
CTexture *CTitle::m_pTexture;

//--------------------------------------
//�R���X�g���N�^
//--------------------------------------
CTitle::CTitle()
{

}

//--------------------------------------
//�f�X�g���N�^
//--------------------------------------
CTitle::~CTitle()
{
}

//--------------------------------------
//������
//--------------------------------------
HRESULT CTitle::Init()
{
	m_pTexture = new CTexture;

	//�Q�[�����̃I�u�W�F�N�g����
	CBg* pBg = CApplication::GetBg()->Create(D3DXVECTOR3(1280.0f / 2, 
											720.0f / 2, 0.0f), 
											1280.0f, 
											720.0f, 
											CTexture::TEXTURE::TEXTURE_TITLE);
	//m_pBg = CBg::Create(D3DXVECTOR3(1280.0f / 2, 720.0f / 2, 0.0f), 1280.0f, 720.0f, CTexture::TEXTURE::TEXTURE_TITLE);

	CApplication::GetSound()->Play(CSound::SOUND_BGM_TITLE);

	return S_OK;
}

//--------------------------------------
//�I��
//--------------------------------------
void CTitle::Uninit()
{
	CApplication::GetSound()->Stop(CSound::SOUND_BGM_TITLE);

	//�I�u�W�F�N�g�̑S�j��
	CObject::ReleaseAll();
}

//--------------------------------------
//�X�V
//--------------------------------------
void CTitle::Update()
{

	//if (m_pBg != nullptr)
	//{//�w�i�̃|�C���^�[�ɒl�������Ă����Ƃ�
	//	m_pBg->Update();							//�w�i�̍X�V
	//}

	//����L�[(ENTER)�������ꂽ���ǂ���
	if (CApplication::GetKyeboard()->GetkeyboardTrigger(DIK_RETURN))
	{
		CApplication::SetMode(CApplication::MODE::MODE_GAME);
	}
}

//--------------------------------------
//�`��
//--------------------------------------
void CTitle::Draw()
{

}

//---------------------------------------
// �e�N�X�`���̏��擾
//---------------------------------------
CTexture* CTitle::GetTexture()
{
	return m_pTexture;
}
