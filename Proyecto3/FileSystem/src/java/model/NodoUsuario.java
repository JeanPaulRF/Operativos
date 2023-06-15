
/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package model;

/**
 *
 * @author david
 */
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class NodoUsuario extends Nodo{
    public List<NodoCarpeta> Carpetas;
    public List<NodoArchivo> Archivos;
    public String password;
    
    public NodoUsuario(String user, String clave){
        super(user, "Usuario");
        
        this.password = clave;
        this.Carpetas = new ArrayList<>();
        this.Archivos = new ArrayList<>();
        this.Carpetas.add(new NodoCarpeta("Compartido"));
    }
    
    public NodoArchivo buscarArchivo(String path){
        // Aqui podemos buscar primero en los archivos sueltos, si el path no tiene /
        // luego aplicamos el desglose.
        NodoArchivo archivoError = new NodoArchivo("No existe, error 101");
        
        // Primero partimos el path
        String[] partes = path.split("/");
        
        if (partes.length == 1){
            //indica que busca un archivo suelto
            for (NodoArchivo archivo : Archivos) {
                if (archivo.getNombre().equals(partes[0])) {
                    return archivo;
                }
            }
            System.out.println("Error el archivo no existe.");
            return archivoError; // En caso de que no exista
        }
        else if(partes.length > 1){
            // Si es mayor que 1, la primera parte es la primera carpeta
            for (NodoCarpeta carpeta :Carpetas){
                if (carpeta.getNombre().equals(partes[0])) {
                    // si encuentra una coincidencia, busca en la carpeta
                    String newpath = String.join("/", Arrays.copyOfRange(partes, 1, partes.length));
                    return carpeta.buscarArchivo(newpath);
                }
            }
            // no lo encontro
            System.out.println("Error en el path. La carpeta no existe en el usuario");
            return archivoError;
        }
        else{
            System.out.println("Error en el path.");
            return archivoError;
        }
    }
    
    public void agregarCarpeta(NodoCarpeta newCarpeta) {
        Carpetas.add(newCarpeta);
    }
    
    public String getPassword() {
        return password;
    }
    
    public void setPassword(String newPass){
        this.password = newPass;
    }

    public List<NodoCarpeta> getCarpetas() {
        return Carpetas;
    }

    public List<NodoArchivo> getArchivos() {
        return Archivos;
    }
    
    
}
