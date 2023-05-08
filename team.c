#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include "team.h"

const int MAX_PLAYERS = 5;
const int TEAM_INVALID_ID = -1;
const struct team team_empty = {TEAM_INVALID_ID, 0}; // Doesn't set players to empty_player
                                                     // Must be done by team_init_empty

const int FAIL_INSUFFICIENT_FUNDS = -1;
const int FAIL_ROSTER_FULL = -2;
//swap(a, b) swaps two value
// requires: a and b are valid pointer
// effect: mutation by the pointer
void swap (struct player* const a, struct player* const b) {
  assert(a);
  assert(b);
  struct player temp = *a;
  *a = *b;
  *b = temp;
}

// sort(a, len) sorts the elements of a
//   in increasing order
// requires: len > 0
// effects: modifies a
void sort(struct player a[], int len) {
  assert(a);
  assert(len > 0);
  for (int i = 0; i < len - 1; ++i) {
    int pos = i;
    for (int j = i + 1; j < len; ++j) {
      if (a[j].player_id < a[pos].player_id) {
        pos = j;
      }
    }
    swap(&a[i], &a[pos]); 
  }
}

// YOU MUST COMPLETE THIS FUNCTION
void team_print(const struct team* const t) {
  assert(t);
  assert(team_player_value(t) + team_cash(t) == team_value(t));
  printf("Team %d : ", team_get_id(t));

  // INSERT CODE HERE FOR PRINTING PLAYERS
  // Players must be printed from the lowest player_id to highest player_id.
  // You must NOT print players with player_id == PLAYER_INVALID_ID
  // The function you use to print the player is 
  //    player_print(player_ptr);  See player.h
  // player_print will take care of proper spacing.
  // See team_print in team.c of A5 if you need a better idea of what to do.
  struct player p[5] = {0};
  for (int i = 0; i < 5; i++) {
    p[i] = t->players[i];
  }
  sort(p, 5);
  for (int i = 0; i < 5; i++) {
    if(p[i].player_id != player_empty.player_id 
        && p[i].player_id != player_empty.value){
          player_print(&p[i]);
        }
  }
  printf("player value = %d cash = %d", team_player_value(t), team_cash(t));
  printf("\n");
}
// -----------------------------------------------------------------------

// if_empty(p1) return true if p1 is empty. otherwise false
// requires: p1 is a valid pointer to player
bool if_empty_p(const struct player *p) {
  assert(p);
  if (p->player_id == player_empty.player_id 
        && p->value == player_empty.value) {
    return true;
  } else {
    return false;
  }
}

// if_empty(p1) return true if all of the player in array p is empty. otherwise 
//   false
// requires: p1 is a valid pointer to player
bool if_empty(struct player p []) {
  assert(p);
  if ((p[1].player_id == player_empty.player_id &&
      p[1].value == player_empty.value) ||
      (p[2].player_id == player_empty.player_id &&
      p[2].value == player_empty.value) ||
      (p[3].player_id == player_empty.player_id &&
      p[3].value == player_empty.value) ||
      (p[4].player_id == player_empty.player_id &&
      p[4].value == player_empty.value) ||
      (p[0].player_id == player_empty.player_id &&
      p[0].value == player_empty.value)
      ) {
        return true;
  } else {
        return false;
  }
}

// team_player_value(t) returns the sum of the value of all of the players
//     on team t
// requires: t is a valid pointer to a team with a valid team_id
int team_player_value(const struct team* const t) {
  // Replace this with your code
  assert(t);
  assert(t->team_id != TEAM_INVALID_ID);
  int val = 0;
  for (int i = 0; i < 5; i++) {
    if (if_empty_p(&(t->players[i]))) {
      continue;
    }
    val += t->players[i].value;
  }
  return val;
}

// team_value(t) returns the total value of the team t
//     (i.e., the sum of the value of all of the players and the cash_available)
// requires: t is a valid pointer to a team with a valid team_id
int team_value(const struct team* const t) {
  // Replace this with your code
  assert(t->team_id != TEAM_INVALID_ID);
  assert(t);
  return team_cash(t) + team_player_value(t);
}

// team_cash(t) returns the cash available for team t
// requires: t is a valid pointer to a team with a valid team_id
int team_cash(const struct team* const t) {
  // Replace this with your code
  assert(t && t->team_id != TEAM_INVALID_ID);
  return t->cash_available;
}

// team_init_empty(t) 
//     Initialize team t to empty.
//       Team id should be set to TEAM_INVALID_ID and other fields
//       besides player structures should be zero.
//     All players must be initialized to player_empty.
// requires: t is a valid pointer to a team
// effects: modifies team t
void team_init_empty(struct team* const t) {
  // Replace this with your code
  assert(t);
  t->team_id = TEAM_INVALID_ID;
  t->cash_available = 0;
  t->num_players = 0;
  for (int i = 0; i < 5; i++) {
    t->players[i].player_id = player_empty.player_id;
    t->players[i].value = player_empty.value;
  }
}

// team_setup(t, id, cash) Setup (create) team t by assigning it a team id = id
//       and the initial amount of cash_available.
// requires: t is a valid pointer to a team with a team_id = TEAM_INVALID_ID
//           no players have been assigned to the team 
//           (i.e., player_id = PLAYER_INVALID_ID)
//           for all players on the team
//           id and cash >= 0
//           num_players = 0
// effects: modifies team t
void team_setup(struct team* const t, const int id, const int cash) {
  // Replace this with your code
  assert(t);
  assert(t->team_id = TEAM_INVALID_ID);
  assert(if_empty_p(&(t->players[0])) &&
         if_empty_p(&(t->players[1])) &&
         if_empty_p(&(t->players[2])) &&
         if_empty_p(&(t->players[3])) &&
         if_empty_p(&(t->players[4])));
  assert(id >= 0 && cash >= 0);
  t->team_id = id;
  t->cash_available = cash;
}


// team_get_id(t) returns the id that was assigned to team t
// requires: t is a valid pointer to a team
int team_get_id(const struct team* const t) {
  // Replace this with your code
  assert(t);
  return t->team_id;
}


// team_is_player_on(t, id) returns true if the team has a player
//     with player id = id on the team.
//     Otherwise returns false.
// requires: t is a valid pointer to a team with a valid team_id
//           id >= 0
bool team_is_player_on(const struct team* const t, const int id) {
  // Replace this with your code
  assert(t);
  assert(t->team_id != TEAM_INVALID_ID);
  assert(id >= 0);
  if (t->players[1].player_id == id ||
      t->players[2].player_id == id ||
      t->players[3].player_id == id ||
      t->players[4].player_id == id ||
      t->players[0].player_id == id) {
      return true;
      } else {
      return false;
  }
}

// team_add_player(t, id, val, r)
//     Attempt to add player with id and value (val) to team t
//     First, if the team has reached the maximum number of players the call
//        fails (and the reason is provided). 
//     Second if the team does not have
//        enough cash available to pay for the value of the player,
//        the call fails (and the reason is provided). 
//     On a failure, information about the failure is provided in reason r
//        before the call returns false.
//     If the player can be added the amount of cash available for the team
//        is decreased by the value (val) of the player
//        (i.e., they have to pay for the player).
//     If successful, the call returns true and the reason should be ignored.
// requires: t is a valid pointer to a team with a valid team_id
//     id and val >= 0
//     player with identity id is not already on the team
//     Reason r is a valid pointer.
// effects: may modify team t and reason r
bool team_add_player(struct team* const t, const int id, const int val,
   struct reason *r) {
  // Replace this with your code
  assert(id >=0 && val >= 0);
  assert(!team_is_player_on(t, id));
  assert(r);
  assert(t->team_id != TEAM_INVALID_ID);
  if (! (if_empty(t->players))) {
    r->code = FAIL_ROSTER_FULL;
    r->team_num = t->team_id;
    return false;
  } else if (val > t->cash_available) {
    r->code = FAIL_INSUFFICIENT_FUNDS;
    r->team_num = t->team_id;
    return false;
  } else {
    t->cash_available -= val;
    if (if_empty_p(&(t->players[0]))) {
      t->players[0].player_id = id;
      t->players[0].value = val;
    } else if (if_empty_p(&(t->players[1]))) {
      t->players[1].player_id = id;
      t->players[1].value = val;
    } else if (if_empty_p(&(t->players[2]))) {
      t->players[2].player_id = id;
      t->players[2].value = val;
    } else if (if_empty_p(&(t->players[3]))) {
      t->players[3].player_id = id;
      t->players[3].value = val;
    } else if (if_empty_p(&(t->players[4]))) {
      t->players[4].player_id = id;
      t->players[4].value = val;
    } 
    t->num_players += 1;
    return true;
  }
}

// team_sell_player(t1, id, t2, r) 
//     Team t1 attempts to sell the specified player (id) to team t2
//     First, if team t2 has reached the maximum number of players, the call
//        fails (and the reason is provided). 
//     Second if the team t2 does not have
//        enough cash available to pay for the value of the player,
//        the call fails (and the reason is provided). 
//     On a failure, information about the failure is provided in reason r
//        before the call returns false.
//     If successful, the call returns true and the reason should be ignored.
// requires: t1 and t2 are valid pointer to a team both with a valid team_id
//     The specified player (id) is on team t1.
//     The specified player (id) is not on team t2.
//     Reason r is a valid pointer.
//     id >= 0.
//     t1 != t2
// effects: may modify team t1 and t2 and reason r
bool team_sell_player(struct team* const t1, const int id,
     struct team* const t2, struct reason *r) {
  // Replace this with your code
  assert(t1 && t2 
    && t1->team_id != TEAM_INVALID_ID && t2->team_id != TEAM_INVALID_ID);
  assert(team_is_player_on(t1, id));
  assert(!team_is_player_on(t2, id));
  assert(r);
  assert(id >= 0);
  assert(t1->team_id != t2->team_id);
  struct player *trade = &(t1->players[0]);
  if (t1->players[1].player_id == id) {
    *trade = t1->players[1];
  } else if (t1->players[2].player_id == id) {
    *trade = t1->players[2];
  } else if (t1->players[3].player_id == id) {
    *trade = t1->players[3];
  } else if (t1->players[4].player_id == id) {
    *trade = t1->players[4];
  }

  if (! (if_empty_p(&(t2->players[0])) ||
         if_empty_p(&(t2->players[1])) ||
         if_empty_p(&(t2->players[2])) ||
         if_empty_p(&(t2->players[3])) ||
         if_empty_p(&(t2->players[4])))) {
    r->code = FAIL_ROSTER_FULL;
    r->team_num = t2->team_id;
    return false;
  } else if (trade->value > t2->cash_available) {
    r->code = FAIL_INSUFFICIENT_FUNDS;
    r->team_num = t2->team_id;
    return false;
  } else {
    t1->cash_available += trade->value;
    t2->cash_available -= trade->value;
    if (if_empty_p(&(t2->players[0]))) {
      t2->players[0].player_id = trade->player_id;
      t2->players[0].value = trade->value;
    } else if (if_empty_p(&(t2->players[1]))) {
      t2->players[1].player_id = trade->player_id;
      t2->players[1].value = trade->value;
    } else if (if_empty_p(&(t2->players[2]))) {
      t2->players[2].player_id = trade->player_id;
      t2->players[2].value = trade->value;
    } else if (if_empty_p(&(t2->players[3]))) {
      t2->players[3].player_id = trade->player_id;
      t2->players[3].value = trade->value;
    } else if (if_empty_p(&(t2->players[4]))) {
      t2->players[4].player_id = trade->player_id;
      t2->players[4].value = trade->value;
    }
    *trade = player_empty;
    t1->num_players -= 1;
    t2->num_players += 1;
    return true;
  }
}

// team_trade_players(t) team t1 attempts to trade player with id1 to team t2
//     in exchange for the player with id2 on team t2
//     If team t1 or t2 do not have enough cash available to cover the difference
//        in value between the two players, the call fails.
//     On a failure, information about the failure is provided in reason r
//        before the call returns false.
//     If successful, the call returns true and the reason should be ignored.
// requires: t1 and t2 are valid pointer to a team both with a valid team_id
//     The specified player (id1) is on team t1.
//     The specified player (id2) is on team t2.
//     Reason r is a valid pointer.
//     id1 and id2 >= 0
//     t1 != t2
// effects: may modify team t1 and t2 and reason r
bool team_trade_players(struct team* const t1, const int id1,
     struct team* const t2, const int id2, struct reason *r) {
  // Replace this with your code
  assert(t1 && t2 
    && t1->team_id != TEAM_INVALID_ID && t2->team_id != TEAM_INVALID_ID);
  assert(team_is_player_on(t1, id1) && team_is_player_on(t2, id2));
  assert(r);
  assert(id1 >= 0 && id2 >= 0);
  assert(t1->team_id != t2->team_id);
  struct player *trade1 = &(t1->players[0]);
  if (t1->players[1].player_id == id1) {
    trade1 = &(t1->players[1]);
  } else if (t1->players[2].player_id == id1) {
    trade1 = &(t1->players[2]);
  } else if (t1->players[3].player_id == id1) {
    trade1 = &(t1->players[3]);
  } else if (t1->players[4].player_id == id1) {
    trade1 = &(t1->players[4]);
  }

  struct player *trade2 = &(t2->players[0]);
  if (t2->players[1].player_id == id2) {
    trade2 = &(t1->players[1]);
  } else if (t2->players[2].player_id == id2) {
    trade2 = &(t1->players[2]);
  } else if (t2->players[3].player_id == id2) {
    trade2 = &(t1->players[3]);
  } else if (t2->players[4].player_id == id2) {
    trade2 = &(t1->players[4]);
  }

  int diff = trade1->value - trade2->value;
  if (t1->cash_available < 0 - diff) {
    r->code = FAIL_INSUFFICIENT_FUNDS;
    r->team_num = t1->team_id;
    return false;
  } else if (t2->cash_available < diff) {
    r->code = FAIL_INSUFFICIENT_FUNDS;
    r->team_num = t2->team_id;
    return false;
  } else {
    t1->cash_available += diff;
    t2->cash_available -= diff;
    struct player temp = *trade2;
    *trade2 = *trade1;
    *trade1 = temp;
    return true;
  }
  return false;
}

