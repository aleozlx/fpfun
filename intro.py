#!/usr/bin/env python
import itertools

# Start from the simplest: constant functions
#  - they are constants as functions and lazy-evaluations as data structure, depending on perspective of view
zero = lambda: 0
one = lambda: 1

# Higher order functions: operations that take functions and return another function
#  - all they do is to return a function (which is a constant!)
#    and nothing serious would ever happen
add = lambda a, b: lambda: a()+b()
mul = lambda a, b: lambda: a()*b()
dot = lambda a1, a2, b1, b2: add(mul(a1, a2), mul(b1, b2))

# Higher order function that returns lazy data structures,
#  - which only ever contain another bunch of functions (which are contants!)
dot2 = lambda A, B: lambda: (lambda (a1, a2, a3, a4), (b1, b2, b3, b4): (dot(a1, b1, a2, b3), dot(a1, b2, a2, b4), dot(a3, b1, a4, b3), dot(a3, b2 ,a4, b4)))(A(), B())

# Recursive higher order functions
power = lambda m, n: dot2(power(m, n-1), m) if n>1 else (m if n==1 else lambda: (one, zero, zero, one))

# Do you realize that, to a computer, we did nothing but defining constants so far?
#  - time to borrow some mathematical junk to make this enlightening
magic = lambda: (one, one, one, zero)

# Infinite data structures are possible because of lazy-evaluation
voodoo = (power(magic, n) for n in itertools.count(0))

# All good things must come to an end :(
print [i() for i in (F()[0] for F in itertools.islice(voodoo, 9))]