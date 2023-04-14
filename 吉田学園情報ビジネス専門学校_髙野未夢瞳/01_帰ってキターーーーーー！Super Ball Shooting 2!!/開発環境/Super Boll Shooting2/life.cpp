//------------------------------------------------------------------------------
//
//���C�t
//Author::TAKANO
//
//------------------------------------------------------------------------------
#include"life.h"

//---------------
//�}�N����`
//---------------
#define MAX_LIFE			(256)								//�ő僉�C�t

//---------------------
//�X�^�e�B�b�N�ϐ�
//---------------------
static bool bUseLife[MAX_LIFE];
static int nCountNumber;

//--------------------------------------
//�R���X�g���N�^
//--------------------------------------
CLife::CLife()
{

}

//--------------------------------------
//�f�X�g���N�^
//--------------------------------------
CLife::~CLife()
{
}

//--------------------------------------
//������
//--------------------------------------
HRESULT CLife::Init(void)
{
	//������
	CObject2D::Init();
	//�e�N�X�`���̐ݒ�
	CObject2D::SetTexture(CTexture::TEXTURE_PLAYER);

	return S_OK;
}


//--------------------------------------
//�N���G�C�g
//--------------------------------------
CLife* CLife::Create(D3DXVECTOR3 pos, float ObfHi, float ObfWd)
{
	CLife* pbg;

	pbg = new CLife;
	if (pbg != nullptr)
	{
		pbg->Init();
		pbg->SetObjectType(OBJTYPE_BG);
		pbg->Setpos(pos);
		pbg->SetSize(ObfHi, ObfWd);
	}

	return pbg;
}

//--------------------------------------
//�I��
//--------------------------------------
void CLife::Uninit(void)
{
	CObject2D::Uninit();
}

//--------------------------------------
//�X�V
//--------------------------------------
void CLife::Update(void)
{
	CObject2D::Update();
}

//--------------------------------------
//�`��
//--------------------------------------
void CLife::Draw(void)
{
	CObject2D::Draw();
}

//-----------------------------------
//���C�t�̔z�u
//-----------------------------------
void CLife::SetLife()
{
	if (nCountNumber < MAX_LIFE)
	{//MAXLIFE�ȏ����̂�h��

		bUseLife[nCountNumber] = true;		//�g�p����

		nCountNumber++;						//���C�t�̃J�E���^�[�𑝂₷
	}
}

//-----------------------------------
//���C�t�̃q�b�g����
//-----------------------------------
void CLife::HitLife()
{
	if (nCountNumber > 0)
	{//0�ȉ�������̂�h��

		nCountNumber--;						//���C�t�̃J�E���^�[�����炷

		bUseLife[nCountNumber] = false;		//�g�p���Ȃ���Ԃɂ���
	}

}