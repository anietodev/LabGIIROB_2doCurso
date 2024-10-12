with ada.Text_IO; use ada.Text_IO;
with ada.Integer_Text_IO; use ada.Integer_Text_IO;
with ada.Numerics.Elementary_Functions; use ada.Numerics.Elementary_Functions;

procedure Main is
   a,b : integer;
begin
   get(a);
   get(b);
   if a>0 and b>0 then
      loop
         if a = b then
            Put_Line("MCD: " & a'Image);
            exit;
         elsif a < b then
            b := b - a;
         else
            a := a - b;
         end if;
      end loop;
   else
      put_line("Numero/s invalidos");
   end if;
end Main;
