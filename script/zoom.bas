rem Zoom to object

@title Zoom and Shoot
@param a Shoot count
@default a 8
@param b Zoom step
@default b 1

if a<1 then let a=8
if b<1 then let b=1

sleep 500
for s=1 to a
    print "Shooting at", s; "..."
    shoot
    for n=1 to b
        print "Zooming-in ", n; "..."
        click "zoom_in"
    next n
next s

sleep 500
for s=1 to a*b
    print "Zooming-out ", s; "..."
    click "zoom_out"
    sleep 300
next s

end
