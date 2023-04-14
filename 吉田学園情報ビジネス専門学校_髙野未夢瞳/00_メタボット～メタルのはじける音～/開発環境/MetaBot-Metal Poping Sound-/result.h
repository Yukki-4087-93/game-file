//---------------------------------------------------------
//
//���U���g
//Author::TAKANO
//
//---------------------------------------------------------
#ifndef _RESULT_H_
#define _RESULT_H_

#include <d3dx9.h>

//----------------------------------------
//�O���錾
//----------------------------------------
class CBg;
class CTexture;
class CSoundManager;

//----------------------------------------
//�N���X��`
//�}�l�[�W���[
//----------------------------------------
class CResult
{
public:
	CResult();															//�R���X�g���N�^
	~CResult();															//�f�X�g���N�^
	HRESULT Init();														//������
	void Uninit();														//�I��
	void Update();														//�X�V
	void Draw();														//�`��
	static void Set(int nCount);
	static CBg* GetBg();												//�w�i�̏��擾
	//static CTexture* GetTexture();										//�e�N�X�`�����̎擾

private:
	static int m_nResult;												//���U���g�̌��ʂ��󂯎��ϐ�
	static CBg* m_pBg;													//�w�i�̃|�C���^�[
	//static CTexture* m_pTexture;										//�e�N�X�`���̃|�C���^�[
};

#endif // !_RESULT_H_
