generic
   N : integer;
   type item is private;
   with procedure Put(x: item);
package Colas is
   
   type Cola_circular is limited private;
   function Vacia(C : in Cola_Circular) return Boolean;
   function Llena(C : in Cola_Circular) return Boolean;
   procedure Inicializar (C : in out Cola_Circular);
   procedure Anyadir( C : in out Cola_Circular; I: in item);
   procedure Sacar (C : in out Cola_Circular; I: out item);
   procedure Listar(C : in out Cola_Circular);
private
   subtype Index is Integer range 1..N;
   type Cola is array (Index) of item;
   type Cola_Circular is
      record
         Vector: Cola;
         Entrada: Integer := 1;
         Salida: Integer := 1;
         Contador: Integer :=0;
      end record;   
end Colas;
