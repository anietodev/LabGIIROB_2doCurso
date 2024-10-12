with Colas;
with Ada.Float_Text_IO; use Ada.Float_Text_IO;
with ada.Text_IO; use ada.Text_IO;
with ada.Integer_Text_IO; use ada.Integer_Text_IO;

procedure Main is
   subtype float2 is float digits 2;
   a : float2;
   opcion : integer;
   procedure Put_float (f : Float2) is
   begin
      Put (f);
   end Put_float;
   package cola_floats is new colas (10,float2, Put_float);
   use cola_floats;
   C : Cola_circular;
begin
   loop
      Put_Line("Introduce operacion a realizar (Exit(0),Inicializar(1),Push(2),Pop(3),Listar(4)): ");
      Get(opcion);
      case opcion is
         when 0      => exit;
         when 1      => Inicializar (C);
                        Put_line("Cola inicializada");
         when 2      => Put("Introduce elemento: ");
                        Get(a);
                        Anyadir(C,a);
         when 3      => Sacar(C,a);
                        Put_Line("Elemento sacado: " & a'image);
         when 4      => Listar(C);
         when others => null;
      end case;
   end loop;
end Main;
