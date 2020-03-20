#include "Simon.h"

void Simon::LoadResources()
{
	Textures* texture = Textures::GetInstance();

	texture->Add(ID_TEX_SIMON, FILEPATH_TEX_SIMON, D3DCOLOR_XRGB(255, 255, 255));

	Sprites* sprites = Sprites::GetInstance();
	Animations* animations = Animations::GetInstance();

	LPDIRECT3DTEXTURE9 texSimon = texture->Get(ID_TEX_SIMON);

	sprites->Add(1, 0, 20, 17, 53, texSimon); // idle

	sprites->Add(2, 28, 20, 45, 53, texSimon); // walk
	sprites->Add(3, 45, 20, 62, 53, texSimon);
	sprites->Add(4, 45, 20, 62, 53, texSimon);
	sprites->Add(5, 62, 20, 79, 53, texSimon);

	sprites->Add(6, 83, 20, 100, 43, texSimon); // duck

	sprites->Add(7, 83, 20, 100, 53, texSimon); // jump

	sprites->Add(8, 0, 134, 33, 167, texSimon); // standing and jumping
	sprites->Add(9, 33, 134, 66, 167, texSimon);
	sprites->Add(10, 66, 134, 111, 167, texSimon);
	sprites->Add(11, 111, 134, 156, 167, texSimon);
	sprites->Add(12, 156, 134, 173, 167, texSimon);

	sprites->Add(13, 177, 134, 210, 167, texSimon); // ducking
	sprites->Add(14, 210, 134, 243, 167, texSimon);
	sprites->Add(15, 243, 134, 288, 167, texSimon);
	sprites->Add(16, 288, 134, 333, 167, texSimon);
	sprites->Add(17, 333, 134, 350, 167, texSimon);


	LPANIMATION ani;

	ani = new Animation();
	ani->Add(1);
	animations->Add(IDLE, ani);

	ani = new Animation();
	ani->Add(2);
	ani->Add(3);
	ani->Add(4);
	ani->Add(5);
	animations->Add(WALK, ani);

	ani = new Animation();
	ani->Add(6);
	animations->Add(DUCK, ani);

	ani = new Animation();
	ani->Add(7);
	animations->Add(JUMP, ani);

	ani = new Animation();
	ani->Add(8);
	ani->Add(9);
	ani->Add(10);
	ani->Add(11);
	ani->Add(12);
	animations->Add(STANDING, ani);

	ani = new Animation();
	ani->Add(13);
	ani->Add(14);
	ani->Add(15);
	ani->Add(16);
	ani->Add(17);
	animations->Add(DUCKING, ani);

	AddAnimation(IDLE);
	AddAnimation(WALK);
	AddAnimation(DUCK);
	AddAnimation(JUMP);
	AddAnimation(STANDING);
	AddAnimation(DUCKING);

	SetPosition(10.0f, 150.0f);
}

void Simon::Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects)
{
	GameObject::Update(dt);

	vy += SIMON_GRAVITY;
	if (y > 150)
	{
		vy = 0;
		y = 150.0f;
	}
}

void Simon::Render()
{
	animations[state]->Render(nx, x, y);
}

void Simon::SetState(int state)
{
	GameObject::SetState(state);

	switch (state)
	{
	case IDLE:
		isStand = true;
		vx = 0;
		break;
	case WALK:
		if (nx > 0) vx = SIMON_WALKING_SPEED;
		else vx = -SIMON_WALKING_SPEED;
		break;
	case DUCK:
		isStand = false;
		vx = 0;
		vy = 0;
		break;
	case JUMP:
		isStand = true;
		if (y == 150)
			vy = -SIMON_JUMP_SPEED_Y;
		break;
	case STANDING:
		isStand = true;
		animations[STANDING]->Reset();
		break;
	case DUCKING:
		isStand = false;
		animations[DUCKING]->Reset();
		break;
	default:
		break;
	}
}

bool Simon::IsStand()
{
	return this->y == 150.0f;
}

void Simon::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + SIMON_BBOX_WIDTH;
	bottom = y + SIMON_BBOX_HEIGHT;
}





