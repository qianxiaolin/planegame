
#include<easyx.h>
#include<graphics.h>
#include<time.h>
#include<string.h>
#include<math.h>
#include<mmsystem.h>//ý����ƽӿ�
#pragma comment(lib,"winmm.lib")
#pragma  comment(lib,"Msimg32.lib")
enum Data
{
	BK_WIDTH = 500,
	BK_HEIGHT = 800,

	Player_WIDTH = 116,
	Player_HEIGHT = 120,

	Boss_width = 366,
	Boss_height = 285,

	Bigenemy_width = 200,
	Bigenemy_height = 200,

	Smallenemy_width = 84,
	Smallenemy_height = 87,

	bull_num = 15,//�ӵ���
	enemy_num = 5,

	plane1,
	plane2,
	plane3,
	plane4,
	Big,//��л�
	Small,
};
struct Plane
{
	int x;
	int y;
	bool live;
	int width;
	int height;
	double hp;
	int type;
}player, bull[bull_num], Light, enemy[enemy_num], Boss, BossBull[12], bk[2];//��ҷɻ�
IMAGE BK[2];
IMAGE Score;
IMAGE IMG_life;
IMAGE Img_Player[4];
IMAGE Img_Bull[2];
IMAGE Img_enemy[3];
IMAGE Img_broken[2][2];
IMAGE cover[2];
IMAGE GameBgegin[2];
IMAGE GameOver[2];
IMAGE GameExplain[3];
IMAGE back[2];
IMAGE PlayerChoose_BK;
IMAGE PlayerChoose_HP[2];
IMAGE PlayerChoose_Gold;
IMAGE PlayerChoose_Demond;
IMAGE PlayerChoose_Add;
IMAGE PlayerChoose_Kuan[2];
IMAGE PlayerChoose_Begin[2];
IMAGE PlayerChoose_active[2];
IMAGE PlayerChoose_VIP;
IMAGE PlayerChoose_award;
IMAGE PlayerChoose_shop[2];
IMAGE choosePlane[4];
IMAGE PlayerChoose_show[2];
IMAGE PlayerChoose_turn[2];
IMAGE BOSS[2];
IMAGE IMG_BossBull[12];
IMAGE IMG_BOSSHP[2];
IMAGE IMG_StopBk;
IMAGE Backgame;
IMAGE Closegame;
IMAGE Backchoose;

#define PI 3.14159;
int SCORE = 0;
int Enemykilled_num = 0;

void showimage(IMAGE* P, int x, int y, int width, int high)
{
	HDC GP = GetImageHDC();
	HDC PH = GetImageHDC(P);
	TransparentBlt(GP, x, y, width, high, PH, 0, 0, width, high, RGB(255, 255, 255));
}
void Music()
{
	mciSendString("open ��������.mp3", 0, 0, 0);
	mciSendString("play ��������.mp3", 0, 0, 0);
}
void BeginLoadImg()
{
	loadimage(&cover[0], "����.png");
	loadimage(&GameBgegin[1], "��ʼ��Ϸ2.png");
	loadimage(&GameOver[1], "������Ϸ2.png");
	loadimage(&GameExplain[1], "�淨����2.png");
	loadimage(&GameExplain[2], "����.png");
	loadimage(&back[1], "����2.png");
}
void BeginputImg()
{
	putimage(0, 0, &cover[0]);
	showimage(&GameBgegin[1], 180, 360, 155, 54);
	showimage(&GameOver[1], 180, 460, 154, 53);
	showimage(&GameExplain[1], 180, 560, 154, 53);
}
void playexplain()
{

	int b = 1;
	BeginBatchDraw();
	while (b)
	{
		putimage(0, 0, &cover[0]);
		putimage(50, 100, &GameExplain[2]);//��ͼ
		showimage(&back[1], 363, 100, 87, 46);
		ExMessage msg;
		if (peekmessage(&msg, EM_MOUSE))
		{
			if (msg.message == WM_LBUTTONDOWN && msg.x >= 363 && msg.x <= 450 && msg.y >= 100 && msg.y <= 146)
				b = 0;
		}
		FlushBatchDraw();
	}
	EndBatchDraw();
}
void BeginChoose()
{
	BeginBatchDraw();
	int a = 1;
	BeginLoadImg();
	BeginputImg();
	FlushBatchDraw();
	while (a)
	{
		ExMessage msg = { 0 };
		if (peekmessage(&msg, EM_MOUSE))
		{
			if (msg.message == WM_LBUTTONDOWN && msg.x >= 180
				&& msg.x <= 335 && msg.y >= 360 && msg.y <= 414)
				a = 0;
			if (msg.message == WM_LBUTTONDOWN && msg.x >= 180
				&& msg.x <= 335 && msg.y >= 460 && msg.y <= 514)
				closegraph();
			if (msg.message == WM_LBUTTONDOWN && msg.x >= 180
				&& msg.x <= 335 && msg.y >= 560 && msg.y <= 614)
				playexplain();
		}
	}
	EndBatchDraw();
}
void LoadImg_PlayerChoose()
{
	loadimage(&PlayerChoose_BK, "ѡ�񱳾�.png");

	loadimage(&PlayerChoose_HP[0], "����.png");
	loadimage(&PlayerChoose_HP[1], "����.png");
	loadimage(&PlayerChoose_Add, "��.png");
	loadimage(&PlayerChoose_Gold, "���.jpg");
	loadimage(&PlayerChoose_Demond, "��ʯ.png");

	loadimage(&PlayerChoose_active[0], "active.png");
	loadimage(&PlayerChoose_award, "award.png");
	loadimage(&PlayerChoose_VIP, "VIP.png");
	loadimage(&PlayerChoose_shop[0], "shop1.png");
	loadimage(&PlayerChoose_shop[1], "shop2.png");

	loadimage(&PlayerChoose_Kuan[0], "ѡ��ɻ�2.png");
	loadimage(&PlayerChoose_Kuan[1], "��2.png");

	loadimage(&PlayerChoose_turn[0], "left.png");
	loadimage(&PlayerChoose_turn[1], "right.png");

	loadimage(&choosePlane[0], "chooseplane1.png");
	loadimage(&choosePlane[1], "chooseplane2.png");
	loadimage(&choosePlane[2], "chooseplane3.png");
	loadimage(&choosePlane[3], "chooseplane4.png");

	loadimage(&PlayerChoose_Begin[0], "����1.png");
	loadimage(&PlayerChoose_Begin[1], "����2.png");

}
void PutImg_PlayerChoose(int type)
{
	LoadImg_PlayerChoose();
	putimage(0, 0, &PlayerChoose_BK);
	putimage(0, 0, &PlayerChoose_HP[0], SRCINVERT);
	putimage(100, 10, &PlayerChoose_Add, SRCINVERT);
	putimage(150, 0, &PlayerChoose_Gold, SRCINVERT);
	putimage(300, 0, &PlayerChoose_Demond, SRCINVERT);

	putimage(0, 45, &PlayerChoose_active[0]);//��ͼ
	putimage(65, 45, &PlayerChoose_award);//��ͼ
	putimage(130, 45, &PlayerChoose_VIP);//��ͼ
	//Ѱ��
	putimage(250, 45, &PlayerChoose_shop[0], NOTSRCERASE);//��ͼ
	putimage(250, 45, &PlayerChoose_shop[1], SRCINVERT);

	showimage(&PlayerChoose_Kuan[0], 0, 120, 500, 126);

	putimage(50, 350, &PlayerChoose_turn[0], SRCINVERT);
	putimage(430, 350, &PlayerChoose_turn[1], SRCINVERT);

	switch (type)
	{
	case 1:player.type = plane1; break;
	case 2:player.type = plane2; break;
	case 3:player.type = plane3; break;
	case 4:player.type = plane4; break;
	}

	switch (player.type)
	{
	case plane1:putimage(150, 270, &choosePlane[0], SRCINVERT); break;
	case plane2:putimage(150, 270, &choosePlane[1], SRCINVERT); break;
	case plane3:putimage(150, 270, &choosePlane[2], SRCINVERT); break;
	case plane4:putimage(150, 270, &choosePlane[3], SRCINVERT); break;
	}



	//����
	putimage(123, 600, &PlayerChoose_Begin[0], NOTSRCERASE);
	putimage(123, 600, &PlayerChoose_Begin[1], SRCINVERT);

	showimage(&PlayerChoose_Kuan[1], 0, 525, 500, 385);

}
void PutText_PlayerChoose()
{
	settextcolor(WHITE);
	outtextxy(50, 18, "150/200");
	outtextxy(200, 18, "9999");
}
void PlaneChoose()
{
	player.type = plane1;
	int c = 1;
	int choose = 1;
	BeginBatchDraw();
	while (c)
	{

		PutImg_PlayerChoose(choose);
		PutText_PlayerChoose();
		FlushBatchDraw();
		ExMessage msg;
		if (peekmessage(&msg, EM_MOUSE))
		{
			if (msg.message == WM_LBUTTONDOWN && msg.x >= 123 &&
				msg.x <= 377 && msg.y >= 600 && msg.y <= 656)
			{
				c = 0;
			}
			if (msg.message == WM_LBUTTONDOWN && msg.x >= 33 &&
				msg.x <= 128 && msg.y >= 678 && msg.y <= 773)
				choose = 1;
			if (msg.message == WM_LBUTTONDOWN && msg.x >= 149 &&
				msg.x <= 244 && msg.y >= 678 && msg.y <= 773)
				choose = 2;
			if (msg.message == WM_LBUTTONDOWN && msg.x >= 265 &&
				msg.x <= 360 && msg.y >= 678 && msg.y <= 773)
				choose = 3;
			if (msg.message == WM_LBUTTONDOWN && msg.x >= 381 &&
				msg.x <= 472 && msg.y >= 678 && msg.y <= 773)
				choose = 4;
			if (msg.message == WM_LBUTTONDOWN && msg.x >= 50 &&
				msg.x <= 83 && msg.y >= 350 && msg.y <= 396 && choose > 1)
				choose--;
			if (msg.message == WM_LBUTTONDOWN && msg.x >= 430 &&
				msg.x <= 460 && msg.y >= 350 && msg.y <= 396 && choose < 4)
				choose++;
		}
	}
	EndBatchDraw();
}
void loadImg()
{
	loadimage(&BK[0], "����.jpg");
	loadimage(&BK[1], "����.jpg");


	loadimage(&Score, "score.png");

	loadimage(&IMG_life, "life.png");//���Ѫ��

	loadimage(&Img_Player[0], "plane1.png");
	loadimage(&Img_Player[1], "plane2.png");
	loadimage(&Img_Player[2], "plane3.png");
	loadimage(&Img_Player[3], "plane4.png");
	//�ӵ�ͼƬ
	loadimage(&Img_Bull[1], "bullet.png");
	//С�л�ͼƬ
	loadimage(&Img_enemy[0], "smallenemy.png");
	//��л�ͼƬ
	loadimage(&Img_enemy[1], "bigenemy.png");
	//BOSSͼƬ
	loadimage(&BOSS[0], "boss1.png");
	loadimage(&BOSS[1], "boss2.png");

	//BOSS�ӵ�
	for (int i = 0; i < 12; i++)
	{
		loadimage(&IMG_BossBull[i], "BossBull.png");

	}
	loadimage(&IMG_BOSSHP[0], "BossHP_Bk.png");
	loadimage(&IMG_BOSSHP[1], "BossHP.png");
	//��ͣ��Ϸ
	loadimage(&IMG_StopBk, "StopBk.png");
	loadimage(&Backgame, "backgame.png");
	loadimage(&Closegame, "closegame.png");
	loadimage(&Backchoose, "backchoose.png");

}//���ر��������ͼƬ
bool time(int ms)
{
	static DWORD t1, t2;
	if (t2 - t1 > ms)
	{
		t1 = t2;
		return true;
	}
	t2 = clock();
	return false;
}
void BkMove()
{
	static int i = 0;
	bk[1].x = 0;
	bk[0].y = i;
	bk[1].y = i - 1024;
	if (i <= 1024)
	{
		putimage(bk[0].x, bk[0].y, &BK[0]);
		putimage(bk[1].x, bk[1].y, &BK[1]);
		i++;
	}
	else i = 0;
}

void CreatPlayerBull()
{
	for (int i = 0; i < bull_num; i++)
	{
		if (!bull[i].live)
		{
			bull[i].x = player.x + 49;
			bull[i].y = player.y;
			bull[i].live = true;
			break;
		}
	}
}
void PlayerBullMove(int speed)
{
	for (int i = 0; i < bull_num; i++)
	{
		if (bull[i].live)
		{
			bull[i].y -= speed;
			if (bull[i].y < 0) bull[i].live = false;
		}
	}
}
void PlaneMove(int speed)
{
	if (GetAsyncKeyState(VK_UP) || GetAsyncKeyState('W'))
	{
		if (player.y >= 0)
			player.y -= speed;
	}
	if (GetAsyncKeyState(VK_DOWN) || GetAsyncKeyState('S'))
	{
		if (player.y <= BK_HEIGHT - Player_HEIGHT)
			player.y += speed;
	}
	if (GetAsyncKeyState(VK_LEFT) || GetAsyncKeyState('A'))
	{
		if (player.x > 0)
			player.x -= speed;
	}
	if (GetAsyncKeyState(VK_RIGHT) || GetAsyncKeyState('D'))
	{
		if (player.x <= BK_WIDTH - Player_WIDTH)
			player.x += speed;
	}
	static DWORD t1 = 0, t2 = 0;
	if (GetAsyncKeyState(VK_SPACE) && t2 - t1 > 500)
	{
		CreatPlayerBull();
		t1 = t2;
	}
	t2 = GetTickCount();
}
void EnemyType(int i)
{
	if (rand() % 10 == 3 || rand() % 10 == 1)//�����
	{
		enemy[i].type = Big;
		enemy[i].hp = 5;
		enemy[i].width = Bigenemy_width;
		enemy[i].height = Bigenemy_height;
	}
	else
	{
		enemy[i].type = Small;
		enemy[i].hp = 3;
		enemy[i].height = Smallenemy_height;
		enemy[i].width = Smallenemy_width;
	}
}
void EnemyMove()
{
	for (int i = 0; i < enemy_num; i++)
	{
		if (enemy[i].live)
		{
			if (enemy[i].y > 0 && enemy[i].y < 800)enemy[i].y += 2;
			if (enemy[i].y > BK_HEIGHT) enemy[i].live = false;
		}
	}

}
void enemymaking()
{
	for (int i = 0; i < enemy_num; i++)
	{
		if (!enemy[i].live)
		{
			enemy[i].live = true;
			enemy[i].x = rand() % (BK_WIDTH - enemy[i].width);
			enemy[i].y = rand() % (BK_WIDTH / 3);
			EnemyType(i);
			break;
		}
	}
}
void BossBullMaking(int j)
{
	static double angle[12];
	static int speed[3] = { 0 };//��Ȧ
	for (int i = 0; i < 12; i++)
		angle[i] = (i * 2 * 3.17159) / 12;
	for (int i = 0; i < 12; i++)
	{
		putimage(BossBull[i].x, BossBull[i].y, &IMG_BossBull[i], SRCINVERT);
		BossBull[i].x = Boss.x + 160 + speed[j] * cos(angle[i]);
		BossBull[i].y = Boss.y + 260 + speed[j] * sin(angle[i]);
	}
	speed[j]++;
	if (speed[j] >= 60 && j <= 4)
		BossBullMaking(j + 1);
}
void BossMaking()
{
	if (Boss.live == true && Boss.hp > 0)
	{
		putimage(40, 50, 400, 32, &IMG_BOSSHP[0], 0, 0);
		putimage(45, 58, Boss.hp, 15, &IMG_BOSSHP[1], 0, 0);
		settextstyle(15, 0, "���Ĳ���");
		outtextxy(8, 58, "BOSS");

		putimage(Boss.x, Boss.y, &BOSS[0], NOTSRCERASE);
		putimage(Boss.x, Boss.y, &BOSS[1], SRCINVERT);
		if (Boss.y >= 0 && Boss.y < 300) Boss.y++;
		else	if (Boss.y < 450) Boss.y--;
		BossBullMaking(0);
	}
}
void gameinit()
{
	bk[0].x = 0;
	bk[0].y = 0;
	//���
	player.hp = 240;
	player.x = BK_WIDTH / 2;
	player.y = BK_HEIGHT - Player_HEIGHT;
	player.live = true;
	//�ӵ�
	for (int i = 0; i < bull_num; i++)
	{
		bull[i].x = 0;
		bull[i].y = 0;
		bull[i].live = false;
	}
	//�л�
	for (int i = 0; i < enemy_num; i++)
	{
		enemy[i].live = false;
		EnemyType(i);
	}

	for (int i = 0; i < 12; i++)
	{
		BossBull[i].x = 100;
		BossBull[i].y = 200;
		BossBull[i].live = false;
	}
	//�л�
	Boss.x = 100;
	Boss.y = 0;
	Boss.live = false;
	Boss.hp = 385;
}
void gameDraw()
{

	loadImg();
	BkMove();
	putimage(0, 0, &Score);
	switch (player.type)
	{
	case plane1:putimage(player.x, player.y, &Img_Player[0], SRCINVERT); break;
	case plane2:putimage(player.x, player.y, &Img_Player[1], SRCINVERT); break;
	case plane3:putimage(player.x, player.y, &Img_Player[2], SRCINVERT); break;
	case plane4:putimage(player.x, player.y, &Img_Player[3], SRCINVERT); break;
	}
	//�ӵ�
	for (int i = 0; i < bull_num; i++)
	{
		if (bull[i].live)
		{
			putimage(bull[i].x, bull[i].y, &Img_Bull[1], SRCINVERT);

		}
	}
	//����
	for (int i = 0; i < enemy_num; i++)
	{
		if (enemy[i].live)
		{
			if (enemy[i].type == Big)
			{
				//showimage(&Img_enemy[1], enemy[i].x, enemy[i].y, 381, 315);
				putimage(enemy[i].x, enemy[i].y, &Img_enemy[1], SRCINVERT);
			}
			else
			{
				showimage(&Img_enemy[0], enemy[i].x, enemy[i].y, 84, 87);
				//putimage(enemy[i].x, enemy[i].y, &Img_enemy[0], SRCINVERT);
			}
		}
	}
}
void Together()
{
	for (int k = 0; k < bull_num; k++)
	{
		if (Boss.hp > 0 && bull[k].x >= Boss.x && bull[k].x <= Boss.x + Boss_width
			&& bull[k].y >= Boss.y && bull[k].y <= Boss.y + Boss_height)
		{
			Boss.hp -= 0.05;
		}
		for (int i = 0; i < enemy_num; i++)
		{
			if (!enemy[i].live)
				continue;
			if (!bull[k].live)
				continue;
			if (bull[k].x >= enemy[i].x && bull[k].x <= enemy[i].x + enemy[i].width
				&& bull[k].y >= enemy[i].y && bull[k].y <= enemy[i].y + enemy[i].height)
			{
				bull[k].live = false;
				enemy[i].hp--;
			}
			if (enemy[i].hp <= 0)
			{
				if (enemy[i].type == Big)
					SCORE += 100;
				if (enemy[i].type == Small)
					SCORE += 50;
				enemy[i].live = false;
				Enemykilled_num++;
				enemymaking();
			}
			if (enemy[i].live && enemy[i].type == Big && player.x >= enemy[i].x && player.x <= enemy[i].x + 189
				&& player.y >= enemy[i].y && player.y <= enemy[i].y + 167)
			{
				player.hp -= 0.5;
			}
			if (enemy[i].live && enemy[i].type == Small && player.x >= enemy[i].x && player.x <= enemy[i].x + 84
				&& player.y >= enemy[i].y && player.y <= enemy[i].y + 87)
			{
				player.hp -= 0.05;
			}
		}
		if (Boss.hp <= 0)
			Boss.live = false;
	}
}
void Over()//������Ϸ
{
	if (player.hp <= 0)
		closegraph();
}
void PlayerHp()
{
	putimage(100, 11, (int)player.hp, 16, &IMG_life, 0, 0);
}
void score()//�Ʒ�
{
	char str[50] = { 0 };
	sprintf(str, "%d��", SCORE);
	settextstyle(25, 0, "����");
	settextcolor(RGB(92, 242, 255));
	setbkmode(TRANSPARENT);
	outtextxy(410, 8, str);
	if (SCORE > 100)
	{
		outtextxy(410, 400, "BOSS����");
		Boss.live = true;
		BossMaking();
	}
}
void StopChoose()
{
	int c = 1;
	char arr[50] = { 0 };
	char str[50] = { 0 };
	BeginBatchDraw();
	while (c)
	{
		ExMessage msg = { 0 };
		showimage(&IMG_StopBk, 50, 100, 400, 400);
		sprintf(arr, "�÷֣�%d��", SCORE);
		sprintf(str, "��ɱ����%d", Enemykilled_num);
		settextstyle(25, 0, "����");
		outtextxy(200, 250, arr);
		outtextxy(200, 300, str);
		settextstyle(25, 0, "��������");
		outtextxy(90, 430, "�ص���Ϸ");
		outtextxy(210, 430, "�˳���Ϸ");
		outtextxy(320, 430, "������");
		if (peekmessage(&msg, EM_MOUSE))
		{
			if (msg.message == WM_LBUTTONDOWN && msg.x >= 90
				&& msg.x <= 200 && msg.y >= 430 && msg.y <= 480)
				c = 0;
			if (msg.message == WM_LBUTTONDOWN && msg.x >= 210
				&& msg.x <= 310 && msg.y >= 430 && msg.y <= 480)
				closegraph();
			if (msg.message == WM_LBUTTONDOWN && msg.x >= 320
				&& msg.x <= 410 && msg.y >= 430 && msg.y <= 480)
				;
		}
		FlushBatchDraw();
	}
	EndBatchDraw();
}
void MOUSE()
{
	ExMessage msg;
	if (peekmessage(&msg, EM_MOUSE))
	{
		if (msg.message == WM_LBUTTONDOWN && msg.x >= 0 &&
			msg.x <= 108 && msg.y >= 0 && msg.y <= 44)
		{
			StopChoose();
		}
	}
}
int main()
{
	initgraph(BK_WIDTH, BK_HEIGHT, SHOWCONSOLE);
	gameinit();//��Ϸ���ݳ�ʼ��
	BeginBatchDraw();
label:BeginChoose();//����ѡ��
	PlaneChoose();//�ɻ�ѡ��
	Music();
	while (1)
	{
		gameDraw();
		PlaneMove(2);
		PlayerBullMove(1);
		if (time(10))
		{
			enemymaking();
			SCORE++;
		}
		EnemyMove();
		Together();
		PlayerHp();
		score();
		MOUSE();
		FlushBatchDraw();
	}
	EndBatchDraw();
	return 0;
}