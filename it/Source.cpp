#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

int rdice = 1;
void cardpick(int& doublecard, int& blockedcard, int& rethrowcard, int& trapcard) {
    int cardnum;
    cardnum = ((rand() % 4) + 1);
    if (cardnum == 1)
        doublecard++;
    if (cardnum == 2)
        blockedcard++;
    if (cardnum == 3)
        rethrowcard++;
    if (cardnum == 4)
        trapcard++;


    printf("%d%d%d%d ", doublecard, blockedcard, rethrowcard, trapcard);
}
void tunnelg(int tunnel[], int n) {

    int t = ((rand() % 6) + 1);
    if (t == 1) {
        tunnel[0] = 56;
        tunnel[1] = 75;
        tunnel[2] = 68;
    }
    if (t == 2) {
        tunnel[0] = 75;
        tunnel[1] = 56;
        tunnel[2] = 68;
    }
    if (t == 3) {
        tunnel[0] = 75;
        tunnel[1] = 68;
        tunnel[2] = 56;
    }
    if (t == 4) {
        tunnel[0] = 68;
        tunnel[1] = 75;
        tunnel[2] = 56;
    }
    if (t == 5) {
        tunnel[0] = 68;
        tunnel[1] = 56;
        tunnel[2] = 75;
    }

    return;

}

int diceroll(int& dicecheck, int& dice , int &rdice) {
    dicecheck = dice;
    

    do {
        dice = ((rand() % 6) + 1);

    } while (dicecheck == dice);


    if (dice == 3)
        rdice =-3;
    else rdice =(dice - 3);
    return rdice;
}

void getcordw(int& corwx, int& corwy, int& pl1,int &dice, int& dicecheck, int &x, bool &wdouble) {
   
    
        x = diceroll(dicecheck, dice, rdice);
     
        pl1 = pl1 + x;
     
    
    corwx = 318 + 59 * ((pl1 - 1) % 9);
    corwy = 731 - 60 * ((pl1 - 1) / 9);


}
void getcordg(int& corgx, int& corgy, int& plg,int &dice, int &dicecheck , int &x , bool &gdouble) {
  
    
        x = diceroll(dicecheck, dice , rdice);
      
        plg = plg + x;
  
    corgx = 790 - 59 * ((plg - 1) % 9);
    corgy = 251 + 60 * ((plg - 1) / 9);

}
void must_init(bool test, const char* description)
{
    if (test) return;

    printf("couldn't initialize %s\n", description);
    exit(1);
}

int main()
{
    int x, y, i,d =1, dice = 2, dicecheck = 1, rdice = 1, doublecard1 = 0, blockedcard1 = 0, rethrowcard1 = 0, trapcard1 = 0
        ,doublecard = 0, blockedcard = 0, rethrowcard = 0, trapcard = 0;
    int pl1 = 1, corw1x = 318, corw1y = 731;
    int plg = 1, corg1x = 790, corg1y = 251;
    int plg2 = 1, corg2x = 790, corg2y = 251;
    int sw1 = 1, sw2 = 1;
    int countn1 = 0, countn2 = 0;
    int fps = 0,fps2 = 0;
    int tunnelpg[3] = { 56,68,75 };
    const int width = 1112;
    const int height = 834;
    const int wicardu = 330;
    const int wicardd = 515;
    const int xmove = 58;
    const int ymove = 60;
    int wpx = 318,wpy=731,gpx = 790, gpy = 251;
    int gameboarda[81] = { 0 };
    int tunnels[6] = { 14, 21, 35, 57, 69, 74 };
    int cards[7] = { 3, 16, 31, 38, 50, 61, 76 };
    for (i = 0; i < 81; i++)
        gameboarda[i] = i + 1;
    char name1[8] = "player1";
    char name2[8] = "player2";
    must_init(al_init(), "allegro");
    must_init(al_install_keyboard(), "keyboard");
    must_init(al_install_mouse(), "mouse");
    must_init(al_init_ttf_addon(), "font addon");
    must_init(al_install_audio(), "audio");
    must_init(al_init_acodec_addon(), "audio codecs");
    must_init(al_reserve_samples(16), "reserve samples");
    al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
    al_set_new_display_option(ALLEGRO_SAMPLES, 8, ALLEGRO_SUGGEST);
    al_set_new_bitmap_flags(ALLEGRO_MIN_LINEAR | ALLEGRO_MAG_LINEAR);
    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 30.0);
    must_init(timer, "timer");

    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
    must_init(queue, "queue");

    ALLEGRO_DISPLAY* disp = al_create_display(width, height);
    must_init(disp, "display");

    ALLEGRO_FONT* font = al_load_ttf_font("cb.ttf",32,0);
    must_init(font, "font");

    must_init(al_init_image_addon(), "image addon");
    ALLEGRO_BITMAP* gameboard = al_load_bitmap("gameboard.png");
    must_init(gameboard, "gameboard");
    ALLEGRO_BITMAP* start = al_load_bitmap("start.png");
    must_init( start , "start");
    ALLEGRO_BITMAP* pause = al_load_bitmap("pause.png");
    must_init(pause, "pause");
    ALLEGRO_BITMAP* startmenu = al_load_bitmap("startmenu.png");
    must_init(startmenu, "startmenu");
    ALLEGRO_BITMAP* graywins = al_load_bitmap("graywins.png");
    must_init(graywins, "graywins");
    ALLEGRO_BITMAP* whitewins = al_load_bitmap("whitewins.png");
    must_init(whitewins, "whitewins");
    ALLEGRO_BITMAP* tut1 = al_load_bitmap("tut1.png");
    must_init(tut1, "tut1");
    ALLEGRO_BITMAP* tut2 = al_load_bitmap("tut2.png");
    must_init(tut2, "tut2");
    ALLEGRO_BITMAP* tut3 = al_load_bitmap("tut3.png");
    must_init(tut3, "tut3");
    ALLEGRO_BITMAP* tut4 = al_load_bitmap("tut4.png");
    must_init(tut4, "tut4");
    ALLEGRO_BITMAP* tut5 = al_load_bitmap("tut5.png");
    must_init(tut5, "tut5");
    ALLEGRO_BITMAP* tut6 = al_load_bitmap("tut6.png");
    must_init(tut6, "tut6");
    ALLEGRO_BITMAP* tut7 = al_load_bitmap("tut7.png");
    must_init(tut7, "tut7");
    ALLEGRO_BITMAP* tut8 = al_load_bitmap("tut8.png");
    must_init(tut8, "tut8");
    ALLEGRO_BITMAP* name = al_load_bitmap("name.png");
    must_init(name, "name");
    ALLEGRO_BITMAP* gray = al_load_bitmap("gray.png");
    must_init(gray, "gray");
    ALLEGRO_BITMAP* white = al_load_bitmap("white.png");
    must_init(white, "white");
    ALLEGRO_SAMPLE* win2 = al_load_sample("win2.wav");
    must_init(win2, "win2");
    ALLEGRO_SAMPLE* card = al_load_sample("card down.wav");
    must_init(card, "card");
    ALLEGRO_SAMPLE* cardslide = al_load_sample("cardslide.wav");
    must_init(cardslide, "cardslide");
    ALLEGRO_SAMPLE* chess = al_load_sample("chess.wav");
    must_init(card, "chess");
    ALLEGRO_SAMPLE* button = al_load_sample("buttons.wav");
    must_init(button, "button");
    ALLEGRO_SAMPLE* zap = al_load_sample("theone.wav");
    must_init(zap, "zap");
    ALLEGRO_SAMPLE* fall = al_load_sample("fall.wav");
    must_init(fall, "fall");
    ALLEGRO_SAMPLE* mousetrap = al_load_sample("mousetrap.wav");
    must_init(mousetrap, "mousetrap");
    ALLEGRO_SAMPLE* invalid = al_load_sample("invalid.wav");
    must_init(invalid, "invalid");
    ALLEGRO_AUDIO_STREAM* music = al_load_audio_stream("music.opus", 2, 2048);
    must_init(music, "music");
    al_set_audio_stream_playmode(music, ALLEGRO_PLAYMODE_LOOP);
   
    ALLEGRO_USTR* str = al_ustr_new("");
    int pos1 = (int)al_ustr_size(str);

    ALLEGRO_USTR* str2 = al_ustr_new("");
    int pos2 = (int)al_ustr_size(str2);

    ALLEGRO_BITMAP* mysha = al_load_bitmap("mysha.png");
    must_init(mysha, "mysha");
    must_init(al_init_primitives_addon(), "primitives");

    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(disp));
    al_register_event_source(queue, al_get_timer_event_source(timer));
    al_register_event_source(queue, al_get_mouse_event_source());

    bool done = false;
    bool butt = false;
    bool redraw = true;
    bool redraw2 = true;
    bool redraw3 = false;
    bool redraw4 = false;
    bool redraw5 = false;
    bool redraw6 = false;
    bool bug = true;
    bool diceroll = false;
    bool turn = false;
    bool turn1 = true;
    bool turn2 = false;
    bool wblocked = false;
    bool gblocked = false;
    bool wtrap = false;
    bool gtrap = false;
    bool wdouble = false;
    bool gdouble = false;
    bool wre = false;
    bool gre = false;
    bool t1 = true;
    bool t2 = true;
    bool redraw51 = false;
    bool mus = false;
    bool sound = true;
    bool bugm = true;
    bool nvalidg = false;
    bool nvalidw = false;
    bool tutorial1 = false;
    bool tutorial2 = false;
    bool tutorial3 = false;
    bool tutorial4 = false;
    bool tutorial5 = false;
    bool tutorial6 = false;
    bool tutorial7 = false;
    bool tutorial8 = false;
    bool doublee = true;
    bool getname = false;
    bool getname1 = true;
    bool ntunnel = true;
    bool ntunnelw = true;
    
    
    tunnelg(tunnelpg, 3);
    ALLEGRO_EVENT event;

    al_start_timer(timer);
    while (1)

    {

        al_wait_for_event(queue, &event);

        switch (event.type)
        {
           

        case ALLEGRO_EVENT_TIMER:
            if (redraw4) {
                 ntunnel = true;
                 ntunnelw = true;
                doublee = true;
                wpx = corw1x;
                wpy = corw1y;
                gpx = corg1x;
                gpy = corg1y;
            
              //game logic
                if(wre && turn1)
                {
                    turn1 = false;
                    turn2 = true;
                    wre = false;
                }
                if (gre && turn2)
                {
                    turn2 = false;
                    turn1 = true;
                    gre = false;
                }
                if (gdouble || wdouble) {
                    doublee = false;
                    if (wdouble && turn1) {
                        pl1 += d;
                        corw1x = 318 + 59 * ((pl1 - 1) % 9);
                        corw1y = 731 - 60 * ((pl1 - 1) / 9);
                        if (pl1 > 0 && pl1 < 82) {
                            if (sound)
                                al_play_sample(chess, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                        }

                        else {
                            if (sound)
                                al_play_sample(invalid, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                            nvalidw = true;
                            pl1 = pl1 - d;
                            corw1x = 318 + 59 * ((pl1 - 1) % 9);
                            corw1y = 731 - 60 * ((pl1 - 1) / 9);

                        }
                        wdouble = false;
                    }
                    else {
                        if (turn2 && gdouble) {
                            plg += d;
                            corg1x = 790 - 59 * ((plg - 1) % 9);
                            corg1y = 251 + 60 * ((plg - 1) / 9);
                            if (plg > 0 && plg < 82) {
                                if (sound)
                                    al_play_sample(chess, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                            }
                            else {
                                if (sound)
                                    al_play_sample(invalid, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                                nvalidg = true;
                                plg = plg - d;
                                corg1x = 790 - 59 * ((plg - 1) % 9);
                                corg1y = 251 + 60 * ((plg - 1) / 9);

                            }
                            gdouble = false;
                        }
                    }
                    wdouble = false;
                    gdouble = false;
                }
               
                if (turn && turn1&& doublee ) {
                    if (plg == 8 && t1 && !wblocked) {
                        plg = tunnelpg[0];
                        if(sound)
                        al_play_sample(zap, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                        corg1x = 790 - 59 * ((plg - 1) % 9);
                        corg1y = 251 + 60 * ((plg - 1) / 9);
                        ntunnel = false;
                         t1 = false;

                    }
                    if (plg == tunnelpg[0] && t1 && !wblocked) {
                        plg = 8;
                        if (sound)
                        al_play_sample(zap, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                        corg1x = 790 - 59 * ((plg - 1) % 9);
                        corg1y = 251 + 60 * ((plg - 1) / 9);
                        ntunnel = false;
                        t1 = false;

                    }
                    if (plg == 13 && t1 && !wblocked) {
                        plg = tunnelpg[1];
                        if (sound)
                        al_play_sample(zap, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                        corg1x = 790 - 59 * ((plg - 1) % 9);
                        corg1y = 251 + 60 * ((plg - 1) / 9);
                        ntunnel = false;
                        t1 = false;
                    }
                    if (plg == tunnelpg[1] && t1 && !wblocked) {
                        plg = 13;
                        if (sound)
                        al_play_sample(zap, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                        corg1x = 790 - 59 * ((plg - 1) % 9);
                        corg1y = 251 + 60 * ((plg - 1) / 9);
                        ntunnel = false;
                        t1 = false;

                    }
                    if (plg == 25 && t1 && !wblocked) {
                        plg = tunnelpg[2];
                        if (sound)
                        al_play_sample(zap, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                        corg1x = 790 - 59 * ((plg - 1) % 9);
                        corg1y = 251 + 60 * ((plg - 1) / 9);
                        ntunnel = false;
                        t1 = false;

                    }
                    if (plg == tunnelpg[2] && t1 && !wblocked) {
                        plg = 25;
                        if (sound)
                        al_play_sample(zap, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                        corg1x = 790 - 59 * ((plg - 1) % 9);
                        corg1y = 251 + 60 * ((plg - 1) / 9);
                        ntunnel = false;
                        t1 = false;

                    }
                    if (pl1 == 82 - plg) {
                        if (sound)
                            al_play_sample(fall, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                        plg = 1;
                        corg1x = 790 - 59 * ((plg - 1) % 9);
                        corg1y = 251 + 60 * ((plg - 1) / 9);
                        ntunnel = false;

                    }
                    if (wtrap && sound)
                        al_play_sample(mousetrap, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                    if (ntunnel && !wtrap) {
                        getcordg(corg1x, corg1y, plg,dice, dicecheck,d,gdouble);
                        if (plg > 0 && plg < 82) {
                            if (sound)
                                al_play_sample(chess, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                        }
                        else {
                            if (sound)
                                al_play_sample(invalid, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                            nvalidg = true;
                            plg = plg - d;
                            corg1x = 790 - 59 * ((plg - 1) % 9);
                            corg1y = 251 + 60 * ((plg - 1) / 9);

                        }
                        
                        gdouble = false;
                        if (plg == 6 || plg == 21 || plg == 32 || plg == 44 || plg == 51 || plg == 66 || plg == 79) {

                            cardpick(doublecard, blockedcard, rethrowcard, trapcard);
                            if (sound)
                            al_play_sample(card, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                        }
                         t1 = true;
                     
                    }
                    wtrap = false;
                    wblocked = false;
                  
                    turn = false;
                    turn1 = false;
                    turn2 = true;
                }
                if (turn && turn2 && doublee) {
                    if (pl1 == 82 - tunnelpg[0] && t2 && !gblocked) {
                        pl1 = 57;
                        if (sound)
                        al_play_sample(zap, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                        corw1x = 318 + 59 * ((pl1 - 1) % 9);
                        corw1y = 731 - 60 * ((pl1 - 1) / 9);

                        ntunnelw = false;
                        t2 = false;
                    }
                    if (pl1 == 57 && t2 && !gblocked) {
                        pl1 = 82 - tunnelpg[0];
                        if (sound)
                        al_play_sample(zap, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                        corw1x = 318 + 59 * ((pl1 - 1) % 9);
                        corw1y = 731 - 60 * ((pl1 - 1) / 9);
                        ntunnelw = false;
                        t2 = false;
                    }
                    if (pl1 == 82 - tunnelpg[1] && t2 && !gblocked) {
                        pl1 = 69;
                        if (sound)
                        al_play_sample(zap, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                        corw1x = 318 + 59 * ((pl1 - 1) % 9);
                        corw1y = 731 - 60 * ((pl1 - 1) / 9);
                        ntunnelw = false;
                        t2 = false;

                    }
                    if (pl1 == 69 && t2 && !gblocked) {
                        pl1 = 82 - tunnelpg[1];
                        if (sound)
                        al_play_sample(zap, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                        corw1x = 318 + 59 * ((pl1 - 1) % 9);
                        corw1y = 731 - 60 * ((pl1 - 1) / 9);
                        ntunnelw = false;
                        t2 = false;

                    }
                    if (pl1 == 82 - tunnelpg[2] && t2 && !gblocked) {
                        pl1 = 74;
                        if (sound)
                        al_play_sample(zap, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                        corw1x = 318 + 59 * ((pl1 - 1) % 9);
                        corw1y = 731 - 60 * ((pl1 - 1) / 9);
                        ntunnelw = false;
                        t2 = false;

                    }
                    if (pl1 == 74 && t2 && !gblocked) {
                        pl1 = 82 - tunnelpg[2];
                        if (sound)
                        al_play_sample(zap, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                        corw1x = 318 + 59 * ((pl1 - 1) % 9);
                        corw1y = 731 - 60 * ((pl1 - 1) / 9);
                        ntunnelw = false;
                        t2 = false;

                    }
              
                    if (pl1 == 82 - plg) {
                        if (sound)
                            al_play_sample(fall, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                        pl1 = 1;
                        corw1x = 318 + 59 * ((pl1 - 1) % 9);
                        corw1y = 731 - 60 * ((pl1 - 1) / 9);
                        ntunnelw = false;

                    }
                    if (gtrap && sound)
                        al_play_sample(mousetrap, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                    if (ntunnelw && !gtrap) {
                        
                        getcordw(corw1x, corw1y, pl1,dice, dicecheck, d,wdouble);
                        if (pl1 > 0 && pl1 < 82) {
                            if (sound)
                                al_play_sample(chess, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                        }
                      
                        else {
                            if (sound)
                                al_play_sample(invalid, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                            nvalidw = true;
                        pl1 = pl1 - d;
                        corw1x = 318 + 59 * ((pl1 - 1) % 9);
                        corw1y = 731 - 60 * ((pl1 - 1) / 9);
                     
                        }
                        wdouble = false;
                        if (pl1 == 16 || pl1 == 3 || pl1 == 31 || pl1 == 38 || pl1 == 50 || pl1 == 61 || pl1 == 76) {
                            cardpick(doublecard1, blockedcard1, rethrowcard1, trapcard1);
                            if (sound)
                            al_play_sample(card, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                        }
                        t2 = true;
                   
                   
                    }
                    gtrap = false;
                    gblocked = false;

              

                    turn = false;
                    turn2 = false;
                    turn1 = true;
                }
                if (corw1x == 554 && corw1y == 491)
                    sw1 = 0;
                if (corg1x == 554 && corg1y == 491)
                    sw2 = 0;

                if (sw1 == 0) {
                    redraw6 = true;
                    redraw51 = true;
                    redraw4 = false;
                }
                if (sw2 == 0) {
                    redraw5 = true;
                    redraw51 = true;
                    redraw4 = false;
                }
               
            
            }
               
            
         
            redraw = true;
            break;

        case  ALLEGRO_EVENT_KEY_CHAR:
            if (event.keyboard.keycode == ALLEGRO_KEY_ENTER && redraw2) {
                if (sound)
                al_play_sample(button, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                redraw2 = false;
                butt = true;
            }
            //tutorial right
            if (event.keyboard.keycode == ALLEGRO_KEY_RIGHT && tutorial8)
            {
                if (sound)
                    al_play_sample(button, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                bug = true;
                redraw = true;
                tutorial8 = false;

            }
            if (event.keyboard.keycode == ALLEGRO_KEY_RIGHT && tutorial7)
            {
                if (sound)
                    al_play_sample(button, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
             
                tutorial8 = true;
                tutorial7 = false;
            }
            if (event.keyboard.keycode == ALLEGRO_KEY_RIGHT && tutorial6)
            {
                if (sound)
                    al_play_sample(button, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                tutorial7 = true;
                tutorial6 = false;
            }
            if (event.keyboard.keycode == ALLEGRO_KEY_RIGHT && tutorial5)
            {
                if (sound)
                    al_play_sample(button, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                tutorial6 = true;
                tutorial5 = false;
            }
            if (event.keyboard.keycode == ALLEGRO_KEY_RIGHT && tutorial4)
            {
                if (sound)
                    al_play_sample(button, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                tutorial5 = true;
                tutorial4 = false;
            }
            if (event.keyboard.keycode == ALLEGRO_KEY_RIGHT && tutorial3)
            {
                if (sound)
                    al_play_sample(button, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                tutorial4 = true;
                tutorial3 = false;
            }
            if (event.keyboard.keycode == ALLEGRO_KEY_RIGHT && tutorial2)
            {
                if (sound)
                    al_play_sample(button, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                tutorial3 = true;
                tutorial2 = false;
            }
            if (event.keyboard.keycode == ALLEGRO_KEY_RIGHT && tutorial1)
            {
                if (sound)
                    al_play_sample(button, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                tutorial2 = true;
                tutorial1 = false;
            }
            //tutorial left
            if (event.keyboard.keycode == ALLEGRO_KEY_LEFT && tutorial2)
            {
                if (sound)
                    al_play_sample(button, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);

                tutorial2 = false;
                tutorial1 = true;
            }
            if (event.keyboard.keycode == ALLEGRO_KEY_LEFT && tutorial3)
            {
                if (sound)
                    al_play_sample(button, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                tutorial3 = false;
                tutorial2 = true;
            }
            if (event.keyboard.keycode == ALLEGRO_KEY_LEFT && tutorial4)
            {
                if (sound)
                    al_play_sample(button, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                tutorial4 = false;
                tutorial3 = true;
            }
            if (event.keyboard.keycode == ALLEGRO_KEY_LEFT && tutorial5)
            {
                if (sound)
                    al_play_sample(button, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                tutorial5 = false;
                tutorial4 = true;
            }
            if (event.keyboard.keycode == ALLEGRO_KEY_LEFT && tutorial6)
            {
                if (sound)
                    al_play_sample(button, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                tutorial6 = false;
                tutorial5 = true;
            }
            if (event.keyboard.keycode == ALLEGRO_KEY_LEFT && tutorial7)
            {
                if (sound)
                    al_play_sample(button, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                tutorial7 = false;
                tutorial6 = true;
            }
            if (event.keyboard.keycode == ALLEGRO_KEY_LEFT && tutorial8)
            {
                if (sound)
                    al_play_sample(button, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                tutorial8 = false;
                tutorial7 = true;
            }

     
     
            if (event.keyboard.keycode == ALLEGRO_KEY_R)
                turn = true;
            if (event.keyboard.keycode == ALLEGRO_KEY_P && redraw4)
            {
                redraw3 = true;
                redraw4 = false;
            }
           
            if ((event.keyboard.unichar >= 32 || event.keyboard.keycode == ALLEGRO_KEY_ENTER ) && getname)
            {
                if (event.keyboard.keycode == ALLEGRO_KEY_ENTER || countn1>5 || countn2>4) {
                    if (getname1) {
                        getname1 = false;
                        countn1 = 0;
                    }
                   
                    else {
                        
                        getname = false;
                        redraw4 = true;
                        bug = false;
                    }
                 
                }
                if (getname1) {
                    countn1++;
                    pos1 += al_ustr_append_chr(str, event.keyboard.unichar);
                }
                else if(event.keyboard.keycode != ALLEGRO_KEY_ENTER ){
                    countn2++;
                    pos2 += al_ustr_append_chr(str2, event.keyboard.unichar);
                }
            }
            else if (event.keyboard.keycode == ALLEGRO_KEY_BACKSPACE && getname)
            {
                if (al_ustr_prev(str, &pos1) && getname1) {
                    countn1--;
                    al_ustr_truncate(str, pos1);
                }
                else if (al_ustr_prev(str2, &pos2)) {
                    countn2--;
                    al_ustr_truncate(str2, pos2);
                }
            }

            break;

            if (event.keyboard.keycode != ALLEGRO_KEY_ESCAPE)
                break;
        case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
            x = event.mouse.x;
            y = event.mouse.y;
            //start menu
            if (x > 137 && x < 500 && y < 330 && y>195 &&  bug)
            {
                if (sound)
                al_play_sample(button, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                mus = true;
                al_attach_audio_stream_to_mixer(music, al_get_default_mixer());
               
                FILE* outf;
                outf = fopen("savegame.txt", "rt");
                if (outf == NULL)
                    printf("cant open file");
                
                fscanf(outf, "%d", &d);
                fscanf(outf, "%d", &pl1);
                fscanf(outf, "%d", &plg);
                fscanf(outf, "%d", &corw1x);
                fscanf(outf, "%d", &corw1y);
                fscanf(outf, "%d", &corg1x);
                fscanf(outf, "%d", &corg1y);
                fscanf(outf, "%d", &trapcard);
                fscanf(outf, "%d", &rethrowcard);
                fscanf(outf, "%d", &doublecard);
                fscanf(outf, "%d", &blockedcard);
                fscanf(outf, "%d", &trapcard1);
                fscanf(outf, "%d", &rethrowcard1);
                fscanf(outf, "%d", &doublecard1);
                fscanf(outf, "%d", &blockedcard1);
                fscanf(outf, "%s", &*str);
                fscanf(outf, "%s", &str2);


                fclose(outf);
                redraw4 = true;
                bug = false;
                
            }
            if (x > 137 && x < 500 && y < 518 && y>375 &&  bug)
            {
                if (sound)
                al_play_sample(button, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                mus = true;
                al_attach_audio_stream_to_mixer(music, al_get_default_mixer());

                getname = true;

            }

            if (x > 16 && x < 98 && y < 822&& y>738 &&  bug)
            {
                if (sound)
                    al_play_sample(button, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
              

                tutorial1 = true;
                bug = false;

            }
            if (x > 137 && x < 500 && y < 710 && y>565 && bug) {
 
                if (sound)
                al_play_sample(button, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);

                done = true;
            }
            //tutorial
            if (x > 1005 && x < 1080 && y < 753 && y>706 && tutorial8)
            {
                if (sound)
                    al_play_sample(button, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                bug = true;
                redraw = true;
                tutorial8 = false;


            }
            if (x > 1005 && x < 1080 && y < 753 && y>706 && tutorial7)
            {
                if (sound)
                    al_play_sample(button, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);

                tutorial8 = true;
                tutorial7 = false;


            }
            if (x > 1005 && x < 1080 && y < 753 && y>706 && tutorial6)
            {
                if (sound)
                    al_play_sample(button, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);

                tutorial7 = true;
                tutorial6 = false;


            }
            if (x > 1005 && x < 1080 && y < 753 && y>706 && tutorial5)
            {
                if (sound)
                    al_play_sample(button, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);

                tutorial6 = true;
                tutorial5 = false;


            }
            if (x > 1005 && x < 1080 && y < 753 && y>706 && tutorial4)
            {
                if (sound)
                    al_play_sample(button, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);

                tutorial5 = true;
                tutorial4 = false;


            }
            if (x > 1005 && x < 1080 && y < 753 && y>706 && tutorial3)
            {
                if (sound)
                    al_play_sample(button, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);

                tutorial4 = true;
                tutorial3 = false;


            }
            if (x > 1005 && x < 1080 && y < 753 && y>706 && tutorial2)
            {
                if (sound)
                    al_play_sample(button, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);

                tutorial3 = true;
                tutorial2 = false;


            }
            if (x > 1005 && x < 1080 && y < 753 && y>706  && tutorial1)
            {
                if (sound)
                    al_play_sample(button, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);

                tutorial2 = true;
                tutorial1 = false;
               

            }
            //tutorial

         
            if (x > 40 && x < 115 && y < 753 && y>706 && tutorial2)
            {
                if (sound)
                    al_play_sample(button, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);

                tutorial2 = false;
                tutorial1 = true;


            }
            if (x > 40 && x < 115 && y < 753 && y>706 && tutorial3)
            {
                if (sound)
                    al_play_sample(button, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);

                tutorial3 = false;
                tutorial2 = true;


            }

            if (x > 40 && x < 115 && y < 753 && y>706 && tutorial4)
            {
                if (sound)
                    al_play_sample(button, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);

                tutorial4 = false;
                tutorial3 = true;


            }
            if (x > 40 && x < 115 && y < 753 && y>706 && tutorial5)
            {
                if (sound)
                    al_play_sample(button, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);

                tutorial5 = false;
                tutorial4 = true;


            }
            if (x > 40 && x < 115 && y < 753 && y>706 && tutorial6)
            {
                if (sound)
                    al_play_sample(button, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);

                tutorial6 = false;
                tutorial5 = true;


            }
            if (x > 40 && x < 115 && y < 753 && y>706 && tutorial7)
            {
                if (sound)
                    al_play_sample(button, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);

                tutorial7 = false;
                tutorial6 = true;


            }
            if (x > 40 && x < 115 && y < 753 && y>706 && tutorial8)
            {
                if (sound)
                    al_play_sample(button, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);

                tutorial8 = false;
                tutorial7 = true;

            }
            //pause menu
           
            if (x > 267 && x <343 && y> 205 && y <350 && redraw3) {
           
                if (sound)
                    sound = false;
                else sound = true;
            }
            if (x > 770 && x < 845 && y> 205 && y < 350 && redraw3) {
            
                if (mus)
                    mus = false;
                else mus = true;
                bugm = true;
                
            }
           if ( x > 375 && x <735 && y > 205 && y <350 && redraw3)
           {
               if (sound)
               al_play_sample(button, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
               redraw3 = false;
               redraw4 = true;
           }
           if (x > 375 && x < 735 && y > 395 && y < 540 && redraw3)
           {
               if (sound)
               al_play_sample(button, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
               d = 1, dice = 2, dicecheck = 1, rdice = 1, doublecard1 = 0, blockedcard1 = 0, rethrowcard1 = 0, trapcard1 = 0
                   , doublecard = 0, blockedcard = 0, rethrowcard = 0, trapcard = 0;
               pl1 = 1, corw1x = 318, corw1y = 731;
           
               plg = 1, corg1x = 790, corg1y = 251;
            
               redraw3 = false;
               redraw4 = true;
           }
           //dice

           if (x > 512 && x < 600 && y > 48 && y < 137 && redraw4)
           {
               if (sound)
               al_play_sample(button, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
               turn = true;
           }

           //cards
           if (x > 9 && x < 125 && y > 320 && y < 496 && redraw4 && blockedcard1)
           {
               
               gblocked = true;
               blockedcard1--;
               if (sound)
               al_play_sample(cardslide, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
           }
            

           if (x > 9 && x < 125 && y > 504 && y < 675 && redraw4 && trapcard1)
           {
               wtrap = true;
               trapcard1--;
               if (sound)
               al_play_sample(cardslide, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
           }

           if (x > 133 && x < 247  && y > 504 && y < 675 && redraw4 && doublecard1)
           {
               wdouble = true;
               doublecard1--;
               if (sound)
               al_play_sample(cardslide, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
           }
           if (x > 133 && x < 247 && y > 320 && y < 496 && redraw4 && rethrowcard1)
           {
               wre = true;
               rethrowcard1--;
               if (sound)
               al_play_sample(cardslide, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
           }
           if (x > 990 && x < 1105 && y > 504 && y < 675 && redraw4 && doublecard)
           {
               gdouble = true;
               doublecard--;
               if (sound)
               al_play_sample(cardslide, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
           }

           if (x > 866 && x < 983 && y > 320 && y < 496 && redraw4 && blockedcard)
           {
               wblocked = true;
              
               blockedcard--;
               if (sound)
               al_play_sample(cardslide, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
           }

           if (x > 990 && x < 1105 && y > 320 && y < 496 && redraw4 && rethrowcard)
           {
               gre = true;
               rethrowcard--;
               if (sound)
               al_play_sample(cardslide, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
           }


           if (x > 866 && x < 983 && y > 504 && y < 675 && redraw4 && trapcard)
           {
               gtrap = true;
               trapcard--;
               if (sound)
               al_play_sample(cardslide, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
           }

       

           if (x > 375 && x < 735 && y > 585 && y < 735 && redraw3)
           {

               done = true;
           }

         
            break;

        case ALLEGRO_EVENT_DISPLAY_CLOSE:
            done = true;
            break;
        }
        if (done) {
            FILE* inputf;
            inputf = fopen("savegame.txt", "w");
            if (inputf == NULL)
                printf("cant open file");
            fprintf(inputf, "%d\n", d);
            fprintf(inputf, "%d\n", pl1);
            fprintf(inputf, "%d\n", plg);
            fprintf(inputf, "%d\n", corw1x);
            fprintf(inputf, "%d\n", corw1y);
            fprintf(inputf, "%d\n", corg1x);
            fprintf(inputf, "%d\n", corg1y);
            fprintf(inputf, "%d\n", trapcard);
            fprintf(inputf, "%d\n", rethrowcard);
            fprintf(inputf, "%d\n", doublecard);
            fprintf(inputf, "%d\n", blockedcard);
            fprintf(inputf, "%d\n", trapcard1);
            fprintf(inputf, "%d\n", rethrowcard1);
            fprintf(inputf, "%d\n", doublecard1);
            fprintf(inputf, "%d\n", blockedcard1);
            fprintf(inputf, "%s\n", str);
            fprintf(inputf, "%s\n", str2);
            fclose(inputf);

            break;
        }
      
        //rendering

        if (redraw2 && al_is_event_queue_empty(queue))
        {
            al_clear_to_color(al_map_rgb(0, 0, 0));

            al_draw_bitmap(start, 0, 0, 0);
            al_draw_text(font, al_map_rgb(0, 0, 0), 75, 405, 0, "PRESS ENTER TO PLAY");
            al_draw_text(font, al_map_rgb(255, 255, 255), 70, 400, 0, "PRESS ENTER TO PLAY");
            al_flip_display();

        
  }
        if (redraw && butt  && bug)
        {
            al_clear_to_color(al_map_rgb(0, 0, 0));

            al_draw_bitmap(startmenu, 0, 0, 0);

            
        
            al_flip_display();

            redraw = false;
        }

        if (tutorial1) {
            al_clear_to_color(al_map_rgb(0, 0, 0));

            al_draw_bitmap(tut1, 0, 0, 0);

            al_flip_display();

        }
        if (tutorial2) {
            al_clear_to_color(al_map_rgb(0, 0, 0));

            al_draw_bitmap(tut2, 0, 0, 0);

            al_flip_display();

        }
        if (tutorial3) {
            al_clear_to_color(al_map_rgb(0, 0, 0));

            al_draw_bitmap(tut3, 0, 0, 0);



            al_flip_display();

        }
        if (tutorial4) {
            al_clear_to_color(al_map_rgb(0, 0, 0));

            al_draw_bitmap(tut4, 0, 0, 0);



            al_flip_display();

        }
        if (tutorial5) {
            al_clear_to_color(al_map_rgb(0, 0, 0));

            al_draw_bitmap(tut5, 0, 0, 0);



            al_flip_display();

        }
        if (tutorial6) {
            al_clear_to_color(al_map_rgb(0, 0, 0));

            al_draw_bitmap(tut6, 0, 0, 0);



            al_flip_display();

        }
        if (tutorial7) {
            al_clear_to_color(al_map_rgb(0, 0, 0));

            al_draw_bitmap(tut7, 0, 0, 0);



            al_flip_display();

        }
        if (tutorial8) {
            al_clear_to_color(al_map_rgb(0, 0, 0));

            al_draw_bitmap(tut8, 0, 0, 0);



            al_flip_display();

        }
        if (getname) {
            al_clear_to_color(al_map_rgb(0, 0, 0));

            al_draw_bitmap(name, 0, 0, 0);
            al_draw_text(font, al_map_rgb(0, 0, 0), 425, 115, 0, "type your name");
            al_draw_text(font, al_map_rgb(255, 255, 255), 420, 110, 0, "type your name");
          
            al_draw_ustr(font, al_map_rgb(107, 58, 0), 170, 255,0, str);
            al_draw_ustr(font, al_map_rgb(107, 58, 0), 765, 255, 0, str2);


            al_flip_display();

        }
        if (redraw4)                                                    
        {
            al_clear_to_color(al_map_rgb(0, 0, 0));

            al_draw_bitmap(gameboard, 0, 0, 0);
            if (nvalidg) {
                al_draw_text(font, al_map_rgb(255, 255, 255), corg1x - 26, corg1y - 50, 0, "invalid");
                nvalidg = false;
            }
            if (nvalidw) {
                al_draw_text(font, al_map_rgb(255, 255, 255), corw1x - 26, corw1y - 50, 0, "invalid");
                nvalidw = false;
            }
           if((wpx == corw1x && wpy == corw1y) || !ntunnelw)
            al_draw_bitmap(white, wpx - 26, wpy - 28, 0);
           else while (wpx != corw1x || wpy != corw1y) {
               if (wpx < corw1x && fps2 % 10 == 0)
                   wpx= wpx + 59;
               else if (wpx > corw1x && fps2 % 10 == 0)
                   wpx= wpx - 59;
               if (wpy < corw1y && fps2 % 10 == 0)
                   wpy= wpy + 60;
               else if (wpy > corw1y && fps2 % 10 == 0)
                   wpy=wpy - 60;
               al_draw_bitmap(white, wpx - 26, wpy - 28, 0);
           }
           if ((gpx == corg1x && gpy == corg1y) || !ntunnel)
               al_draw_bitmap(gray, gpx - 26, gpy - 28, 0);
           else while (gpx != corg1x || gpy != corg1y) {
               fps++;
               if (gpx < corg1x && fps% 10 == 0)
                   gpx = gpx + 59;
               else if (gpx > corg1x && fps% 10 == 0)
                   gpx = gpx - 59;
               if (gpy < corg1y && fps2% 10 == 0)
                   gpy = gpy + 60;
               else if (gpy > corg1y && fps% 10 == 0)
                   gpy = gpy - 60;
               al_draw_bitmap(gray, gpx - 26, gpy - 28, 0);
           }
         
            al_draw_ustr(font, al_map_rgb(107, 58, 0), 70, 245, 0, str);
            al_draw_ustr(font, al_map_rgb(107, 58, 0), 900, 245, 0, str2);
         
            al_draw_text(font, al_map_rgb(255, 255, 255), 0, 800, 0, "press p to pause");
            if(d>0)
            al_draw_textf(font, al_map_rgb(109, 57, 3), 545, 80, 0, "%d",d);
            else
            al_draw_textf(font, al_map_rgb(109, 57, 3), 530, 80, 0, "%d", d);
            al_draw_textf(font, al_map_rgb(255, 255, 255),15, wicardu, 0, "x%d", blockedcard1);
            al_draw_textf(font, al_map_rgb(255, 255, 255), 139, wicardu, 0, "x%d", rethrowcard1);
            al_draw_textf(font, al_map_rgb(255, 255, 255), 996, wicardu, 0, "x%d", rethrowcard);
            al_draw_textf(font, al_map_rgb(255, 255, 255),875 , wicardu, 0, "x%d", blockedcard);
            al_draw_textf(font, al_map_rgb(255, 255, 255), 15, wicardd, 0, "x%d", trapcard1);
            al_draw_textf(font, al_map_rgb(255, 255, 255), 139, wicardd, 0, "x%d", doublecard1);
            al_draw_textf(font, al_map_rgb(255, 255, 255), 996, wicardd, 0, "x%d", doublecard);
            al_draw_textf(font, al_map_rgb(255, 255, 255), 875, wicardd, 0, "x%d", trapcard);

            al_flip_display();

            
        }
        if (redraw3 && !bug && !redraw2)
        {
            al_clear_to_color(al_map_rgb(0, 0, 0));

            al_draw_bitmap(pause, 0, 0, 0);
            if(!sound)
            al_draw_line(280, 263, 326, 221, al_map_rgb(107, 58, 0), 5);
            if (!mus)
            al_draw_line(784, 263, 828, 221, al_map_rgb(107, 58, 0), 5);
            al_flip_display();


        }
        if (redraw5)
        {
           
          
                al_clear_to_color(al_map_rgb(0, 0, 0));

                al_draw_bitmap(graywins, 0, 0, 0);
                al_draw_ustr(font, al_map_rgb(255, 255, 255), 340, 90, 0, str2);
                al_draw_text(font, al_map_rgb(255, 255, 255), 380, 120, 0, "WINS");
                al_flip_display();
              
         }
        if ( redraw51 ) {
            al_detach_audio_stream(music);
            if (sound)
            al_play_sample(win2, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
            redraw51 = false;
        }
        if (redraw6)
         {
                al_clear_to_color(al_map_rgb(0, 0, 0));

                al_draw_bitmap(whitewins, 0, 0, 0);
                al_draw_ustr(font, al_map_rgb(255, 255, 255), 340, 90, 0, str);
                al_draw_text(font, al_map_rgb(255, 255, 255), 380, 120, 0, "WINS");
                al_flip_display();
         }
        
        if(!mus)
            al_detach_audio_stream(music);
        else if (bugm) {
            al_attach_audio_stream_to_mixer(music, al_get_default_mixer());
            bugm = false;
        }
    }
    al_destroy_audio_stream(music);
    al_destroy_sample(win2);
    al_destroy_bitmap(mysha);
    al_destroy_bitmap(gameboard);
    al_destroy_font(font);
    al_destroy_display(disp);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);

    return 0;
}