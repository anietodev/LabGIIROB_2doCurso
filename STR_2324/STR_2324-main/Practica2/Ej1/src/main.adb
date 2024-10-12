with Text_IO; use Text_IO;
with ada.Integer_Text_IO; use ada.Integer_Text_IO;
with pilas; use pilas;

procedure Main is
   C : pila;
   i,opcion,x : Integer;
begin

   loop
      Put_Line("Introduce operacion a realizar (Exit(0),Inicializar(1),Push(2),Pop(3),Listar(4)): ");
      Get(opcion);
      case opcion is
         when 0      => exit;
         when 1      => Inicializar (C);
                        Put_line("Pila inicializada");
         when 2      => Put("Introduce elemento: ");
                        Get(x);
                        Push(C,x);
         when 3      => Pop(C,i);
                        Put_Line("Elemento sacado: " & i'image);
         when 4      => Listar(C);
         when others => null;
      end case;
   end loop;
   --Push (C, 3);
   --Push (C, 5);
   --Push (C, -1);
   --Listar (C);
   --Pop (C, i);
   --Put_Line("Elemento sacado: " & i'image);
   --Listar (C);
end Main;
