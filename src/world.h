#include "graph.h"

enum type_world {
  SQUARED = 0,
  DONUT = 1,
  CLOVER = 2,
  EIGHT = 3,
  NUM_TYPE = 4,
};

struct graph_t * world_init(int m, enum type_world t);
