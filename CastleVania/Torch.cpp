#include "Torch.h"

void Torch::LoadResources()
{
	Textures* texture = Textures::GetInstance();

	texture->Add(ID_TEX_TORCH, FILEPATH_TEX_TORCH, D3DCOLOR_XRGB(255, 255, 255));

	Sprites* sprites = Sprites::GetInstance();
	Animations* animations = Animations::GetInstance();

	LPDIRECT3DTEXTURE9 texCandle = texture->Get(ID_TEX_TORCH);

	sprites->Add(100, 174, 0, 191, 33, texCandle); 
	sprites->Add(101, 191, 0, 208, 33, texCandle);


	LPANIMATION ani;

	ani = new Animation();
	ani->Add(100, 150);
	ani->Add(101, 150);
	animations->Add(10, ani);

	AddAnimation(10);

	SetPosition(150.0f, 150.0f);
}

void Torch::Render()
{
	animations[state]->Render(nx, x, y);
}
