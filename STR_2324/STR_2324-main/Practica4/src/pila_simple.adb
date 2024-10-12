with Ada.Text_IO;       use Ada.Text_IO;
with Ada.Float_Text_IO; use Ada.Float_Text_IO;

package body pila_simple is
   function Vacia (C : in pila) return Boolean is
   begin
      return C.Contador = 0;
   end Vacia;
   function Llena (C : in pila) return Boolean is
   begin
      return C.Contador = N;
   end Llena;
   procedure Inicializar (C : in out pila) is
   begin
      C.Cima     := 0;
      C.Contador := 0;
   end Inicializar;
   procedure Push (C : in out pila; I : in item) is
   begin
      if Llena (C) then
         raise cola_llena;
         --Put_line ("Pila llena");
      else
         C.v (C.Cima) := I;
         C.Cima       := C.Cima + 1;
         C.Contador   := C.Contador + 1;
      end if;
   exception
      when cola_llena =>
         Put_Line ("La cola esta llena");
      when others =>
         null;
   end Push;
   procedure Pop (C : in out pila; I : out item) is
   begin
      if Vacia (C) then
         --Put_Line ("Pila vacia");
         raise cola_vacia;
      else
         I          := C.v (C.Cima - 1);
         C.Cima     := C.Cima - 1;
         C.Contador := C.Contador - 1;
      end if;
      exception
      when cola_vacia =>
         Put_Line ("La cola esta vacia");
      when others =>
         null;
   end Pop;
   procedure Listar (C : in out pila) is
      i : Integer;
   begin
      Put_Line ("Elementos de la pila: " & C.Contador'Image);
      i := 0;
      if (Vacia (C) = False) then
         loop
            Put (C.v (i));
            Put (" - ");
            i := i + 1;
            exit when i = C.Contador;
         end loop;
      end if;
      New_Line;
   end Listar;
end pila_simple;
