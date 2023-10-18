gcc ../2-3.c -o ./2-3r
for VAR in {1..10}; do
    ./2-3r <$VAR.in >$VAR.out
done