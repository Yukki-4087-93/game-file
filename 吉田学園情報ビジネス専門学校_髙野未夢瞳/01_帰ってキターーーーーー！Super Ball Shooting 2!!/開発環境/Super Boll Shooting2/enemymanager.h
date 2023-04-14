//--------------------------------------------------------------------------------------
//
// �G�l�~�[�̊Ǘ�
// Author::TAKANO
//
//--------------------------------------------------------------------------------------
#ifndef _CENEMYMANAGER_H_
#define _CENEMYMANAGER_H_

//----------------------------------------
//�O���錾
//----------------------------------------
class CEnemy;

//----------------------------------------
//�N���X��`
//�I�u�W�F�N�g
//----------------------------------------
class CEnemyManager
{
public:
	enum ENEMY_PART
	{
		PART_NONE = 0,
		PART_WAVETYPE_ONE,
		PART_WAVETYPE_TWO,
		PART_WAVETYPE_TREE,
		PART_BOSS,
		PART_BOSS_SECOND,
		PART_BOSS_THIRD,
		PART_MAX
	};

	CEnemyManager();						//�R���X�g���N�^
	~CEnemyManager();						//�f�X�g���N�^
	void Init();							//������
	void Uninit();							//�I��	
	void CreateEnemy();						//�G�l�~�[�̐���
	void PopEnenmy();						//�G�l�~�[�̏o��
	void SwitchPart(ENEMY_PART part);		//�p�[�g�ؑ�
	void DestroyEnemy();					//�G�l�~�[�̍폜
	static CEnemy* GetEnemy();				//�G�l�~�[�̏��̎擾

private:
	static CEnemy* m_pEnemy;				//�G�l�~�[�̃|�C���^
	int m_nPopCount;						//�G�l�~�[�̏o���J�E���^�[
	int m_CollPop;							//�G�l�~�[���ǂꂾ���Ă΂ꂽ���̃J�E���^�[
	int m_BossCount;
	int m_nCount;
	bool m_UseSound;
	bool m_BossColl;
	CEnemyManager::ENEMY_PART m_Part;
};

#endif // !_CENEMYMANAGER_H_