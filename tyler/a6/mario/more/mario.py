from cs50 import get_int

def make_pyramid(h,i):
    if i == 1:
        print(" "*(h-i)+"# #")
    else:
        make_pyramid(h,i-1)
        print(" "*(h-i)+"#"*i+" "+"#"*i)

h = get_int("Height: \n")
make_pyramid(h,h)
