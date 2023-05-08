/////////////////////////////////////////////////////////////////////////////////////////
// INTEGRITY STATEMENT (v4)
//
// By signing your name and ID below you are stating that you have agreed
// to the online academic integrity statement posted on edX:
// (Course > Assignments > Assignment Information & Policies > Academic Integrity Policy)
/////////////////////////////////////////////////////////////////////////////////////////
// I received help from and/or collaborated with:


//
// Name: Jiheng Li
// login ID: j53li
//////////////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <assert.h>
#include "team.h"
#include "cs136-trace.h"

//////////////////////////////////////////////////////////////////////////////////////////
// These definitions are used to control testing.
const int MAX_TEAMS = 4;

// -----------------------------------------------------------------------
// DO NOT CHANGE THIS REGION OF CODE

// print_reason(r) prints information about the reason for a failure
//    as indicated in the structure r.
// requires: r is a valid pointer to a reason
//           The reason code is either FAIL_INSUFFICIENT_FUNDS or FAIL_ROSTER_FULL
// effects: produces output

void print_reason(const struct reason* const r) {
  assert(r);
  assert(r->code == FAIL_INSUFFICIENT_FUNDS || r->code == FAIL_ROSTER_FULL);
  if (r->code == FAIL_INSUFFICIENT_FUNDS) {
    printf("Team %d doesn't have enough money\n", r->team_num);
  } else if (r->code == FAIL_ROSTER_FULL) {
    printf("Team %d has a full roster\n", r->team_num);
  } 
}
// END OF DO NOT CHANGE REGION
//////////////////////////////////////////////////////////////////////////////////////////
void do_io_tests(void) {

  // Possible messages for team command (nothing is printed if successful)
  //   "Teams are all initialized\n"

  // Possible messages for is_on command
  //   "Player %d is on team %d\n"
  //   "Player %d is not on team %d\n"

  // Possible messages for add_player command (nothing is printed if successful)
  //   "add_player failed : " 
  //    followed by calling print_reason to print the reason for the failure

  // Possible messages for sell_player command (nothing is printed if successful)
  //   "sell_player failed : "
  //    followed by calling print_reason to print the reason for the failure

  // Possible messages for trade_players command (nothing is printed if successful)
  //   "trade_players failed : "
  //    followed by calling print_reason to print the reason for the failure

  int team = lookup_symbol("team");
  int add_player = lookup_symbol("add_player");
  int sell_player = lookup_symbol("sell_player");
  int trade_players = lookup_symbol("trade_players");
  int print = lookup_symbol("print");
  int is_on = lookup_symbol("is_on");
  struct team arr [5] = {
    team_empty, team_empty, team_empty, team_empty, team_empty};
  struct reason r = {1, 1};
  int count = 0;
  while (1) {
    int command = read_symbol();
    if (command > 1) {
      printf("1");
    }
    if (command == team) {
      int team_id = 0;
      int cash = 0;
      if (count > MAX_TEAMS - 1) {
        if (scanf("%d%d", &team_id, &cash)) {
          printf("Teams are all initialized\n");
        }
      } else {
        if (scanf("%d%d", &team_id, &cash)) {
          team_init_empty(&(arr[count]));
          team_setup(&(arr[count]), team_id, cash);
        }
        count += 1;
      }
    } else if (command == add_player) {
      int team_id = 0;
      int player_id = 0;
      int val = 0;
      if (scanf("%d%d%d", &team_id, &player_id, &val)) {
        int i = 0;
        while (i < 5) {
          if (arr[i].team_id == team_id) {
            break;
          } else {
            i += 1;
          }
        }
        
        if (team_add_player(&(arr[i]), player_id, val, &r) == false) {
            printf("add_player failed : ");
            print_reason(&r);
        }
      }
    } else if (command == sell_player) {
      int team_id1 = 0;
      int team_id2 = 0;
      int player_id = 0;
      if (scanf(" %d%d%d", &team_id1, &player_id, &team_id2)) {
        int i = 0; 
        while (i < 5) {
          if (arr[i].team_id == team_id1) {
            break;
          } else {
            i += 1;
          }
        }

        int j = 0;
        while (j < 5) {
          if (arr[j].team_id == team_id2) {
            break;
          } else {
            j += 1;
          }
        }
        if (team_sell_player(&(arr[i]), player_id, &(arr[j]), &r) == false) {
            printf("sell_player failed : ");
            print_reason(&r);
          }
      }
    } else if (command == trade_players) {
      int team_id1 = 0;
      int team_id2 = 0;
      int player_id1 = 0;
      int player_id2 = 0;
      if (scanf("%d%d%d%d", &team_id1, &player_id1, &team_id2, &player_id2)) {
        int i = 0; 
        while (i < 5) {
          if (arr[i].team_id == team_id1) {
            break;
          } else {
            i += 1;
          }
        }
        int j = 0;
        while (j < 5) {
          if (arr[j].team_id == team_id2) {
            break;
          } else {
            j += 1;
          }
        }
      
        if (team_trade_players
            (&(arr[i]), player_id1, &(arr[j]), player_id2, &r) == false) {
            printf("trade_players failed : ");
            print_reason(&r);
          }
      }
    } else if (command == print) {
      printf("1\n");
      int team_id = 0;
      
      if (scanf(" %d", &team_id) > 0) {
        int i = 0; 
        while (i < 5) {
          if (arr[i].team_id == team_id) {
            break;
          } else {
            i += 1;
          }
        }

      team_print(&(arr[i]));
      } 
    } else if (command == is_on) {
      int team_id = 0;
      int player_id = 0;
      if (scanf(" %d%d", &team_id, &player_id)) {
        int i = 0; 
        while (i < 5) {
          if (arr[i].team_id == team_id) {
            break;
          } else {
            i += 1;
          }
        }

        if (team_is_player_on(&(arr[i]), player_id) == false) {
            printf("Player %d is not on team %d\n", player_id, team_id);
          } else {
            printf("Player %d is on team %d\n", player_id, team_id);
          }
      }
    } else {
      break;
    }
  }
}

int main(void) {
  // DO NOT CHANGE THE CODE BELOW THIS LINE
  do_io_tests();
}
