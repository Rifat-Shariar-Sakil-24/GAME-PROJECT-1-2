
#include<iostream>
#include<iostream>
#include<fstream>
#include<string>
#include<map>
#include<vector>
#include<set>
#include<algorithm>
#include <limits>
#include "iGraphics.h"

using namespace std;


#define screenwidth 1200
#define screenheight 780
#define function_speed 20
#define total_brick 60
#define left_par 0
#define right_par 0
#define bottom_par 0
#define brick_shuru_y 80
#define brick_width  100
#define brick_height  30
#define brick_col 5
#define brick_row 12
#define eps 0.0001
#define PI acos(-1)

struct brick_sructure
{
	double brick_x;
	double brick_y;


	double line_top_left[2];
	double line_top_right[2];
	double line_bottom_right[2];
	double line_bottom_left[2];

	bool brick_show = true;

	// variables to control effects
	bool hasEffect = false;
	double effectX, effectY;
	bool effectShow = false;
	double effectDy;
	int effectIndex = rand() % 6;
	bool effectNotUsed = true;
	bool alive = true;

};

bool effectPause = false;

brick_sructure brick[total_brick];



int brick_r = 82;
int brick_g = 82;
int brick_b = 82;



int line_r = 0;
int line_g = 0;
int line_b = 0;



double ang_dx, ang_dy;

int bgIndex = 0;

char bg[1][20] = { "image\\bgupdate.bmp" };
char life[4][20] = { "life\\life3.bmp", "life\\life2.bmp", "life\\life1.bmp", "life\\gameOver.bmp" };
char boat[1][30] = { "image\\boatupdate.bmp" };

// effects
char effect[6][30] = { "image\\monster1.bmp", "image\\monster2.bmp", "image\\monster3.bmp", "image\\monster4.bmp", "image\\monster5.bmp", "image\\monster6.bmp" };

/*boat*/
double boat_image_x = 600 - 96;
double boat_image_y = 625;

double boat_image_movement_x = boat_image_x;
double boat_image_movement_y = boat_image_y;

double boat_bottom_left_main_x = 600 - 95;
double boat_bottom_right_main_x = 600 + 95;
double boat_bottom_main_y = 625;

double boat_bottom_left_x = boat_bottom_left_main_x;
double boat_bottom_right_x = boat_bottom_right_main_x;

double boat_bottom_y = boat_bottom_main_y;
double boat_bottom_length = boat_bottom_right_x - boat_bottom_left_x; // = 190;
double boat_keyboard_dx = 20;




/*ball*/
double main_ball_radius = 20;
double ball_radius = main_ball_radius;
double ball_x = boat_bottom_left_x + (boat_bottom_length / 2);
double ball_y = boat_bottom_y - ball_radius;

double ball_main_dx = -7;
double ball_main_dy = -13;

double main_velocity = 10;
double main_angle = 30;
double  velocity = main_velocity;
double angle = main_angle;
double ball_dx = ball_main_dx;
double ball_dy = ball_main_dy;

bool ball_movement_on = false;
bool direction_change_on_colusion = false;




/*Music*/
bool musicon = false;


/*variables for exact movement for the ball in each direction*/
bool ball_hit_the_boat = 0;
bool bottom_par_or_boat_touched = 0;
double ball_exact_dy;



/*added functions*/
void background_image_set();
void boat_image_set();
void drawing_brick_rectangle();
void drawing_brick_lines();
void drawing_ball();
void right_key_movement();
void left_key_movement();
void brick_coordination_set();
void ball_movement_change();
void ball_movement_left_under_boat();
void ball_movement_right_under_boat();
void new_start();
void ball_touched_boat();
void ball_right_under_boat();
void collision_free_ball_movement_pos_x_axis();
void collision_free_ball_movement_neg_x_axis();




int brick_collision();
bool game_over();
bool check_right_par_cross();
bool check_left_par_cross();
bool angular_collision_detection(double xx, double yy, double nn, int sp, int sn, int cc);
bool upper_and_lower_surface_collision_detection(int ii);
bool left_and_right_surface_collision_detection(int ii);



bool game_sesh = false;

int screen = 1;

double screen2_all_x1 = 409;
double screen2_all_x2 = 806;
double screen2_newgame_y1 = 489;
double screen2_newgame_y2 = 526;
double screen2_leaderboard_y1 = 431;
double screen2_leaderboard_y2 = 468;
double screen2_howtoplay_y1 = 374;
double screen2_howtoplay_y2 = 411;
double screen2_credits_y1 = 317;
double screen2_credits_y2 = 354;
double screen2_exit_y1 = 260;
double screen2_exit_y2 = 297;


double credit_to_home_center_x = 98;
double credit_to_home_center_y = 780 - 692;
double home_radius = 38;

double all_home_center_x = 98;
double all_home_center_y = 780 - 692;
double all_home_radius = 38;

double all_right_center_x = 1145 - 38;
double all_right_center_y = 780 - 692;
double all_right_radius = 39;


double all_left_center_x = 1036 - 38;
double all_left_center_y = 780 - 692;
double all_left_radius = 39;

double game_options_x1 = 25;
double game_options_x2 = 76;
double game_options_y1 = 780 - 77;
double game_options_y2 = 780 - 26;


double game_pause_home_center_x = 497 - 38;
double game_pause_home_center_y = 780 - 548;
double game_pause_home_radius = 39;



double game_pause_resume_center_x = 633 - 38;
double game_pause_resume_center_y = 780 - 548;
double game_pause_resume_radius = 39;



double game_pause_retry_center_x = 771 - 38;
double game_pause_retry_center_y = 780 - 548;
double game_pause_retry_radius = 39;



double game_pause_monster_center_x = 633 - 38;
double game_pause_monster_center_y = 780 - 653;
double game_pause_monster_radius = 39;



double all_left_center_x_mons = 1029;
double all_left_center_y_mons = 780 - 692;
double all_left_radius_mons = 39;


double game_over_restart_center_x = 664;
double game_over_restart_center_y = 781 - 404;
double game_over_restart_radius = 39.5;

double game_over_home_center_x = 538;
double game_over_home_center_y = 780 - 404;
double game_over_home_radius = 39.5;


int main_game_screen = 0;


string name, profile_name;
char name_char[100];
int name_ind = 0;


long long score = 0;
char score_char[10];

long long total_vanished_brick = 0;


long long congo = 0;
bool game_win = 0;
bool boat_effect_sound = false;

bool main_music_on = true;

void start_music()
{
	//if (screen==2) Playsound("music\\homescreen.wav", NULL, SND_LOOP | SND_ASYNC);
	if (main_game_screen)PlaySound(0, 0, 0);


}

void brick_vanish_sound()
{
	PlaySound("music\\ballbrick.wav", NULL, SND_ASYNC);
}



void iDraw()
{


	iClear();

	if (main_game_screen)
	{
		if (main_game_screen < 3 || main_game_screen>6)
		{

			switch (main_game_screen)
			{
			case 1: iShowBMP(0, 0, "image//main_game_screen1.bmp");
				break;
			case 2: iShowBMP(0, 0, "image//main_game_screen2.bmp");
				break;
			case 7: iShowBMP(0, 0, "image//main_game_screen7.bmp");
				break;
			case 8: iShowBMP(0, 0, "image//main_game_screen8.bmp");
				break;
			case 9: iShowBMP(0, 0, "image//main_game_screen9.bmp");
				break;
			case 10: iShowBMP(0, 0, "image//main_game_screen10.bmp");
				break;
			case 11: iShowBMP(0, 0, "image//main_game_screen11.bmp");
				break;
			case 12: iShowBMP(0, 0, "image//main_game_screen12.bmp");
				break;
			case 13: iShowBMP(0, 0, "image//main_game_screen13.bmp");
				break;
			case 14: iShowBMP(0, 0, "image//main_game_screen14.bmp");
				break;
			case 15: iShowBMP(0, 0, "image//main_game_screen15.bmp");
				break;
			case 16: iShowBMP(0, 0, "image//main_game_screen16.bmp");
				break;
			case 17: iShowBMP(0, 0, "image//main_game_screen17.bmp");

				break;
			}

			if ((bgIndex < 3 && game_sesh == false) && main_game_screen<15) {
				boat_image_set();
				drawing_ball();
				drawing_brick_rectangle();
				drawing_brick_lines();


				for (int i = 0; i < total_brick; i++){

					bool f = 0;
					if (brick[i].effectY >= screenheight) {
						brick[i].effectShow = false;
					}

					if (brick[i].effectY >= boat_bottom_y - 60) {


						if ((brick[i].effectY + 60 >= boat_bottom_y && brick[i].effectY <= boat_bottom_y) && ((brick[i].effectX + 60 >= boat_bottom_left_x && brick[i].effectX <= boat_bottom_left_x) || (brick[i].effectX >= boat_bottom_left_x && brick[i].effectX + 60 <= boat_bottom_right_x) || (brick[i].effectX <= boat_bottom_right_x && brick[i].effectX + 60 >= boat_bottom_right_x))) {
							brick[i].effectShow = false;
							if (!brick[i].alive) {
								continue;
							}

							if (brick[i].effectIndex == 5 && brick[i].effectNotUsed) {
								int randCurr = rand() % 4;
								brick[i].effectNotUsed = false;
								brick[i].effectIndex = randCurr;
								f = 1;

							}


							// speed barbe, when effectIndex = 0
							if (brick[i].effectIndex == 0 && brick[i].effectNotUsed) {
								brick[i].effectNotUsed = false;
								score += 10;

								double xx = ball_dx;
								double yy = ball_dy;

								double ball_dy_new = ball_dy;

								if (ball_dx)
								{

									if (ball_dy < 0)
									{
										ball_dy_new -= 5;
										ball_dy_new = max(-30, ball_dy_new);
									}

									else
									{
										ball_dy_new += 5;
										ball_dy_new = min(30, ball_dy_new);
									}

									double ball_dx_new = (ball_dx * ball_dy_new) / ball_dy;
									ball_dx = ball_dx_new;
									ball_dy = ball_dy_new;
								}
								else if (ball_dy < 0) {
									ball_dy_new -= 5;
									ball_dy_new = max(-30, ball_dy_new);
								}
								else {
									ball_dy_new += 5;
									ball_dy_new = min(30, ball_dy_new);
								}



							}
							// speed kombe, when effectIndex = 1
							else if (brick[i].effectIndex == 1 && brick[i].effectNotUsed) {
								brick[i].effectNotUsed = false;
								score += 10;
								double ball_dy_new = ball_dy;

								if (ball_dx)
								{
									if (ball_dy > 0)
									{
										ball_dy_new -= 5;
										ball_dy_new = max(8, ball_dy_new);
									}

									else
									{
										ball_dy_new += 5;
										ball_dy_new = min(-8, ball_dy_new);
									}


									double ball_dx_new = (ball_dx * ball_dy_new) / ball_dy;
									ball_dx = ball_dx_new;
									ball_dy = ball_dy_new;
								}
								else if (ball_dy < 0)
								{
									ball_dy_new += 5;
									ball_dy_new = min(-8, ball_dy_new);
								}
								else
								{
									ball_dy_new -= 5;
									ball_dy_new = max(8, ball_dy_new);
								}

							}
							else if (brick[i].effectIndex == 2 && brick[i].effectNotUsed) {
								brick[i].effectNotUsed = false;
								if (ball_radius <= 20) ball_radius += 10;
								score += 10;
							}
							else if (brick[i].effectIndex == 3 && brick[i].effectNotUsed) {
								brick[i].effectNotUsed = false;
								if (ball_radius >= 20) ball_radius -= 10;
								score += 10;
							}

							else if (brick[i].effectIndex == 4 && brick[i].effectNotUsed) {
								brick[i].effectNotUsed = false;
								score -= 10;
								score = max(0, score);
								new_start();
							}

						}
						else {
							brick[i].alive = false;
						}

					}
					if (brick[i].effectShow) {
						if (f) brick[i].effectIndex = 5;
						iShowBMP(brick[i].effectX, brick[i].effectY, effect[brick[i].effectIndex]);
						if (ball_movement_on)brick[i].effectY += max(5, brick[i].effectDy);
					}
				}

			}

			else if (bgIndex >= 3) game_sesh = true;
			if (main_game_screen<3 || (main_game_screen>6 && main_game_screen < 11))
			{
				iSetColor(0, 0, 0);
				string scr = to_string(score);
				for (int ii = 0; ii < scr.size(); ii++) score_char[ii] = scr[ii];
				for (int ii = scr.size(); ii < 10; ii++) score_char[ii] = '\0';
				iText(90, 750, "SCORE: ", GLUT_BITMAP_TIMES_ROMAN_24);
				iText(180, 750, score_char, GLUT_BITMAP_TIMES_ROMAN_24);
			}


		}


		else
		{
			switch (main_game_screen)
			{
			case 3: iShowBMP(0, 0, "image//main_game_screen3.bmp");
				break;
			case 4: iShowBMP(0, 0, "image//main_game_screen4.bmp");
				break;
			case 5: iShowBMP(0, 0, "image//main_game_screen5.bmp");
				break;
			case 6: iShowBMP(0, 0, "image//main_game_screen6.bmp");
				break;

			}
		}


	}



	else {

		switch (screen)
		{
		case 1: iShowBMP(0, 0, "image\\screen1.bmp");
			break;

		case 2: iShowBMP(0, 0, "image\\screen2.bmp");
			break;

		case 3: iShowBMP(0, 0, "image\\screen3.bmp");
			break;

		case 4: iShowBMP(0, 0, "image\\screen4.bmp");
			break;

		case 5: iShowBMP(0, 0, "image\\screen5.bmp");
			break;

		case 6: iShowBMP(0, 0, "image\\screen6.bmp");
			break;

		case 7: iShowBMP(0, 0, "image\\screen7.bmp");
			break;

		case 8: iShowBMP(0, 0, "image\\screen8.bmp");
			break;
		case 9: iShowBMP(0, 0, "image\\screen9.bmp");

			break;

		case 11: iShowBMP(0, 0, "image\\screen11.bmp");
			break;
		case 12: iShowBMP(0, 0, "image\\screen12.bmp");
			break;
		case 13: iShowBMP(0, 0, "image\\screen13.bmp");
			break;

		case 14: iShowBMP(0, 0, "image\\screen14.bmp");
			break;

		case 15: iShowBMP(0, 0, "image\\screen15.bmp");
			break;

		case 16: iShowBMP(0, 0, "image\\screen16.bmp");
			break;
		case 17: iShowBMP(0, 0, "image\\screen17.bmp");
			break;
		case 18: iShowBMP(0, 0, "image\\screen18.bmp");
			break;
		case 19: iShowBMP(0, 0, "image\\screen19.bmp");
			break;
		case 20: iShowBMP(0, 0, "image\\screen20.bmp");
			break;
		case 21: iShowBMP(0, 0, "image\\screen21.bmp");
			break;
		case 22: iShowBMP(0, 0, "image\\screen22.bmp");
			break;
		case 23: iShowBMP(0, 0, "image\\screen23.bmp");
			break;
		case 24: iShowBMP(0, 0, "image\\screen24.bmp");
			break;
		case 25: iShowBMP(0, 0, "image\\screen25.bmp");
			break;
		case 26: iShowBMP(0, 0, "image\\screen26.bmp");
			break;
		case 27: iShowBMP(0, 0, "image\\screen27.bmp");
			break;
		case 28: iShowBMP(0, 0, "image\\screen28.bmp");
			break;
		case 29: iShowBMP(0, 0, "image\\screen29.bmp");
			break;


		}

		if (screen == 28 || screen == 29)
		{
			iSetColor(0, 0, 0);
			iText(242, 780 - 488, name_char, GLUT_BITMAP_TIMES_ROMAN_24);
		}

		if (screen == 9 || screen == 12)
		{


			string nameall;
			int pos = 1;
			char now[30];
			fstream readn("textfile\\username.txt");
			while (getline(readn, nameall)) {
				iSetColor(0, 0, 0);
				for (int i = 0; i < nameall.size(); i++) now[i] = nameall[i];
				for (int i = nameall.size(); i < 30; i++) now[i] = '\0';


				if (pos == 1){
					iText(545, 780 - 320, now, GLUT_BITMAP_TIMES_ROMAN_24);
					iText(176, 780 - 320, "1", GLUT_BITMAP_TIMES_ROMAN_24);

				}
				else if (pos == 2){
					iText(545, 780 - 395, now, GLUT_BITMAP_TIMES_ROMAN_24);
					iText(176, 780 - 395, "2", GLUT_BITMAP_TIMES_ROMAN_24);
				}
				else if (pos == 3){

					iText(545, 780 - 470, now, GLUT_BITMAP_TIMES_ROMAN_24);
					iText(176, 780 - 470, "3", GLUT_BITMAP_TIMES_ROMAN_24);
				}
				else if (pos == 4){
					iText(545, 780 - 545, now, GLUT_BITMAP_TIMES_ROMAN_24);
					iText(176, 780 - 545, "4", GLUT_BITMAP_TIMES_ROMAN_24);
				}
				else if (pos == 5){
					iText(545, 780 - 621, now, GLUT_BITMAP_TIMES_ROMAN_24);
					iText(176, 780 - 621, "5", GLUT_BITMAP_TIMES_ROMAN_24);
				}
				pos++;
			}
			readn.close();




			string scoreall;
			pos = 1;
			fstream reads("textfile\\userscore.txt");
			while (getline(reads, scoreall)) {

				iSetColor(0, 0, 0);
				for (int i = 0; i < scoreall.size(); i++) now[i] = scoreall[i];
				for (int i = scoreall.size(); i < 30; i++) now[i] = '\0';

				if (pos == 1){

					iText(958, 780 - 320, now, GLUT_BITMAP_TIMES_ROMAN_24);
				}
				else if (pos == 2){
					iText(958, 780 - 395, now, GLUT_BITMAP_TIMES_ROMAN_24);
				}
				else if (pos == 3){
					iText(958, 780 - 470, now, GLUT_BITMAP_TIMES_ROMAN_24);
				}
				else if (pos == 4){
					iText(958, 780 - 545, now, GLUT_BITMAP_TIMES_ROMAN_24);
				}
				else if (pos == 5){
					iText(958, 780 - 621, now, GLUT_BITMAP_TIMES_ROMAN_24);
				}
				pos++;
			}
			reads.close();
		}


	}
	iSetColor(255, 0, 0);

	if ((main_game_screen >= 3 && main_game_screen <= 6) || main_game_screen == 15)
	{
		string now_score = to_string(score);
		cout << now_score << " ";
		char now_scr[5];

		for (int i = 0; i < now_score.size(); i++) now_scr[i] = now_score[i];
		for (int i = now_score.size(); i < 5; i++) now_scr[i] = '\0';

		cout << now_scr << endl;
		iSetColor(0, 0, 0);
		iText(570, 780 - 425, now_scr, GLUT_BITMAP_TIMES_ROMAN_24);
	}

	if (main_game_screen >= 11 && main_game_screen <= 13) {

		string now_score = to_string(score);
		char now_scr[5];

		for (int i = 0; i < now_score.size(); i++) now_scr[i] = now_score[i];
		for (int i = now_score.size(); i < 5; i++) now_scr[i] = '\0';

		iSetColor(0, 0, 0);
		iText(640, 780 - 307, now_scr, GLUT_BITMAP_TIMES_ROMAN_24);

	}



	if (game_win)
	{
		if (congo < 100) {
			congo++;
			iShowBMP(0, 0, "image\\main_game_screen14.bmp");
		}
		else {
			game_win = false; congo = 0; main_game_screen = 11;
			total_vanished_brick = 0;
		}
	}

}

int in_range(int x1, int x2, int y1, int y2, int mx, int my)
{
	if (mx >= x1 && mx <= x2 && my >= y1 && my <= y2) return 1;
	else return 0;
}

int in_range_circle(double center_x, double center_y, double radius, double mx, double my)
{
	double distance = sqrt(((mx - center_x) * (mx - center_x)) + ((my - center_y) * (my - center_y)));
	if (distance <= radius) return 1;
	else return 0;
}





void iMouseMove(int mx, int my){}
void iPassiveMouseMove(int mx, int my)
{

	if (main_game_screen)
	{
		if (main_game_screen >= 1 && main_game_screen <= 2) main_game_screen = 1;
		else if ((main_game_screen >= 3 && main_game_screen <= 6) || main_game_screen == 15) main_game_screen = 3;
		else if (main_game_screen >= 7 && main_game_screen <= 8) main_game_screen = 7;
		else if (main_game_screen >= 9 && main_game_screen <= 10) main_game_screen = 9;
		else if (main_game_screen >= 11 && main_game_screen <= 13) main_game_screen = 11;
		else if (main_game_screen >= 16 && main_game_screen <= 17) main_game_screen = 16;


		switch (main_game_screen)
		{
		case 1: if (in_range(game_options_x1, game_options_x2, game_options_y1, game_options_y2, mx, my)) main_game_screen = 2;
			break;

		case 3: if (in_range_circle(game_pause_home_center_x, game_pause_home_center_y, game_pause_home_radius, mx, my))main_game_screen = 4;
				else if (in_range_circle(game_pause_resume_center_x, game_pause_resume_center_y, game_pause_resume_radius, mx, my)) main_game_screen = 5;
				else if (in_range_circle(game_pause_retry_center_x, game_pause_retry_center_y, game_pause_retry_radius, mx, my)) main_game_screen = 6;
				else if (in_range_circle(game_pause_monster_center_x, game_pause_monster_center_y, game_pause_monster_radius, mx, my)) main_game_screen = 15;
				break;
		case 7: if (in_range(game_options_x1, game_options_x2, game_options_y1, game_options_y2, mx, my)) main_game_screen = 8;
			break;
		case 9: if (in_range(game_options_x1, game_options_x2, game_options_y1, game_options_y2, mx, my)) main_game_screen = 10;
			break;

		case 11:  if (in_range_circle(game_over_home_center_x, game_over_home_center_y, game_over_home_radius, mx, my))main_game_screen = 12;
				  else if (in_range_circle(game_over_restart_center_x, game_over_restart_center_y, game_over_restart_radius, mx, my)) main_game_screen = 13;
				  break;

		case 16: if (in_range_circle(all_left_center_x_mons, all_left_center_y_mons, all_left_radius_mons, mx, my))main_game_screen = 17;
			break;

		}
	}
	else
	{

		if (screen >= 2 && screen <= 7)
			screen = 2;
		else if (screen == 12) screen = 9;
		else if (screen == 13) screen = 11;
		else if (screen >= 14 && screen <= 16) screen = 14;
		else if (screen >= 17 && screen <= 20) screen = 17;
		else if (screen >= 21 && screen <= 24) screen = 21;
		else if (screen >= 25 && screen <= 27) screen = 25;
		else if (screen >= 28 && screen <= 29) screen = 28;
		else if (screen == 9 || screen == 12) screen = 9;

		switch (screen)
		{
		case 2: if (mx >= screen2_all_x1 && mx <= screen2_all_x2)
		{
					if (my >= screen2_newgame_y1 && my <= screen2_newgame_y2)
					{
						screen = 3;
						break;
					}
					else if (my >= screen2_leaderboard_y1 && my <= screen2_leaderboard_y2)
					{
						screen = 4;
						break;
					}
					else if (my >= screen2_howtoplay_y1 && my <= screen2_howtoplay_y2)
					{
						screen = 5;
						break;
					}
					else if (my >= screen2_credits_y1 && my <= screen2_credits_y2)
					{
						screen = 6;
						break;
					}
					else if (my >= screen2_exit_y1 && my <= screen2_exit_y2)
					{
						screen = 7;
						break;
					}
					else
						screen = 2;

		}
				else
					screen = 2; break;

		case 9: 	if (in_range_circle(all_home_center_x, all_home_center_y, all_home_radius, mx, my)) screen = 12;
			break;
		case 11: if (in_range_circle(credit_to_home_center_x, credit_to_home_center_y, home_radius, mx, my))screen = 13;
			break;
		case 14:   if (in_range_circle(all_home_center_x, all_home_center_y, all_home_radius, mx, my)) screen = 15;
				   else if (in_range_circle(all_right_center_x, all_right_center_y, all_right_radius, mx, my)) screen = 16;
				   break;


		case 17: if (in_range_circle(all_home_center_x, all_home_center_y, all_home_radius, mx, my)) screen = 18;
				 else if (in_range_circle(all_right_center_x, all_right_center_y, all_right_radius, mx, my)) screen = 20;
				 else if (in_range_circle(all_left_center_x, all_left_center_y, all_left_radius, mx, my)) screen = 19;
				 break;

		case 21: if (in_range_circle(all_home_center_x, all_home_center_y, all_home_radius, mx, my)) screen = 22;
				 else if (in_range_circle(all_right_center_x, all_right_center_y, all_right_radius, mx, my)) screen = 24;
				 else if (in_range_circle(all_left_center_x, all_left_center_y, all_left_radius, mx, my)) screen = 23;
				 break;
		case 25: if (in_range_circle(all_home_center_x, all_home_center_y, all_home_radius, mx, my)) screen = 26;
				 else if (in_range_circle(all_left_center_x, all_left_center_y, all_left_radius, mx, my)) screen = 27;
				 break;

		case 28: if (in_range_circle(all_home_center_x, all_home_center_y, all_home_radius, mx, my)) screen = 29;
			break;


		}


	}

}

void shob_ager_moto()
{

	for (int i = 0; i < total_brick; i++) {
		brick[i].effectShow = false;
		brick[i].brick_show = true;

		// variables to control effects
		brick[i].hasEffect = false;
		//double effectX, effectY;
		/*brick[i].effectShow = false;
		brick[i].effectIndex =  rand() % 6;
		brick[i].effectNotUsed = true;
		brick[i].alive = true;*/

	}
	ball_radius = main_ball_radius;
	boat_image_movement_x = boat_image_x;
	boat_image_movement_y = boat_image_y;


	boat_bottom_left_x = boat_bottom_left_main_x;
	boat_bottom_right_x = boat_bottom_right_main_x;
	boat_bottom_y = boat_bottom_main_y;



	boat_bottom_length = boat_bottom_right_x - boat_bottom_left_x;

	ball_x = (boat_bottom_length / 2) + boat_bottom_left_x;
	ball_y = boat_bottom_y - ball_radius;

	velocity = main_velocity;
	angle = main_angle;
	ball_dx = ball_main_dx;
	ball_dy = ball_main_dy;

	direction_change_on_colusion = 0;
	ball_movement_on = false;


	brick_coordination_set();




	for (int i = 0; i < total_brick; i++) {

		brick[i].effectIndex = rand() % 6;
		brick[i].effectNotUsed = true;
		brick[i].alive = true;
	}

	bgIndex = 0;


	if (score)
	{

		bool paisi = false;


		long long curr_score = score;
		string all_scores;

		fstream readID_score("textfile\\userscore.txt");
		while (getline(readID_score, all_scores)) {

			long long x = 1, scoreall = 0;
			int i = all_scores.size();

			while (i)
			{
				long long el = x *(all_scores[i - 1] - '0');
				scoreall += el;
				i--;
				x *= 10;
			}

			if (curr_score > scoreall) {
				paisi = true; break;
			}

		}
		readID_score.close();


		if (paisi)
		{

			vector < pair <long long, string > > listall;
			vector <string> arrayofnames;
			vector<long long> arrayofscores;

			string namesall;
			fstream readu("textfile\\username.txt");
			while (getline(readu, namesall)) {
				arrayofnames.push_back(namesall);
			}
			readu.close();



			string scoresall;
			fstream reads("textfile\\userscore.txt");
			while (getline(reads, scoresall)) {
				long long x = 1, ii = scoresall.size(), tot = 0;
				while (ii)
				{
					long long el = x *(scoresall[ii - 1] - '0');
					tot += el;
					ii--;
					x *= 10;
				}
				arrayofscores.push_back(tot);
				cout << "score: " << tot << endl;
			}
			reads.close();




			arrayofnames.push_back(profile_name);
			arrayofscores.push_back(curr_score);

			int index = 0;



			while (index < 6)
			{

				listall.push_back(make_pair(arrayofscores[index], arrayofnames[index]));
				index++;

			}
			sort(listall.begin(), listall.end());

			std::ofstream ofscore;
			ofscore.open("textfile\\userscore.txt", std::ofstream::out | std::ofstream::trunc);
			ofscore.close();


			std::ofstream ofnames;
			ofnames.open("textfile\\username.txt", std::ofstream::out | std::ofstream::trunc);
			ofnames.close();

			int co = 1;

			for (auto it = listall.rbegin(); it != listall.rend(); it++) {
				cout << it->first << "  " << it->second << endl;
				ofstream insertidnames("textfile\\username.txt", ios::app);
				insertidnames << it->second + '\n';
				insertidnames.close();


				ofstream insertidscore("textfile\\userscore.txt", ios::app);
				insertidscore << to_string(it->first) + '\n';
				insertidscore.close();

				if (co == 5) break;
				co++;
			}



		}


	}

	total_vanished_brick = 0;


}
void iMouse(int button, int state, int mx, int my)
{

	if (main_game_screen)
	{

		switch (main_game_screen)
		{
		case 2: main_game_screen = 3;


			ball_movement_on = true;
			break;
		case 8: main_game_screen = 3;
			ball_movement_on = true;
			break;
		case 10: main_game_screen = 3;
			ball_movement_on = true;
			break;
		case 4: main_game_screen = 0;
			shob_ager_moto();
			screen = 2;
			PlaySound("music\\homescreen.wav", NULL, SND_LOOP | SND_ASYNC);
			score = 0;
			break;
		case 5:
			if (bgIndex == 0) main_game_screen = 1;
			else if (bgIndex == 1) main_game_screen = 7;
			else if (bgIndex == 2) main_game_screen = 9;
			break;
		case 6:
			shob_ager_moto();
			main_game_screen = 1;
			score = 0;
			break;
		case 12: shob_ager_moto();
			bgIndex = 0;
			game_sesh = false;
			screen = 2;
			PlaySound("music\\homescreen.wav", NULL, SND_LOOP | SND_ASYNC);
			main_game_screen = 0;
			score = 0;
			break;
		case 13: shob_ager_moto();
			bgIndex = 0;
			game_sesh = 0;
			main_game_screen = 1;
			score = 0;
			break;
		case 15: main_game_screen = 16;
			break;
		case 17: main_game_screen = 3;
			break;
		}
	}
	else {

		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		{
			switch (screen)
			{
			case 3:
				screen = 28;
				break;

			case 4: screen = 9;
				break;

			case 5: screen = 14;
				break;

			case 6: screen = 11;
				break;
			case 7: exit(0);
				break;
			case 12: screen = 2;
				//PlaySound("music\\homescreen.wav", NULL, SND_LOOP | SND_ASYNC);
				break;
			case 13: screen = 2;
				//PlaySound("music\\homescreen.wav", NULL, SND_LOOP | SND_ASYNC);
				break;
			case 15: screen = 2;
				//PlaySound("music\\homescreen.wav", NULL, SND_LOOP | SND_ASYNC);
				break;
			case 16: screen = 17;
				break;

			case 18: screen = 2;
				//PlaySound("music\\homescreen.wav", NULL, SND_LOOP | SND_ASYNC);
				break;
			case 19: screen = 16;
				break;
			case 20: screen = 21;
				break;

			case 22: screen = 2;
				//PlaySound("music\\homescreen.wav", NULL, SND_LOOP | SND_ASYNC);
				break;
			case 23: screen = 17;
				break;
			case 24: screen = 25;
				break;

			case 26: screen = 2;
				//PlaySound("music\\homescreen.wav", NULL, SND_LOOP | SND_ASYNC);
				break;
			case 27: screen = 21;
				break;

			case 29: screen = 2;
				//PlaySound("music\\homescreen.wav", NULL, SND_LOOP | SND_ASYNC);
				break;

			}
		}
	}


	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{

	}


	//start_music();

}



void iKeyboard(unsigned char key)
{

	if ((screen == 28 || screen == 29) && main_game_screen == 0)
	{
		if ((int)(key) != 13)
		{
			if ((int)(key) != 8 && name.size()<26)
			{
				name.push_back(key);
				name_char[name_ind] = key;
				name_ind++;
			}
			else if (name.size() && (int)(key) == 8)
			{
				if (name_ind) name_ind--;
				if (name.size())name.pop_back();
				for (int i = name_ind; i < 100; i++) name_char[i] = '\0';
			}
		}
		else
		{
			if (name.size()) main_game_screen = 1;
		}

		profile_name = name;
	}
	else
	{
		if (key == ' ')
		{
			if (screen == 1) screen++;
			else
			if ((main_game_screen == 1 || main_game_screen == 2) || (main_game_screen >= 7 && main_game_screen <= 10))
			{
				if (ball_movement_on == false)ball_movement_on = true;
				else ball_movement_on = false;
			}
		}

	}

	start_music();
}




void iSpecialKeyboard(unsigned char key)
{

	if (key == GLUT_KEY_RIGHT && ball_movement_on) right_key_movement();
	if (key == GLUT_KEY_LEFT && ball_movement_on)  left_key_movement();

}





int main()
{
	if (main_music_on)
		PlaySound("music\\homescreen.wav", NULL, SND_LOOP | SND_ASYNC);
	iSetTimer(function_speed, ball_movement_change);
	iInitialize(screenwidth, screenheight, "IN YOUR SERVICE");
	brick_coordination_set();
	iStart();
	return 0;
}




void background_image_set()
{

	iShowBMP(0, 0, life[bgIndex]);

}




void boat_image_set()
{

	iShowBMP2(boat_image_movement_x, boat_image_movement_y, boat[0], 255);

}




void drawing_ball()
{
	iSetColor(0, 0, 0);
	iFilledCircle(ball_x, ball_y, ball_radius, 1000);
}





void drawing_brick_rectangle()
{

	for (int i = 0; i < total_brick; i++)
	{
		if (brick[i].brick_show)
		{
			iSetColor(brick_r, brick_g, brick_b);
			iFilledRectangle(brick[i].brick_x, brick[i].brick_y, brick_width, brick_height);
		}
	}

}






void drawing_brick_lines()
{

	for (int i = 0; i < total_brick; i++)
	{
		if (brick[i].brick_show)
		{

			iSetColor(line_r, line_g, line_b);

			iLine(brick[i].line_top_left[0], brick[i].line_top_left[1], brick[i].line_top_right[0], brick[i].line_top_right[1]);
			iLine(brick[i].line_top_left[0], brick[i].line_top_left[1], brick[i].line_bottom_left[0], brick[i].line_bottom_left[1]);
			iLine(brick[i].line_bottom_left[0], brick[i].line_bottom_left[1], brick[i].line_bottom_right[0], brick[i].line_bottom_right[1]);
			iLine(brick[i].line_bottom_right[0], brick[i].line_bottom_right[1], brick[i].line_top_right[0], brick[i].line_top_right[1]);




		}
	}
}







void right_key_movement()
{

	double total = boat_bottom_right_x + boat_keyboard_dx; // right movement of boat in X axis for movement key(right arrow)

	double ball_move; // for every click on right movement key of boat, the ball will also move if the ball movement is off. ball_move indicates how much the ball will move in X axis for every movement key click 

	if (total - (screenwidth - right_par) <= eps) // boat can move freely with the defined  movement value for right movement key
	{
		boat_image_movement_x += boat_keyboard_dx; // boat main moves 
		boat_bottom_left_x += boat_keyboard_dx;    // the bottom left corner of the boat moves
		boat_bottom_right_x += boat_keyboard_dx;   // he bottom right corner of the boat moves
		ball_move = boat_keyboard_dx;

	}

	else     //at some positions of the boat in X axis, it won't move that much what it was supposed to.
	{

		double exact_boat_movement_X_axis = screenwidth - right_par - 3 - total + boat_keyboard_dx; // appropiate amount of movement in X axis for right movement key

		boat_image_movement_x += exact_boat_movement_X_axis;  // boat image moves some certain amount such that its right side doesn't cross right_par
		boat_bottom_left_x += exact_boat_movement_X_axis;     // boat bottom left corner will also move along with its holding picture
		boat_bottom_right_x += exact_boat_movement_X_axis;    // boat bottom left corner will also move along with its holding picture
		ball_move = exact_boat_movement_X_axis;
	}

	if (ball_movement_on == false) ball_x += ball_move; // if ball movement is off , ball will also move if the boat moves. Amount of movement will be the same of boat movement


}




void left_key_movement()
{
	double total = boat_bottom_left_x - boat_keyboard_dx; // left movement of boat in X axis for left movement key(left arrow)

	double ball_move;  // for every click on left movement key, the ball will also move if the ball movement is off. ball_move indicates how much the ball will move in X axis for every left movement key click 

	if (total >= left_par + 5)  // boat can move freely with the defined movement value for left movement key
	{
		boat_image_movement_x -= boat_keyboard_dx;  // boat image moves 
		boat_bottom_left_x -= boat_keyboard_dx;     // the bottom left corner of the boat moves
		boat_bottom_right_x -= boat_keyboard_dx;    // the bottom right corner of the boat moves
		ball_move = boat_keyboard_dx;

	}

	else    //at some positions of the boat in X axis, it won't move that much what it was supposed to.
	{

		double exact_boat_movement_X_axis = boat_bottom_left_x - left_par - 5;

		boat_image_movement_x -= exact_boat_movement_X_axis;   // boat image moves some certain amount such that its left side doesn't cross left_par
		boat_bottom_left_x -= exact_boat_movement_X_axis;      //  boat bottom left corner will also move along with its holding picture
		boat_bottom_right_x -= exact_boat_movement_X_axis;     //  boat bottom right corner will also move along with its holding picture
		ball_move = exact_boat_movement_X_axis;
	}

	if (ball_movement_on == false) ball_x -= ball_move;  // if ball movement is off , ball will also move if the boat moves. Amount of movement will be the same of boat movement

}







void brick_coordination_set()
{

	/*first brick's coordination*/
	double starting_x = left_par;
	double starting_y = brick_shuru_y;

	int brick_number = 0;

	for (int i = 0; i < brick_col; i++)
	{
		for (int j = 0; j < brick_row; j++)
		{
			// probability to have an effect in a block is 1/2 = 0.55
			int temp = rand() % 2;
			if (!temp) {
				brick[brick_number].hasEffect = true;
				int x = rand() % 5;
				brick[brick_number].effectIndex = x;

			}


			else brick[brick_number].hasEffect = false;
			brick[brick_number].effectDy = max(5, rand() % 15);

			brick[brick_number].brick_x = starting_x;
			brick[brick_number].brick_y = starting_y;

			brick[brick_number].effectX = starting_x + 20;
			brick[brick_number].effectY = starting_y;

			brick[brick_number].line_bottom_left[0] = starting_x;
			brick[brick_number].line_bottom_left[1] = starting_y;

			brick[brick_number].line_top_left[0] = starting_x;
			brick[brick_number].line_top_left[1] = starting_y + brick_height;



			starting_x += brick_width;


			brick[brick_number].line_bottom_right[0] = starting_x;
			brick[brick_number].line_bottom_right[1] = starting_y;


			brick[brick_number].line_top_right[0] = starting_x;
			brick[brick_number].line_top_right[1] = starting_y + brick_height;



			brick_number++;
		}

		starting_x = left_par;
		starting_y += brick_height;
	}

}




void ball_movement_change()
{

	if ((main_game_screen == 1 || main_game_screen == 2) || (main_game_screen >= 7 && main_game_screen <= 10))
	{

		name.clear();
		for (int i = 0; i < 100; i++) name_char[i] = '\0';
		name_ind = 0;
	}
	else ball_movement_on = false;

	if (screen == 2)
	{

		name.clear();
		for (int i = 0; i < 100; i++) name_char[i] = '\0';
		name_ind = 0;
		profile_name.clear();
	}

	if (ball_movement_on && game_sesh == false)
	{
		int number;

		if (ball_y + ball_dy + ball_radius >= boat_bottom_y)
		{

			double new_ball_dy = boat_bottom_y - ball_y - ball_radius;
			double new_ball_dx = (ball_dx*new_ball_dy) / ball_dy;

			bool check = 0;

			if (ball_dx > 0)check = check_right_par_cross();
			else check = check_left_par_cross();


			if (!check) ball_touched_boat();

		}


		else if (boat_bottom_y - ball_radius - ball_y <= eps)ball_right_under_boat();


		else   if ((number = brick_collision()) == 0)
		{

			if (ball_dx > 0) collision_free_ball_movement_pos_x_axis();
			else collision_free_ball_movement_neg_x_axis();
		}

		else  {
			brick_vanish_sound();
			brick[number - 1].brick_show = 0;
			if (brick[number - 1].hasEffect) brick[number - 1].effectShow = true;
			score += 5;
			total_vanished_brick++;
			if (total_vanished_brick == total_brick)
			{
				main_game_screen = 14;
				game_sesh = true;
				shob_ager_moto();
				game_win = true;
				congo = 1;
				//

			}
		}
	}



}







bool check_right_par_cross()
{
	double new_ball_dy = boat_bottom_y - ball_y - ball_radius;
	double new_ball_dx = (ball_dx*new_ball_dy) / ball_dy;


	if (ball_x + ball_radius + new_ball_dx > (screenwidth - right_par + 1))
	{
		new_ball_dx = screenwidth - right_par + 1 - ball_x - ball_radius;
		new_ball_dy = (ball_dy*new_ball_dx) / ball_dx;
		ball_dx *= (-1);
		return 1;
	}
	return 0;
}







bool check_left_par_cross()
{
	double new_ball_dy = boat_bottom_y - ball_y - ball_radius;
	double new_ball_dx = (ball_dx*new_ball_dy) / ball_dy;

	if (ball_x - ball_radius + new_ball_dx < (left_par - 1))
	{
		new_ball_dx = ball_x - ball_radius - left_par + 1;
		new_ball_dy = (ball_dy*new_ball_dx) / ball_dx;
		ball_dx *= (-1);
		return 1;
	}
	return 0;
}






void ball_touched_boat()
{

	double new_ball_dy = boat_bottom_y - ball_y - ball_radius;
	double new_ball_dx = (ball_dx*new_ball_dy) / ball_dy;


	ball_y += new_ball_dy;
	ball_x += new_ball_dx;

	ball_dy *= (-1);

	angle = boat_bottom_right_x - ball_x - 5;
	ball_dx = velocity*cos(PI*angle / 180);
}



void ball_right_under_boat()
{
	if (!game_over()) new_start();
	else
	{
		if (ball_dx > 0) ball_movement_right_under_boat();
		else ball_movement_left_under_boat();

	}
}




void collision_free_ball_movement_pos_x_axis()
{
	double ball_new_dx;
	int right_cross = 0;
	int y_shift = 0;

	if (ball_x + ball_dx + ball_radius > (screenwidth - right_par + 1))
	{
		ball_new_dx = screenwidth - right_par + 1 - ball_x - ball_radius;
		right_cross = 1;
	}
	else ball_new_dx = ball_dx;


	double ball_new_dy;

	if (ball_new_dx == 0) ball_new_dy = ball_dy;

	else
	{
		ball_new_dy = (ball_new_dx*ball_dy) / ball_dx;
	}

	if (ball_y - ball_radius + ball_new_dy <= bottom_par)
	{
		ball_new_dy = ball_y - ball_radius - bottom_par;
		ball_new_dx = (ball_dx*ball_new_dy) / ball_dy;
		y_shift = 1;
	}
	else if (right_cross)ball_dx *= (-1);


	ball_x += abs(ball_new_dx);
	if (ball_dy < 0) ball_y -= abs(ball_new_dy);
	else ball_y += abs(ball_new_dy);
	if (y_shift) ball_dy *= (-1);
}







void collision_free_ball_movement_neg_x_axis()
{

	double ball_new_dx;
	int left_cross = 0;

	int y_shift = 0;
	if (ball_x - ball_radius + ball_dx < left_par - 1)
	{
		ball_new_dx = ball_x - ball_radius - left_par + 1;
		left_cross = 1;
	}

	else
		ball_new_dx = ball_dx;

	ball_new_dx = -(abs(ball_new_dx));

	double ball_new_dy;
	if (ball_new_dx == 0) ball_new_dy = ball_dy;
	else
	{
		ball_new_dy = (ball_new_dx*ball_dy) / ball_dx;
	}

	if (ball_y - ball_radius + ball_new_dy <= bottom_par)
	{
		ball_new_dy = ball_y - ball_radius - bottom_par;
		ball_new_dx = (ball_dx*ball_new_dy) / ball_dy;
		y_shift = 1;

	}
	else if (left_cross) ball_dx *= (-1);

	ball_x -= abs(ball_new_dx);
	if (ball_dy < 0) ball_y -= abs(ball_new_dy);
	else ball_y += abs(ball_new_dy);

	if (y_shift) 	ball_dy *= (-1);

}








int brick_collision()
{


	for (int i = 0; i < total_brick; i++)
	{
		if (brick[i].brick_show)
		{
			if (ball_x >= brick[i].brick_x && ball_x <= brick[i].brick_x + brick_width)
			{
				if (upper_and_lower_surface_collision_detection(i))
				{
					return i + 1;
				}

			}
			else if (ball_y >= brick[i].brick_y && ball_y <= brick[i].brick_y + brick_height)
			{

				if (left_and_right_surface_collision_detection(i))
				{
					return i + 1;

				}

			}

		}

	}

	for (int i = 0; i < total_brick; i++)
	{
		if (brick[i].brick_show)
		{

			if (angular_collision_detection(brick[i].line_top_left[0], brick[i].line_top_left[1], i, 1, -1, 1)) {
				return i + 1;
			}

			if (angular_collision_detection(brick[i].line_bottom_left[0], brick[i].line_bottom_left[1], i, 1, 1, 4)) {
				return i + 1;
			}


			if (angular_collision_detection(brick[i].line_top_right[0], brick[i].line_top_right[1], i, -1, -1, 2)) {
				return i + 1;
			}

			if (angular_collision_detection(brick[i].line_bottom_right[0], brick[i].line_bottom_right[1], i, -1, 1, 3)) {
				return i + 1;
			}

		}
	}

	return 0;

}





bool  angular_collision_detection(double brick_x, double brick_y, double brick_number, int sign_dx, int sign_dy, int corner)
{

	double ball_new_center_x = ball_x + ball_dx;
	double ball_new_center_y = ball_y + ball_dy;
	double x = (ball_new_center_x - brick_x);
	double y = (ball_new_center_y - brick_y);
	double distance = sqrt(x*x + y*y);


	if (distance - ball_radius <= eps)
	{

		double a = brick_x;
		double b = brick_y;
		double r = ball_radius;

		double nx = ball_x + ball_dx;
		double ny = ball_y + ball_dy;


		double p = ball_dx / ball_dy;
		double q = -(p*ny) + nx;
		double d = a - q;


		double A = (1 + (p*p));
		double B = -((2 * b) + (2 * p*d));
		double C = (b*b) + (d*d) - (r*r);


		double y1 = (-B + sqrt((B*B) - (4 * A*C))) / (2 * A);
		double y2 = (-B - sqrt((B*B) - (4 * A*C))) / (2 * A);

		double Y;
		double X;



		switch (corner)
		{

		case 1:

			Y = max(y1, y2);
			X = (-p*Y) + q;
			ang_dy = abs(ball_y - Y);
			ang_dx = (ball_dx*ang_dy) / ball_dy;
			ang_dx = abs(ang_dx);



			if (ball_dx >= 0 && ball_dy < 0)
			{
				ball_x += ang_dx;
				ball_y -= ang_dy;

				ball_dx *= (-1);
				ball_dy *= (-1);
			}
			else if (ball_dx<0)
			{
				ball_x -= ang_dx;
				ball_y -= ang_dy;
				ball_dy *= (-1);
			}
			else
			{


				ball_x += ang_dx;
				ball_y += ang_dy;
				ball_dx *= (-1);
			}

			break;

		case 2:

			Y = max(y1, y2);
			X = (-p*Y) + q;
			ang_dy = abs(ball_y - Y);
			ang_dx = (ball_dx*ang_dy) / ball_dy;
			ang_dx = abs(ang_dx);

			if (ball_dx <= 0 && ball_dy < 0)
			{
				ball_x -= ang_dx;
				ball_y -= ang_dy;

				ball_dx *= (-1);
				ball_dy *= (-1);
			}
			else if (ball_dx>0)
			{
				ball_x += ang_dx;
				ball_y -= ang_dy;
				ball_dy *= (-1);
			}
			else
			{

				ball_x -= ang_dx;
				ball_y += ang_dy;
				ball_dx *= (-1);
			}

			break;



		case 3:
			Y = min(y1, y2);
			X = (-p*Y) + q;
			ang_dy = abs(ball_y - Y);
			ang_dx = (ball_dx*ang_dy) / ball_dy;
			ang_dx = abs(ang_dx);

			if (ball_dx <= 0 && ball_dy > 0)
			{

				ball_x -= ang_dx;
				ball_y += ang_dy;

				ball_dx *= (-1);
				ball_dy *= (-1);
			}
			else if (ball_dx>0)
			{
				ball_x += ang_dx;
				ball_y += ang_dy;
				ball_dy *= (-1);
			}
			else
			{

				ball_x -= ang_dx;
				ball_y -= ang_dy;
				ball_dx *= (-1);
			}

			break;


		case 4:
			Y = min(y1, y2);
			X = (-p*Y) + q;
			ang_dy = abs(ball_y - Y);
			ang_dx = (ball_dx*ang_dy) / ball_dy;
			ang_dx = abs(ang_dx);



			if (ball_dx >= 0 && ball_dy > 0)
			{
				ball_x += ang_dx;
				ball_y += ang_dy;

				ball_dx *= (-1);
				ball_dy *= (-1);
			}

			else if (ball_dx<0)
			{
				ball_x -= ang_dx;
				ball_y += ang_dy;
				ball_dy *= (-1);
			}
			else
			{


				ball_x += ang_dx;
				ball_y -= ang_dy;
				ball_dx *= (-1);
			}

			break;

		}


		return 1;

	}

	return 0;
}








bool upper_and_lower_surface_collision_detection(int brick_number)
{

	bool brick_vanish = 0;

	if (ball_dy < 0)
	{
		if (ball_y - ball_radius + ball_dy - brick[brick_number].brick_y >= eps && ball_y - ball_radius + ball_dy - brick[brick_number].brick_y - brick_height <= eps)
			brick_vanish = 1;
	}

	else if (ball_dy>0)
	{

		if ((brick[brick_number].brick_y + brick_height) - (ball_y + ball_radius + ball_dy) >= eps && ball_y + ball_radius + ball_dy - brick[brick_number].brick_y >= eps)
			brick_vanish = 1;
	}


	if (brick_vanish)
	{

		double new_ball_dy;

		if (ball_dy < 0){ new_ball_dy = -(ball_y - ball_radius - brick[brick_number].brick_y - brick_height); }
		else{ new_ball_dy = abs(ball_y + ball_radius - brick[brick_number].brick_y); }

		double new_ball_dx = (ball_dx*new_ball_dy) / ball_dy;

		if (ball_dx<0) 	ball_x -= abs(new_ball_dx);
		else ball_x += abs(new_ball_dx);

		if (ball_dy<0) ball_y -= abs(new_ball_dy);
		else ball_y += abs(new_ball_dy);

		ball_dy *= (-1);
		return 1;

	}

	return 0;
}








bool left_and_right_surface_collision_detection(int brick_number)
{

	bool brick_vanish = 0;

	if (ball_dx < 0)
	{
		if (ball_x - ball_radius + ball_dx - brick[brick_number].brick_x >= eps && ball_x - ball_radius + ball_dx - brick[brick_number].brick_x - brick_width <= eps)
			brick_vanish = 1;
	}

	else if (ball_dx>0)
	{

		if ((brick[brick_number].brick_x + brick_width) - (ball_x + ball_radius + ball_dx) >= eps && ball_x + ball_radius + ball_dx - brick[brick_number].brick_x >= eps)
			brick_vanish = 1;
	}

	if (brick_vanish)
	{

		double new_ball_dx;

		if (ball_dx < 0){ new_ball_dx = -(ball_x - ball_radius - brick[brick_number].brick_x - brick_width); }
		else{ new_ball_dx = abs(ball_x + ball_radius - brick[brick_number].brick_x); }

		double new_ball_dy = (ball_dy*new_ball_dx) / ball_dx;

		if (ball_dx < 0) 	ball_x -= abs(new_ball_dx);
		else ball_x += abs(new_ball_dx);

		if (ball_dy < 0) ball_y -= abs(new_ball_dy);
		else ball_y += abs(new_ball_dy);

		ball_dx *= (-1);
		return 1;

	}
	return 0;
}










void ball_movement_left_under_boat()
{
	double ball_new_dx;

	if (ball_x - ball_radius + ball_dx < left_par - 1)
	{
		ball_new_dx = ball_x - ball_radius - left_par + 1;
		ball_dx *= (-1);
	}

	else
		ball_new_dx = ball_dx;


	double ball_new_dy;
	if (ball_new_dx == 0) ball_new_dy = 0;
	else
	{
		ball_new_dy = (ball_new_dx*ball_dy) / ball_dx;
	}
	ball_x -= abs(ball_new_dx);
	ball_y -= abs(ball_new_dy);

}



void ball_movement_right_under_boat()
{
	double ball_new_dx;

	if (ball_x + ball_dx + ball_radius > (screenwidth - right_par + 1))
	{
		ball_new_dx = screenwidth - right_par + 1 - ball_x - ball_radius;
		ball_dx *= (-1);
	}
	else ball_new_dx = ball_dx;


	double ball_new_dy;
	if (ball_new_dx == 0) ball_new_dy = 0;
	else
	{
		ball_new_dy = (ball_new_dx*ball_dy) / ball_dx;
	}
	ball_x += abs(ball_new_dx);
	ball_y -= abs(ball_new_dy);
}








bool game_over()
{
	if (ball_x >= boat_bottom_left_x && ball_x <= boat_bottom_right_x)return true;
	return false;
}





void new_start()
{
	bgIndex++;
	if (bgIndex == 0) main_game_screen = 1;
	else if (bgIndex == 1) main_game_screen = 7;
	else if (bgIndex == 2) main_game_screen = 9;
	else if (bgIndex == 3) main_game_screen = 11;

	for (int i = 0; i < total_brick; i++) {
		brick[i].effectShow = false;
	}
	ball_radius = main_ball_radius;
	boat_image_movement_x = boat_image_x;
	boat_image_movement_y = boat_image_y;


	boat_bottom_left_x = boat_bottom_left_main_x;
	boat_bottom_right_x = boat_bottom_right_main_x;
	boat_bottom_y = boat_bottom_main_y;



	boat_bottom_length = boat_bottom_right_x - boat_bottom_left_x;

	ball_x = (boat_bottom_length / 2) + boat_bottom_left_x;
	ball_y = boat_bottom_y - ball_radius;

	velocity = main_velocity;
	angle = main_angle;
	ball_dx = ball_main_dx;
	ball_dy = ball_main_dy;

	direction_change_on_colusion = 0;
	ball_movement_on = false;


}
