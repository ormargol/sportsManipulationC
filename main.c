#include <stdio.h>
#include <stdlib.h>

#define TEAMS_NUM 8
#define GROUP_SIZE 4
#define GROUPS_NUM (TEAMS_NUM / GROUP_SIZE)
#define true 1
#define false 0

typedef int bool;

typedef struct {
    int id;
    int score;
}team;

typedef struct {
    int id;
    team* teams[GROUP_SIZE];
}group;

typedef struct {
    group* groups[GROUPS_NUM];
    team* teams[TEAMS_NUM];
    bool strength_graph[TEAMS_NUM][TEAMS_NUM];
    bool positive_manipulators[TEAMS_NUM][TEAMS_NUM];
    bool negative_manipulators[TEAMS_NUM][TEAMS_NUM];
}league;

int algorithm_init(league* lg) {
    int g, t1, t2;
    for (g = 0; g < GROUPS_NUM; g++) {
        lg->groups[g] = malloc(sizeof(group));
        lg->groups[g]->id = g + 1;
        for (t1 = 0; t1 < GROUP_SIZE; t1++) {
            lg->groups[g]->teams[t1] = malloc(sizeof(team));
            lg->groups[g]->teams[t1]->id = g * GROUP_SIZE + t1;
        }
    }
    for (t1 = 0; t1 < TEAMS_NUM; t1++) {
        for (t2 = 0; t2 < TEAMS_NUM; t2++) {
            if (t2 >= t1 + 1) {
                lg->strength_graph[t1][t2] = true;// t1 beats t2
            } else {
                lg->strength_graph[t1][t2] = false;
            }
            lg->positive_manipulators[t1][t2] = false;
            lg->negative_manipulators[t1][t2] = false;
        }
    }
    lg->positive_manipulators[3][4] = true;
    lg->positive_manipulators[6][4] = true;
    lg->positive_manipulators[8][4] = true;
    return 0;
}

int algorithm_execute(league* league, team* team, bool win_manipulates) {
    return 0;
}

int main(int argc, char** argv) {
    return 0;
}
