from cs50 import get_int
from math import log10

def luhn(n):
    odd = [ y if y < 10 else (y % 10) +1 for y in [(n // 10**x % 10)*2 for x in range(int(log10(n))+1) if x%2==1]]
    even = [(n // 10**x % 10) for x in range(int(log10(n))+1) if x%2==0]
    # print(odd, even)
    # print(sum(odd+even))
    return (sum(odd+even) % 10) == 0

n = get_int("Number: \n")
if luhn(n):
    if 4*10**12 <= n < 5*10**12 or 4*10**15 <= n < 5*10**15:
        print("VISA")
    elif 34*10**13 <= n < 35*10**13 or 37*10**13 <= n < 38*10**13:
        print("AMEX")
    elif 51*10**14 <= n < 56*10**14:
        print("MASTERCARD")
    else:
        print("INVALID")
else:
    print("INVALID")
        