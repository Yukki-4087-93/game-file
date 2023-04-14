//--------------------------------------------------------------------------------------
//
// �}�l�[�W���[�A�v���P�[�V����
// Author::TAKANO
//
//--------------------------------------------------------------------------------------

//--------------------------------------
//�C���N���[�h�t�@�C��
//--------------------------------------
#include "application.h"
#include "result.h"
#include "object2d.h"
#include "input.h"
#include "bg.h"
#include "sound.h"

//--------------------------------------
//�O���[�o���ϐ�
//--------------------------------------
//CBg *CResult::m_pBg;
CTexture *CResult::m_pTexture;
int CResult::m_nResult;

//--------------------------------------
//�R���X�g���N�^
//--------------------------------------
CResult::CResult()
{

}

//--------------------------------------
//�f�X�g���N�^
//--------------------------------------
CResult::~CResult()
{
}

//--------------------------------------
//������
//--------------------------------------
HRESULT CResult::Init()
{
	m_pTexture = new CTexture;

	Set(m_nResult);

	CApplication::GetSound()->Play(CSound::SOUND_BGM_RESULT);

	return S_OK;
}

//--------------------------------------
//�I��
//--------------------------------------
void CResult::Uninit()
{
	CApplication::GetSound()->Stop(CSound::SOUND_BGM_RESULT);
}

//--------------------------------------
//�X�V
//--------------------------------------
void CResult::Update()
{

	//if (m_pBg != nullptr)
	//{//�w�i�̃|�C���^�[�ɒl�������Ă����Ƃ�
	//	m_pBg->Update();							//�w�i�̍X�V
	//}

	//����L�[(ENTER)�������ꂽ���ǂ���
	if (CApplication::GetKyeboard()->GetkeyboardTrigger(DIK_RETURN))
	{
		CApplication::SetMode(CApplication::MODE::MODE_RANKING);
	}
}

//--------------------------------------
//�`��
//--------------------------------------
void CResult::Draw()
{

}

//--------------------------------------
//���U���g�̐ݒ�
//--------------------------------------
void CResult::Set(int nCount)
{
	m_nResult = nCount;

	if (nCount == 0)
	{
		//�Q�[�����̃I�u�W�F�N�g����
		CBg* pBg = CApplication::GetBg()->Create(D3DXVECTOR3(1280.0f / 2, 720.0f / 2, 0.0f), 
												1280.0f, 
												720.0f, 
												CTexture::TEXTURE::TEXTURE_RESULT);
	}
	else
	{
		//�Q�[�����̃I�u�W�F�N�g����
		CBg* pBg = CApplication::GetBg()->Create(D3DXVECTOR3(1280.0f / 2, 720.0f / 2, 0.0f),
												1280.0f,
												720.0f,
												CTexture::TEXTURE::TEXTURE_RESULT_DEATH);
	}
}

//---------------------------------------
// �e�N�X�`���̏��擾
//---------------------------------------
CTexture* CResult::GetTexture()
{
	return m_pTexture;
}
