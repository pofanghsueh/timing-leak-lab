# AI usage log

- 2026-09-30: Used Claude for project planning and repository setup guidance.
- 2026-10-01: Claude provided compare.h, the task spec, and a test skeleton. I wrote compare.c and the test cases. Claude's review caught three mistakes of mine (passing a scalar instead of an array, a wrong expected value, and `=` instead of `|=`), which I fixed.
- 2026-10-01: Week 1, comparison functions
  - Provided by Claude: `compare.h`, the task specification, and skeletons for `compare.c` and `test_compare.c` (function signatures, loop structure, TODO comments, and the first test case).
  - Written by me: the function bodies in `compare.c` (filling in the TODOs) and the remaining test cases.
  - Review: Claude reviewed my code and pointed out three mistakes: passing a scalar instead of an array in the tests, a wrong expected value in one assertion, and using `=` instead of `|=` when accumulating differences. I fixed all three and re-ran the tests.
  - Second review: Claude found no logic errors in the final `compare.c` and suggested cleanup and additional tests.
