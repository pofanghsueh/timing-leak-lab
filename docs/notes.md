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