#include"all.h"
bool onGround = false;
const float KASOKU = 1.0f;
const float SPEED_MAX_X = 8.0f;
const float SPEED_MAX_Y = 16.0f;
const float GROUND_POS_Y = 720;
const float SPEED_JUMP_Y = -18.0f;
const float ADJUST_X = 0.025f;
const float ADJUST_Y = 0.5f;
OBJ2D player;
OBJ2D bomb;
OBJ2D enemy;
OBJ2D portal[6];
OBJ2D asiba[4];
OBJ2D background;
VECTOR2 portalTexPosData[]
{
    {80,0},
    {80,80},
    {80,160},
    {80,160},
    {80,0},
    {80,80}
};
VECTOR2 portalData[] =
{
    {140,40},
    {640,40},
    {1140,40},
    {140,440},
    {640,540},
    {1140,440}
};
VECTOR2 asibaData[] =
{
    {150,600},
    {450,200},
    {750,600},
    {1050,200}
};
void player_update(OBJ2D* obj);
void bomb_update(OBJ2D* obj);
void portal_update(OBJ2D* obj);
void enemy_update(OBJ2D* obj);
void back_update(OBJ2D* obj);
bool takeBomb();
//void judge_chara_asi(OBJ2D* chara, OBJ2D* asi);
void SceneGame::init()
{
    player.pos = { 500,720 };
    player.texpos = { 120,0 };
    player.texHW = { 120,120 };
    player.texprivot = { 60,120 };
    
    background.pos = { 0,0 };
    background.texpos = { 1280,0 };
    background.texHW = { 1280,720 };
    background.texprivot = { 0,0 };

    bomb.bomb_init(&bomb);
    
    enemy.pos = { 500,250 };
    for (int i = 0; i < 6; i++)
    {
        portal[i].pos = portalData[i];
        portal[i].texpos = portalTexPosData[i];
    }
    for (int i = 0; i < 4; i++)
    {
        asiba[i].pos = asibaData[i];
        asiba[i].HW = { 200,20 };
        asiba[i].texprivot = asiba[i].HW / 2;
    }
    state = 0;
}
void SceneGame::render()
{
	GameLib::clear(0, 0, 0);
    sprite_render(background.spr,background.pos.x, background.pos.y, 1, 1, 1280*background.animeno, 0, 1280, 720, 0, 0);
    //primitive::rect(0, GROUND_POS_Y+32, 1280, 120-32, 0, 0, 0, 0, 1, 0);
    sprite_render(enemy.spr, enemy.pos.x, enemy.pos.y, enemy.size.x, enemy.size.y, 284*enemy.animeno, 0, 284, 200, 142, 100);
    for (int i = 0; i < 6; i++)
    {
        sprite_render(portal[i].spr, portal[i].pos.x, portal[i].pos.y, portal[i].size.x, portal[i].size.y, portal[i].texpos.x * portal[i].animeno, portal[i].texpos.y, 80, 80, 40, 40);
    }
    //asiba
    for (int i = 0; i < 4; i++)
    {
        primitive::rect(asiba[i].pos.x, asiba[i].pos.y, asiba[i].HW.x, asiba[i].HW.y, asiba[i].texprivot.x, asiba[i].texprivot.y);
    }
    sprite_render(player.spr, player.pos.x, player.pos.y, player.size.x, player.size.y, player.texpos.x * player.animeno, player.texpos.y, player.texHW.x, player.texHW.x, player.texprivot.x, player.texprivot.y);
    sprite_render(bomb.spr, bomb.pos.x, bomb.pos.y, bomb.size.x, bomb.size.y, bomb.texpos.x * bomb.animeno, bomb.texpos.y, bomb.texHW.x, bomb.texHW.y, bomb.texprivot.x, bomb.texprivot.y);

}
void SceneGame::update()
{
    switch (state)
    {
    case 0:
        GameLib::setBlendMode(Blender::BS_ALPHA);
        bomb.spr = sprite_load(L"./Data/Images/countBom2.png");
        enemy.spr = sprite_load(L"./Data/Images/Dragon2.png");
        for (int i = 0; i < 6; i++)
            portal[i].spr = sprite_load(L"./Data/Images/portal2.png");
        player.spr = sprite_load(L"./Data/Images/maincara2.png");
        background.spr = sprite_load(L"./Data/Images/back.png");
        state++;
    case 1:
        player_update(&player);
        bomb_update(&bomb);
        for (auto& item : portal)
            portal_update(&item);
        enemy_update(&enemy);
        back_update(&background);



        break;
    }
    
}
void player_update(OBJ2D* obj)
{
    switch (obj->state)
    {
    case 0:
        obj->speed.y += KASOKU;
        if (obj->speed.y > SPEED_MAX_Y)
            obj->speed.y = SPEED_MAX_Y;
        obj->pos.y += obj->speed.y;
        if (obj->pos.y > GROUND_POS_Y)
        {
            obj->pos.y = GROUND_POS_Y;
            onGround = true;
            obj->jumpcount = 2;
        }
        if (onGround == true && TRG(0) & PAD_L1 && obj->jumpcount > 0)
        {
            obj->speed.y = SPEED_JUMP_Y;
            obj->jumpcount--;
        }
        obj->timer++;
        switch (STATE(0) & (PAD_LEFT | PAD_RIGHT))
        {
        case PAD_LEFT:  // 左だけが押されている場合
            obj->speed.x -= KASOKU;
            obj->size.x = 1;
            if (obj->timer % 10 == 0)
            {
                obj->animeno++;
                if (obj->animeno == 5)
                    obj->animeno = 1;

            }
            break;
        case PAD_RIGHT: // 右だけが押されている場合
            obj->speed.x += KASOKU;
            obj->size.x = -1;
            if (obj->timer % 10 == 0)
            {
                obj->animeno++;
                if (obj->animeno == 5)
                    obj->animeno = 1;

            }
            break;
        default:        // どちらも押されていないか相殺されている場合
            if (obj->speed.x > 0)
            {
                obj->speed.x -= KASOKU / 2;
                if (obj->speed.x < 0)
                    obj->speed.x = 0;
            }
            if (obj->speed.x < 0)
            {
                obj->speed.x += KASOKU / 2;
                if (obj->speed.x > 0)
                    obj->speed.x = 0;
            }
            obj->animeno = 0;
            break;
        }

        if (obj->speed.x > SPEED_MAX_X)
            obj->speed.x = SPEED_MAX_X;
        if (obj->speed.x < -SPEED_MAX_X)
            obj->speed.x = -SPEED_MAX_X;
        obj->pos.x += obj->speed.x;
        if (TRG(0) & PAD_TRG1&&takeBomb())
        {
            obj->texpos = { 120,120 };
            obj->animeno = 0;
            obj->timer=0;
            obj->state++;
        }
            
        break;
    case 1:        
        
        obj->speed.y += KASOKU;
        if (obj->speed.y > SPEED_MAX_Y)
            obj->speed.y = SPEED_MAX_Y;
        obj->pos.y += obj->speed.y;
        if (obj->pos.y > GROUND_POS_Y)
        {
            obj->pos.y = GROUND_POS_Y;
            onGround = true;
            
            obj->jumpcount = 1;
        }
        if (onGround == true && TRG(0) & PAD_L1 && obj->jumpcount > 0)
        {
            obj->speed.y = SPEED_JUMP_Y;
            obj->jumpcount--;
        }
        obj->timer++;
        switch (STATE(0) & (PAD_LEFT | PAD_RIGHT))
        {
        case PAD_LEFT:  // 左だけが押されている場合
            obj->speed.x -= KASOKU/4;
            obj->size.x = 1;
            if (obj->timer % 10 == 0)
            {
                obj->animeno++;
                if (obj->animeno == 5)
                    obj->animeno = 1;

            }
            break;
        case PAD_RIGHT: // 右だけが押されている場合
            obj->speed.x += KASOKU/4;
            obj->size.x = -1;
            if (obj->timer % 10 == 0)
            {
                obj->animeno++;
                if (obj->animeno == 5)
                    obj->animeno = 1;

            }
            break;
        default:        // どちらも押されていないか相殺されている場合
            if (obj->speed.x > 0)
            {
                obj->speed.x -= KASOKU/4;
                if (obj->speed.x < 0)
                    obj->speed.x = 0;
            }
            if (obj->speed.x < 0)
            {
                obj->speed.x += KASOKU/4;
                if (obj->speed.x > 0)
                    obj->speed.x = 0;
            }
            obj->animeno = 0;
            break;
        }
        if (obj->size.x > 0)
        {
            bomb.pos.x = player.pos.x - player.texHW.x / 2 - bomb.texHW.x / 2;
            bomb.pos.y = player.pos.y - bomb.texHW.y / 2;
        }
        if (obj->size.x < 0)
        {
            bomb.pos.x = player.pos.x + player.texHW.x / 2 + bomb.texHW.x / 2;
            bomb.pos.y = player.pos.y - bomb.texHW.y / 2;

        }
        if (obj->speed.x > SPEED_MAX_X/4)
            obj->speed.x = SPEED_MAX_X/4;
        if (obj->speed.x < -SPEED_MAX_X/4)
            obj->speed.x = -SPEED_MAX_X/4;
        obj->pos.x += obj->speed.x;

        if (TRG(0) & PAD_TRG1)
        {
            
            obj->texpos = { 120,0 };
            obj->animeno = 0;
            obj->timer = 0;
            obj->state--;
        }
            
        break;
    }

}
void bomb_update(OBJ2D* obj)
{
    obj->timer++;
    switch (obj->state)
    {
    case 0:
        if (obj->timer % 60 == 0)
        {
            obj->animeno++;
        }

        if (obj->animeno == 5)
        {
            obj->spr = sprite_load(L"./Data/Images/bakuha2.png");
            obj->texpos = { 120,0 };
            obj->texHW = { 120,120 };
            obj->texprivot = { 60,60 };
            obj->animeno = 0;
            obj->timer = 0;
            obj->state++;
        }

        break;
    case 1:
        if (obj->timer % 3 == 0)
        {
            obj->animeno++;
        }
        if (obj->animeno == 4)
        {
            player.texpos = { 120,0 };
            player.animeno = 0;
            player.timer = 0;
            player.state=0;
        }
        if (obj->timer == 40)
        {
            obj->bomb_init(&bomb);
            obj->spr = sprite_load(L"./Data/Images/countBom2.png");
            obj->animeno = 0;
            obj->timer = 0;
            obj->state--;
        }
        break;
    }

}
void portal_update(OBJ2D* obj)
{
    obj->timer++;
    if (obj->timer % 10 == 0)
    {
        obj->animeno++;
        if (obj->animeno == 4)
            obj->animeno = 0;

    }
}
void enemy_update(OBJ2D* obj)
{
    obj->timer++;


    switch (obj->state)
    {
    case 0:
        obj->pos.x += 5;
        if (obj->pos.x + 142 > 1280)
            obj->state++;
        break;
    case 1:
        obj->pos.x -= 5;
        if (obj->pos.x - 142 < 0)
            obj->state--;
        break;
    }
    if (obj->timer % 10 == 0)
    {
        obj->animeno++;
        if (obj->animeno == 8)
            obj->animeno = 0;

    }
}
void back_update(OBJ2D* obj)
{
    obj->timer++;
    if (obj->timer % 10 == 0)
    {
        obj->animeno++;
        if (obj->animeno == 4)
            obj->animeno = 0;

    }

}
bool takeBomb()
{
    if (player.size.x > 0 && player.pos.x - player.texHW.x / 2< bomb.pos.x + bomb.texHW.x / 2 && player.pos.x - player.texHW.x / 2 > bomb.pos.x - bomb.texHW.x / 2)
        return true;
    if (player.size.x < 0 && player.pos.x + player.texHW.x / 2 > bomb.pos.x - bomb.texHW.x / 2 && player.pos.x + player.texHW.x / 2 < bomb.pos.x + bomb.texHW.x / 2)
        return true;

    return false;
}
/*void judge_chara_asi(OBJ2D* chara, OBJ2D* asi)
{
    //if (asi->pos.y + asi->HW.y / 2 < chara->pos.y && asi->pos.y - asi->HW.y / 2 > chara->pos.y-chara->texHW.y)
    //{
    //    if (chara->pos.x - chara->texHW.x / 2 < asi->pos.x + asi->HW.x / 2 && chara->pos.x - chara->texHW.x / 2 > asi->pos.x - asi->HW.x / 2)
    //        chara->pos.x = asi->pos.x + asi->HW.x / 2 +chara->texHW.x/2+ ADJUST_X;
    //    if(chara->pos.x+chara->texHW.x/2>asi->pos.x-asi->HW.x/2&& chara->pos.x + chara->texHW.x / 2 < asi->pos.x + asi->HW.x / 2)
    //        chara->pos.x = asi->pos.x - asi->HW.x / 2 - chara->texHW.x / 2 - ADJUST_X;
    //}
    if (chara->pos.x - chara->texHW.x / 2 < asi->pos.x + asi->HW.x / 2 && chara->pos.x - chara->texHW.x / 2 > asi->pos.x - asi->HW.x / 2)
    {


        float oldY = chara->pos.y;
        chara->pos.y += chara->speed.y;
        float deltaY = chara->pos.y - oldY;
        if (deltaY > 0)
        {
            if (chara->pos.y < asi->pos.y - asi->HW.y / 2)
            {
                chara->pos.y = asi->pos.y - asi->HW.y / 2 - SPEED_MAX_Y - ADJUST_Y;
                if (chara->speed.y > 0)
                    chara->speed.y = 0;
                onGround = true;

            }
        }
        
            
    }

    
}*/