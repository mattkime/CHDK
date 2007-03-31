rem Interval shooting

@title Interval shooting
@param a Shoot count
@default a 10
@param b Interval (Minutes)
@default b 0
@param c Interval (Seconds)
@default c 10

t=b*60000+c*1000
if a<2 then let a=10
if t<1000 then let t=1000

sleep 1000
shoot
for n=2 to a
    sleep t
    shoot
next n

end
