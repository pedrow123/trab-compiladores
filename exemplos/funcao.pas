program funcao (input, output);
var x,y,z: integer;
function plus (a,b: integer; var c: integer): integer;
begin
    plus := a + b
end;
begin
    read(x);
    read(y);
    z := plus(x,y,z);
    write(z)
end.