with ada.Float_Text_IO; use ada.Float_Text_IO;
with ada.Text_IO; use ada.Text_IO;
with ada.Numerics.Elementary_Functions; use ada.Numerics.Elementary_Functions;

procedure Main is
   d,x,y,x1,x2,y1,y2 : float;
begin
   Put_Line("Punto 1 (x1,y1): ");
   get(x1); get(y1);
   Put_Line("Punto 2 (x2, y2): ");
   get(x2); get(y2);
   x := x2 - x1;
   y := y2 - y1;
   d := sqrt(x*x + y*y);
   put("Distancia: ");
   put(d,exp=>0); -- Para que no lo imprima en notacion cientifica
   new_line;
end Main;

