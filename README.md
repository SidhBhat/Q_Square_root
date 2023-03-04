# Introduction

The fast inverse square root alogorithim to compute the inverse sqaure root `1\sqrt(x)` of a number
`x`. This algorithm was first used in the 1999 first person shooter [Quake-III-Arena](https://github.com/id-Software/Quake-III-Arena/)[^1]
You can find the original [here](https://github.com/id-Software/Quake-III-Arena/blob/master/code/game/q_math.c)
near line 552.

## The Quake Alogorithm

We will not go in depth of how this algorithm works here, but basically we attempt inteprete a floating
point number `x` as a integer in orger to approximate $log_2(x)$.

```math
log_2(x) \approx \ e_x + m_x + \sigma
```

where

```math
\begin{aligned}
e_x & = \text{exponent} \\
m_x & = \text{mantissa} \\
\sigma & = \text{correction factor}\\
\end{aligned}
```

And when we interprete it as an integer:

```math
I_x = E_x L + M_x
```

where

```math
\begin{aligned}
I_x & = \text{integer representation of x} \\
M_x & = m_x L = \text{manttisa as an integer} \\
E_x & = e_x + B = \text{integral part of exponent} \\
B & = \text{exponent Bias} \\
L & = 2^{\text{number of bits in mantissa}}\\
\end{aligned}
```

By substituting $e_x$ above, we can come  up with:

```math
log_2(x) \approx \frac{I_x}{L} - (B - \sigma)
```

We take $y = \frac{1}{\sqrt{x}}$ which gives $log_2(y) = - \frac{1}{2} log_2(x)$
When we apply this to the approximation above we get:

```math
I_y \approx \frac{3}{2} L (B - \sigma) - \frac{1}{2} I_x
```

And this is the principal behind the quake algorithm. $\frac{3}{2} L (B - \sigma)$ is the "magic constant".
In code this correspnods to:

```c
	i  = 0x5f3759df - ( i >> 1 );       // what the fuck?
```

## Q_Square_root

Here I attempt to Calculate the magic number automatically for certain floating point types at compile time
using c++ templates and `constexpr` context. This is the only idea behind this repo.

In *Quake.hpp*:

```cpp
constexpr static typename int_type<_T>::type magic_constant(void);
```

## Building and testing

Along with giving a template implementation of the fast inverse sqare root, I have created a `main.cpp` to
test the function. We test the code on both [IEC 559](https://en.wikipedia.org/wiki/IEEE_754) single and
double precision. To build the test executable:

```bash
make
./build/quaketest 4.0
```
The syntax for `quaktest` is:

```
quaketest [option] <number>
```

The available options are `-d` for double precision and `-f` for single precision.


[^1]: [Wikipedia](https://en.wikipedia.org/wiki/Fast_inverse_square_root)
