//--------------------------------------------------------------------------------------
//
// �}�l�[�W���[�A�v���P�[�V����
// Author::TAKANO
//
//--------------------------------------------------------------------------------------
#ifndef _APPLICATION_H_
#define _APPLICATION_H_

//----------------------------------------
//�C���N���[�h�t�@�C��
//----------------------------------------
#include <d3dx9.h>

//----------------------------------------
//�O���錾
//----------------------------------------
class CRenderer;
class CTexture;
class CTitle;
class CGame;
class CResult;
class CRanking;
class CInput;
class CSound;
class CBg;

//----------------------------------------
//�N���X��`
//�}�l�[�W���[
//----------------------------------------
class CApplication
{
public:
	//���[�h���
	enum MODE
	{
		MODE_TITLE = 0,
		MODE_GAME,
		MODE_RESULT,
		MODE_RANKING,
		MODE_MAX
	};

/*�����o�֐�*/
	CApplication();														//�R���X�g���N�^
	~CApplication();													//�f�X�g���N�^
	HRESULT Init(HINSTANCE hInctance, HWND hWnd, bool bWindow);			//������
	void Uninit();														//�I��
	void Update();														//�X�V
	void Draw();														//�`��

/*���J���Ȃ������o�֐�*/
private:
	void ReleseDustCheck();												//����R������Ă��Ȃ����m�F�p�֐�

/*�ÓI�����o�֐�*/
public:
	static CRenderer* GetRenderer() { return m_aRenderer; }				//�`����̎擾
	static CInput* GetKyeboard() { return m_pInputKyeboard; }			//�L�[�{�[�h���̎擾
	static CTexture* GetTexture() { return m_pTexture; }				//�e�N�X�`�����̎擾
	static CTitle* GetTitle() { return m_pTitle; }						//�^�C�g�����̎擾
	static CGame* GetGame() { return m_pGame; }							//�Q�[�����̎擾
	static CResult* GetResult() { return m_pResult; }					//���U���g���̎擾
	static CRanking* GetRanking() { return m_pRanking; }				//�����L���O���̎擾
	static void SetMode(MODE mode);										//���[�h�̐ݒ�
	static CApplication::MODE GetMode() { return m_mode; }				//���[�h���̎擾
	static CSound* GetSound() { return m_pSound; }						//�T�E���h���̎擾
	static CBg* GetBg() { return m_pBg; }								//�w�i���̎擾

/*�ÓI�����o�ϐ�*/
private:
	static CRenderer* m_aRenderer;										//�����_���[�̃|�C���^�[
	static CInput* m_pInputKyeboard;									//�L�[�{�[�h�̃|�C���^�[
	static CTexture* m_pTexture;										//�e�N�X�`���̃|�C���^�[
	static CTitle* m_pTitle;											//�^�C�g���̃|�C���^�[
	static CGame* m_pGame;												//�Q�[���̃|�C���^�[
	static CResult* m_pResult;											//���U���g�̃|�C���^�[
	static CRanking* m_pRanking;										//�����L���O�̃|�C���^�[
	static MODE m_mode;													//���[�h�̃|�C���^�[
	static CSound* m_pSound;											//�T�E���h�̃|�C���^�[
	static CBg* m_pBg;													//�w�i�̃|�C���^�[
};

#endif // !_APPLICATION_H_
