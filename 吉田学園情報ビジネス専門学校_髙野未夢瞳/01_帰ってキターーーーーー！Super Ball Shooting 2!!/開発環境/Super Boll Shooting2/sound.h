//---------------------------------------------------------
//
//�T�E���h
//Author::TAKANO
//
//---------------------------------------------------------
#ifndef _SOUND_H_
#define _SOUND_H_

//--------------------------------------
//�C���N���[�h�t�@�C��
//--------------------------------------
#include"d3dx9.h"
#include <mfapi.h>
#include <mfidl.h>
#include <mfreadwrite.h>
#include"xaudio2.h"
#include <xaudio2fx.h>

//--------------------------------------
//�N���X��`
//�T�E���h�֘A
//--------------------------------------
class CSound
{
public:
	struct PARAM
	{//�T�E���h�p�����[�^�[�̍\����
		char *m_pFilename;									// �t�@�C����
		int m_nCntLoop;										// ���[�v�J�E���g
	};

	enum SOUND_TYPE
	{//�T�E���h�^�C�v
		SOUND_BGM_TITLE = 0,								// �^�C�g��
		SOUND_BGM_GAME,										// �Q�[��
		SOUND_BGM_GAME_BOSS,								// �Q�[�����̃{�X�Ɏg�p
		SOUND_BGM_GAME_LAST,								// �{�X�o�����玞�Ԃ����b�o�����Ƃ��Ɏg�p
		SOUND_BGM_RESULT,									// ���U���g
		SOUND_BGM_RANKING,									// �����L���O
		SOUND_BGM_TUTORAL,									// �`���[�g���A��
		SOUND_SE_SOOT,										// �e����SE
		SOUND_SE_HIT,										// �_���[�WSE
		SOUND_SE_EXPLOSION,									// ����SE
		SOUND_MAX,
	};

	static const PARAM param[];								// �p�����[�^�̏��

	CSound();												// �R���X�g���N�^
	~CSound();												// �f�X�g���N�^
	HRESULT Init();											// ������
	void Uninit();											// �I��
	HRESULT Play(SOUND_TYPE type);							// �Đ�
	void SetVolume(SOUND_TYPE type, float fVolume);			// ���ʂ̐ݒ�A�������̂Ƃ��Ɏg���Ăق����ł��B�ň��Ȃ��Ă������B���Ȃ݂ɁASE�ɂ͂���Ȃ���
	void SetRate(SOUND_TYPE type, float rate);				// �s�b�`����A�������ȉ����B�ň��Ȃ��Ă������B
	void Stop(SOUND_TYPE type);								// �ꕔ��~
	void Stop();											// �S��~

public:
	void UpVolume(SOUND_TYPE type, float volume);			// ���ʂ��グ�����Ƃ��Ɏg��
	void DownVolume(SOUND_TYPE type, float volume);			// ���ʂ����������Ƃ��Ɏg��
	void UpPitch(SOUND_TYPE type, float pitch);				// �������グ�����Ƃ��Ɏg��
	void DownPitch(SOUND_TYPE type, float pitch);			// ���������������Ƃ��Ɏg��

private:
	HRESULT CheckChunk(HANDLE hFile,						// ���(�`�����N)�̊m�F
					   DWORD format,
					   DWORD *pChunkSize, 
					   DWORD *pChunkDataPosition);			


	HRESULT ReadChunkData(HANDLE hFile,						// ���(�`�����N)�̓ǂݍ���
						  void *pBuffer, 
						  DWORD dwBuffersize, 
						  DWORD dwBufferoffset);			

private:
	static CSound * m_pSound;
	IXAudio2 *m_pXAudio2;									// XAudio2�I�u�W�F�N�g�ւ̃C���^�[�t�F�C�X
	IXAudio2MasteringVoice *m_pMasteringVoice;				// �}�X�^�[�{�C�X
	IXAudio2SourceVoice *m_apSourceVoice[SOUND_MAX];		// �\�[�X�{�C�X
	BYTE *m_apDataAudio[SOUND_MAX];							// �I�[�f�B�I�f�[�^
	DWORD m_aSizeAudio[SOUND_MAX];							// �I�[�f�B�I�f�[�^�T�C�Y
	int m_nCountFade;										// �t�F�[�h�p�J�E���^�[
	float m_fVol;											// �T�E���h�̉��ʂ�ω�������ϐ�
	float m_fPitch;											// �T�E���h�̉�����ω�������ϐ�
};

#endif // !_SOUND_H_
