# Design notes: timing benchmark

Status: draft, written before implementing `bench.c`. The predictions below are hypotheses to be tested, not results.

## 1. What am I measuring, and in what unit?

I measure how long one call to a comparison function takes, and I report it in nanoseconds and in CPU cycles. The exact values are unknown and will be determined by experiment. The conversion between the two is not a fixed constant, so it must be measured separately on each platform (desktop and development board).

If the timer's resolution is coarser than a single call, every input will look identical. To avoid this, I will:

- measure the timer's resolution with a small program first;
- use batch timing: each sample times B consecutive calls to the same function on the same input class, and the total is divided by B. B is chosen so that one batch is well above the measured timer resolution;
- keep all calls in one batch on the same input class, because a mixed batch would average the two classes together and hide the difference I want to measure;
- store each call's return value in a `volatile` variable, so the compiler cannot remove the call as dead code;
- run warm-up calls before measuring, and avoid other sources of random interference, such as cache effects.

Increasing the byte length n is a separate tool. It enlarges the early-exit difference and lets me study how time grows with n, but it does not fix the timer-resolution problem.

## 2. Why two input classes (first byte differs vs. last byte differs)?

For the early-exit function, a first-byte mismatch causes the least work and a last-byte mismatch causes the most. I choose these two extremes because if two classes are close together, the difference is hard to detect and other sources of variation are amplified.

There is no fixed conversion between cycles and nanoseconds that holds on both platforms, so I will measure each platform separately and compare the shape of the results rather than the raw numbers.

To estimate the time per additional byte, I will compute (T_late - T_early) / (n - 1). I will also measure several values of n and fit a linear regression.

## 3. What do I expect to see? (hypotheses)

Let c_e be the time per byte of the early-exit function and c_t the time per byte of the constant-time function.

- Early-exit: the difference between the two classes should be about c_e * (n - 1). More generally, if the function exits at position k, the time should be about c_e * k.
- Constant-time: both classes should cost about c_t * n, so the expected difference is c_t * n - c_t * n = 0.
- Branch prediction: in both classes the loop exits through a mispredicted branch once, so I expect the misprediction penalty to cancel out in the difference. With randomly interleaved inputs, I expect the processor to keep its default prediction. This is a hypothesis; any extra effect has to be estimated experimentally.
- Compiler: optimization may rewrite my code, so I will inspect the compiler's assembly output instead of reasoning only from the source.

## 4. How will I know if the measurement is unreliable?

Warning signs: values that vary a lot between runs, large scatter, and extreme outliers.

What I will do about it:

- repeat the measurements and use different values of n;
- watch CPU load and power state while measuring;
- later, port the experiment to the development board, which has fewer sources of interference than a desktop operating system;
- if the early-exit function shows no difference, increase n to amplify the effect (this applies to the early-exit function only).

Limits of the constant-time result: if I find no difference, that does not prove there is no leakage. It only shows that no timing leakage was observed in this experiment, within its sensitivity (which depends on the sample size and the noise level).

A/A test: I will split the measurements of a single input class randomly into two halves. Their difference should be small. As a provisional criterion I will require it to be under 1%. If a consistent offset persists (rather than random scatter), there is a systematic effect that needs investigation.

## Predictions before running the timer program
- Smallest non-zero difference between two timer readings: I predict about 1 ns 1ns, which needs further experiments  
- Typical difference between two back-to-back timer calls: I predict its most differences will be 0 or 1 ns, which needs further experiments
- Why I think so: while timing on development board is counted by cpu cycles , counting on my cpu isn't. The most common unit near a cpu cycle is nanosecond, however there might be differences between the return value's unit and the actual update interval of the timer, requiring further testing. And the time cost between two timer calls depends on how much work one timer call does and the clock rate, which I predict under 3 cpu cycles.
## Predictions for the 1,000,000-sample run
- Which distinct values will appear, and which will be most common: In 1,000,000 samples , I predict that the numbers which appears are 0 , 1000 ,the most common number appearing should be 0 .
- Roughly what fraction of the deltas will be non-zero: I predict that the fraction of non-zero number will be 0.3% . The first non-zero number should appear at approximately the 3000th sample.
- Why: while not knowing the cpu clock rate of my computer and how many cpu cycles the program takes I optimisticly assume that the cpu clock rate at 3GHz and assume the program takes 1 cpu cycle while running the program . Meaning it takes about 3000 cpu cycles to jump from 0 to 1000ns , however ,leading to the perdiction of a 99.7% of 0 in the resulat