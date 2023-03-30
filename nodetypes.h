typedef struct Node Node;
typedef struct Leaf Leaf;


struct Node{			//�迭���� �θ�, �ڽ��� �����ϱ� ���� ��� �ڷᱸ�� 
	int element[4][4];
	float fnvalue;		//���Լ��� ���� 
	int depth;			//����� ���̰� ���� 
	int unfold;			//�ڽ��� Ȯ���� ����� �Ǻ��� ���� ������ (������� ����)

	Node *parent;		//�θ� ��带 ����Ű�� ������ 

	Node *child[4];		//�ڽ� ��带 ����Ű�� ������ 
};


struct Leaf{			//��� ������ �ܼ� ���� ����Ʈ�� ����Ű�� ������ ������ ���� �ڷᱸ�� 
	Node *leaf;			//Ʈ���� �� ��带 ����Ŵ 
	Leaf *next;			//���� ��带 ����Ű�� ������ 	
};
