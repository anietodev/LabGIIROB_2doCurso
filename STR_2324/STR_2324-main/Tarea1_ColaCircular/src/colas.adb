with ada.Text_IO; use ada.Text_IO;

package body Colas is
   function Vacia (C : in Cola_Circular) return Boolean is
   begin
      return C.Contador = 0;
   end Vacia;
   function Llena (C : in Cola_Circular) return Boolean is
   begin
      return C.Contador = N;
   end Llena;
   procedure Inicializar (C : in out Cola_Circular) is
   begin
      C.Entrada  := 1;
      C.Salida   := 1;
      C.Contador := 0;
   end Inicializar;
   procedure Anyadir (C : in out Cola_Circular; I : in item) is
   begin
      if Llena (C) then
         Put_line ("Cola llena");
      else
         C.Vector (C.Entrada) := I;
         C.Entrada            := (C.Entrada + 1) mod (N + 1);
         if C.entrada = 0 then
            C.entrada := 1;
         end if;
         C.Contador           := C.Contador + 1;
      end if;
   end Anyadir;
   procedure Sacar (C : in out Cola_Circular; I : out Item) is
   begin
      if Vacia (C) then
         Put_line ("Cola vacia");
      else
         I          := C.Vector (C.Salida);
         C.Salida   := (C.Salida + 1) mod (N+1);
         if C.salida = 0 then
            C.salida := 1;
         end if;
         C.Contador := C.Contador - 1;
      end if;
   end Sacar;
   procedure Listar (C : in out Cola_Circular) is
      i : Integer;
   begin
      Put_line ("Elementos de la cola: " & c.Contador'Image);
      i := C.Salida;
      loop
         Put (C.Vector (i));
         Put (" - ");
         i := (i + 1) mod (N+1);
         if i = 0 then
            i := 1;
         end if;
         exit when i = C.Entrada;
      end loop;
      New_line;
   end Listar;

end Colas;
