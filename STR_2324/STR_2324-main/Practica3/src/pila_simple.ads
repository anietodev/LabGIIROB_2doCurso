generic
   N : integer;
   type item is private;
   with procedure Put(x: item);

package pila_simple is
   type pila is private;
   function Vacia (C : in pila) return Boolean;
   function Llena (C : in pila) return Boolean;
   procedure Inicializar (C : in out pila);
   procedure Push (C : in out pila; I : in Item);
   procedure Pop (C : in out pila; I : out item);
   procedure Listar (C : in out pila);
private
   --N : constant Integer := 4;
   subtype Index is Integer range 0 .. N - 1;
   type vector is array (Index) of item;
   type pila is record
      v : vector;
      Cima : integer := 0;
      Contador : Integer := 0;
   end record;
end pila_simple;
