//--------------------------------------------------------------------------------------
//
// �I�u�W�F�N�g
// Author::TAKANO
//
//--------------------------------------------------------------------------------------
#ifndef _OBJECT2D_H_
#define _OBJECT2D_H_

//----------------------------------------
//�C���N���[�h�t�@�C��
//----------------------------------------
#include "object.h"
#include "texture.h"

//----------------------------------------
//�N���X��`
//�I�u�W�F�N�g
//----------------------------------------
class CObject2D : public CObject
{
public:
	// ���_�f�[�^
	struct VERTEX_2D
	{
		D3DXVECTOR3 pos;														//�ʒu
		float rhw;																//RHW
		D3DCOLOR col;															//�F
		D3DXVECTOR2 tex;														//�e�N�X�`��
	};

public:
	CObject2D();																//�R���X�g���N�^
	~CObject2D();																//�f�X�g���N�^
	HRESULT Init()override;														//������
	static CObject2D * Create(D3DXVECTOR3 pos, float ObfHi, float ObfWd);		//�N���G�C�g
	void Update()override;														//�X�V
	void Draw()override;														//�`��
	void Uninit()override;														//�I��
	void SetPos(D3DXVECTOR3 pos) override;
	const D3DXVECTOR3& Getpos() const { return m_pos; }							//�ʒu�̎擾
	void Addmove(D3DXVECTOR3 move) { m_pos += move; }							//�ړ��ʂ̉��Z
	void SetTexture(CTexture::TEXTURE texture) { m_texture = texture; }			//�e�N�X�`���̐ݒ�
	void PattarnTexture(int nPattarn,int nSplit);								//�e�N�X�`���A�j���[�V�����̐ݒ�
	void SetColor(D3DXCOLOR col);												//�I�u�W�F�N�g�̃J���[�ݒ�
	void SetSize(float fHi,float fWd);											//�T�C�Y�ݒ�

protected:
	LPDIRECT3DVERTEXBUFFER9 m_Vertex;											//���_���擾�̎擾
	float m_fAngle;																//�A���O��
	float m_fLength;															//�����O�X
	float m_Change_Height;														//�ύX���鍂��
	float m_Change_Width;														//�ύX���镝
	int m_nCounterAnim;															//�A�j���[�V�����J�E���^�[
	float m_fPatternAnim;														//�A�j���[�V�����J�E���^�[
	CTexture::TEXTURE m_texture;												//�e�N�X�`���̗񋓌^
};

#endif // !_OBJECT2D_H_
