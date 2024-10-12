with ada.Text_IO; use ada.Text_IO;

package body pilas is
   function Vacia (C : in pila) return Boolean is
   begin
      return C.contador = 0;
   end Vacia;
   function Llena (C : in pila) return Boolean is
   begin
      return C.contador = N;
   end Llena;
   procedure Inicializar (C : in out pila) is
   begin
      C.cima := 0;
      C.Contador := 0;
   end Inicializar;
   procedure Push (C : in out pila; I : in Integer) is
   begin
      if Llena (C) then
         Put_line ("Pila llena");
      else
         C.v (C.cima) := I;
         C.cima            := C.cima + 1;
         C.Contador           := C.Contador + 1;
      end if;
   end Push;
   procedure Pop (C : in out pila; I : out Integer) is
   begin
      if Vacia (C) then
         Put_line ("Pila vacia");
      else
         I          := C.v (C.cima-1);
         C.cima   := C.cima - 1;
         C.Contador := C.Contador - 1;
      end if;
   end Pop;
   procedure Listar (C : in out pila) is
      i : Integer;
   begin
      Put_line ("Elementos de la pila: " & c.Contador'Image);
      i := 0;
      if(vacia(C) = False) then
         loop
            Put (C.v (i)'Image & " - ");
            i := i + 1;
            exit when i = c.contador;
         end loop;
      end if;
      New_line;
   end Listar;
end pilas;
