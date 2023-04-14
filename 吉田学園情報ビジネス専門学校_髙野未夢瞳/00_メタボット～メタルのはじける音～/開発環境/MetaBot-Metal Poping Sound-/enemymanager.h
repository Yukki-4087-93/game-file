//---------------------------------------------------------
//
// �G�l�~�[�Ǘ�
// Author::TAKANO
//
//---------------------------------------------------------
#ifndef _ENEMYMANAGER_H_
#define _ENEMYMANAGER_H_

//----------------------------------------
//�C���N���[�h�t�@�C��
//----------------------------------------
#include <d3dx9.h>

//----------------------------------------
//�O���錾
//----------------------------------------
class CEnemy;

//----------------------------------------
//�N���X��`
//�G�o���𑍊�����N���X
//----------------------------------------
class CEnemyManager
{
public:
/*��ʊ֐�*/
	CEnemyManager();													//�R���X�g���N�^
	~CEnemyManager();													//�f�X�g���N�^
	HRESULT Init();														//������
	void Uninit();														//�I��
	void Update();														//�X�V
	void Draw();														//�`��

/*�G�l�~�[���Ǘ�����֐�*/
public:
	static CEnemy* GetEnemy() { return m_pEnemy; }						//�G�l�~�[�̏��擾

/*�}�l�[�W���[�N���X�Ŕ���J�Ɏ����Ă���֐�*/
private:
	void SpawnTutoral();												//�`���[�g���A���p�̃G�l�~�[���o��������
	void SetSpawnPoint();												//�G�l�~�[�̏o���ʒu��ݒ肷��֐�
	void SetAnotherPoint();												//�G�l�~�[�̏o���ʒu��ݒ肷��֐�
	void SetBigSpawnPoint();											//��������G�l�~�[�̏o���ʒu��ݒ肷��֐�
	void SetChangeSpawn();												//�G�l�~�[�̏o������Ƃ��̃^�C�v��ݒ肷��֐�
	void SpawnNormal(float fPosX, float fPosZ);							//�ʏ�̃G�l�~�[�̏o����ݒ肷��֐�
	void SpawnAttacker(float fPosX, float fPosZ);						//�Ἠ}�V�}�V�̃G�l�~�[�̏o����ݒ肷��֐�
	void SpawnSpeeder(float fPosX, float fPosZ);						//���x�}�V�}�V�̃G�l�~�[�̏o����ݒ肷��֐�
	void SpawnDoctor(float fPosX, float fPosZ);							//�񕜃}���̏o����ݒ肷��֐�
	void SpawnMulti(float fPosX, float fPosZ);							//�����\�͎����̏o����ݒ肷��֐�
	void SpawnBoss(float fPosX, float fPosZ,float fsize);							//�{�X�̏o����ݒ肷��֐�

/*�G�l�~�[�W���[�}�l�ŊǗ����郁���o�ϐ�*/
private:
	static CEnemy* m_pEnemy;											//�G�l�~�[�̃|�C���^�[
	int m_nPopCounter;													//�G�l�~�[�̏o�����Ǘ�����ϐ�
	int m_nRand_Spawn_Point;											//�G�l�~�[�̏o���ʒu�����肷��ϐ�
	int m_nScaleCounter;												//�X�P�[���̃T�C�Y��ݒ肷��J�E���^�[�ϐ�
	int m_nBig_Spawn_Point;												//�T�C�Y�̑傫�����̂��o������ʒu��ݒ肷��ϐ�
	int m_nNumber;														//�G�l�~�[�ԍ���ݒ肷��ϐ�
	int m_nSpawnType;
	int m_nChangeSpawn;
};

#endif // !_ENEMYMANAGER_H_
