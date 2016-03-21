#pragma once
#pragma once

/*     think-cell ranges library   */

// this macro is required for the missing assert_fwd.h header
#define RANGE_PROPOSAL_BUILD_STANDALONE

// cont_append algorithm needs definition for this
// for now, simply executing the statement is good enough for me
#define NOEXCEPT(...) __VA_ARGS__
#define NOBADALLOC(...) __VA_ARGS__

// had to make one modification in the range library
// commented out #include "Library/Utilities/SetAndRestore.h"
// in algorithm.h file, as the header is not available
#include <Library/Utilities/Range.h>
