with ada.Text_IO; use ada.Text_IO;
with ada.Float_Text_IO; use ada.Float_Text_IO;
with ada.Numerics.Elementary_Functions;
with Conversion_Unidades; use Conversion_Unidades;

procedure Main is
   k, m, c, f, r, g : float;
begin
   Put("K: "); Get(k);
   k := To_Millas(k);
   Put("Conv a millas: "); Put(k,exp=>0);
   Put("M: "); Get(m);
   m := To_Kilometros(m);
   Put("Conv a kilometros: "); Put(m,exp=>0);
   Put("C: "); Get(c);
   c := To_Fahrenheit(c);
   Put("Conv Fahrenheit: "); Put(c,exp=>0);
   Put("F: "); Get(f);
   f := To_celsius(f);
   Put("Conv a celsius: "); Put(f,exp=>0);
   Put("R: "); Get(r);
   r := To_grados(r);
   Put("Conv a grados: "); Put(r,exp=>0);
   Put("G: "); Get(g);
   g := To_Radianes(g);
   Put("Conv a radianes: "); Put(g,exp=>0);
end Main;
