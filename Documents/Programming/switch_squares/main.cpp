#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include "allegro5/allegro_image.h"
#include "allegro5/allegro_native_dialog.h"
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "allegro5/allegro_primitives.h"
#include <time.h>
#include <iostream>
#include <fstream>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <typeinfo>
#include <cmath>

void start_up();
void close_down();
bool collision_check();

ALLEGRO_DISPLAY *display = nullptr;
ALLEGRO_DISPLAY_MODE disp_data;
ALLEGRO_MONITOR_INFO monit_info;
ALLEGRO_EVENT_QUEUE *eq = nullptr;
ALLEGRO_TIMER *timer = nullptr;
ALLEGRO_BITMAP *square_one = nullptr;
ALLEGRO_BITMAP *square_two = nullptr;
ALLEGRO_BITMAP *square_three = nullptr;
ALLEGRO_BITMAP *square_one_mouseover = nullptr;
ALLEGRO_BITMAP *square_two_mouseover = nullptr;
ALLEGRO_BITMAP *square_three_mouseover = nullptr;

const int square_size = 200;
const int FPS = 30;

float square_one_x;
float square_one_y;
float square_two_x;
float square_two_y;
float square_three_x;
float square_three_y;

bool mouse_over_one = false;
bool mouse_over_two = false;
bool mouse_over_three = false;

bool redraw = false;
bool quit = false;

void start_up(){
al_init(); // I'm not checking the return value for simplicity.
al_init_image_addon();
al_init_primitives_addon();


al_get_display_mode(al_get_num_display_modes() - 1, &disp_data);
al_get_monitor_info(al_get_num_video_adapters() - 1, &monit_info);

al_set_new_display_flags(ALLEGRO_FULLSCREEN_WINDOW);
//al_set_new_display_flags(ALLEGRO_RESIZABLE);
display = al_create_display(disp_data.width, disp_data.height);


timer = al_create_timer(1.0/FPS);
eq = al_create_event_queue();

al_install_mouse();
al_install_keyboard();

al_register_event_source(eq, al_get_display_event_source(display));
al_register_event_source(eq, al_get_timer_event_source(timer));
al_register_event_source(eq, al_get_mouse_event_source());
al_register_event_source(eq, al_get_keyboard_event_source());

square_one = al_create_bitmap(square_size, square_size);
square_two = al_create_bitmap(square_size, square_size);
square_three = al_create_bitmap(square_size, square_size);
square_one_mouseover = al_create_bitmap(square_size, square_size);
square_two_mouseover = al_create_bitmap(square_size, square_size);
square_three_mouseover = al_create_bitmap(square_size, square_size);

al_set_target_bitmap(square_one);
al_clear_to_color(al_map_rgb(100, 0, 0));
al_set_target_bitmap(square_two);
al_clear_to_color(al_map_rgb(0, 100, 0));
al_set_target_bitmap(square_three);
al_clear_to_color(al_map_rgb(0, 0, 100));
al_set_target_bitmap(square_one_mouseover);
al_clear_to_color(al_map_rgb(255, 0, 0));
al_set_target_bitmap(square_two_mouseover);
al_clear_to_color(al_map_rgb(0, 255, 0));
al_set_target_bitmap(square_three_mouseover);
al_clear_to_color(al_map_rgb(0, 0, 255));

}

bool collision_check(float obj1_x, float obj1_y, float obj1_height, float obj1_width, float obj2_x, float obj2_y, float obj2_height, float obj2_width){
if((obj1_x > obj2_x + obj2_width - 1) || (obj1_y > obj2_y + obj2_height - 1) || (obj2_x > obj1_x + obj1_width - 1) || (obj2_y > obj1_y + obj1_height - 1)){
return false;
}
else {
return true;
}

}


int main(int argc, char **argv){

start_up();

//red
square_one_x = monit_info.x2/2 - (square_size/2);
square_one_y = monit_info.y2/2 - (square_size/2);

//green
square_two_x = monit_info.x2/4 - (square_size/2);
square_two_y = monit_info.y2/2 - (square_size/2);

//blue
square_three_x = monit_info.x2 * .75 - (square_size/2);
square_three_y = monit_info.y2/2 - (square_size/2);

std::cout << disp_data.width << "\n";
std::cout << disp_data.height << "\n";
std::cout << monit_info.x1 << "\n";
std::cout << monit_info.x2 << "\n";
std::cout << monit_info.y1 << "\n";
std::cout << monit_info.y2 << "\n";

/*square_one_x = disp_data.width - (square_size/2);
square_one_y = disp_data.height/2 + square_size;
square_two_x = disp_data.width/1.5 - (square_size/2);
square_two_y = disp_data.height/2 + square_size;
square_three_x = disp_data.width*1.41 - square_size;
square_three_y = disp_data.height/2 + square_size;*/

al_start_timer(timer);

while(!quit){

ALLEGRO_EVENT ev;
al_wait_for_event(eq, &ev);

if(ev.type == ALLEGRO_EVENT_TIMER){
redraw = true;}

if(ev.type == ALLEGRO_EVENT_KEY_DOWN){
switch(ev.keyboard.keycode){
case ALLEGRO_KEY_ESCAPE: {
quit = true;
break;}
}}

if(ev.type == ALLEGRO_EVENT_MOUSE_AXES || ev.type == ALLEGRO_EVENT_MOUSE_ENTER_DISPLAY){
mouse_over_one = collision_check(ev.mouse.x, ev.mouse.y, 0, 0, square_one_x, square_one_y, square_size, square_size);
mouse_over_two = collision_check(ev.mouse.x, ev.mouse.y, 0, 0, square_two_x, square_two_y, square_size, square_size);
mouse_over_three = collision_check(ev.mouse.x, ev.mouse.y, 0, 0, square_three_x, square_three_y, square_size, square_size);
//ev.mouse.x
//ev.mouse.y*/
}


if(redraw && al_is_event_queue_empty(eq)){

redraw = false;

al_set_target_bitmap(al_get_backbuffer(display));
al_clear_to_color(al_map_rgb(100,100,100));

if(mouse_over_one){
al_draw_bitmap(square_one_mouseover, square_one_x, square_one_y, 0);}
else{
al_draw_bitmap(square_one, square_one_x, square_one_y, 0);}

if(mouse_over_two){
al_draw_bitmap(square_two_mouseover, square_two_x, square_two_y, 0);}
else{
al_draw_bitmap(square_two, square_two_x, square_two_y, 0);}

if(mouse_over_three){
al_draw_bitmap(square_three_mouseover, square_three_x, square_three_y, 0);}
else{
al_draw_bitmap(square_three, square_three_x, square_three_y, 0);}


al_flip_display();

}




}
if(display){
al_destroy_display(display);}
if(square_one){
al_destroy_bitmap(square_one);}
if(square_two){
al_destroy_bitmap(square_two);}
if(square_three){
al_destroy_bitmap(square_three);}
if(square_one_mouseover){
al_destroy_bitmap(square_one_mouseover);}
if(square_two_mouseover){
al_destroy_bitmap(square_two_mouseover);}
if(square_three_mouseover){
al_destroy_bitmap(square_three_mouseover);}
if(timer){
al_destroy_timer(timer);}
if(eq){
al_destroy_event_queue(eq);}

return 0;
}
