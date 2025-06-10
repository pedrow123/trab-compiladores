program passagemReferencia (input, output);
var 
    r, x, y: integer;

procedure maior(a, b: integer; var c: integer);
begin
    if a > b then
    begin
        c := a;
        if c <= 10 then
            a := 15
        else
            a := 0
    end
    else
        c := b
end;

begin
    x := 10;
    y := 20;
    maior(x,y,r)
end.
