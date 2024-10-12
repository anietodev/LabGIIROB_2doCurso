with Text_IO; use Text_IO;
procedure Main is
   procedure operacion (X : in Integer; Y : in out Integer; Z : out Integer);
   procedure operacion (X : in Integer; Y : in out Integer; Z : out Integer) is
   begin
      Z := X;
   end operacion;

   I : Integer  := 100;
   J : Integer;
   Z : Float    := 10.50;
   K : constant := 100;
begin
   for I in 1 .. 4 loop
      put(I'image);
   end loop;
   --operacion(I, J, K);
   --operacion (3, Z, J);
--operacion(K, I, J);
--operacion(J, I, 3);
--operacion(I+I, I, J);
--operacion(J, J, J);
--operacion(I, I+J, J);
   null;
end Main;
