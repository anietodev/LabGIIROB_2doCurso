package pilas is
   N : constant Integer := 4;
   subtype Index is Integer range 0 .. N - 1;
   type vector is array (Index) of Integer;
   type pila is record
      v : vector;
      Cima : integer := 0;
      Contador : Integer := 0;
   end record;
   function Vacia (C : in pila) return Boolean;
   function Llena (C : in pila) return Boolean;
   procedure Inicializar (C : in out pila);
   procedure Push (C : in out pila; I : in Integer);
   procedure Pop (C : in out pila; I : out Integer);
   procedure Listar (C : in out pila);
end pilas;
