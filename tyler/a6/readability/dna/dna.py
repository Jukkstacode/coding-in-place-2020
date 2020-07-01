from sys import exit, argv

if not len(argv) == 3:
    print("usage: dna.py [STR_counts.csv] [DNA_sequence.csv]")
    exit(1)

with open(argv[1],'r') as f:
    counts=[x.strip("\n").split(",") for x in f.readlines()]
    
people={}
STRs = counts[0][1:]
for row in counts[1:]:
    people["_".join(row[1:])]=row[0]

with open(argv[2],'r') as f:
    sequence = f.readlines()
    
sequence_label = "_".join([str(len(sequence[0].split(x))-1) for x in STRs])

print(people.get(sequence_label,"No match"))
