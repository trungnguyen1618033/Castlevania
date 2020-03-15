﻿#include "Simon.h"

void Simon::LoadResources()
{
	Textures* texture = Textures::GetInstance();

	texture->Add(ID_TEX_SIMON, FILEPATH_TEX_SIMON, D3DCOLOR_XRGB(255, 255, 255));

	Sprites* sprites = Sprites::GetInstance();
	Animations* animations = Animations::GetInstance();

	LPDIRECT3DTEXTURE9 texSimon = texture->Get(ID_TEX_SIMON);

	sprites->Add(10001, 0, 20, 17, 53, texSimon); // stand

	sprites->Add(10011, 28, 20, 45, 53, texSimon); // walk
	sprites->Add(10012, 45, 20, 62, 53, texSimon);
	sprites->Add(10013, 45, 20, 62, 53, texSimon);
	sprites->Add(10014, 62, 20, 79, 53, texSimon);

	sprites->Add(10021, 83, 20, 100, 47, texSimon); // sit

	sprites->Add(10031, 83, 20, 100, 47, texSimon); // jump


	LPANIMATION ani;

	ani = new Animation();
	ani->Add(10001);
	animations->Add(STAND, ani);

	ani = new Animation();
	ani->Add(10011);
	ani->Add(10012);
	ani->Add(10013);
	ani->Add(10014);
	animations->Add(WALK, ani);

	ani = new Animation();
	ani->Add(10021);
	animations->Add(SIT, ani);

	ani = new Animation();
	ani->Add(10031);
	animations->Add(JUMP, ani);

	AddAnimation(STAND);
	AddAnimation(WALK);
	AddAnimation(SIT);
	AddAnimation(JUMP);

	SetPosition(10.0f, 100.0f);
}

void Simon::Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects)
{
	GameObject::Update(dt);

	vy += SIMON_GRAVITY;
	if (y > 160)
	{
		vy = 0;
		y = 160.0f;
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
	case STAND:
		vx = 0;
		break;
	case WALK:
		if (nx > 0) vx = SIMON_WALKING_SPEED;
		else vx = -SIMON_WALKING_SPEED;
		break;
	case JUMP:
		if (y == 300)
			vy = -SIMON_JUMP_SPEED_Y;
	default:
		break;
	}
}

void Simon::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + SIMON_BBOX_WIDTH;
	bottom = y + SIMON_BBOX_HEIGHT;
}





