#include"all.h"
bool onGround = false;
const float KASOKU = 1.0f;
const float KASOKU_X = 5.0f;
const float BOMB_SPEED_MAX_X = 20.0f;
const float SPEED_MAX_X = 8.0f;
const float SPEED_MAX_Y = 16.0f;
const float GROUND_POS_Y = 720;
const float SPEED_JUMP_Y = -18.0f;
const float ADJUST_X = 0.025f;
const float ADJUST_Y = 0.5f;
int playerHP ;
int enemyHP ;
int enemySpeed ;
int enemyBombPause;
VECTOR2 enemyBombPos;
OBJ2D player;
OBJ2D bomb;
OBJ2D enemy;
OBJ2D portal[6];
OBJ2D asiba[4];
OBJ2D background;
OBJ2D enemyBomb;
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
    {140,540},
    {640,540},
    {1140,540}
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
void EnemyBomb(OBJ2D* obj);
bool BombPortalJudge();
bool takeBomb();
bool BombPlayerJudge();
bool BombEnemyJudge();
bool enemyBombFloorJudge();
bool enemyBombPlayerJudge();
void SceneGame::init()
{
    music::play(M_GAME_BATTLE, true);
    player.pos = { 500,720 };
    player.texpos = { 120,0 };
    player.texHW = { 120,120 };
    player.texprivot = { 60,120 };
    player.state = 0;
    player.alpha = 1;
    enemy.alpha = 1;
    enemyBomb.state = 4;
    enemy.texHW.y = 0;
    background.pos = { 0,0 };
    background.texpos = { 1280,0 };
    background.texHW = { 1280,720 };
    background.texprivot = { 0,0 };
    playerHP = 5;
    enemyHP = 8;
    enemySpeed = 5;
    bomb.bomb_init(&bomb);
    enemyBombPause = 6 + enemyHP;
    enemy.pos = { 500,250 };
    for (int i = 0; i < 6; i++)
    {
        portal[i].pos = portalData[i];
        portal[i].texpos = portalTexPosData[i];
    }
    for (int i = 0; i < 2; i++)
    {
        asiba[i].pos = asibaData[i];
        asiba[i].HW = { 200,20 };
        asiba[i].texprivot = asiba[i].HW / 2;
    }
    state = 0;

    

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
        if (obj->pos.x < 0 + obj->texHW.x/2)
        {
            obj->pos.x = obj->texHW.x/2;
            obj->speed.x = 0;
        }
        if (obj->pos.x > 1280 - obj->texHW.x/2)
        {
            obj->pos.x = 1280 - obj->texHW.x/2;
            obj->speed.x = 0;
        }
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
        //takebomb bomb pos
        if (obj->size.x > 0)
        {
            bomb.pos.x = player.pos.x - player.texHW.x / 2 - bomb.texHW.x / 2;
            bomb.pos.y = player.pos.y- bomb.texHW.y / 2-bomb.speed.y;
        }
        if (obj->size.x < 0)
        {
            bomb.pos.x = player.pos.x + player.texHW.x / 2 + bomb.texHW.x / 2;
            bomb.pos.y = player.pos.y - bomb.texHW.y / 2 - bomb.speed.y;

        }
        //TODO::BPJudge;
        if (BombPortalJudge())
        {
            if (bomb.pos.x < 200)
                bomb.pos = portal[2].pos;
            else if (bomb.pos.x < 700)
                bomb.pos = portal[0].pos;
            else if(bomb.pos.x<1200)
                bomb.pos = portal[1].pos;
            obj->texpos = { 120,0 };
            obj->animeno = 0;
            obj->timer = 0;
            obj->state--;
        }
        if (obj->speed.x > SPEED_MAX_X/4)
            obj->speed.x = SPEED_MAX_X/4;
        if (obj->speed.x < -SPEED_MAX_X/4)
            obj->speed.x = -SPEED_MAX_X/4;
        obj->pos.x += obj->speed.x;
        if (obj->pos.x < 0 + obj->texHW.x / 2)
        {
            obj->pos.x = obj->texHW.x / 2;
            obj->speed.x = 0;
        }
        if (obj->pos.x > 1280 - obj->texHW.x / 2)
        {
            obj->pos.x = 1280 - obj->texHW.x / 2;
            obj->speed.x = 0;
        }

        if (TRG(0) & PAD_TRG1)
        {
            bomb.speed.x = 0;
            obj->texpos = { 120,0 };
            obj->animeno = 0;
            obj->timer = 0;
            
            obj->state--;
        }
        
        break;
    }
    obj->alpha += 0.02;
    if (obj->alpha == 1)
        obj->alpha = 1;
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

        obj->speed.y += KASOKU;
        if (obj->speed.y > SPEED_MAX_Y)
            obj->speed.y = SPEED_MAX_Y;
       
        if (obj->pos.y >= GROUND_POS_Y - obj->texHW.y / 2)
        {
            obj->pos.y = GROUND_POS_Y - obj->texHW.y/2 ;
            obj->speed.y = 0;

        }

        obj->pos.y += obj->speed.y;
        if (obj->animeno == 5|| BombEnemyJudge()==true)
        {
            obj->state++;
        }
        break;
    case 1:
        
        if (BombEnemyJudge())
        {
            sound::play(SOUND, SOUND_HITENEMY);
            enemy.alpha = 0;
            enemyHP--;
            if (enemyHP == 0)
            {
                setScene(SCENE_CLEAR);
                music::stop(M_GAME_BATTLE);
                return;

            }
        }
       
        obj->spr = sprite_load(L"./Data/Images/bakuha2.png");
        obj->texpos = { 120,0 };
        obj->texHW = { 120,120 };
        obj->texprivot = { 60,60 };
        obj->animeno = 0;
        obj->timer = 0;
        obj->state++;
    case 2:
        if (obj->timer % 3 == 0)
        {
            obj->animeno++;
        }
        if (obj->animeno == 4)
        {
            sound::play(SOUND,SOUND_BOMB);
            obj->state++;
        }
        break;
    case 3:
        if (BombPlayerJudge())
        {
            sound::play(SOUND, SOUND_HITPLAYER);
            player.alpha = 0;
            playerHP--;
            if (playerHP == 0)
            {
                setScene(SCENE_OVER);
                music::stop(M_GAME_BATTLE);
                return;

            }
        }
        player.texpos = { 120,0 };
        player.animeno = 0;
        player.timer = 0;
        player.state = 0;
        obj->state++;
        break;
    case 4:
        if (obj->timer == 40)
        {
            obj->bomb_init(&bomb);
            obj->spr = sprite_load(L"./Data/Images/countBom2.png");
            obj->animeno = 0;
            obj->timer = 0;
            obj->state = 0;
            break;
        }

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
        obj->pos.x += enemySpeed;
        if (obj->pos.x + 142 > 1280)
            obj->state++;
        //TODO:PORTALCHANGE
        //if (obj->timer == 500)
        //{
        //    for (int i = 0; i < 3; i++)
        //    {
        //        portal[3+i].pos = portalData[5-i];
        //    }
        //}
        break;
    case 1:
        obj->pos.x -= enemySpeed;
        if (obj->pos.x - 142 < 0)
            obj->state--;
        break;
    }
    //TODO ENEMY PICTURE CHANGE
    if (enemyHP == 5)
        enemySpeed = 8;
    if (enemyHP == 2)
    {
        enemySpeed = 12;
        obj->texHW.y = 200;
    }
    obj->alpha += 0.01;
    if (obj->alpha == 1)
        obj->alpha = 1;
    EnemyBomb(&enemyBomb);
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
void EnemyBomb(OBJ2D* obj)
{
    switch (obj->state)
    {
    case 0:
        //生成
        if (obj->timer % 5 == 0)
        {
            enemyBombPause--;
        }
        if (enemyBombPause == 0)
        {
            obj->spr = sprite_load(L"./Data/Images/countBom2.png");
            obj->animeno = 1;
            obj->texpos = { 400,0 };
            obj->texHW = { 80,80 };
            obj->texprivot = { 40,40 };
            enemyBombPos = enemy.pos;
            obj->pos = enemyBombPos;
            //sound::play(SOUND, SOUND_SHOT);
            obj->state++;
        }
        
        break;
    case 1:
        obj->speed.y += KASOKU;
        if (obj->speed.y > SPEED_MAX_Y)
            obj->speed.y = SPEED_MAX_Y;
        obj->pos.y += obj->speed.y;

        //debug::setString("bombspeed %f", obj->pos.y);

        //当たり
        if (enemyBombPlayerJudge()|| enemyBombFloorJudge())
            obj->state++;
        break;
    case 2:
        if (enemyBombPlayerJudge())
        {
            sound::play(SOUND, SOUND_HITPLAYER);
            player.alpha = 0;
            playerHP--;
            if (playerHP == 0)
            {
                setScene(SCENE_OVER);
                music::stop(M_GAME_BATTLE);
                return;
            }
            obj->state++;
        }
        
    case 3:
        
        
        //爆発のデータ読み込む
        
        obj->spr = sprite_load(L"./Data/Images/bakuha2.png");
        obj->texpos = { 120,0 };
        obj->texHW = { 120,120 };
        obj->texprivot = { 60,60 };
        obj->animeno = 0;
        obj->timer = 0;
        
        obj->state++;
        
        break;
    case 4:
        //爆発アニメ
        
        if (obj->timer % 3 == 0)
        {
            obj->animeno++;
        }
        if (obj->animeno == 4)
        {
            sound::play(SOUND, SOUND_BOMB);
            obj->state = 0;
            enemyBombPause = 6+enemyHP;
        }

    }
    obj->timer++;
}
bool takeBomb()
{
    if (player.size.x > 0 && player.pos.x - 46 < bomb.pos.x + bomb.texHW.x / 2 && player.pos.x - 46 > bomb.pos.x - bomb.texHW.x / 2)
        return true;
    if (player.size.x < 0 && player.pos.x + 46 > bomb.pos.x - bomb.texHW.x / 2 && player.pos.x + 46 < bomb.pos.x + bomb.texHW.x / 2)
        return true;

    return false;
}
bool BombPortalJudge()
{
    for (int i = 0; i < 3; i++)
        if (bomb.pos.x > portal[3 + i].pos.x - 40 && bomb.pos.x < portal[3 + i].pos.x + 40 && bomb.pos.y < portal[3 + i].pos.y + 40)
            return true;
    return false;
}
bool BombPlayerJudge()
{
    if (bomb.pos.x + bomb.texHW.x / 2 < player.pos.x - player.texHW.x / 2)
        return false;
    if (bomb.pos.x - bomb.texHW.x / 2 > player.pos.x + player.texHW.x / 2)
        return false;
    if (bomb.pos.y - bomb.texHW.y / 2 > player.pos.y)
        return false;
    return true;
}
bool BombEnemyJudge()
{
    if (bomb.pos.y + bomb.texHW.y / 2 < enemy.pos.y - 40)
        return false;
    if (bomb.pos.y - bomb.texHW.y / 2 > enemy.pos.y + 100)
        return false;
    if (bomb.pos.x + bomb.texHW.x / 2 < enemy.pos.x - 142)
        return false;
    if (bomb.pos.x - bomb.texHW.x / 2 > enemy.pos.x + 142)
        return false;
    
    return true;
}
bool enemyBombFloorJudge()
{
    if (enemyBomb.pos.y + enemyBomb.texHW.y / 2 < GROUND_POS_Y)
        return false;
    return true;
}
bool enemyBombPlayerJudge()
{
    if (enemyBomb.pos.y + enemyBomb.texHW.y / 2 <player.pos.y - player.texHW.y)
        return false;
    if (enemyBomb.pos.x + enemyBomb.texHW.x / 2 < player.pos.x - player.texHW.x / 2)
        return false;
    if (enemyBomb.pos.x - enemyBomb.texHW.x / 2 > player.pos.x + player.texHW.x / 2)
        return false;
    return true;
}
void SceneGame::render()
{
    GameLib::clear(0, 0, 0);
    //background
    sprite_render(background.spr, background.pos.x, background.pos.y, 1, 1, 1280 * background.animeno, 0, 1280, 720, 0, 0);
    //enemy
    sprite_render(enemy.spr, enemy.pos.x, enemy.pos.y, enemy.size.x, enemy.size.y, 284 * enemy.animeno, enemy.texHW.y, 284, 200, 142, 100,0,1,1,1,enemy.alpha);
    sprite_render(enemyBomb.spr, enemyBomb.pos.x, enemyBomb.pos.y, 1, 1, enemyBomb.texpos.x * enemyBomb.animeno, 0, enemyBomb.texHW.x, enemyBomb.texHW.y, enemyBomb.texprivot.x, enemyBomb.texprivot.y);
    //portal
    for (int i = 0; i < 6; i++)
    {
        sprite_render(portal[i].spr, portal[i].pos.x, portal[i].pos.y, portal[i].size.x, portal[i].size.y, portal[i].texpos.x * portal[i].animeno, portal[i].texpos.y, 80, 80, 40, 40);
    }
    ////asiba
    //for (int i = 0; i < 2; i++)
    //{
    //    primitive::rect(asiba[i].pos.x, asiba[i].pos.y, asiba[i].HW.x, asiba[i].HW.y, asiba[i].texprivot.x, asiba[i].texprivot.y);
    //}

    //player
    sprite_render(player.spr, player.pos.x, player.pos.y, player.size.x, player.size.y, player.texpos.x * player.animeno, player.texpos.y, player.texHW.x, player.texHW.y, player.texprivot.x, player.texprivot.y, 0, 1, 1, 1,player.alpha);
    //bomb
    sprite_render(bomb.spr, bomb.pos.x, bomb.pos.y, bomb.size.x, bomb.size.y, bomb.texpos.x * bomb.animeno, bomb.texpos.y, bomb.texHW.x, bomb.texHW.y, bomb.texprivot.x, bomb.texprivot.y);
    //PlayerHpBar
    primitive::rect(10, 170, 40, 300, 0, 0, 0, 0, 0, 0);
    primitive::rect(17, 177+284 * (5-playerHP) / 5, 26, 284*playerHP/5, 0, 0, 0, 1, 0, 0);
    //EnemyHpBar
    primitive::rect(1230, 170, 40, 300, 0, 0, 0, 0, 0, 0);
    primitive::rect(1237, 177+ 284 * (8-enemyHP) / 8, 26, 284*enemyHP/8, 0, 0, 0, 0, 1, 0);

}
void SceneGame::deinit()

{
    safe_delete(bomb.spr);
    safe_delete(enemy.spr);
    safe_delete(enemy.spr);
    for (int i = 0; i < 6; i++)
    {
        safe_delete(portal[i].spr);
    }
    safe_delete(player.spr);
    safe_delete(background.spr);
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