//--------------------------------------------------------------------------------------
//
// ���U���g�}�l�[�W���[
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
CBg *CResult::m_pBg;
//CTexture *CResult::m_pTexture;
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
	//m_pTexture = new CTexture;

	Set(m_nResult);

	return S_OK;
}

//--------------------------------------
//�I��
//--------------------------------------
void CResult::Uninit()
{
	CApplication::GetSound()->Stop();
}

//--------------------------------------
//�X�V
//--------------------------------------
void CResult::Update()
{

	if (m_pBg != nullptr)
	{//�w�i�̃|�C���^�[�ɒl�������Ă����Ƃ�
		m_pBg->Update();							//�w�i�̍X�V
	}

	//����L�[(ENTER)�������ꂽ���ǂ���
	if (CApplication::GetKyeboard()->GetkeyboardTrigger(DIK_RETURN))
	{
		CApplication::SetMode(CApplication::MODE::MODE_RANKING);
	}

	//����L�[(ENTER)�������ꂽ���ǂ���
	if (CApplication::GetKyeboard()->GetkeyboardTrigger(DIK_SPACE))
	{
		CApplication::SetMode(CApplication::MODE::MODE_GAME);
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
	//���U���g��ʂ̌��ʂ�ς���ϐ��ɑ��
	m_nResult = nCount;

	//�T�E���h���̎擾
	CSound* pSound = CApplication::GetSound();


	if (m_nResult == 0)
	{//���ʂ�0��������
		
		//�w�i�̐���
		m_pBg = CBg::Create(D3DXVECTOR3(1280.0f / 2, 720.0f / 2, 0.0f), 
							1280.0f, 
							720.0f, 
							CTexture::TEXTURE::TEXTURE_RESULT);

		//���S�̐���
		m_pBg = CBg::Create(D3DXVECTOR3(1280.0f / 2, 630.0f, 0.0f),
			600.0f,
			300.0f,
			CTexture::TEXTURE::TEXTURE_RESULT_LOGO);

		//BGM���Đ�
		pSound->Play(CSound::SOUND_BGM_RESULT);
	}

	else
	{//���ʂ�0�ȊO��������
		
		//�w�i�̐���
		m_pBg = CBg::Create(D3DXVECTOR3(1280.0f / 2, 720.0f / 2, 0.0f),
							1280.0f,
							720.0f,
							CTexture::TEXTURE::TEXTURE_RESULT_DEATH);

		//���S�̐���
		m_pBg = CBg::Create(D3DXVECTOR3(1280.0f / 2, 630.0f, 0.0f),
			600.0f,
			300.0f,
			CTexture::TEXTURE::TEXTURE_RESULT_LOGO);
		
		pSound->Play(CSound::SOUND_BGM_RESULT_DETH);		//BGM���Đ�
		pSound->Play(CSound::SOUND_SE_EAT);					//SE���Đ�
		pSound->Play(CSound::SOUND_SE_GAMEOVER);			//�i���ɗ����SE���Đ�
		pSound->SetVolume(CSound::SOUND_SE_GAMEOVER,0.8f);	//�i���ɗ����SE�̉��ʂ�ݒ�
	}
}

//---------------------------------------
//�w�i���擾
//---------------------------------------
CBg * CResult::GetBg()
{
	return m_pBg;
}

////---------------------------------------
//// �e�N�X�`���̏��擾
////---------------------------------------
//CTexture* CResult::GetTexture()
//{
//	return m_pTexture;
//}
