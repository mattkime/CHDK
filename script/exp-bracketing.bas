@title EXP bracketing 
@param a Number of ñsteps 
@default a 2
@param b Step size (1/3EV)
@default b 3

if a<1 then let a=2
if b<1 then let b=3

sleep 1000

click "erase"
for n=1 to a*b
    click "left"
next n

for s=1 to a*2
    shoot
    for n=1 to b
        click "right"
    next n
next s

shoot

for n=1 to a*b
    click "left"
next n

click "erase"

end
