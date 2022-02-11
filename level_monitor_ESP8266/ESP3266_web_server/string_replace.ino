// Función para reemplazar un string //
/*Esta función tiene tres parametros:
    -source
      Es el string en el se encuentra el contenido a reemplazar.

    -substring
      Es lo que se desea reemplazar.

    -with
      Es con lo que se quiere reemplazar
*/

void string_replace(char* source, char* substring, char* with){
  char* substring_source = strstr(source,substring);
  
  if(substring_source == NULL){
    return;
  }

  memmove(

    substring_source + strlen(with),
    substring_source + strlen(substring),
    strlen(substring_source) - strlen(substring) + 1
    
  );

  memcpy(substring_source, with, strlen(with));
  
}
