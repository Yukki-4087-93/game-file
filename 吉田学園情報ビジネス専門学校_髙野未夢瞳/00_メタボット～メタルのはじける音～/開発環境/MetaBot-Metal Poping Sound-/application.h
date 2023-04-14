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
class CCamera;
class CTexture;
class CInput;
class CSound;
class CObject;
class CObject2D;
class CObject3D;
class CObjectX;
class CTitle;
class CGame;
class CResult;
class CRanking;

//----------------------------------------
//�N���X��`
//�}�l�[�W���[
//----------------------------------------
class CApplication
{
public:
/*���[�h�𐧌䂷���*/
	enum MODE
	{
		MODE_NONE = -1,													//���[�h���g�p���Ă��Ȃ����
		MODE_TITLE = 0,													//�^�C�g�����[�h
		MODE_TUTORE,													//�`���[�g���A��
		MODE_GAME,														//�Q�[�����[�h
		MODE_RESULT,													//���U���g���[�h
		MODE_RANKING,													//�����L���O���[�h
		MODE_MAX
	};

/*���J�����o�֐�*/
	CApplication();														//�R���X�g���N�^
	~CApplication();													//�f�X�g���N�^
	HRESULT Init(HINSTANCE hInctance, HWND hWnd, bool bWindow);			//������
	void Uninit();														//�I��
	void Update();														//�X�V
	void Draw();														//�`��

/*����J�����o�֐�*/
private:
	void ReleseDustCheck();												//����R������Ă��Ȃ����m�F�p�֐�

/*���J�ÓI�����o�֐�*/
public:
	static CRenderer* GetRenderer() { return m_aRenderer; }				//�`��̏��擾
	static CInput* GetKyeboard() { return m_pInputKeyboard; }			//�L�[�{�[�h�̏��擾
	static CTexture* GetTexture() { return m_pTexture; }				//�e�N�X�`���̏��擾
	static CSound* GetSound() { return m_pSound; }						//�T�E���h�̏��擾
	static void SetMode(MODE mode);	
	static MODE GetMode() { return m_mode; }
	static void UpdateMode(MODE mode);
	
	static CTitle* GetTitle() { return m_pTitle; }						//�^�C�g���̏��擾
	static CGame* GetGame() { return m_pGame; }							//�Q�[���̏��擾
	static CResult* GetResult() { return m_pResult; }					//���U���g�̏��擾
	static CRanking* GetRanking() { return m_pRanking; }				//�����L���O�̏��擾

/*��ʃ����o�ϐ�*/
private:
	CObject3D* m_pObj3D;												//�I�u�W�F�N�g3D�̃|�C���^�[
	CObject2D* m_pObj2D;												//�I�u�W�F�N�g2D�̃|�C���^�[

/*�ÓI�����o�ϐ�*/
private:
	static MODE m_mode;
	static CRenderer* m_aRenderer;										//�����_���[�̃|�C���^�[
	static CInput* m_pInputKeyboard;									//�L�[�{�[�h�̃|�C���^�[
	static CTexture* m_pTexture;										//�e�N�X�`���̃|�C���^�[																		//static MODE m_mode;
	static CSound* m_pSound;											//�T�E���h�̃|�C���^�[

	static CTitle* m_pTitle;											//�^�C�g���̃|�C���^�[
	static CGame* m_pGame;												//�Q�[���̃|�C���^�[
	static CResult* m_pResult;											//���U���g�̃|�C���^�[
	static CRanking* m_pRanking;										//�����L���O�̃|�C���^�[
};

#endif // !_APPLICATION_H_
