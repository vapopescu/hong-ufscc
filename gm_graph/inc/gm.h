#ifndef GM_H_
#define GM_H_

#define _CRT_SECURE_NO_DEPRECATE
#include <math.h>
#include <stdlib.h>
#include <cstddef>

//------------------------------------------------------------
// This is the root header for external applications.
// This header includes all the 'modules' in gm_graph lib
//------------------------------------------------------------
#include "gm_internal.h"

#include "gm_graph_typedef.h"
#include "gm_graph.h"
#include "gm_runtime.h"
#include "gm_atomic_wrapper.h"
#include "gm_atomic_operations.h"
#include "gm_lock.h"
#include "gm_bitmap.h"
#include "gm_mem_helper.h"

#include "gm_bfs_template.h"
#include "gm_dfs_template.h"

#include "gm_set.h"
#include "gm_seq.h"
#include "gm_order.h"
#include "gm_collection.h"
#include "gm_map.h"

#endif  // GM_H_
