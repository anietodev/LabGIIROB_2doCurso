with Text_IO; use Text_IO;
with ada.Integer_Text_IO; use ada.Integer_Text_IO;
with ada.Float_Text_IO; use ada.Float_Text_IO;
with ada.Calendar; use ada.Calendar;
with pila_simple;

procedure Main is
   subtype float2 is float digits 2;
   procedure Put_float (f : Float2) is
   begin
      Put (f);
   end Put_float;
   procedure Put_integer (i : integer) is
   begin
      Put (i);
   end Put_integer;
   procedure Put_duration (d : duration) is
   begin
      Put (d'image);
   end Put_duration;

   package pila_floats is new pila_simple (2,float2, Put_float);
   use pila_floats;
   package pila_integer is new pila_simple (2,integer, Put_integer);
   use pila_integer;
   package pila_duration is new pila_simple (2000,Duration, Put_duration);
   use pila_duration;

   Pi : pila_integer.pila;
   Pf : pila_floats.pila;
   Pd : pila_duration.pila;
   a,j : float2;
   i,opcion1,opcion2,x : Integer;
   ti, tf : time;
   t, med : duration;
begin
   for k in 1..2000 loop
      ti := clock;
      delay 0.01;
      tf := clock;
      Push(Pd, tf - ti);
   end loop;
   Listar(Pd);
   med := 0.0;
   for k in 1..2000 loop
      Pop(Pd,t);
      med := med + (t/2000);
   end loop;
   Put("Media: ");
   Put(med'image);
   New_Line;
   loop
      Put_Line("Introduce operacion a realizar (Exit(0),Inicializar(1),Push(2),Pop(3),Listar(4)): ");
      Get(opcion1);
      case opcion1 is
         when 0      => exit;
         when 1      =>
            Put_Line("Elige pila donde realizar la operacion (Pila_integer(0), Pila_float(1)): ");
            get(opcion2);
            if opcion2 = 0 then
               Inicializar (Pi);
               Put_line("Pila de integers inicializada");
            elsif opcion2 = 1 then
               Inicializar (Pf);
               Put_line("Pila de floats inicializada");
            else
               Put_line("Opcion no valida");
            end if;
         when 2      =>
            Put_Line("Elige pila donde realizar la operacion (Pila_integer(0), Pila_float(1)): ");
            get(opcion2);
            if opcion2 = 0 then
               Put("Introduce un integer: ");
               Get(x);
               Push(Pi,x);
            elsif opcion2 = 1 then
               Put("Introduce un float: ");
               Get(a);
               Push(Pf,a);
            else
               Put_line("Opcion no valida");
            end if;
         when 3      =>
            Put_Line("Elige pila donde realizar la operacion (Pila_integer(0), Pila_float(1)): ");
            get(opcion2);
            if opcion2 = 0 then
               Pop(Pi,i);
               Put_Line("Elemento sacado: " & i'image);
            elsif opcion2 = 1 then
               Pop(Pf,j);
               Put_Line("Elemento sacado: " & j'image);
            else
               Put_line("Opcion no valida");
            end if;
         when 4      =>
            Put_Line("Elige pila donde realizar la operacion (Pila_integer(0), Pila_float(1)): ");
            get(opcion2);
            if opcion2 = 0 then
               Listar(Pi);
            elsif opcion2 = 1 then
               Listar(Pf);
            else
               Put_line("Opcion no valida");
            end if;
         when others => null;
      end case;
   end loop;

end Main;
