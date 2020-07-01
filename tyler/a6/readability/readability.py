from cs50 import get_string

s = get_string("Text: ")
letters   = sum(c.isalpha() for c in s)
words  = (sum(c.isspace() for c in s)+1)/100
sentances = s.count(".")+s.count("!")+s.count("?")
CL = 0.0588 * letters/words - 0.296 * sentances/words - 15.8
# print(CL)
if CL >= 16:
    print("Grade 16+")
elif CL < 1:
    print("Before Grade 1")
else:
    print(f"Grage {int(round(CL,0))}")