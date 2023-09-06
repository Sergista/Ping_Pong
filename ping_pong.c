#include <stdio.h>

// gcc -Wall -Werror -Wextra -o main main.c
int render(int ball_x, int ball_y, int rocket_y_one, int rocket_y_two, int map_x, int map_y, int score_one, int score_two) {
    for (int y = 0; y < map_y; y++) {
        for (int x = 0; x < map_x; x++) {
            if ((y == 0) && ((x < 30) || (x >40))) printf("#");          // render up wall
            if (y == map_y - 1) printf("#");  // render down wall
            if ((y == 0) && (x == 30)) printf(" SCORE: %d : %d ", score_one, score_two);
            if ((y != 0) && (y != map_y - 1)) {
                if ((ball_x == x) && (ball_y == y)) printf("*");
                else if ((y == rocket_y_one) && (x == 1)) printf("|");
                else if ((y == rocket_y_one + 1) && (x == 1)) printf("|");
                else if ((y == rocket_y_one + 2) && (x == 1)) printf("|");
                else if ((y == rocket_y_two) && (x == 78)) printf("|");
                else if ((y == rocket_y_two + 1) && (x == 78)) printf("|");
                else if ((y == rocket_y_two + 2) && (x == 78)) printf("|");
                else printf(" ");
            }
            
        }
        printf("\n");
    }
    return 0;
}



int collision(int ball_x, int ball_y, int rocket_y_one, int rocket_y_two)
{
    //left rocket
    if(ball_x == 3){
        if (ball_y == rocket_y_one) return 1; //1 == up rocket
        if (ball_y == rocket_y_one + 1) return 2; //2 == center rocket
        if (ball_y == rocket_y_one + 2) return 3; //3 == down rocket
    }
    //right rocket
    else if (ball_x == 77){
        if (ball_y == rocket_y_two) return 1; //1 == up rocket
        if (ball_y == rocket_y_two + 1) return 2; //2 == center rocket
        if (ball_y == rocket_y_two + 2) return 3; //3 == down rocket
    }
    else if(ball_y == 2)return 4; // up wall
    else if(ball_y == 23) return 5; //down wall
    
    return 0;
}


int main() {
    float ball_x = 40, ball_y = 12;
    int ball_v_x = 1;
    int ball_v_y = 0;
    int rocket_y_one = 12;
    int rocket_y_two = 12;
    int map_x = 80, map_y = 25;
    int score_one = 0, score_two = 0;
    // get char
    int game = 1;
    // game while
    render(ball_x, ball_y, rocket_y_one, rocket_y_two, map_x, map_y, score_one, score_two);
    
    while (game == 1) {
        //keyboard
        char ch = getchar();
        if((ch == 'A') && (rocket_y_one >= 2)) rocket_y_one--;
        if((ch == 'Z') && (rocket_y_one <= 20)) rocket_y_one++;
        
        if((ch == 'K') && (rocket_y_one >= 2)) rocket_y_two--;
        if((ch == 'M') && (rocket_y_one <= 20)) rocket_y_two++;
        if(ch == 'Q') return 0;
        
        printf("\e[1;1H\e[2J");
    
        int collision_ball = collision(ball_x, ball_y, rocket_y_one, rocket_y_two);
        
        //printf("%d %d %d", collision_ball, ball_v_x, ball_v_y);
        
        if (collision_ball != 0){
            if ( (ball_v_x == 1) && (collision_ball <= 3) ) ball_v_x = -1;
            else if ( (ball_v_x == -1) && (collision_ball <= 3) ) ball_v_x = 1;
            
            if (collision_ball == 1) ball_v_y = -1;
            else if (collision_ball == 2) ball_v_y = 0;
            else if (collision_ball == 3) ball_v_y = 1;
            
            if (collision_ball == 4){ball_v_y = 1;}
            else if (collision_ball == 5){ball_v_y = -1;}
        }
        
        if (ball_x < 1) {score_two++; ball_x =40; ball_y = 12;}
        else if(ball_x > 78) {score_one++; ball_x=40; ball_y = 12;}
        
        ball_x += ball_v_x;
        ball_y += ball_v_y;
            
        render(ball_x, ball_y, rocket_y_one, rocket_y_two, map_x, map_y, score_one, score_two);
    }
    return 0;
}
