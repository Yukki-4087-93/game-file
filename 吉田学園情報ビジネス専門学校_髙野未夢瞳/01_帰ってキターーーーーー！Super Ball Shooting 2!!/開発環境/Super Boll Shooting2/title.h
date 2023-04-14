//---------------------------------------------------------
//
//�^�C�g��
//Author::TAKANO
//
//---------------------------------------------------------
#ifndef _TITLE_H_
#define _TITLE_H_

#include <d3dx9.h>

//----------------------------------------
//�O���錾
//----------------------------------------
//class CBg;
class CTexture;
class CSoundManager;

//----------------------------------------
//�N���X��`
//�}�l�[�W���[
//----------------------------------------
class CTitle
{
public:
	CTitle();															//�R���X�g���N�^
	~CTitle();															//�f�X�g���N�^
	HRESULT Init();														//������
	void Uninit();														//�I��
	void Update();														//�X�V
	void Draw();														//�`��
	//static CBg* GetBg();												//�w�i�̏��擾
	static CTexture* GetTexture();										//�e�N�X�`�����̎擾

private:
	//static CBg* m_pBg;													//�w�i�̃|�C���^�[
	static CTexture* m_pTexture;										//�e�N�X�`���̃|�C���^�[
};

#endif // !_TITLE_H_
