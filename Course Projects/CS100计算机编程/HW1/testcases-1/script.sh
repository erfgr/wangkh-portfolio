gcc ../1-1_reference.c -o ./1-1r
for VAR in {1..10}; do
    ./1-1r <$VAR.in >$VAR.out
done