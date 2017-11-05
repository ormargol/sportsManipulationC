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
    bool strength_graph[TEAMS_NUM][TEAMS_NUM];
    bool positive_manipulators[TEAMS_NUM][TEAMS_NUM];
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
        }
    }
    lg->positive_manipulators[3][4] = true;
    lg->positive_manipulators[6][4] = true;
    lg->positive_manipulators[8][4] = true;
    return 0;
}

int calculate_groups_scores(league* lg) {
    int g, t1, t2;
    team* temp;
    for (g = 0; g < GROUPS_NUM; g++) {
        for (t1 = 0; t1 < GROUP_SIZE; t1++) {
            for (t2 = t1 + 1; t2 < GROUP_SIZE; t2++) {

                if (lg->positive_manipulators[lg->groups[g]->teams[t1]->id][lg->groups[g]->teams[t2]->id]) {
                    lg->groups[g]->teams[t2]->score += 3;
                    continue;
                }
                if (lg->strength_graph[lg->groups[g]->teams[t2]->id][lg->groups[g]->teams[t1]->id]) {
                    lg->groups[g]->teams[t2]->score +=3;
                    continue;
                }
                lg->groups[g]->teams[t1]->score += 3;
            }
        }
        for (t1 = 0; t1 < GROUP_SIZE; t1++) {
            for (t2 = t1 + 1; t2 < GROUP_SIZE; t2++) {
                if (lg->groups[g]->teams[t1]->score < lg->groups[g]->teams[t2]->score) {
                    temp = lg->groups[g]->teams[t1];
                    lg->groups[g]->teams[t1] = lg->groups[g]->teams[t2];
                    lg->groups[g]->teams[t2] = temp;
                }
            }
        }
        printf("GROUP %d:\n", lg->groups[g]->id);
        for (t1 = 0; t1 < GROUP_SIZE; t1++) {
            printf("TEAM %d: score=%d\n", lg->groups[g]->teams[t1]->id, lg->groups[g]->teams[t1]->score);
        }
        printf("\n");
    }
    return 0;
}

bool calculate_tree(league* lg, team* tm) {
    team* tree_teams[GROUPS_NUM * 2];
    int g, t = 0;
    for (g = 0; g < GROUPS_NUM; g++, t++) {
        if (g %2 == 0) {
            tree_teams[t] = lg->groups[g]->teams[0];
            tree_teams[GROUPS_NUM * 2 - t - 1] = lg->groups[g]->teams[1];
        } else {
            tree_teams[t] = lg->groups[g]->teams[1];
            tree_teams[GROUPS_NUM * 2 - t - 1] = lg->groups[g]->teams[0];
        }
    }
    int left_teams;
    for (left_teams = GROUPS_NUM * 2; left_teams > 1; left_teams /= 2) {
        for (t = 0; t < left_teams / 2; t++) {
            printf("%d %c %d , ", tree_teams[2 * t]->id, (lg->strength_graph[tree_teams[2 * t]->id][tree_teams[2 * t + 1]->id] || lg->positive_manipulators[tree_teams[2 * t + 1]->id][tree_teams[2 * t]->id])? '>':'<', tree_teams[2 * t + 1]->id);
            if (lg->strength_graph[tree_teams[2 * t]->id][tree_teams[2 * t + 1]->id] || lg->positive_manipulators[tree_teams[2 * t + 1]->id][tree_teams[2 * t]->id]) {
                tree_teams[t] = tree_teams[2 * t];
            } else {
                tree_teams[t] = tree_teams[2 * t + 1];
            }
        }
        printf("\n");
    }
    printf("%d\n", tree_teams[0]->id);
    if (tree_teams[0]->id == tm->id) {
        return true;
    } else {
        return false;
    }
}

bool try_swap_two_firsts_on_tm_group(league* lg) {
    return false;
}

int algorithm_execute(league* lg, team* tm) {
    calculate_groups_scores(lg);
    if (calculate_tree(lg, tm)) {
        printf("yes!\n");
        return 0;
    }
    if (try_swap_two_firsts_on_tm_group(lg)) {
        if (calculate_tree(lg, tm)) {
            printf("yes!\n");
            return 0;
        }
    }
    printf("no!\n");
    return 0;
}

int main(int argc, char** argv) {
    league lg;
    algorithm_init(&lg);
    algorithm_execute(&lg, lg.groups[0]->teams[0]);
    return 0;
}
