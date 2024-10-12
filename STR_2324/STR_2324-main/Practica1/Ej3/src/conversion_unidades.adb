package body Conversion_Unidades is

   function To_Millas(kilometros: Float) return Float is
   begin
      return kilometros/1.60934;
   end To_Millas;

   function To_Kilometros(millas: Float) return Float is
   begin
      return millas*1.60934;
   end To_Kilometros;

   function To_Fahrenheit(celsius: Float) return Float is
   begin
      return celsius * 9.0/5.0 + 32.0;
   end To_Fahrenheit;

   function To_celsius(Fahrenheit: Float) return Float is
   begin
      return (Fahrenheit - 32.0)*5.0/9.0;
   end To_celsius;

   function To_Grados(radianes: Float) return Float is
   begin
      return radianes*180.0/3.14;
   end To_Grados;
   function To_Radianes(grados: Float) return Float is
   begin
      return grados * 3.14/180.0;
   end To_Radianes;
end Conversion_Unidades;
