#include <stdio.h>

#define GROUPS_NUM 8

typedef int bool;

struct team_t;
typedef struct team_t team;

struct {
    int id;
    int score;
    team* prev;
    team* next;
    team* parent;
    team* right;
    team* left;
}team_t;

typedef struct {
    int id;
    team* teams;
}group;

typedef struct {
    team* cup_root;
    group* groups_head;
    team* teams_head;
    bool strength_graph[GROUPS_NUM][GROUPS_NUM];
    bool positive_manipulators[GROUPS_NUM][GROUPS_NUM];
    bool negative_manipulators[GROUPS_NUM][GROUPS_NUM];
}league;

int algorithm_init(league* league) {
    return 0;
}

int algorithm_execute(league* league, team* etam, bool win_manipulates) {
    return 0;
}

int main(int argc, char** argv) {
    return 0;
}
